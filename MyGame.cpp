#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), playerRect(100, 100, 50, 50), box1Rect(700, 100, 50, 50), box2Rect(200, 100, 50, 50), platform1Rect(-100, 570, 1000, 30), platform2Rect(-100, 0, 1000, 30), platform3Rect(300, 400, 200, 30), platform4Rect(-100, 200, 300, 30), platform5Rect(600, 200, 300, 30), backgroundTextureRect(), playerTextureRect(), box1TextureRect(), box2TextureRect(), platform1TextureRect(), platform2TextureRect(), platform3TextureRect(), platform4TextureRect(), platform5TextureRect() {
	TTF_Font* font = ResourceManager::loadFont("res/fonts/advanced_pixel-7.ttf", 64);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

	//play background music
	sfx->playMP3(backgroundMusic, 0);

	//set collider names to define which collider is being collided with
	playerCollider.name = "player";
	box1Collider.name = "box1";
	box2Collider.name = "box2";
	platform1Collider.name = "platform1";
	platform2Collider.name = "platform2";
	platform3Collider.name = "platform3";
	platform4Collider.name = "platform4";
	platform5Collider.name = "platform5";

	//set static texture rects pos & size
	backgroundTextureRect.x = 0;
	backgroundTextureRect.y = 0;
	backgroundTextureRect.h = DEFAULT_WINDOW_HEIGHT;
	backgroundTextureRect.w = DEFAULT_WINDOW_WIDTH;

	platform1TextureRect.x = platform1Rect.x;
	platform1TextureRect.y = platform1Rect.y;
	platform1TextureRect.h = platform1Rect.h;
	platform1TextureRect.w = platform1Rect.w;

	platform2TextureRect.x = platform2Rect.x;
	platform2TextureRect.y = platform2Rect.y;
	platform2TextureRect.h = platform2Rect.h;
	platform2TextureRect.w = platform2Rect.w;

	platform3TextureRect.x = platform3Rect.x;
	platform3TextureRect.y = platform3Rect.y;
	platform3TextureRect.h = platform3Rect.h;
	platform3TextureRect.w = platform3Rect.w;

	platform4TextureRect.x = platform4Rect.x + 100;
	platform4TextureRect.y = platform4Rect.y;
	platform4TextureRect.h = platform4Rect.h;
	platform4TextureRect.w = platform4Rect.w - 100;

	platform5TextureRect.x = platform5Rect.x;
	platform5TextureRect.y = platform5Rect.y;
	platform5TextureRect.h = platform5Rect.h;
	platform5TextureRect.w = platform5Rect.w - 100;

	//set rigidbody values
	playerRigidbody.setRigidbodyValues(3, 3);

	box1Rigidbody.setRigidbodyValues(2, 2);

	box2Rigidbody.setRigidbodyValues(2, 1.5);

	//set startingAirResistance value
	playerRigidbody.startingAirResistance = playerRigidbody.airResistance;

	box1Rigidbody.startingAirResistance = box1Rigidbody.airResistance;

	box2Rigidbody.startingAirResistance = box2Rigidbody.airResistance;
}

MyGame::~MyGame() {

}

// handle key inputs (movement)
void MyGame::handleKeyEvents() {

	if (eventSystem->isPressed(Key::W) || (eventSystem->isPressed(Key::UP))) 
	{
		if (playerCollider.canMoveUp)
		{
			playerRigidbody.applyNegativeVelocityY(playerCollider);
		}
	}

	if (eventSystem->isPressed(Key::S) || (eventSystem->isPressed(Key::DOWN))) 
	{
		if (playerCollider.canMoveDown)
		{
			playerRigidbody.applyPositiveVelocityY(playerCollider);
		}
	}

	else if (eventSystem->isPressed(Key::A) || (eventSystem->isPressed(Key::LEFT))) 
	{
		if (playerCollider.canMoveLeft)
		{
			playerRigidbody.applyNegativeVelocityX(playerCollider);
		}
		else
		{
			//fixes screen wrap and movement when player pushing other rects
			if (playerCollider.collidingWithNameRight == "box1")
			{
				playerRigidbody.applyTotalNegativeVelocityX(playerCollider, box1Rigidbody);
			}
			if (playerCollider.collidingWithNameRight == "box2")
			{
				playerRigidbody.applyTotalNegativeVelocityX(playerCollider, box2Rigidbody);
			}
		}
	}

	else if (eventSystem->isPressed(Key::D) || (eventSystem->isPressed(Key::RIGHT))) 
	{
		if (playerCollider.canMoveRight)
		{
			playerRigidbody.applyPositiveVelocityX(playerCollider);
		}
		else
		{
			//fixes screen wrap and movement when player pushing other rects
			if (playerCollider.collidingWithNameLeft == "box1")
			{
				playerRigidbody.applyTotalPositiveVelocityX(playerCollider, box1Rigidbody);
			}
			if (playerCollider.collidingWithNameLeft == "box2")
			{
				playerRigidbody.applyTotalPositiveVelocityX(playerCollider, box2Rigidbody);
			}
		}
	}

	//reverse gravity once when key is pressed
	if (eventSystem->isPressed(Key::SPACE))
	{
		if (gravitySwitch && !keyDown)
		{
			playerRigidbody.reverseGravity = false;
			box1Rigidbody.reverseGravity = false;
			box2Rigidbody.reverseGravity = false;
			gravitySwitch = false;
			keyDown = true;
		}
		if (!gravitySwitch && !keyDown)
		{
			playerRigidbody.reverseGravity = true;
			box1Rigidbody.reverseGravity = true;
			box2Rigidbody.reverseGravity = true;
			gravitySwitch = true;
			keyDown = true;
		}
	}
	else
	{
		keyDown = false;
	}
}

void MyGame::update() {

	//add rects position to rigidbody velocity
	playerRect.x += playerRigidbody.velocity.x;
	playerRect.y += playerRigidbody.velocity.y;

	box1Rect.x += box1Rigidbody.velocity.x;
	box1Rect.y += box1Rigidbody.velocity.y;

	box2Rect.x += box2Rigidbody.velocity.x;
	box2Rect.y += box2Rigidbody.velocity.y;

	//set rigidbody velocity to zero when idle
	playerRigidbody.velocity.x = 0;
	playerRigidbody.velocity.y = 0;

	box1Rigidbody.velocity.x = 0;
	box1Rigidbody.velocity.y = 0;

	box2Rigidbody.velocity.x = 0;
	box2Rigidbody.velocity.y = 0;

	//update players position if OOB
	if (playerCollider.outOfBoundsLeft && !playerCollider.collidingWithLeft)
	{
		playerRect.x = DEFAULT_WINDOW_WIDTH;
	}
	if (playerCollider.outOfBoundsRight)
	{
		playerRect.x = 0 - playerRect.w;
	}

	//update box1 position if OOB
	if (box1Collider.outOfBoundsLeft)
	{
		box1Rect.x = DEFAULT_WINDOW_WIDTH;
	}
	if (box1Collider.outOfBoundsRight)
	{
		box1Rect.x = 0 - box1Rect.w;
	}

	//update box2 position if OOB
	if (box2Collider.outOfBoundsLeft)
	{
		box2Rect.x = DEFAULT_WINDOW_WIDTH;
	}
	if (box2Collider.outOfBoundsRight)
	{
		box2Rect.x = 0 - box2Rect.w;
	}

	//update textureRects to objectRects positions;
	playerTextureRect.x = playerRect.x;
	playerTextureRect.y = playerRect.y;
	playerTextureRect.h = playerRect.h;
	playerTextureRect.w = playerRect.w;

	box1TextureRect.x = box1Rect.x;
	box1TextureRect.y = box1Rect.y;
	box1TextureRect.h = box1Rect.h;
	box1TextureRect.w = box1Rect.w;

	box2TextureRect.x = box2Rect.x;
	box2TextureRect.y = box2Rect.y;
	box2TextureRect.h = box2Rect.h;
	box2TextureRect.w = box2Rect.w;

	//-----MyEngineSystem Updates-----
	
	//check MyEngineSystem is initialized
	if (init == false)
	{
		initMyEngineSystem.init();
		init = true;
	}

	//display easter egg on collision between player and box1
	text.displayEasterEgg(playerRect, box1Rect, playerCollider, box1Collider);

	//player colliders
	playerCollider.collideUntilRect2Moves(playerRect, box1Rect, box1Collider);

	playerCollider.collideUntilRect2Moves(playerRect, box2Rect, box2Collider);

	playerCollider.collideUntilRect1Moves(playerRect, platform1Rect, platform1Collider);

	playerCollider.collideUntilRect1Moves(playerRect, platform2Rect, platform2Collider);

	playerCollider.collideUntilRect1Moves(playerRect, platform3Rect, platform3Collider);

	playerCollider.collideUntilRect1Moves(playerRect, platform4Rect, platform4Collider);

	playerCollider.collideUntilRect1Moves(playerRect, platform5Rect, platform5Collider);

	//box 1 colliders
	box1Collider.collideUntilRect2Moves(box1Rect, playerRect, playerCollider);

	box1Collider.collideUntilRect2Moves(box1Rect, box2Rect, box2Collider);

	box1Collider.collideUntilRect1Moves(box1Rect, platform1Rect, platform1Collider);

	box1Collider.collideUntilRect1Moves(box1Rect, platform2Rect, platform2Collider);

	box1Collider.collideUntilRect1Moves(box1Rect, platform3Rect, platform3Collider);

	box1Collider.collideUntilRect1Moves(box1Rect, platform4Rect, platform4Collider);

	box1Collider.collideUntilRect1Moves(box1Rect, platform5Rect, platform5Collider);

	//box 2 colliders
	box2Collider.collideUntilRect2Moves(box2Rect, playerRect, playerCollider);

	box2Collider.collideUntilRect2Moves(box2Rect, box1Rect, box1Collider);

	box2Collider.collideUntilRect1Moves(box2Rect, platform1Rect, platform1Collider);

	box2Collider.collideUntilRect1Moves(box2Rect, platform2Rect, platform2Collider);

	box2Collider.collideUntilRect1Moves(box2Rect, platform3Rect, platform3Collider);

	box2Collider.collideUntilRect1Moves(box2Rect, platform4Rect, platform4Collider);

	box2Collider.collideUntilRect1Moves(box2Rect, platform5Rect, platform5Collider);

	//check if rects are within screen bounds
	playerCollider.checkWithinScreenBounds(playerRect);

	box1Collider.checkWithinScreenBounds(box1Rect);

	box2Collider.checkWithinScreenBounds(box2Rect);

	//apply gravity to objects
	playerRigidbody.applyGravity(playerCollider);

    box1Rigidbody.applyGravity(box1Collider);

	box2Rigidbody.applyGravity(box2Collider);

	//push rigidbodies
	box1Rigidbody.pushedHorizontallyByOtherCollider(box1Rect, box2Rect, box1Collider, box2Collider, box2Rigidbody);

	box2Rigidbody.pushedHorizontallyByOtherCollider(box2Rect, box1Rect, box2Collider, box1Collider, box1Rigidbody);

	box1Rigidbody.pushedHorizontallyByOtherCollider(box1Rect, playerRect, box1Collider, playerCollider, playerRigidbody);

	box2Rigidbody.pushedHorizontallyByOtherCollider(box2Rect, playerRect, box2Collider, playerCollider, playerRigidbody);

	//set air resistance on collision (push horizontally under gravity)
	box2Rigidbody.setAirResistanceOnCollision(box2Rect, box1Rect, box2Collider, box1Collider, box1Rigidbody);

	box1Rigidbody.setAirResistanceOnCollision(box1Rect, playerRect, box1Collider, playerCollider, playerRigidbody);

	box2Rigidbody.setAirResistanceOnCollision(box2Rect, playerRect, box2Collider, playerCollider, playerRigidbody);

	//------END of MyEngineSystem Updates-----
}

void MyGame::render() {

	//draw textures
	gfx->drawTexture(backgroundTexture, &backgroundTextureRect);

	gfx->drawTexture(playerTexture, &playerTextureRect);

	gfx->drawTexture(box1Texture, &box1TextureRect);

	gfx->drawTexture(box2Texture, &box2TextureRect);

	gfx->drawTexture(platformTexture1, &platform1TextureRect);

	gfx->drawTexture(platformTexture1, &platform2TextureRect, SDL_FLIP_HORIZONTAL);

	gfx->drawTexture(platformTexture2, &platform3TextureRect, SDL_FLIP_VERTICAL);

	gfx->drawTexture(platformTexture2, &platform4TextureRect);

	gfx->drawTexture(platformTexture2, &platform5TextureRect, SDL_FLIP_HORIZONTAL);
}

void MyGame::renderUI() {

	//draw text
	gfx->setDrawColor(SDL_COLOR_GREEN);
	gfx->drawText(text.easterEgg, 130, 550);
}
