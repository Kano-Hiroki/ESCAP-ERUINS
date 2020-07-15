#pragma once
#include"../ESGLib.h"
#include"Efect.h"
class SOSHuman {
public:
	void Initialize(Vector3 pos);
	void Update();
	void Reset();
	void Draw();
	void Start();
	void Hit();
	void Efect_Draw();
	bool GetStartFlag() { return Start_flag; };
	bool GetEndFlag() { return Hit_flag; };
	MODEL GetModel() { return model; };
private:
    MODEL model;
	Efect human;
	bool Start_flag;
	bool End_flag;
	float efect_count;
	int efect_state;
	SPRITE hit_sprite;
	bool Hit_flag;
	int count;
};