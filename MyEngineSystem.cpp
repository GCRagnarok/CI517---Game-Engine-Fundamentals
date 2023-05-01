#include "MyEngineSystem.h"
#include <ctime>

//-----START of TEST functions-----

void Test::init()
{
	std::cout << text;
}

//-----END of TEST functions-----

//-----START of COLLISION functions-----

void Collision::checkCollisionWithRect(Rect pRect1, Rect pRect2, Collision pRect2Collider)
{
	//include offset to ensure graphics don't overlap
	int offset = 2;

	pRect1.h = pRect1.h + offset;
	pRect1.w = pRect1.w + offset;
	pRect2.h = pRect2.h + offset;
	pRect2.w = pRect2.w + offset;

	//define pRect1 & pRect2 bottom and right
	float pRect1_bottom = pRect1.y + pRect1.h;
	float pRect2_bottom = pRect2.y + pRect2.h;
	float pRect1_right = pRect1.x + pRect1.w;
	float pRect2_right = pRect2.x + pRect2.w;

	//define which direction the collision is occuring on pRect2
	float bottomCollision = pRect2_bottom - pRect1.y;
	float topCollision = pRect1_bottom - pRect2.y;
	float leftCollision = pRect1_right - pRect2.x;
	float rightCollision = pRect2_right - pRect1.x;

	//AABB Collision Detection
	if (pRect1.x < pRect2.x + pRect2.w &&
		pRect1.x + pRect1.w > pRect2.x &&
		pRect1.y < pRect2.y + pRect2.h &&
		pRect1.y + pRect1.h > pRect2.y) {

		//colliding with TOP of pRect2
		if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
		{
			collidingWithTop = true;
			storedXPosTop = pRect1.x;
			storedYPosTop = pRect1.y;
			storedXPosTop2 = pRect2.x;
			storedYPosTop2 = pRect2.y;
			collidingWithNameTop = pRect2Collider.name;
		}
		//colliding with BOTTOM of pRect2
		if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
		{
			collidingWithBottom = true;
			storedXPosBottom = pRect1.x;
			storedYPosBottom = pRect1.y;
			storedXPosBottom2 = pRect2.x;
			storedYPosBottom2 = pRect2.y;
			collidingWithNameBottom = pRect2Collider.name;
		}
		//colliding with LEFT of pRect2
		if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
		{
			collidingWithLeft = true;
			storedXPosLeft = pRect1.x;
			storedYPosLeft = pRect1.y;
			storedXPosLeft2 = pRect2.x;
			storedYPosLeft2 = pRect2.y;
			collidingWithNameLeft = pRect2Collider.name;
		}
		//colliding with RIGHT of pRect2
		if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision)
		{
			collidingWithRight = true;
			storedXPosRight = pRect1.x;
			storedYPosRight = pRect1.y;
			storedXPosRight2 = pRect2.x;
			storedYPosRight2 = pRect2.y;
			collidingWithNameRight = pRect2Collider.name;
		}
	}
}

void Collision::collideUntilRect1Moves(Rect pRect1, Rect pRect2, Collision pRect2Collider)
{
	checkCollisionWithRect(pRect1, pRect2, pRect2Collider);

	if (collidingWithTop)
	{
		canMoveDown = false;
		checkRect1MovedSinceCollisionTop(pRect1, pRect2);
	}
	else
	{
		canMoveDown = true;
	}

	if (collidingWithBottom)
	{
		canMoveUp = false;
		checkRect1MovedSinceCollisionBottom(pRect1, pRect2);
	}
	else
	{
		canMoveUp = true;
	}

	if (collidingWithLeft)
	{
		canMoveRight = false;
		checkRect1MovedSinceCollisionLeft(pRect1, pRect2);
	}
	else
	{
		canMoveRight = true;
	}

	if (collidingWithRight)
	{
		canMoveLeft = false;
		checkRect1MovedSinceCollisionRight(pRect1, pRect2);
	}
	else
	{
		canMoveLeft = true;
	}

}

//set can move directions to false until rect2 has moved
void Collision::collideUntilRect2Moves(Rect pRect1, Rect pRect2, Collision pRect2Collider)
{
	checkCollisionWithRect(pRect1, pRect2, pRect2Collider);

	if (collidingWithTop && collidingWithNameTop == pRect2Collider.name)
	{
		canMoveDown = false;
		checkRect2MovedSinceCollisionTop(pRect1, pRect2);
	}
	else
	{
		canMoveDown = true;
	}

	if (collidingWithBottom && collidingWithNameBottom == pRect2Collider.name)
	{
		canMoveUp = false;
		checkRect2MovedSinceCollisionBottom(pRect1, pRect2);
	}
	else
	{
		canMoveUp = true;
	}

	if (collidingWithLeft && collidingWithNameLeft == pRect2Collider.name)
	{
		canMoveRight = false;
		checkRect2MovedSinceCollisionLeft(pRect1, pRect2);
	}
	else
	{
		canMoveRight = true;
	}

	if (collidingWithRight && collidingWithNameRight == pRect2Collider.name)
	{
		canMoveLeft = false;
		checkRect2MovedSinceCollisionRight(pRect1, pRect2);
	}
	else
	{
		canMoveLeft = true;
	}
}

void Collision::checkRect1MovedSinceCollisionTop(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (UP, LEFT OR RIGHT) since collision
	if (pRect1.y < storedYPosTop || pRect1.x != storedXPosTop)
	{
		collidingWithTop = false;
	}
}

void Collision::checkRect1MovedSinceCollisionBottom(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (DOWN, LEFT OR RIGHT) since collision
	if (pRect1.y > storedYPosBottom || pRect1.x != storedXPosBottom)
	{
		collidingWithBottom = false;
	}
}

void Collision::checkRect1MovedSinceCollisionLeft(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (RIGHT, UP OR DOWN) since collision
	if (pRect1.x < storedXPosLeft || pRect1.y != storedYPosLeft)
	{
		collidingWithLeft = false;
	}
}

void Collision::checkRect1MovedSinceCollisionRight(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (LEFT, UP OR DOWN) since collision
	if (pRect1.x > storedXPosRight || pRect1.y != storedYPosRight)
	{
		collidingWithRight = false;
	}
}

void Collision::checkRect2MovedSinceCollisionTop(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (UP, LEFT OR RIGHT) since collision
	if (pRect2.y > storedYPosTop2 || pRect2.x != storedXPosTop2)
	{
		collidingWithTop = false;
	}
}

void Collision::checkRect2MovedSinceCollisionBottom(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (DOWN, LEFT OR RIGHT) since collision
	if (pRect2.y < storedYPosBottom2 || pRect2.x != storedXPosBottom2)
	{
		collidingWithBottom = false;
	}
}

void Collision::checkRect2MovedSinceCollisionLeft(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (RIGHT, UP OR DOWN) since collision
	if (pRect2.x > storedXPosLeft2|| pRect2.y != storedYPosLeft2)
	{
		collidingWithLeft = false;
	}
}

void Collision::checkRect2MovedSinceCollisionRight(Rect pRect1, Rect pRect2)
{
	//Check if pRect1 has moved (LEFT, UP OR DOWN) since collision
	if (pRect2.x < storedXPosRight2 || pRect2.y != storedYPosRight2)
	{
		collidingWithRight = false;
	}
}

// check if rect is within the screen bounds
void Collision::checkWithinScreenBounds(Rect pRect)
{
	if (pRect.x + pRect.w < 0)
	{
		outOfBoundsLeft = true;
	}
	else if (pRect.x > DEFAULT_WINDOW_WIDTH)
	{
	    outOfBoundsRight = true;
	}
	else if (pRect.y + pRect.h < 0)
	{
		outOfBoundsAbove = true;
	}
	else if (pRect.y > DEFAULT_WINDOW_HEIGHT)
	{
		outOfBoundsBelow = true;
	}
	else
	{
		outOfBoundsAbove = false;
		outOfBoundsBelow = false;
		outOfBoundsLeft = false;
		outOfBoundsRight = false;
	}
}
//-----END of COLLISION function-----

//----- START of PHYSICS function-----

void Physics::applyPositiveVelocityX(Collision pCollider)
{
	velocity.x = force;
}
void Physics::applyNegativeVelocityX(Collision pCollider)
{
	velocity.x = -force;
}

void Physics::applyPositiveVelocityY(Collision pCollider)
{
	velocity.y = force;
}

void Physics::applyNegativeVelocityY(Collision pCollider)
{
	velocity.y = -force;
}

void Physics::applyTotalPositiveVelocityX(Collision pCollider, Physics pAdditionalRigidbody)
{
	//subtract smaller number from larger number to ensure result is a positive value.
	if (force > pAdditionalRigidbody.force)
	{
		float totalForce = force - pAdditionalRigidbody.force;
		velocity.x =  totalForce;
	}
	if (force < pAdditionalRigidbody.force)
	{
		float totalForce = pAdditionalRigidbody.force - force;
		velocity.x = totalForce;
	}
	//ensure velocity is set to 1 if totalForce will = 0
	if (force == pAdditionalRigidbody.force)
	{
		velocity.x = 1;
	}
}
void Physics::applyTotalNegativeVelocityX(Collision pCollider, Physics pAdditionalRigidbody)
{
	//subtract larger number from smaller number to ensure result is a negative value.
	if (force < pAdditionalRigidbody.force)
	{
		float totalForce = force - pAdditionalRigidbody.force;
		velocity.x = totalForce;
	}
	if (force > pAdditionalRigidbody.force)
	{
		float totalForce = pAdditionalRigidbody.force - force;
		velocity.x = totalForce;
	}
	//ensure velocity is set to -1 if totalForce will = 0
	if (force == pAdditionalRigidbody.force)
	{
		velocity.x = -1;
	}
}

void Physics::applyTotalPositiveVelocityY(Collision pCollider, Physics pAdditionalRigidbody)
{
	//subtract smaller number from larger number to ensure result is a positive value.
	if (force > pAdditionalRigidbody.force)
	{
		float totalForce = force - pAdditionalRigidbody.force;
		velocity.y = totalForce;
	}
	if (force < pAdditionalRigidbody.force)
	{
		float totalForce = pAdditionalRigidbody.force - force;
		velocity.y = totalForce;
	}
	//ensure velocity is set to 1 if totalForce will = 0
	if (force == pAdditionalRigidbody.force)
	{
		velocity.y = 1;
	}
}

void Physics::applyTotalNegativeVelocityY(Collision pCollider, Physics pAdditionalRigidbody)
{
	//subtract larger number from smaller number to ensure result is a negative value.
	if (force < pAdditionalRigidbody.force)
	{
		float totalForce = force - pAdditionalRigidbody.force;
		velocity.y = totalForce;
	}
	if (force > pAdditionalRigidbody.force)
	{
		float totalForce = pAdditionalRigidbody.force - force;
		velocity.y = totalForce;
	}
	//ensure velocity is set to -1 if totalForce will = 0
	if (force == pAdditionalRigidbody.force)
	{
		velocity.y = -1;
	}
}

void Physics::setRigidbodyValues(float pForce, float pAirResistance)
{
	force = pForce;
	airResistance = pAirResistance;
}

void Physics::applyGravity(Collision pCollider)
{
	int gravitationalForce = 3;

	if (!reverseGravity)
	{
		if (pCollider.canMoveDown)
		{
			velocity.y = gravitationalForce * airResistance, pCollider;
		}
	}
	else
	{
		if (pCollider.canMoveUp)
		{
			velocity.y = -gravitationalForce * airResistance, pCollider;
		}
	}
}

void Physics::pushedHorizontallyByOtherCollider(Rect pRect1, Rect pRect2, Collision pRect1Collider, Collision pRect2Collider, Physics pRect2Rigidbody)
{
	pRect1Collider.checkCollisionWithRect(pRect1, pRect2, pRect2Collider);

	if (pRect1Collider.collidingWithRight && pRect1Collider.collidingWithNameRight == pRect2Collider.name)
	{
		applyTotalPositiveVelocityX(pRect1Collider, pRect2Rigidbody);
	}
	if (pRect1Collider.collidingWithLeft && pRect1Collider.collidingWithNameLeft == pRect2Collider.name)
	{
		applyTotalNegativeVelocityX(pRect1Collider, pRect2Rigidbody);
	}
}

void Physics::setAirResistanceOnCollision(Rect pRect1, Rect pRect2, Collision pRect1Collider, Collision pRect2Collider, Physics pRect2Rigidbody)
{
	pRect1Collider.checkCollisionWithRect(pRect1, pRect2, pRect2Collider);

	if (pRect1Collider.collidingWithBottom && pRect1Collider.collidingWithNameBottom == pRect2Collider.name && !pRect1Collider.collidingWithTop)
	{
		airResistance = pRect2Rigidbody.airResistance;
	}
	if (pRect1Collider.collidingWithTop && pRect1Collider.collidingWithNameTop == pRect2Collider.name && !pRect1Collider.collidingWithBottom)
	{
		airResistance = pRect2Rigidbody.airResistance;
	}
	if (velocity.y == 0)
	{
		airResistance = startingAirResistance;
	}
}
//-----END of PHYSICS function-----

//-----EASTEREGG FUNCTION-----

void EasterEgg::displayEasterEgg(Rect pRect1, Rect pRect2, Collision pRect1Collider, Collision pRect2Collider)
{
	pRect1Collider.checkCollisionWithRect(pRect1, pRect2, pRect2Collider);

	if (pRect1Collider.collidingWithTop && pRect1Collider.collidingWithNameTop == pRect2Collider.name ||
		pRect1Collider.collidingWithBottom && pRect1Collider.collidingWithNameBottom == pRect2Collider.name ||
		pRect1Collider.collidingWithLeft && pRect1Collider.collidingWithNameLeft == pRect2Collider.name ||
		pRect1Collider.collidingWithRight && pRect1Collider.collidingWithNameRight == pRect2Collider.name)
	{
		if (!easterEggOn)
		{
			easterEgg = "Glen_Church - CI517_2023";
			easterEggOn = true;

		}
	}
	else
	{
		easterEgg = " ";
		easterEggOn = false;
	}
}
