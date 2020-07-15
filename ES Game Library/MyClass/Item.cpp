#include "Item.h"

void Coin_Item::Initialize( Vector3 pos,int coin_type) {
	item = GraphicsDevice.CreateModelFromFile(_T("Item/coin/coin.X"));
	if (coin_type == RED) {
		item = GraphicsDevice.CreateModelFromFile(_T("Item/coin/coin1.X"));
	}
	if (coin_type == GREEN) {
		item = GraphicsDevice.CreateModelFromFile(_T("Item/coin/coin2.X"));

	}
	if (coin_type == BLUE) {
		item = GraphicsDevice.CreateModelFromFile(_T("Item/coin/coin3.X"));

	}

	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	item->SetMaterial(material);
	item->SetPosition(pos);
	item->SetScale(7.0f);
	OrientedBoundingBox obb = item->GetOBB();//ゲートのOBB取得
	SimpleShape box;//ボックスを生成
	box.Type = Shape_Box;
	box.Width = obb.Radius.x * 2;
	box.Height = obb.Radius.y * 2;
	box.Depth = obb.Radius.z * 10;
	item_prefab = GraphicsDevice.CreateModelFromSimpleShape(box);
	item_prefab->SetPosition(pos);
	item_get_flag = false;
	efect_flag = false;
	efect_flame = 0;
}
void Coin_Item::Setpos(Vector3 pos) {
	item->SetPosition(pos);
	item_get_flag = false;

}
int BoolInt(bool Unco) {
	if (Unco) {
		return 1;
	}
	else {
		return -1;
	}
}

int Oor1() {
	int Dialga = MathHelper_Random(0, 100);

	if (Dialga > 50) return 1;
	return -1;
}

void Coin_Item::Reset() {
	item_get_flag = false;
	efect_flag = false;
	efect_flame = 0;

}
void Coin_Item::Update() {
	if (efect_flag) {
		efect_flame += 0.2;

		if (efect_flame >= 7) {
			efect_flag = false;
		}
	}

}
void Coin_Item::Set() {
     item_prefab->SetPosition(item->GetPosition());
}
void Coin_Item::Hit() {
	item_get_flag = true;
	efect_flag = true;
}
void Coin_Item::Draw() {
	if (!item_get_flag) {
		item->Draw();
		item->Rotation(0, 0, 2);
	}
	else {
	}
}
void Coin_Item::Efect_Draw() {

}

void Sigen_Item::Initialize(Vector3 pos,int item_type) {
	if (item_type==RED) {
		item = GraphicsDevice.CreateModelFromFile(_T("Item/box_red.X"));
	}
	if (item_type == GREEN) {
		item = GraphicsDevice.CreateModelFromFile(_T("Item/box_green.X"));

	}
	if (item_type == BLUE) {
		item = GraphicsDevice.CreateModelFromFile(_T("Item/box_blue.X"));

	}
	item->SetPosition(pos);
	item_get_flag = false;
	StartFlag = false;
	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	item->SetMaterial(material);
	sigen_type_ = item_type;
}
void Sigen_Item::Setpos(Vector3 pos) {
	item->SetPosition(pos);
	item_get_flag = false;
	StartFlag = false;

}
void Sigen_Item::Hit() {
	item_get_flag = true;
}
void Sigen_Item::Draw() {
	if (StartFlag) {
		if (!item_get_flag) {
			item->Rotation(0, 2, 0);
			item->Draw();
		}
	}
}
//file_nameにモデルの場所を入力
void Item_base::setImage(char* file_name) {
	char* msg = file_name;
	wchar_t* wmsg = new wchar_t[strlen(msg) + 1];
	mbstowcs(wmsg, msg, strlen(msg) + 1);

	Item = GraphicsDevice.CreateModelFromFile(wmsg);

}
//それぞれの数値を自由にいじれるように改良
void Item_base::SetBoxRadius(float Rx, float Ry, float Rz) {
	x = Rx; y = Ry; z = Rz;
}
//setposとsetscaleを統合ここで位置と大きさをいじれる
void Item_base::SetPosAndSetScale(Vector3 pos, float scale) {
	ItemPos = pos;
	Item->SetPosition(ItemPos);
	Item->SetScale(scale);
	OrientedBoundingBox obb = Item->GetOBB();//ゲートのOBB取得
	SimpleShape box;//ボックスを生成
	box.Type = Shape_Box;
	box.Width = obb.Radius.x * x;//2
	box.Height = obb.Radius.y * y;//2
	box.Depth = obb.Radius.z * z;//10
	ItemPrefab = GraphicsDevice.CreateModelFromSimpleShape(box);
	ItemPrefab->SetPosition(ItemPos);
	item_X_speed = (MathHelper_Random(0.0f, 30.0f) / 10.0f) * Oor1();
	//Y初期値
	item_G = (MathHelper_Random(20.0f, 36.0f) / 10.0f);
	item_G_time = 0;
	itemX_addSpeed = 0.025f;
	itemX_MaxSpeed = 0.0f;
}
void Item_base::move() {



	//float item_Y_speed = 0;

	item_G_time += 1.0f;

	Vector3 angle = Item->GetPosition();

	if (itemX_MaxSpeed == 0.0f) {
		if (item_X_speed > 0.0f) item_X_speed = max(item_X_speed - abs(itemX_addSpeed), 0.0f);
		if (item_X_speed < 0.0f) item_X_speed = min(item_X_speed + abs(itemX_addSpeed), 0.0f);

	}
	else
	{
		if (itemX_MaxSpeed > 0.0f) item_X_speed = min(item_X_speed + itemX_addSpeed, itemX_MaxSpeed);
		if (itemX_MaxSpeed < 0.0f) item_X_speed = max(item_X_speed + itemX_addSpeed, itemX_MaxSpeed);
	}


	//angle.y += MathHelper_Random(1.0f, 2.0f);

	if (item_G_time < 90) {
		item_G = max(item_G - 0.05f, -2.0f);
	}
	else
	{
		item_G = 0;
		item_X_speed = 0;

	}
	angle.x += item_X_speed;
	angle.y += item_G;
	Item->SetPosition(angle);
}

void Item_base::Draw() {
	if(!EndFlag)
	Item->Draw();
}



ItemBattery::ItemBattery() {


	setImage("Item/battery/battery.X");
	SetBoxRadius(2, 2, 10);
	SetPosAndSetScale(mypos, 1.0f);
	move();
}

void ItemBattery::draw() {
	Item_base::Draw();
}

