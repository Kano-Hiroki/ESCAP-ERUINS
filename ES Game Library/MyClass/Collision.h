#pragma once
#include"../ESGLib.h"
#include"Enemy.h"
#include"Player.h"
#include"Object.h"
#include"Ground.h"
#include"Item.h"

class Collision {
public:
	bool collision(MODEL model1, MODEL model2);
	bool collision(ANIMATIONMODEL model1, MODEL model2);
	bool collision(ANIMATIONMODEL model1, ANIMATIONMODEL model2);
private:
	
};