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
	 void Shot_Hit();//弾が当たった時のリアクション 
	 void Efect_Draw();
	 void exp();//爆発
	 void Draw();
	 MODEL re_enemy() { return enemy; };
	 bool re_end_flag() { return end_flag; };
	 int re_pattern(){ return enemy_pattern; }

	 //---------------------------------------
	 //◆<追加関数> スピード制御
	 //---------------------------------------
	 void Enemy_Base::SpeedControl();

private:
	Efect efect;//エフェクトクラス
	MODEL enemy;
	MODEL  enemy_prefab;
	OrientedBoundingBox  enemy_obb;
     //爆発
	MODEL exp_model;
	SPRITE exp_sprite;
	bool exp_flag;
	float exp_flame;
	float exp_size;
	Vector3 efect_pos;
	Vector3 pos_hosei;
	//テクスチャ&マテリアル
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
	//◆パラメータ
	//・お好みの数値に調整してください
	//--------------------------------------------------------

	//ホーミング時間(0になるとホーミングを辞めちゃうヨ!)
	int HomingFrame = 65535;

	//現在移動方向(初期値)
	float Kyou_x_Aya = 90;

	//現在速度(初速)
	float Speed = 0.01f;

	//最高速度
	float MaxSpeed = 1.5f;

	//1F当たりの加速度
	float AddSpeed = 0.05f;

	//ホーミングの精度セイヤ!!!!!!!!!!!!!!!!(0.0～1.0 1.0に近いほど精度が高くなるセイヤ!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
	float SEIYASEIYA = 0.9f;
};
//動かない
//class Enemy_0 :public Enemy_Base {
//public:
//	virtual ~Enemy_0() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//
//};
////左に流れる
//class Enemy_1 :public Enemy_Base {
//public:
//	virtual ~Enemy_1() {}
//	virtual  void Move(std::vector<Ground> &ground_, Player player);
//};
////右に流れる
//class Enemy_2 :public Enemy_Base {
//public:
//	virtual ~Enemy_2() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////下に流れる
//class Enemy_3 :public Enemy_Base {
//public:
//	virtual ~Enemy_3() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////上に流れる
//class Enemy_4 :public Enemy_Base {
//public:
//	virtual ~Enemy_4() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////波移動　右から左
//class Enemy_5 :public Enemy_Base {
//public:
//	virtual ~Enemy_5() {}
//	virtual void Move(std::vector<Ground> &ground_, Player player);
//};
////ついてくる
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
