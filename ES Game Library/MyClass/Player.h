#pragma once
class Enemy_Base;
#include"../ESGLib.h"
#include "Enemy.h"
#include "Ground.h"
#include "Object.h"
#include "enum.h"
#include"SOSHuman.h"
#include"Efect.h"
#include"BatteryGauge.h"
#include"Item.h"
class Player {
public:
	void Initialize();
	void Reset();
	//�v���C���[
	void PlayerUpdate(Ground &ground, std::vector<Enemy_Base> &enemy, std::vector<SOSHuman>&human, Sigen_Item *item);
	//�|�W�V�������Z�b�g
	void SetPosition(Vector3 pos);
	//�ړ�
	void PlayerMove(Ground &ground);
	void Grabity(int houkou);
	//�ǂɓ����������ɒ��˕Ԃ�
	void Reflection(Ground &ground_);
	//���C�g
	void light_control();
	//�`��
	void Draw();
	void Alpha_Draw();
	//�E�B�O���[
	//UI
	void Ui();
	void Enemy_hit();//�G�ɓ��������Ƃ�
	//���[�_�[
	void radar(Sigen_Item *item);
   //�o�b�e���[
	void battery_charge(int a);
	void battery_heal();
	void battery_damage();
	void battery_heal_state(int a);
	void Hit_Coin();
	void Player_End();
	void Heel_Efect();
	

	MODEL re_ply_prefab() { return player_prefab; }
	ANIMATIONMODEL re_player() { return player; }
	MODEL re_right_model() { return light_prefab; }
	CAMERA re_camera() { return main_camera; }
	bool GetEndFlag() {return end_flag; }
	void Wiggler(float randam);
	void Light_Start(bool light_mode);
private:
	FONT DefaultFont;
	BatteryGauge Battery_Gauge;
	//�J����
	CAMERA main_camera;
	CAMERA fps_camera;
	//���C�g
	MODEL light_model;
	

	Light Main_light;
	Light point_light;
	Light player_light[2];
	float point_light_Theta;
	OrientedBoundingBox light_OBB;
	MODEL light_prefab;
	float light_model_width;
	bool light_flag;//���C�g�I���I�t
	//�L�[�{�[�h&�}�E�X
	KeyboardBuffer key_buffer;
	KeyboardState key_state;
	MouseState mouse_state;
	MouseBuffer mouse_buffer;

	//�Q�[���p�b�h
	GamePadState pad_state;
	GamePadBuffer pad_buffer;

	ANIMATIONMODEL player;
	MODEL houdai;

	Vector3 camera_pos;//�J�������W
	//����
	bool reflection_flag = false;
	int reflection_count = 0;
	Vector3 hansya;
	Vector3 F;
	//�o���A
	bool barrier_flag = false;
	Vector3 barrier_pos;
	SPRITE barrier_;
	//�u�[�X�g
	int boost;
	int boost_switch;
	int boost_recharge;


	int p_move_state;//���݂̈ړ�����
	MODEL player_prefab;//�����蔻��p
	
	Material mtrl;

	Vector3 ply_pos;
	//FPS�J�������[�N//
	//�}�E�X
	MODEL mouse;
	Vector3 mouse_pos;	//�}�E�X�̍��W
	//�q�b�g
	bool tenmetsu_flag;
	int count_;

	//�ړ����x
	float speed;
	float speed_side;
	float speed_length;
	int speed_state;
	bool tate_move_state;
	bool yoko_move_state;
	Vector3 move;
	Vector3 plus_move;
	Vector3 minus_move;
	int boost_length;
	//�o�b�e���[
	static const int BATTERY_MAX;	//�̗͂̍ő�l
	static const Vector2 BATTERY_UI_OUTER_SIZE;//�Q�[�W�O�g�̑傫��
	static const Vector2 BATTERY_UI_INNER_SIZE;//�Q�[�W���g�̑傫��
	static const Vector3 BATTERY_UI_POSITION;//�Q�[�W�\���ʒu
	static const Vector3 BATTERY_UI_INNER_RIVISION;//�Q�[�W�̒��g�̈ʒu�̒���

	int battery;
	int battery_mode;
	int battery_time;
	int battery_count;
	int battery_heal_time;
	int heal_mode;
	SPRITE battery_sprite;
	SPRITE battery_zanryou;
	int battery_heel_n=0;
	bool battery_heal_flag=false;
	//���[�_�[
	Vector3 light_spot[100];
	int radar_time;

	float xxx[100];
	float yyy[100];


	SPRITE radar_base;

	float distance[100];

	Vector3 p_point;
	Vector3 def;
	//�d��
	Vector3 Grabity_move;

	Vector3 rising_downward;
	float fall_g;
	float fall_up;

	float propeller_rotate;

	Vector3   old_position;

	float dist[100];
	int coin_count;

	float around_;
	Vector3 LR;
	Vector3 UD;
	float p_G;
	//�����G�t�F�N�g
	Efect efect;
	float exp_flame;
	bool end_flag;
	Vector3 Start_Pos;
	//�}�e���A��
	Material tenp_material;
	Material hit_material;
	int heal_count=0;
	int player_anim_statet;
	double   anim_time;
	int track_mode;
	int track_mode_time;
	//�J�����h��p
	Vector3 YureYuri = Vector3_Zero;//�h��x�N�g��
	float YurePower = 0.0f;//�h���J
	SPRITE radar_point[3];
};
