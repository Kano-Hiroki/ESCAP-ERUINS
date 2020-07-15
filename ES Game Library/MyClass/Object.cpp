#include"Object.h"

void Object_base::Initialize(Vector3 pos, float size, int hp_, LPCTSTR file) {
	object = GraphicsDevice.CreateModelFromFile(file);
	object->SetPosition(pos);
	object->SetScale(size);
	flag = false;
	OrientedBoundingBox obb = object->GetOBB();//�Q�[�g��OBB�擾
	//�����蔻�萶��
	SimpleShape box;//�{�b�N�X�𐶐�
	box.Type = Shape_Box;
	box.Width = obb.Radius.x * 2;
	box.Height = obb.Radius.y * 2;
	box.Depth = obb.Radius.z * 10;//�Q�[�g�Ƒ傫�������킹��
	object_prefab = GraphicsDevice.CreateModelFromSimpleShape(box);
	hp = hp_;
	theta = 20;
	theta_pattern = 0;
	
}
void Object_base::hit(){
	hp -= 10;

}
void Object_base::Draw() {
	object_prefab->SetPosition(object->GetPosition());
	if (hp> 0) {
		object->Draw();
	}
	//object_prefab->Draw();
}
void LightObject::Update() {
	light_control();
}
void LightObject::light_control() {
	light.Type = Light_Spot;
	light.Diffuse = Color(1.5f, 0.5f, 0.5f); // �f�B�t���[�Y�F
	light.Specular = Color(1.5f, 0.5f, 0.5f); // �X�y�L�����[�F
	light.Ambient = Color(1.0f, 1.0f, 1.5f); // �A���r�G���g�F
	light.Range = 30.0f; // ���C�g�̗L���͈�
	light.Attenuation0 = 1.0f; // �����萔
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Direction = Vector3(0, 90, 90);
	light.Theta = MathHelper_ToRadians(theta);
	light.Phi = MathHelper_ToRadians(theta+40);
	light.Position = object->GetPosition() + Vector3(0, 0, -100);
	light.Direction = Vector3_Forward;
	if(theta_pattern==0){
		theta +=0.1;
		if (theta >= 60) {
			theta_pattern = 1;
		}
	}
	else if (theta_pattern == 1) {
		theta-=0.1;
		if (theta <= 40) {
			theta_pattern = 0;

		}

	}
}
