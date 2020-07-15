#include"Enemy.h"

void Enemy_Base::Initialize(Vector3 pos,float scale,int speed_,LPCTSTR model_file) {
	efect.Initialize(0.0625f, 10, (_T("Efect/exp.png")));
	enemy = GraphicsDevice.CreateModelFromFile(model_file);
	enemy->SetScale(scale);//�傫��
	enemy->SetPosition(pos);
	//�}�e���A��
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(0.2f, 0.2f, 0.2f);
	enemy->SetMaterial(material);
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	//�����������̃}�e���A��
	hit_material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	hit_material.Ambient = Color(0.3f, 0.5f, 0.2f);
	hit_material.Emissive = Color(0.5f, 0.5f, 0.0f);
	//�����蔻�萶��
	OrientedBoundingBox obb = enemy->GetOBB();//�Q�[�g��OBB�擾
	SimpleShape box;//�{�b�N�X�𐶐�
	box.Type = Shape_Box;
	box.Width = obb.Radius.x * 1;
	box.Height = obb.Radius.y * 1;
	box.Depth = obb.Radius.z * 1;
	enemy_prefab = GraphicsDevice.CreateModelFromSimpleShape(box);
	//�p�����[�^������
	end_flag = false;
	count = 0;
	hit_flag = false;
	thetai = 0;
	exp_flag = false;
	exp_flame = 0;
	tenp_material = enemy->GetMaterial();
	tenp_sprite = enemy->GetTexture();
	move_state = 0;
}
void Enemy_Base::Reset() {
	//�p�����[�^������
	end_flag = false;
	count = 0;
	hit_flag = false;
	thetai = 0;
	exp_flag = false;
	exp_flame = 0;
	tenp_material = enemy->GetMaterial();
	tenp_sprite = enemy->GetTexture();
	move_state = 0;

}
void Enemy_Base::Main(Ground &ground,Player &player) {
	if (!end_flag) {
	}
	Move(ground, player);//�ړ�����

	//�U���H��������̃��A�N�V����
	if (hit_flag) {
		Hit_Reaction();
	}
	//HP��0�ȉ��ɂȂ����甚�����ď�����
	if (end_flag) {
		exp();
		efect.Update((int)exp_flame,enemy->GetPosition());
	}

}

//�����W�A�����x���ϊ�
//(rad �ϊ��������x��) �߂�l �ϊ����ꂽ���W�A��
float Deg(float rad) {
	return rad * (180 / __PI__);//(�z����g���Ẵ������팸����)
}

//���x�������W�A���ϊ�
//(deg �ϊ����������W�A��) �߂�l �ϊ����ꂽ�x��
float Rad(float deg) {
	return deg * (__PI__ / 180);
}

//�����l�̕����𒲂ׂ�
//�߂�l ���@1 
//�@�@�@�@  �� -1 
//�@�@�@�@�@0
int Sgn(int a) {
	if (a > 0) return 1;
	if (a < 0) return -1;
	return 0;
}

//����
void Enemy_Base::Move(Ground &ground, Player &player) {
	//���x����
	SpeedControl();

	//�z�[�~���O���Ԃ����炷
	HomingFrame = max(HomingFrame-1,0.0f);

	//�ړ���
	Vector3 MovePower = Vector3_Zero;
	//�ړ��ʂ��w��
	MovePower.x = cos(Rad(Kyou_x_Aya)) * Speed;
	MovePower.y = sin(Rad(Kyou_x_Aya)) * Speed;

	//������
	enemy->Move(MovePower);

	//�z�[�~���O���Ԃ��؂�Ă���Ȃ�z�[�~���O�������J�b�g
	if (HomingFrame <= 0)  return;

	//���v�Z�p
	Vector3 PlayerPos = player.re_ply_prefab()->GetPosition();
	Vector3 EnemyPos = enemy->GetPosition();

	//�ړ�����p�x
	float TagetDir = Deg(atan2f( PlayerPos.y - EnemyPos.y , PlayerPos.x - EnemyPos.x ));
	
	//����ʒ����p
	float Saku_x_Hima = TagetDir - Kyou_x_Aya;
	if (Saku_x_Hima >= 180) Saku_x_Hima -= 360;
	if (Saku_x_Hima <= -180) Saku_x_Hima += 360;

	//�ŏI�I�Ȉړ��p�x
	Kyou_x_Aya += (Sgn(Saku_x_Hima)*SEIYASEIYA);
}

//�X�s�[�h����
void Enemy_Base::SpeedControl() {
	if (MaxSpeed>0.0f) {
		Speed = min(Speed + AddSpeed, MaxSpeed);
	}
	else {
		Speed = max(Speed + AddSpeed, MaxSpeed);
	}
}

//�H��������̃��A�N�V����
void Enemy_Base::Hit_Reaction() {
	count++;
	if (count % 6 == 0) {
		enemy->SetTexture((IDirect3DBaseTexture9*)nullptr);//���̃e�N�X�`���[���Z�b�g����
		enemy->SetMaterial(hit_material);
	}
	else {
		enemy->SetTexture(tenp_sprite);//���̃e�N�X�`���[������
		enemy->SetMaterial(tenp_material);

	}
	if (count > 30) {
		enemy->SetTexture(tenp_sprite);
		enemy->SetMaterial(tenp_material);
		hit_flag = false;
		count = 0;
	}
}
//�e�������������̏���
void Enemy_Base::Shot_Hit() {
	if (!hit_flag) {
		hit_flag = true;
		//hit_effeck->Play(enemy->GetPosition());

	}
}
//����
void Enemy_Base::exp() {
	exp_flame += 0.2;

	if (exp_flame >= 9) {
		exp_flag = false;
	}
}
//�`��
void Enemy_Base::Draw() {
	if (!end_flag) {
		enemy->Draw();
		enemy_prefab->SetPosition(enemy->GetPosition());
		enemy_prefab->SetDirection(enemy->GetDirectionQuaternion());

	}
}
void Enemy_Base::Efect_Draw() {
	if (end_flag) {
		efect.Draw();
	}

}


