	#include"SOSHuman.h"
void SOSHuman::Initialize(Vector3 pos) {
	model = GraphicsDevice.CreateModelFromFile(_T("Item/res1.X"));	
	model->SetPosition(pos);
	model->SetScale(5.0f);
	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	Start_flag = true;
	End_flag = false;
	Hit_flag = false;
	efect_state = 0;
	count = 0;
	model->SetMaterial(material);
	hit_sprite = GraphicsDevice.CreateSpriteFromFile(_T("Item/rescuer02.png"));
}
void SOSHuman::Reset() {
	Start_flag = true;
	End_flag = false;
	Hit_flag = false;
	efect_state = 0;
}
void SOSHuman::Update() {
	if (efect_state ==0) {
		efect_count += 0.1;
		if (efect_count >= 1) {
			efect_state == 1;
		}
	}
	else if (efect_state == 1) {
		efect_count -= 0.1;
		if (efect_count <= 0) {
			efect_state == 0;
		}

	}
	if (Hit_flag) {
		count++;
		model->Move(0, 2, 0);
		if (count >= 120) {
			End_flag = true;
		}
	}
}
void SOSHuman::Start() {
	Start_flag = true;
}
void SOSHuman::Hit() {
	Hit_flag = true;
	model->SetTexture(*hit_sprite);
}
void SOSHuman::Draw() {
	if (Start_flag ) {

	}

}
void SOSHuman::Efect_Draw() {
	if (Start_flag) {
		if (!End_flag) {
			model->Draw();
		}
	}

	//human.Draw();

}