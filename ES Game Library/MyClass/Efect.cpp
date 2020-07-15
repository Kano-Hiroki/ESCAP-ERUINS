#include"Efect.h"
void Efect::Initialize(float one_frame_,int end_flame_, LPCTSTR sprite) {
	float   SIZE = 100.0f / 2.0f;
	one_flame = one_frame_;
	//”š”­‚Ì0.0625f;
	vec[0].x = -SIZE;
	vec[0].y = SIZE;
	vec[0].z = 0.0f;
	vec[0].nx = 0.0f;
	vec[0].ny = 0.0f;
	vec[0].nz = -1.0f;
	vec[0].tu = 0.0f;
	vec[0].tv = 0.0f;

	vec[1].x = SIZE;
	vec[1].y = SIZE;
	vec[1].z = 0.0f;
	vec[1].nx = 0.0f;
	vec[1].ny = 0.0f;
	vec[1].nz = -1.0f;
	vec[1].tu = one_flame;
	vec[1].tv = 0.0f;

	vec[2].x = SIZE;
	vec[2].y = -SIZE;
	vec[2].z = 0.0f;
	vec[2].nx = 0.0f;
	vec[2].ny = 0.0f;
	vec[2].nz = -1.0f;
	vec[2].tu = one_flame;
	vec[2].tv = 0.8f;

	vec[3] = vec[2];

	vec[4].x = -SIZE;
	vec[4].y = -SIZE;
	vec[4].z = 0.0f;
	vec[4].nx = 0.0f;
	vec[4].ny = 0.0f;
	vec[4].nz = -1.0f;
	vec[4].tu = 0.0f;
	vec[4].tv = 0.8f;

	vec[5] = vec[0];

	texture = GraphicsDevice.CreateSpriteFromFile(sprite);
	model = GraphicsDevice.CreateModelFromFile(_T("Efect/exp.X"));
	end_flame = end_flame_;
}
void Efect::Update(int now_flame,Vector3 pos) {
	vec[0].tu = one_flame*now_flame;
	vec[1].tu = vec[0].tu + one_flame;
	vec[2].tu = vec[1].tu;
	vec[3].tu = vec[2].tu;
	vec[4].tu = vec[0].tu;
	vec[5].tu = vec[0].tu;
	model->SetPosition(pos);
	//if (now_flame == end_flame) {
	//	end_flag = true;
	//}
}
void Efect::Draw() {
		GraphicsDevice.SetTransform(D3DTS_WORLD, model->GetWorldMatrix());

		Material   material;
		material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
		material.Ambient = Color(1.0f, 1.0f, 1.0f, 1.0f);
		material.Emissive = Color(1.0f, 1.0f, 1.0f, 1.0f);
		GraphicsDevice.SetMaterial(material);

		GraphicsDevice.SetTexture(0, *texture);

		GraphicsDevice.DrawUserPrimitives(PrimitiveType_TriangleList, vec, 2, vec[0].FVF());
	
}