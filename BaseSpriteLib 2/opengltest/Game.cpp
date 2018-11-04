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
	score = 0;
	isShipCollide = false;

	srand(time(NULL));
	////Initalize Space Ship
	spaceShip = new SpaceShip("images/SpaceShip.png");
	spaceShip->setNumberOfAnimations(1);
	spaceShip->setSpriteFrameSize(21, 31);
	spaceShip->addSpriteAnimFrame(0, 0, 0);
	spaceShip->setPosition(Vector3(900, 450, 0));
	spaceShip->setCenterForRotation(21 / 2, 31 / 2); // center of the sprites origin for rotation
	spaceShip->setRadius();
	spaceShip->setLayerID(3);
	this->addSpriteToDrawList(spaceShip); //Add to drawing list

	//Initalize Default bullet
	defaultBullet = new Bullet("images/Bullet.png");
	defaultBullet->setNumberOfAnimations(1);
	defaultBullet->setSpriteFrameSize(4, 4);
	defaultBullet->addSpriteAnimFrame(0, 0, 0);
	defaultBullet->setPosition(Vector3(100, 100, 0));
	defaultBullet->setCenterForRotation(4 / 2, 4 / 2); // center of the sprites origin for rotation
	defaultBullet->updateCenterPoint();
	defaultBullet->setRadius();
	defaultBullet->setLayerID(3);
	//this->addSpriteToDrawList(defaultBullet);

	defaultSmallAsteroid = new Asteroid("images/SmallAsteroid.png");
	defaultSmallAsteroid->setNumberOfAnimations(1);
	defaultSmallAsteroid->setSpriteFrameSize(50, 50);
	defaultSmallAsteroid->addSpriteAnimFrame(0, 0, 0);
	defaultSmallAsteroid->setPosition(Vector3(1200, 425, 0));
	defaultSmallAsteroid->setCenterForRotation(50 / 2, 50 / 2); // center of the sprites origin for rotation
	defaultSmallAsteroid->updateCenterPoint();
	defaultSmallAsteroid->setRadius(22);
	defaultSmallAsteroid->setLayerID(3);

	//this->addSpriteToDrawList(defaultSmallAsteroid);

	defaultLargeAsteroid = new Asteroid("images/BigAsteroid.png");
	defaultLargeAsteroid->setNumberOfAnimations(1);
	defaultLargeAsteroid->setSpriteFrameSize(101, 101);
	defaultLargeAsteroid->addSpriteAnimFrame(0, 0, 0);
	defaultLargeAsteroid->setPosition(Vector3(1000, 450, 0));
	defaultLargeAsteroid->setCenterForRotation(101 / 2, 101 / 2); // center of the sprites origin for rotation
	defaultLargeAsteroid->setRadius(47);
	defaultLargeAsteroid->setLayerID(3);
	//this->addSpriteToDrawList(defaultLargeAsteroid); //Add to drawing list


	///* load the background */
	bg = new HorizontalScrollingBackground("images/Black Background.png", stateInfo.windowWidth, stateInfo.windowHeight);
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
	glViewport(0, 0, stateInfo.windowWidth, stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red,
		stateInfo.bgClearColor.green,
		stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	setColor(255, 255, 255);
	drawText("Score: " + std::to_string(score), 100, 875);
	drawText("Lives: " + std::to_string(spaceShip->liveCounts), 1700, 875);
	drawText("Shield: " + std::to_string(spaceShip->shieldCounts), 1700, 850);

	if (spaceShip->liveCounts <= 0) {
		drawText("Game Over", 900, 450);
	}
	
	if (isShipCollide) {
		drawCircle(20, spaceShip->radius, spaceShip->centerPoint.x, spaceShip->centerPoint.y);
		isShipCollide = false;
	}
	
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
	for (it = spriteListToDraw.begin(); it != spriteListToDraw.end(); it++)
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
void Game::ProcessKeyInput() {
	const float appliedForce = 200;
	if (input.upKeyArrow) {
		spaceShip->force.set(appliedForce* -sin(spaceShip->getOrientation() / 180 * M_PI),
			appliedForce* cos(spaceShip->getOrientation() / 180 * M_PI), 0);
	}

	if (input.downKeyArrow) {
		spaceShip->force.set(appliedForce * sin(spaceShip->getOrientation() / 180 * M_PI),
			appliedForce*-cos(spaceShip->getOrientation() / 180 * M_PI), 0);
	}
	if (input.leftKeyArrow) {
		spaceShip->addOrientation(10.0f);
	}
	if (input.rightKeyArrow) {
		spaceShip->addOrientation(-10.0f);
	}

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
	float deltaTime = updateTimer->getElapsedTimeSeconds();

	if (smallAsteroidList.size() < 5) {
		SpawnSmallAsteroid();
	}
	if (largeAsteroidList.size() < 2) {
		SpawnLargeAsteroid();
	}


	ProcessKeyInput();
	//Update every object in the game
	spaceShip->update(deltaTime);

	for (int i = 0; i < bulletList.size(); i++) {
		bulletList.at(i)->update(deltaTime);
		if (bulletList.at(i)->GetLifeTime() <= 0) {
			delete bulletList.at(i);
			for (int j = 0; j < spriteListToDraw.size(); j++) {
				if (bulletList.at(i) == spriteListToDraw.at(j))
					spriteListToDraw.erase(spriteListToDraw.begin() + j);
			}
			bulletList.erase(bulletList.begin() + i);
		}
	}
	for (int i = 0; i < smallAsteroidList.size(); i++) {
		smallAsteroidList.at(i)->update(deltaTime);
	}

	for (int i = 0; i < largeAsteroidList.size(); i++) {
		largeAsteroidList.at(i)->update(deltaTime);
	}



	//Check for collision
	for (int j = 0; j < smallAsteroidList.size(); j++) {
		for (int i = 0; i < bulletList.size(); i++) {
			if (smallAsteroidList.at(j)->checkIfCollide(bulletList.at(i))) {
				DeleteSprite(smallAsteroidList.at(j));
				DeleteSprite(bulletList.at(i));
				smallAsteroidList.erase(smallAsteroidList.begin() + j);
				bulletList.erase(bulletList.begin() + i);
				j--; i--;
				score += 10;
				break;
			}
		}
		try {
			if (smallAsteroidList.at(j)->checkIfCollide(spaceShip)) {
				DeleteSprite(smallAsteroidList.at(j));
				smallAsteroidList.erase(smallAsteroidList.begin() + j);
				spaceShip->decreaseShield(1);
				score += 10;
				j--;
				isShipCollide = true;
			}
		}
		catch (...) {
			break;
		}
	}

	for (int i = 0; i < largeAsteroidList.size(); i++) {
		for (int j = 0; j < bulletList.size(); j++) {
			if (largeAsteroidList.at(i)->checkIfCollide(bulletList.at(j))) {
				for (int k = 0; k <= rand() % 4 + 2; k++)
					SpawnSmallAsteroid(largeAsteroidList.at(i)->position);
				DeleteSprite(largeAsteroidList.at(i));
				DeleteSprite(bulletList.at(j));
				largeAsteroidList.erase(largeAsteroidList.begin() + i);
				bulletList.erase(bulletList.begin() + j);
				i--; j--;
				break;
			}
		}
		try {
			if (largeAsteroidList.at(i)->checkIfCollide(spaceShip)) {
				for (int k = 0; k <= rand() % 4 + 2; k++)
					SpawnSmallAsteroid(largeAsteroidList.at(i)->position);
				DeleteSprite(largeAsteroidList.at(i));
				largeAsteroidList.erase(largeAsteroidList.begin() + i);
				spaceShip->decreaseShield(2);
				isShipCollide = true;
				i--;
			}
		}
		catch (...) {
			break;
		}
	}

	

}

/*
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
void Game::addSpriteToDrawList(Sprite *s)
{
	if (s)
	{
		/* push the sprite to the back of the list */
		this->spriteListToDraw.push_back(s);
	}
}

void Game::DeleteSprite(Sprite *spriteToDelete) {
	delete spriteToDelete;
	spriteListToDraw.erase(std::find(spriteListToDraw.begin(), spriteListToDraw.end(), spriteToDelete));
}

/*
	This function spawn small asteroids at random location and set random
	velocity
*/
void Game::SpawnSmallAsteroid() {
	Asteroid *tempAsteroid = new Asteroid(*defaultSmallAsteroid);
	tempAsteroid->position.set(Vector3(rand() % 2000+1900, rand() % 900+800, 0));
	tempAsteroid->velocity.set(Vector3(rand() % 601 + (-300), rand() % 601 + (-300), 0));
	this->addSpriteToDrawList(tempAsteroid);
	smallAsteroidList.push_back(tempAsteroid);
}

/*
	This function spawn small asteroids when large asteroid is destroyed
	@param _position The Vector where the small asteroid whill spawn
*/
void Game::SpawnSmallAsteroid(Vector3 _position) {
	Asteroid *tempAsteroid = new Asteroid(*defaultSmallAsteroid);
	tempAsteroid->position.set(_position);
	tempAsteroid->velocity.set(Vector3(rand() % 601 + (-300), rand() % 601 + (-300), 0));
	this->addSpriteToDrawList(tempAsteroid);
	smallAsteroidList.push_back(tempAsteroid);
}


void Game::SpawnLargeAsteroid() {
	Asteroid *tempAsteroid = new Asteroid(*defaultLargeAsteroid);
	tempAsteroid->position.set(Vector3(rand() % 2000 + 1900, rand() % 900 + 800, 0));
	tempAsteroid->velocity.set(Vector3(rand() % 301 + (-150), rand() % 301 + (-150), 0));
	this->addSpriteToDrawList(tempAsteroid);
	largeAsteroidList.push_back(tempAsteroid);
}

void Game::SpawnBullet() {
	Bullet *newBullet = new Bullet(*defaultBullet);
	newBullet->setPosition(spaceShip->centerPoint);
	newBullet->velocity.set(spaceShip->velocity);
	newBullet->force.set(500 * -sin(spaceShip->getOrientation() / 180 * M_PI),
		500 * cos(spaceShip->getOrientation() / 180 * M_PI), 0);
	this->addSpriteToDrawList(newBullet);
	bulletList.push_back(newBullet);
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
	switch (key)
	{
	case 'r':  // reset position, velocity, and force
		break;
	case 32: // the space bar
		//input.spaceKey = true;

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
	switch (key)
	{
	case 32: // the space bar
		SpawnBullet();
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	case 'w':
		input.upKeyArrow = false;
		spaceShip->force.set(0, 0, 0);
		break;
	case's':
		input.downKeyArrow = false;
		spaceShip->force.set(0, 0, 0);
		break;
	case'a':
		input.leftKeyArrow = false;
		break;
	case'd':
		input.rightKeyArrow = false;
		break;
	}
}