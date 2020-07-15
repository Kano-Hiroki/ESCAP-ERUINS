#pragma once
#include "../ESGLib.h"
class SOSHuman {
public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw();
	void Start();
	void Hit();
	bool GetStartFlag() { return Start_flag; };
	bool GetEndFlag() { return End_flag; };
	MODEL GetModel() { return model; };
private:
    MODEL model;
	bool Start_flag;
	bool End_flag;
};