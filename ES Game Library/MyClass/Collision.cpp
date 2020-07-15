#include "Collision.h"
bool Collision::collision(MODEL model1, MODEL model2) {
	bool hit = false;
	OrientedBoundingBox model_obb1 = model1->GetOBB();
	OrientedBoundingBox model_obb2 = model2->GetOBB();
	if (model_obb1.Intersects(model_obb2)) {
		hit = true;
	}
	return hit;
}
bool Collision::collision(ANIMATIONMODEL model1, MODEL model2) {
	bool hit = false;
	OrientedBoundingBox model_obb1 = model1->GetOBB();
	OrientedBoundingBox model_obb2 = model2->GetOBB();
	if (model_obb1.Intersects(model_obb2)) {
		hit = true;
	}
	return hit;
}
bool Collision::collision(ANIMATIONMODEL model1, ANIMATIONMODEL model2) {
	bool hit = false;
	OrientedBoundingBox model_obb1 = model1->GetOBB();
	OrientedBoundingBox model_obb2 = model2->GetOBB();
	if (model_obb1.Intersects(model_obb2)) {
		hit = true;
	}
	return hit;
}