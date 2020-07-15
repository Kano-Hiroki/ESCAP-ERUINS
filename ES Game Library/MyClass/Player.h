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
	//プレイヤー
	void PlayerUpdate(Ground &ground, std::vector<Enemy_Base> &enemy, std::vector<SOSHuman>&human, Sigen_Item *item);
	//ポジションをセット
	void SetPosition(Vector3 pos);
	//移動
	void PlayerMove(Ground &ground);
	void Grabity(int houkou);
	//壁に当たった時に跳ね返る
	void Reflection(Ground &ground_);
	//ライト
	void light_control();
	//描画
	void Draw();
	void Alpha_Draw();
	//ウィグラー
	//UI
	void Ui();
	void Enemy_hit();//敵に当たったとき
	//レーダー
	void radar(Sigen_Item *item);
   //バッテリー
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
	//カメラ
	CAMERA main_camera;
	CAMERA fps_camera;
	//ライト
	MODEL light_model;
	

	Light Main_light;
	Light point_light;
	Light player_light[2];
	float point_light_Theta;
	OrientedBoundingBox light_OBB;
	MODEL light_prefab;
	float light_model_width;
	bool light_flag;//ライトオンオフ
	//キーボード&マウス
	KeyboardBuffer key_buffer;
	KeyboardState key_state;
	MouseState mouse_state;
	MouseBuffer mouse_buffer;

	//ゲームパッド
	GamePadState pad_state;
	GamePadBuffer pad_buffer;

	ANIMATIONMODEL player;
	MODEL houdai;

	Vector3 camera_pos;//カメラ座標
	//反射
	bool reflection_flag = false;
	int reflection_count = 0;
	Vector3 hansya;
	Vector3 F;
	//バリア
	bool barrier_flag = false;
	Vector3 barrier_pos;
	SPRITE barrier_;
	//ブースト
	int boost;
	int boost_switch;
	int boost_recharge;


	int p_move_state;//現在の移動方向
	MODEL player_prefab;//当たり判定用
	
	Material mtrl;

	Vector3 ply_pos;
	//FPSカメラワーク//
	//マウス
	MODEL mouse;
	Vector3 mouse_pos;	//マウスの座標
	//ヒット
	bool tenmetsu_flag;
	int count_;

	//移動速度
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
	//バッテリー
	static const int BATTERY_MAX;	//体力の最大値
	static const Vector2 BATTERY_UI_OUTER_SIZE;//ゲージ外枠の大きさ
	static const Vector2 BATTERY_UI_INNER_SIZE;//ゲージ中身の大きさ
	static const Vector3 BATTERY_UI_POSITION;//ゲージ表示位置
	static const Vector3 BATTERY_UI_INNER_RIVISION;//ゲージの中身の位置の調整

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
	//レーダー
	Vector3 light_spot[100];
	int radar_time;

	float xxx[100];
	float yyy[100];


	SPRITE radar_base;

	float distance[100];

	Vector3 p_point;
	Vector3 def;
	//重力
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
	//爆発エフェクト
	Efect efect;
	float exp_flame;
	bool end_flag;
	Vector3 Start_Pos;
	//マテリアル
	Material tenp_material;
	Material hit_material;
	int heal_count=0;
	int player_anim_statet;
	double   anim_time;
	int track_mode;
	int track_mode_time;
	//カメラ揺れ用
	Vector3 YureYuri = Vector3_Zero;//揺れベクトル
	float YurePower = 0.0f;//揺れるカ
	SPRITE radar_point[3];
};
