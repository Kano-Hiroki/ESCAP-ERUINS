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

	float one_flame;//一コマ当たりの大きさ
	int end_flame;//何コマ目で終わるか
	bool end_flag;
	Vector3 pos;
};