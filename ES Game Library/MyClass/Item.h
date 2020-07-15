#pragma once
#include "../ESGLib.h"
#include"enum.h"
#include"Efect.h"
enum Item_Type {
	TYPE_NONE,
	TYPE_COIN,
	TYPE_BATTERY
};

class Coin_Item {
public:
	void Initialize( Vector3 pos,int coin_type);
	void Setpos(Vector3 pos);
	void Reset();
	void Set();
	void Hit();
	void Draw();
	void Efect_Draw();
	void Update();
	//これが実行されたらエフェクトを表示する
	MODEL re_model() { return item; }
	bool re_flag() { return item_get_flag; }
	int re_id() { return model_id_; }

protected:
	Efect efect;
	MODEL item;
	MODEL item_prefab;
	bool item_get_flag;
	int model_id_;
	float efect_flame;
	bool efect_flag;

};
class Sigen_Item {
public:
	void Initialize(Vector3 pos, int coin_type);
	void Setpos(Vector3 pos);
	void Hit();
	void Draw();
	void Start() { StartFlag = true; }
	MODEL GetModel() { return item; };
	bool GetStartFlag() { return StartFlag; }
	bool GetEndFlag() { return item_get_flag; }
	int GetItemType() { return sigen_type_; }
	Vector3 GetPos() { return item->GetPosition(); }
private:
	MODEL item;
	int sigen_type_;
	bool StartFlag;
	bool item_get_flag;
};

class Item_base
{
	bool remove_flag;
public:
	Item_base() {}
	void SetPosAndSetScale(Vector3 pos, float scale);
	void SetBoxRadius(float Rx, float Ry, float Rz);
	bool isRemove() { return remove_flag; }
	void Draw();
	void move();
	void setImage(char*);
	MODEL GetModel() { return Item; }
	virtual Item_Type getType() = 0;
	void hit() { EndFlag = true; }
	bool GetEndFlag() { return EndFlag; }
private:
	//アイテムのモデル
	MODEL Item;
	//アイテムのプレハブ
	MODEL ItemPrefab;
	//アイテムの座標
	Vector3 ItemPos;

	bool EndFlag = false;

	
	//プレハブの大きさ設定数値
	int x, y, z;
	float item_X_speed = 0;
	float item_G;
	float item_G_time = 0;

	float itemX_addSpeed;
	float itemX_MaxSpeed;
};


class ItemBattery :public Item_base {
public:
	ItemBattery();
	Item_Type getType() { return TYPE_BATTERY; }
	void draw();
	void Setpos(Vector3 pos);
	static const int NUM = 3;
private:
	Vector3 mypos;

};
