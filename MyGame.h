#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/GraphicsEngine.h"
#include "../engine/AudioEngine.h"
#include "../engine/custom/MyEngineSystem.h"

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:

		//Rects (GameObjects)
		Rect playerRect;

		Rect box1Rect;

		Rect box2Rect;

		Rect platform1Rect;

		Rect platform2Rect;

		Rect platform3Rect;

		Rect platform4Rect;

		Rect platform5Rect;

		//SDL_Rects (textures)
		SDL_Rect backgroundTextureRect;

		SDL_Rect playerTextureRect;

		SDL_Rect box1TextureRect;

		SDL_Rect box2TextureRect;

		SDL_Rect platform1TextureRect;

		SDL_Rect platform2TextureRect;

		SDL_Rect platform3TextureRect;

		SDL_Rect platform4TextureRect;

		SDL_Rect platform5TextureRect;

		//pickup objects
		std::vector<std::shared_ptr<GameKey>> gameKeys;

		//Test objects
		Test initMyEngineSystem;

		//Collision objects
		Collision playerCollider;

		Collision box1Collider;

		Collision box2Collider;

		Collision platform1Collider;

		Collision platform2Collider;

		Collision platform3Collider;

		Collision platform4Collider;

		Collision platform5Collider;

		//Physics objects
		Physics playerRigidbody;

		Physics box1Rigidbody;

		Physics box2Rigidbody;

		//Easter egg objects
		EasterEgg text;

		//SDL_Textures*;

		SDL_Texture* backgroundTexture = ResourceManager::loadTexture("res/images/background.png", SDL_COLOR_RED);

		SDL_Texture* playerTexture = ResourceManager::loadTexture("res/images/player.png", SDL_COLOR_RED);

		SDL_Texture* platformTexture1 = ResourceManager::loadTexture("res/images/platform1&2.png", SDL_COLOR_RED);

		SDL_Texture* platformTexture2 = ResourceManager::loadTexture("res/images/platform3-5.png", SDL_COLOR_RED);

		SDL_Texture* box1Texture = ResourceManager::loadTexture("res/images/box1.png", SDL_COLOR_RED);

		SDL_Texture* box2Texture = ResourceManager::loadTexture("res/images/box2.png", SDL_COLOR_RED);

		//Audio

		Mix_Music* backgroundMusic = ResourceManager::loadMP3("res/audio/background.mp3");

		//Custom Variables
		bool init = false;

		bool gravitySwitch = false;

		bool keyDown = false;
		//End of Custom Variables

		/* GAMEPLAY */
		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
	public:

        MyGame();
		~MyGame();
};

#endif
