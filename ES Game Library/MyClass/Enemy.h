#pragma once
class Player;
#include "../ESGLib.h"
#include"enum.h"
#include"Ground.h"
#include "Player.h"
#include"Efect.h"
class Enemy_Base {
public:

	void Initialize(Vector3 pos,float scale,int speed_, LPCTSTR MODEL);
	void Reset();
	 void Main(Ground &ground_,Player &player);
	 void Hit_Reaction();
	 void Move(Ground &ground_,Player &player) ;
	 void Shot_Hit();//�e�������������̃��A�N�V���� 
	 void Efect_Draw();
	 void exp();//����
	 void Draw();
	 MODEL re_enemy() { return enemy; };
	 bool re_end_flag() { return end_flag; };
	 int re_pattern(){ return enemy_pattern; }

	 //---------------------------------------
	 //��<�ǉ��֐�> �X�s�[�h����
	 //---------------------------------------
	 void Enemy_Base::SpeedControl();

private:
	Efect efect;//�G�t�F�N�g�N���X
	MODEL enemy;
	MODEL  enemy_prefab;
	OrientedBoundingBox  enemy_obb;
     //����
	MODEL exp_model;
	SPRITE exp_sprite;
	bool exp_flag;
	float exp_flame;
	float exp_size;
	Vector3 efect_pos;
	Vector3 pos_hosei;
	//�e�N�X�`��&�}�e���A��
	Material material;
	Material hit_material;
	SPRITE null_sprite;
	SPRITE rock_sprite;
	IDirect3DBaseTexture9* tenp_sprite;
	Material tenp_material;

	bool hit_flag;
	int count;
	bool end_flag;
	float thetai;
	int move_state;
	
	int enemy_pattern;

	//--------------------------------------------------------
	//���p�����[�^
	//�E���D�݂̐��l�ɒ������Ă�������
	//--------------------------------------------------------

	//�z�[�~���O����(0�ɂȂ�ƃz�[�~���O�����߂��Ⴄ��!)
	int HomingFrame = 65535;

	//���݈ړ�����(�����l)
	float Kyou_x_Aya = 90;

	//���ݑ��x(����)
	float Speed = 0.01f;

	//�ō����x
	float MaxSpeed = 1.5f;

	//1F������̉����x
	float AddSpeed = 0.05f;

	//�z�[�~���O�̐��x�Z�C��!!!!!!!!!!!!!!!!(0.0�`1.0 1.0�ɋ߂��قǐ��x�������Ȃ�Z�C��!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
	float SEIYASEIYA = 0.9f;
};
//�����Ȃ�
//class Enemy_0 :public Enemy_Base {
//public:
//	virtual ~Enemy_0() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//
//};
////���ɗ����
//class Enemy_1 :public Enemy_Base {
//public:
//	virtual ~Enemy_1() {}
//	virtual  void Move(std::vector<Ground> &ground_, Player player);
//};
////�E�ɗ����
//class Enemy_2 :public Enemy_Base {
//public:
//	virtual ~Enemy_2() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////���ɗ����
//class Enemy_3 :public Enemy_Base {
//public:
//	virtual ~Enemy_3() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////��ɗ����
//class Enemy_4 :public Enemy_Base {
//public:
//	virtual ~Enemy_4() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////�g�ړ��@�E���獶
//class Enemy_5 :public Enemy_Base {
//public:
//	virtual ~Enemy_5() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////���Ă���
//class Enemy_6 :public Enemy_Base {
//public:
//	virtual ~Enemy_6() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
//class Enemy_7 :public Enemy_Base {
//public:
//	virtual void Initialize(Vector3 pos, float scale, int speed_, LPCTSTR MODEL);
//	virtual ~Enemy_7() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//private:
//	float move_count;
//	float move_random;
//	float rotation_count;
//	float rotation_random;
//};
//class Enemy_8 :public Enemy_Base {
//public:
//	virtual ~Enemy_8() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
//class Enemy_9 :public Enemy_Base {
//public:
//	virtual ~Enemy_9() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
//class Enemy_10 :public Enemy_Base {
//public:
//	virtual ~Enemy_10() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
