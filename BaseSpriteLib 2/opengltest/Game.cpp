#include "Game.h"
#include "drawPrimitives.h"

/* this is called by std::sort to sort the list based on layerID 
 *  for drawing in the proper order 
 */
bool spriteSortingFunction(Sprite *s1, Sprite *s2)
{
	// return true if s1's layerID is less than s2's layerID
	return (s1->layerID < s2->layerID);
}

/* constructor */
Game::Game(void)
{
	/* green background */
	stateInfo.bgClearColor.red = 1;
	stateInfo.bgClearColor.green = 1;
	stateInfo.bgClearColor.blue = 1;

	/* init state */
	stateInfo.gameState = STATE_GAMEPLAY;
	renderingTimer = new Timer("RENDER");
	updateTimer = new Timer("UPDATE");
}

/* destructor */
Game::~Game(void)
{
	/* deallocate memory and clean up here. if needed */
}

/* 
 * initializeGame()
 * - this function is called in the constructor to initialize everything related
 *   to the game, i..e loading sprites etc.
 * - MUST be called prior to any drawing/updating (you should add in checks to ensure this occurs in the right order)
 */
void Game::initializeGame()
{
	//Initalize Space Ship
	spaceShip = new Sprite("images/redbird.png");
	spaceShip->setNumberOfAnimations(1);
	spaceShip->setSpriteFrameSize(148, 125);
	spaceShip->addSpriteAnimFrame(0, 0, 0);
	spaceShip->setPosition(100, 300);
	spaceShip->setCenter(148 / 2, 125 / 2); // center of the sprites origin for rotation
	spaceShip->setLayerID(3);
	this->addSpriteToDrawList(spaceShip); //Add to drawing list

	

	///* load the background */
	bg = new HorizontalScrollingBackground("images/BG.png",stateInfo.windowWidth,stateInfo.windowHeight);
	this->addSpriteToDrawList(bg);
	bg->setLayerID(0);
}

/* draw()
 * - this gets called automatically about 30 times per second
 * - this function just draws the sprites 
 */
void Game::draw()
{
	/* pre-draw - setup the rendering */
	PreDraw();

	/* draw - actually render to the screen */
	DrawGame();
	
	/* post-draw - after rendering, setup the next frame */
	PostDraw();
}

/*
 * Pre-Draw() is for setting up things that need to happen in order to draw
 *    the game, i.e. sorting, splitting things into appropriate lists etc.
 */
void Game::PreDraw()
{
	/* clear the screen */
	glViewport(0,0,stateInfo.windowWidth,stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red, 
				 stateInfo.bgClearColor.green, 
				 stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // clear out the transformation matrix
	glEnable(GL_TEXTURE_2D); // turn on texturing

	// if we update our timer it will tell us the elapsed time since the previous 
	// frame that we rendered
	renderingTimer->tick();


	/* sort the sprites by layerID so we draw them in the right order */
	std::sort(spriteListToDraw.begin(), spriteListToDraw.end(), spriteSortingFunction);

}

/* 
 * DrawGame()
 *  - this is the actual drawing of the current frame of the game.
 */
void Game::DrawGame()
{
	/* here is where your drawing stuff goes */
	drawSprites();

	glDisable(GL_TEXTURE_2D);
	drawTestPrimitives();  

	/* this makes it actually show up on the screen */
	glutSwapBuffers();
}

/*
 * PostDraw()
 *  - in here you should clean up and set up things for the next frame
 *  - i.e. once I've used my assets, I can change them to set up things for
 *    the next frame, usually just memory management or setting up game state 
 *    boolean values etc.  
 */
void Game::PostDraw()
{
	// nothing here at the moment
}

/* drawSprites()
 * - this function is what actually draws the sprites
 *   onto the screen at their appropriate location
 * - it actually loops through a list of active sprites
 *   and then sorts them by their layerID and then draws them
 * - the sorting has to happen so that you draw from back to front
 *   just like a painter and a canvas.
 */
void Game::drawSprites()
{
	// this just goes through the list of sprites and tells them to draw
	std::vector<Sprite*>::iterator it; 
	for(it=spriteListToDraw.begin(); it != spriteListToDraw.end();it++)
	{
		Sprite *s = (*it);
		s->draw();
	}

}

/* for testing purposes to show you how to use
   the drawing primitives capabilities */
void Game::drawTestPrimitives()
{
	/* draw line */
	if (input.mouseDown)
	{
		setLineWidth(5.f);
		setColor(1, 0, 0);
		drawLine(input.clickX, input.clickY, input.currentX, input.currentY);
		setLineWidth(1.f);
	}
}
/*
*/
void Game::ProcessKeyboardInput(Sprite *sprite) {
	const float appliedForce = 50;
	if (input.upKeyArrow)
		sprite->force.set(appliedForce* sin(sprite->getOrientation() / 180 * M_PI),
			appliedForce* cos(sprite->getOrientation() / 180 * M_PI),0);
	if (input.downKeyArrow)
		sprite->force.set(appliedForce * -sin(sprite->getOrientation() / 180 * M_PI),
			appliedForce*-cos(sprite->getOrientation() / 180 * M_PI), 0);
	if (input.leftKeyArrow)
		sprite->addOrientation(15.0f);
	if (input.rightKeyArrow)
		sprite->addOrientation(-15.0f);
}
/* update()
  - this function is essentially the game loop
    it gets called often and as such you
	don't actually need a "loop" to define the game
	it happens behind the scenes
  - think of this function as one iteration of the game loop
  - if you need to update physics calculations, sprite animation info,
    or sound etc, it goes in here
*/
void Game::update()
{
	// update our clock so we have the delta time since the last update
	updateTimer->tick();
	
	/*Vector3 gravity;
	gravity.set(0, -100, 0);
	spaceShip->addForce(gravity);*/

	ProcessKeyboardInput(spaceShip);
	/* you should probably update all of the sprites in a list just like the drawing */
	/* maybe two lists, one for physics updates and another for sprite animation frame update */
	float deltaTime = updateTimer->getElapsedTimeSeconds();
	spaceShip->update(deltaTime);
}

/* 
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
void Game::addSpriteToDrawList(Sprite *s)
{
	if(s)
	{
		/* push the sprite to the back of the list */
		this->spriteListToDraw.push_back(s);
	}
}


/*************************************************/
/* INPUT - keyboard/mouse functions below        */
/*************************************************/
/* keyboardDown()
   - this gets called when you press a key down
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 'r':  // reset position, velocity, and force
		spaceShip->position.set(100, 100, 0);
		spaceShip->velocity.set(0, 0, 0);
		spaceShip->acceleration.set(0, 0, 0);
		spaceShip->force.set(0, 0, 0);
		break;
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	case 'w':
		input.upKeyArrow = true;
		break;
	case's':
		input.downKeyArrow = true;
		break;
	case'a':
		input.leftKeyArrow = true;
		break;
	case'd':
		input.rightKeyArrow = true;
		break;
	}
}
/* keyboardUp()
   - this gets called when you lift a key up
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	case 'w':
		input.upKeyArrow = false;
		break;
	case's':
		input.downKeyArrow = false;
		break;
	case'a':
		input.leftKeyArrow = false;
		break;
	case'd':
		input.rightKeyArrow = false;
		break;
	}
}

/*
 * mouseClicked
 * - this function is called when the mouse is clicked and it handles the 
 *   input state managment
 */
void Game::mouseClicked(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) 
	{
		input.mouseDown = true;
		input.clickX = x*stateInfo.ratioWidth;
		input.clickY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
		input.button = button;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			
			break;
		case GLUT_RIGHT_BUTTON:
		
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
	}
	else
	{
		/* set force */
		Vector3 f;
		f.set(input.currentX - input.clickX, input.currentY - input.clickY, 0);
		f = f * 20.f;
		spaceShip->addForce(f);
		
		input.mouseDown = false;
	}

}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus 
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
	/* convert from window to screen pixel coordinates */
	input.currentX = x*stateInfo.ratioWidth;
	input.currentY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
	
	if(input.mouseDown)
	{
		if(input.button == GLUT_LEFT_BUTTON)
		{
			// nothing yet
		}
	}
}
