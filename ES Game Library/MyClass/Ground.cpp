#include"Ground.h"

void Ground::Initialize(Vector3 pos,int id) {
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f);
	material.Emissive = Color(0.2f, 0.2f, 0.2f);
	switch (id) {
	case 0:
		block = GraphicsDevice.CreateModelFromFile(_T("Ground/stage1.X"));
		block->SetScale(0.55f);
		break;
	case 1:
		block = GraphicsDevice.CreateModelFromFile(_T("Ground/stage2.X"));
		block->SetScale(0.55f);
		break;
	case 2:
		block = GraphicsDevice.CreateModelFromFile(_T("Ground/stage3.X"));
		block->SetScale(0.55f);
		break;

	}
	block->SetMaterial(material);
	block->SetPosition(pos);
}
void Haikei::Initialize(Vector3 pos) {
	haikei = GraphicsDevice.CreateModelFromFile(_T("Ground/back.X"));
	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(0.2f, 0.2f, 0.2f);
	haikei->SetMaterial(material);
	haikei->SetScale(2.0f);
	haikei->SetPosition(pos);
}
void Grabity_Area::Initialize(Vector3 pos, int houkou_) {
	area= GraphicsDevice.CreateModelFromFile(_T("Ground/back.X"));
	area->SetScale(0.5f);
	area->SetPosition(pos);
	obb = area->GetOBB();
	houkou = houkou_;
}
void Ground::Update() {



}
void Ground::Draw() {
	block->Draw();
}
void Haikei::Draw() {
	haikei->Draw();
}
