#pragma once
#include"../ESGLib.h"
class Efect {
public:
	void Initialize(float one_frame_,int end_flame_, LPCTSTR sprite);
	void Update(int now_flame,Vector3 pos);
	void Draw();
	MODEL GetModel() { return model; };
private:
	MODEL model;
	VertexPositionNormalTexture  vec[6];
	SPRITE texture;

	float one_flame;//��R�}������̑傫��
	int end_flame;//���R�}�ڂŏI��邩
	bool end_flag;
	Vector3 pos;
};