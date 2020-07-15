#pragma once
#include "../ESGLib.h"
class Object_base {
public:
	virtual ~Object_base() {}
	virtual void Initialize(Vector3 pos, float size, int hp_, LPCTSTR file);
	virtual void Draw();
	virtual void Update() {};
	virtual void light_control() {};
	virtual void light_initialize() {};
	virtual MODEL re_object(){ return object; }
	virtual bool re_flag(){return flag; }
	virtual void hit();
	virtual Light re_light(){ return light; }
protected:
	MODEL object;
	bool flag;
	MODEL object_prefab;
	int hp;
	Light light;
	float theta;
	int theta_pattern;

};
class LightObject :public Object_base {
public:
	virtual ~LightObject() {}
	void Update();
	void light_control();
private:
};