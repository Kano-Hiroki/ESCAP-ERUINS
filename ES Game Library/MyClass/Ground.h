#pragma once
#include "../ESGLib.h"
#include"enum.h"
class Ground {
public:
	void Initialize(Vector3 pos,int Block_id);
	void Update();
	void Draw();


	MODEL re_ground() {return block;};
	//À•W‚ð•Ô‚·
	Vector3 re_pos() { return block->GetPosition(); }

private:
	MODEL block;


};
class Grabity_Area {
public:
	void Initialize(Vector3 pos, int direction_);
	
	int re_houkou() { return houkou; };
	MODEL re_model() { return area; }
private:
	OrientedBoundingBox obb;
	MODEL area;
	int houkou;
};
class Haikei {
public:
	void Initialize(Vector3 pos);
	void Draw();
	Vector3 re_pos() { return haikei->GetPosition(); }
private:
	MODEL haikei;

};