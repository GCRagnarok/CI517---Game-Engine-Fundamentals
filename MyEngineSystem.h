#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../GraphicsEngine.h"
#include "../AudioEngine.h"

class MyEngineSystem {
	friend class XCube2Engine;
	private:

	public:
};

//-----Test Class-----
class Test {
private:

public:
	//Class functions
	void init();
	//Class variables
	std::string text = "\nMyEngineSystem is initialized\n";
};
//-----END of Test Class-----

//-----Collider Class-----
class Collision {
private:

	int storedXPosTop = 0;
	int storedYPosTop = 0;

	int storedXPosBottom = 0;
	int storedYPosBottom = 0;

	int storedXPosLeft = 0;
	int storedYPosLeft = 0;

	int storedXPosRight = 0;
	int storedYPosRight = 0;

	int storedXPosTop2 = 0;
	int storedYPosTop2 = 0;

	int storedXPosBottom2 = 0;
	int storedYPosBottom2 = 0;

	int storedXPosLeft2 = 0;
	int storedYPosLeft2 = 0;

	int storedXPosRight2 = 0;
	int storedYPosRight2 = 0;

public:
	//Class functions
	void checkCollisionWithRect(Rect pRect1, Rect pRect2, Collision pRect2Collider);

	void collideUntilRect1Moves(Rect pRect1, Rect pRect2, Collision pRect2Collider);

	void collideUntilRect2Moves(Rect pRect1, Rect pRect2, Collision pRect2Collider);

	void checkRect1MovedSinceCollisionTop(Rect pRect1, Rect pRect2);

	void checkRect1MovedSinceCollisionBottom(Rect pRect1, Rect pRect2);

	void checkRect1MovedSinceCollisionLeft(Rect pRect1, Rect pRect2);

	void checkRect1MovedSinceCollisionRight(Rect pRect1, Rect pRect2);

	void checkRect2MovedSinceCollisionTop(Rect pRect1, Rect pRect2);

	void checkRect2MovedSinceCollisionBottom(Rect pRect1, Rect pRect2);

	void checkRect2MovedSinceCollisionLeft(Rect pRect1, Rect pRect2);

	void checkRect2MovedSinceCollisionRight(Rect pRect1, Rect pRect2);

	void checkWithinScreenBounds(Rect pRect);

	//Class variables

	bool collidingWithTop = false;

	bool collidingWithBottom = false;

	bool collidingWithLeft = false;

	bool collidingWithRight = false;

	bool canMoveUp = true;

	bool canMoveDown = true;

	bool canMoveLeft = true;

	bool canMoveRight = true;

	bool outOfBoundsAbove = true;

	bool outOfBoundsBelow = true;

	bool outOfBoundsLeft = false;

	bool outOfBoundsRight = false;

	std::string name = " ";

	std::string collidingWithNameTop = " ";

	std::string collidingWithNameBottom = " ";

	std::string collidingWithNameLeft = " ";

	std::string collidingWithNameRight = " ";
};
//-----END of Collider Class-----


//-----Physics Class-----
class Physics {
private:

public:
	//Class functions
	void applyPositiveVelocityX(Collision pCollider);
	void applyNegativeVelocityX(Collision pCollider);
	void applyPositiveVelocityY(Collision pCollider);
	void applyNegativeVelocityY(Collision pCollider);

	void applyTotalPositiveVelocityX(Collision pCollider, Physics pAdditionalRigidbody);
	void applyTotalNegativeVelocityX(Collision pCollider, Physics pAdditionalRigidbody);
	void applyTotalPositiveVelocityY(Collision pCollider, Physics pAdditionalRigidbody);
	void applyTotalNegativeVelocityY(Collision pCollider, Physics pAdditionalRigidbody);

	void setRigidbodyValues(float pForce, float pAirResistance);

	void applyGravity(Collision pCollider);

	void pushedHorizontallyByOtherCollider(Rect pRect1, Rect pRect2, Collision pRect1Collider, Collision pRect2Collider, Physics pRect2Rigidbody);

	void setAirResistanceOnCollision(Rect pRect1, Rect pRect2, Collision pRect1Collider, Collision pRect2Collider, Physics pRect2Rigidbody);

	//Class variables
	Vector2i velocity;

	float force = 0;

	float airResistance = 0;

	float startingAirResistance = 0;

	bool reverseGravity = false;
};
//-----END of Physics Class-----
// 
//-----EasterEgg Class-----
class EasterEgg {
private:

public:
	//Class functions
	void displayEasterEgg(Rect pRect1, Rect pRect2, Collision pRect1Collider, Collision pRect2Collider);

	//Class variables
	std::string easterEgg = " ";

	bool easterEggOn = false;
};

//-----END of Physics Class-----
#endif
