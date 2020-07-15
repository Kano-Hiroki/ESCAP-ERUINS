#include "Player.h"
//体力最大値の設定
const int Player::BATTERY_MAX = 100;
const float Camera_Hikiguai = 500;

//体力ゲージ関連の設定
const Vector3 Player::BATTERY_UI_POSITION = Vector3(950.0f, 30.0f, 0.0f); //位置
const Vector3 Player::BATTERY_UI_INNER_RIVISION = Vector3(6.0f, 6.0f, 0.0f); //中身を描画する際の位置ずれの補正
const Vector2 Player::BATTERY_UI_OUTER_SIZE = Vector2(299.0f, 38.0f);//外枠のサイズ
const Vector2 Player::BATTERY_UI_INNER_SIZE = Vector2(278.0f, 26.0f);//中身のサイズ

void Player::Initialize() 
{
	//ビューポート
	Viewport   view = GraphicsDevice.GetViewport();

	//カメラ
	main_camera->SetView(Vector3(0.0f, 70.0f, -500.0f), Vector3(00.0f, 0.0f, 00.0f));
	main_camera->SetPerspectiveFieldOfView(45.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(main_camera);
	//レーダー
	radar_point[0] = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar2.png"));
	radar_point[1] = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar3.png"));
	radar_point[2] = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar4.png"));

	//メインライト
	Main_light.Type = Light_Directional;
	Main_light.Diffuse = Color(1.0f, 1.0f, 1.0f); // ディフューズ色
	Main_light.Ambient = Color(1.0f, 1.0f, 1.0f); // アンビエント色
	Main_light.Specular = Color(1.0f, 1.0f, 1.0f); // スペキュラー色
	Main_light.Direction = Vector3(0, 90, 90);

	//ポイントライト(プレイヤーの周りを照らす)
	point_light.Type = Light_Spot;
	point_light.Diffuse = Color(0.5f, 0.5f, 0.5f); // ディフューズ色
	point_light.Specular = Color(0.5f, 0.5f, 0.5f); // スペキュラー色
	point_light.Ambient = Color(0.3f, 0.3f, 0.3f); // アンビエント色
	point_light.Range = 30.0f; // ライトの有効範囲
	point_light.Attenuation0 = 1.0f; // 減衰定数
	point_light.Attenuation1 = 0.0f;
	point_light.Attenuation2 = 0.0f;
	point_light.Range = 1000.0f;
	point_light.Falloff = 1.0f;
	point_light.Direction = Vector3(0,90, 90);
	point_light_Theta = 80.0f;
	point_light.Theta = MathHelper_ToRadians(point_light_Theta);
	point_light.Phi = MathHelper_ToRadians(point_light_Theta+20.0f);

	//スポットライトオンオフ
	light_flag = false;

	//ライトの範囲を表示するモデル
	light_model = GraphicsDevice.CreateModelFromFile(_T("Player/Light.X"));
	light_model->SetScale(3);
	Material mat = light_model->GetMaterial();
	mat.Emissive = Color(0.5f, 0.5f, 0.5f);
	light_model->SetMaterial(mat);

	// 当たり判定生成
	light_OBB = light_model->GetOBB();
	light_model_width = light_OBB.Radius.x;
	SimpleShape light_box;
	light_box.Type = Shape_Box;
	light_box.Width = light_OBB.Radius.x * 2;
	light_box.Height = light_OBB.Radius.y * 2;
	light_box.Depth = light_OBB.Radius.z * 3;
	light_prefab = GraphicsDevice.CreateModelFromSimpleShape(light_box);

    //プレイヤー
	player = GraphicsDevice.CreateAnimationModelFromFile(_T("Player/jiki8.X"));

	player->SetScale(0.15f);
	player->SetPosition(0,0,0);//仮でポジションをセット
	player->SetRotation(0, 0, 0);
	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	player->SetMaterial(material);
	tenp_material = material;
	//ヒール時のマテリル
	hit_material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	hit_material.Ambient = Color(1.0f, 1.0f, 1.0f);
	hit_material.Emissive = Color(1.0f, 1.0f, 1.0f);
	//ブースト
	boost = 0;
	boost_length = 0;
	boost_switch = 0;
	boost_recharge = 0;

	//スピード
	speed = 0;

	//マウス
	material.Diffuse = Color(1.0f, 0.0f, 0.0f);
	material.Ambient = Color(1.0f, 0.0f, 0.0f);

	material.Emissive = Color(1.0f, 0.0f, 0.0f);

	mouse = GraphicsDevice.CreateModelFromFile(_T("UI/Reticle.x"));
	mouse->SetMaterial(material);

	//当たり判定生成
	//プレイヤー
	OrientedBoundingBox pl_obb = player->GetOBB();//ゲートのOBB取得
	SimpleShape pl_box;//ボックスを生成
	pl_box.Type = Shape_Box;
	pl_box.Width = pl_obb.Radius.x * 20;
	pl_box.Height = pl_obb.Radius.y * 5;
	pl_box.Depth = pl_obb.Radius.z * 3;//ゲートと大きさを合わせる
	player_prefab = GraphicsDevice.CreateModelFromSimpleShape(pl_box);
	//ライト

	DefaultFont = GraphicsDevice.CreateSpriteFont(_T("メイリオ"),50);
	//点滅
	tenmetsu_flag = false;
	count_ = 0;
    //点滅で使うカウント
	//エフェクトをカメラにセット	
	//---------------------------------------------------------------------
	//バッテリー
	battery_mode = 0;

	battery = 500;
	battery = 100;
	battery_heal_time = 0;
	battery_count = 0;
	battery_time = 0;
	battery_sprite = GraphicsDevice.CreateSpriteFromFile(_T("UI/battery1.png"));
	battery_zanryou = GraphicsDevice.CreateSpriteFromFile(_T("UI/battery2.png"));
	speed_length = 0;
	speed_side = 0;
	mouse_pos = Vector3(player->GetPosition());

	//camera_stste = 0;
	plus_move = Vector3(0, 0, 0);
	minus_move = Vector3(0, 0, 0);
	move = Vector3(0, 0, 0);

	//レーダー
	radar_time = 120;
	radar_base = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar.png"));
	Grabity_move = Vector3(0, 0, 0);

	rising_downward = Vector3(0, 0, 0);
	fall_g  = 0;
	fall_up = 0;

	propeller_rotate = 0;
	//バリア
	barrier_ = GraphicsDevice.CreateSpriteFromFile(_T("Efect/barrier3.png"));
	//コインの入手数
	coin_count = 0;
	around_    = 0;
	p_G        = 0;
	UD = Vector3(0, 0, 0);
	LR = Vector3(0, 0, 0);
	//エフェクト初期化
	efect.Initialize(0.0625f, 10, (_T("Efect/exp.png")));
	exp_flame = 0;
	end_flag = false;
	BatteryGauge::LoadSprite();//バッテリー画像読み込み
	Battery_Gauge.Initialize();//バッテリー初期化
	player->SetTrackEnable(1, FALSE);
	player->SetTrackEnable(2, FALSE);
	player->SetTrackLoopMode(0, AnimationLoopMode_Once);
	player_anim_statet = FALSE;
	track_mode_time = 0;	

}
void Player::Reset() {
	//スポットライトオンオフ
	light_flag = false;

	//ライトの範囲を表示するモデルb
	light_model->SetScale(3);
	Material mat = light_model->GetMaterial();
	mat.Emissive = Color(0.5f, 0.5f, 0.5f);
	light_model->SetMaterial(mat);

	// 当たり判定生成

	player->SetScale(0.15f);
	player->SetPosition(0, 0, 0);//仮でポジションをセット
	player->SetRotation(0, 0, 0);

	//ブースト
	boost = 0;
	boost_length = 0;
	boost_switch = 0;
	boost_recharge = 0;

	//スピード
	speed = 0;

	//点滅
	tenmetsu_flag = false;
	count_ = 0;
	//点滅で使うカウント
	//エフェクトをカメラにセット	
	//---------------------------------------------------------------------
	//バッテリー
	battery_mode = 0;

	battery = 500;
	battery = 100;
	battery_heal_time = 0;
	battery_count = 0;
	battery_time = 0;
	speed_length = 0;
	speed_side = 0;
	mouse_pos = Vector3(player->GetPosition());

	//camera_stste = 0;
	plus_move = Vector3(0, 0, 0);
	minus_move = Vector3(0, 0, 0);
	move = Vector3(0, 0, 0);

	//レーダー
	radar_time = 120;
	Grabity_move = Vector3(0, 0, 0);

	rising_downward = Vector3(0, 0, 0);
	fall_g = 0;
	fall_up = 0;

	propeller_rotate = 0;
	//バリア
	//コインの入手数
	coin_count = 0;
	around_ = 0;
	p_G = 0;
	UD = Vector3(0, 0, 0);
	LR = Vector3(0, 0, 0);
	//エフェクト初期化
	exp_flame = 0;
	end_flag = false;
	player->SetPosition(Start_Pos);
	main_camera->SetPosition(Vector3(Start_Pos.x, Start_Pos.y, Camera_Hikiguai));
	old_position = Start_Pos;
	ply_pos = Start_Pos;
	Battery_Gauge.Initialize();//バッテリー初期化
}
//マップから初期座標を反映
void Player::SetPosition(Vector3 pos) 
{
	player->SetPosition(pos);
	old_position = pos;
	ply_pos      = pos;
	main_camera->SetPosition(Vector3(pos.x,pos.y,Camera_Hikiguai));
	Start_Pos = pos;
}
//全てを統括
void Player::PlayerUpdate(Ground &ground_,std::vector<Enemy_Base> &enemy, std::vector<SOSHuman>&human, Sigen_Item *item)
{
	key_buffer = Keyboard->GetBuffer();
	key_state = Keyboard->GetState();
	mouse_state = Mouse->GetState();
	mouse_buffer = Mouse->GetBuffer();
	pad_buffer = GamePad(0)->GetBuffer();
	pad_state = GamePad(0)->GetState();
	old_position = player->GetPosition();
	PlayerMove(ground_);
	radar(item);
	efect.Update((int)exp_flame, player->GetPosition()+Vector3(0,0,-100));//エフェクト
	if (battery <= 0) 
	{
		Player_End();

		if (Battery_Gauge.GetChangingState() == CHANGING_STATE_NONE) 
		{
			;
		}
	}

	if (Battery_Gauge.GetChangingState() == CHANGING_STATE_UP) 
	{
		Heel_Efect();
	}
	else 
	{
		player->SetMaterial(tenp_material);
	}

	light_control();
	player_prefab->SetPosition(player->GetPosition());
	GraphicsDevice.SetCamera(main_camera);
	Battery_Gauge.Update();
	Battery_Gauge.SetTargetPersent((float)battery / (float)Player::BATTERY_MAX);
	
	if (battery >= 100) { battery = 100; }
}
//lerp補間
Vector3 Vector3_Lerp(Vector3 A, Vector3 B, float t) {

	Vector3 YuiKyou = Vector3_Zero;

	YuiKyou.x = MathHelper_Lerp(A.x, B.x, t);
	YuiKyou.y = MathHelper_Lerp(A.y, B.y, t);
	YuiKyou.z = MathHelper_Lerp(A.z, B.z, t);

	return YuiKyou;
}

//移動を統括
void Player::PlayerMove(Ground &ground_)
{
	battery_charge(heal_mode);

	//バッテリー管理テスト用

	ply_pos = player->GetPosition();

	Vector3  up = player->GetUpVector();

	//----------------------------------------------------------------------------------------------
	//上昇下降
	if (player_anim_statet == 0) //上昇
	{
		anim_time += 0.02f;

		if (anim_time > 1.0f)
		{
			anim_time = 1.0f;
		}
		player->SetTrackPosition(0, anim_time);

		track_mode_time++;
		if (track_mode_time >= 120)
		{
			player_anim_statet = 1;
			anim_time = 0.7;
		}
	}
	else if (player_anim_statet == 1) //下降
	{
		anim_time -= 0.02f;
		if (anim_time < 0)
		{
			anim_time = 0;
		}
		player->SetTrackPosition(0, anim_time);
	}

	if (key_buffer.IsPressed(Keys_Up) || pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) ||
		pad_buffer.IsPressed(GamePad_Button3) || pad_buffer.IsPressed(GamePad_Button4))
	{
		if (anim_time >= 0) 
		{
			;
		}
		else 
		{
			anim_time = 0;

		}
		player_anim_statet = 0;
	}

	if (key_state.IsKeyDown(Keys_Up) || pad_state.Buttons[1]) 
	{
		track_mode_time = 0;
		if (anim_time >= 0.5)
		{
			player->SetTrackEnable(1, TRUE);
			player->SetTrackPosition(1, propeller_rotate / 7);
		}

		//上昇速度の加算
		p_G -= 0.045f;
		propeller_rotate += 0.15f;
		battery_time++;
		rising_downward.x++;
	}
	else
	{
		player->SetTrackEnable(1, FALSE);
		p_G += 0.0425f;
		propeller_rotate -= 0.015f;
		rising_downward.x--;
	}

    //プロペラの回転はマイナスにならない//
	if (propeller_rotate <= 0) { propeller_rotate = 0; }

	//重力を計算  *1
	if (p_G < -2) { p_G = -2; }

	//落下最大速度はここできめよう!
	p_G = min(p_G, 3.0f);

	//プレイヤーのy軸に重力を加算
	ply_pos.y -= p_G;

	//デバッグ----------------------------------------
	if (key_state.IsKeyDown(Keys_Left))
	{
		LR.x -= 0.5f;
	}
	if (key_state.IsKeyDown(Keys_Right))
	{
		LR.x += 0.5f;
	}

	if (Axis_Center != (float)pad_state.X) 
	{
		LR += Vector3_Right * (((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center)) / 10.0f;// / 20;
		if (Vector3_Length(LR) > 10.0f) 
		{
			LR = Vector3_Normalize(LR) * 10.0f;
		}
	}
	else 
	{
		LR *= 0.95f;
	}

	ply_pos += LR;

	rising_downward.z = -60.0f*(((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center));

	player->SetRotation(rising_downward);

	if (battery_time >= 180.0f) //バッテリータイムが○○を越えたら
	{
		battery_time = 0.0f;
		battery--; //バッテリーを1減らす
	}

	player->SetPosition(ply_pos); //上昇下降

	if (rising_downward.x >= 20.0f) //上昇角度最大値
	{
		rising_downward.x = 20.f;
	}
	if (rising_downward.x <= -25.0f) //下降角度最大値
	{
		rising_downward.x = -25.0f;
	}

	//-------------------------------------------------------------------------

	//左右角度最大値
	rising_downward.z -= 10.0 * (((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center));

	//左右角度最大値
	if (rising_downward.z >= 45)
	{
		rising_downward.z = 45;
	}
	else if (rising_downward.z <= -45)
	{
		rising_downward.z = -45;
	}

	player->SetRotation(rising_downward);

	//ライト関係---------------------------------------
	Reflection(ground_);

	//揺れ
	YurePower = max(YurePower - 0.5f, 0.0f);
	YureYuri.x = MathHelper_Random(-1.0f, 1.0f)*YurePower;
	YureYuri.y = MathHelper_Random(-1.0f, 1.0f)*(YurePower*2.0f);

	//カメラ
	main_camera->SetPosition(Vector3_Lerp(main_camera.GetPosition(), ply_pos - Vector3(-LR.x*30.0f, p_G * 20, Camera_Hikiguai), 0.05f) + YureYuri);
}

//壁反射
void Player::Reflection(Ground &ground_) {
	float kabe_r = FLT_MAX;
	float kabe_l = FLT_MAX;
	float kabe_u = FLT_MAX;
	float kabe_d = FLT_MAX;
	float  min_dist_r = FLT_MAX;
	float  min_dist_l = FLT_MAX;
	float  min_dist_u = FLT_MAX;
	float  min_dist_d = FLT_MAX;
	Vector3 hozon_r;
	Vector3 hozon_l;
	Vector3 hozon_u;
	Vector3 hozon_d;

	Vector3 N_R;
	Vector3 N_L;
	Vector3 N_U;
	Vector3 N_D;
	Vector3 N;

	Vector3   pos = player->GetPosition();
	pos.z = 0.0f;
	old_position.z = 0.0f;
	Vector3   dir = Vector3_Normalize(pos - old_position);//今の座標と1f前の座標で角度を求める
  //レイを飛ばす------------------------------------------------------------------------------------------------------------------------------
		min_dist_u = FLT_MAX;
		hozon_u = Vector3_Zero;
		ground_.re_ground()->IntersectRay(pos, dir, &min_dist_u, &hozon_u);//壁判定
		if (min_dist_u < kabe_u) 
		{
			kabe_u = min_dist_u;
			N_U = hozon_u;
		}
	
	//当たったかを調べる------------------------------------------------------------------------------------------------------------------------------

	if (kabe_u < 15) 
	{
		N = N_U;
		F = dir;//進行ベクトル
		hansya = F + 2 * Vector3_Dot(-F, N)*N;//反射ベクトル
		reflection_count = 5;//反射の強さ
		if (!barrier_flag) //バリアを張ってなければダメージ
		{
			battery -= 5;
		}
		LR = Vector3_Zero;
		p_G = 0;
		reflection_flag = true;
		barrier_flag = true;
	}

	//当たった時の処理
	if (reflection_flag) 
	{
		//揺れセット
		YurePower = 5.0f;

		reflection_count--;
		hansya.z = 0;
		ply_pos += hansya * reflection_count;
		//当たったかを取る------------------------------------------------------------------------------------------------------------------------------

		if (kabe_u < 15) //壁じゃなかったら動く
		{
			F = dir;//進行ベクトル

			hansya = F + 2 * Vector3_Dot(-F, N_U)*N_U;//反射ベクトル
			reflection_count = 5;
			reflection_flag = true;
			barrier_flag = true;
			LR = Vector3_Zero;
			p_G = 0;
		}

		if (reflection_count <= 0) {
			reflection_flag = false;

		}
	}
	player->SetPosition(ply_pos);
}
//ゲームオーバー処理
void Player::Player_End() {
	exp_flame += 0.2;

	if (exp_flame >= 9) 
	{
		end_flag = true;
	}
}
void Player::Heel_Efect() {
	heal_count++;
	if (heal_count % 6 == 0) 
	{
		player->SetMaterial(hit_material);
	}
	else 
	{
		player->SetMaterial(tenp_material);

	}

}
//ライト関係
void Player::light_control() 
{

	//ポイントライト風(プレイヤーの周りを照らす)
	point_light.Position = player->GetPosition() + Vector3(0, 0, -200);
	point_light.Direction = Vector3_Forward;
	point_light.Theta = MathHelper_ToRadians(point_light_Theta);
	point_light.Phi = MathHelper_ToRadians(point_light_Theta + 20.0f);

	//ライトをセット
	
	if (light_flag) 
	{
		//ライトオフ
		GraphicsDevice.SetLight(point_light, 1,1);
		GraphicsDevice.SetLight(Main_light, 999999,0);

	}
	else
	{
		//ライトオン
		GraphicsDevice.SetLight(point_light, 1,0);
		GraphicsDevice.SetLight(Main_light, 999999,1);
	}
}

void Player::Light_Start(bool a) {
	light_flag = a;
}

//攻撃を受けた時のリアクション
void Player::Enemy_hit() 
{
	if (!tenmetsu_flag) 
	{
		tenmetsu_flag = true;
	}
}
void Player::Hit_Coin() {
	coin_count++;
}
//バッテリー関係
void Player::battery_charge(int a)
{
	if (battery < 100)
	{
		if (a == 99)
		{
			;
		}
		if (a == 0) //バッテリー回復(極小)
		{
			battery_heal(); //バッテリー回復
			if (battery_count >= 2) //バッテリー回復量
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 1) //バッテリー回復(少)
		{
			battery_heal();
			if (battery_count >= 10)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 2) //バッテリー回復(ノーマル)
		{
			battery_heal();
			if (battery_count >= 20)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 3) //バッテリ全回復(大)
		{
			battery_heal();
			if (battery_count >= 50)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 4) //バッテリー全回復
		{
			battery_heal();
			if (battery_count >= 100)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 10) //ダメージの発生
		{
			battery_damage();
			if (battery_count >= 25) 
			{
				battery_count = 0;
			}
		}
	}
}
void Player::battery_heal()
{
	battery_heal_time++;
	if (battery_heal_time >= 20)  //回復速度
	{
		battery_count++;          //カウント(回復量)
		battery_heal_time = 0;
		battery++;                //回復(バッテリー)
	}
}
void Player::battery_damage()
{
	battery_heal_time++;
	if (battery_heal_time >= 20)  //ダメージ速度
	{
		battery_count++;          //カウント(ダメージ)
		battery_heal_time = 0;
		battery--;                //ダメージ(バッテリー)
	}
}

void Player::battery_heal_state(int a) 
{	
	battery += a;
}
void Player::radar(Sigen_Item *item)
{
	//レーダー

	Vector3 item_pos[3];
	int get_end_flag[3];
	int get_start_flag[3];
	p_point = player->GetPosition();

	radar_time--;

	if (radar_time <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			item_pos[i] = item[i].GetPos();
			get_end_flag[i] = item[i].GetEndFlag();
			get_start_flag[i] = item[i].GetStartFlag();

			if (get_start_flag[i] && !get_end_flag[i])
			{
				dist[i] = Vector3_Distance(p_point, item_pos[i]);

				xxx[i] = (p_point.x - item_pos[i].x) / 8000 * 170.0f; //xに入れる変数 = (プレイヤーx - 資源x) ÷ 索敵(レーダー)範囲 × レーダー(画像)のサイズ
				yyy[i] = (p_point.y - item_pos[i].y) / 8000 * 170.0f; //↑のy軸バージョン

			}
			else
			{
				xxx[i] = FLT_MAX;
				yyy[i] = FLT_MAX;
			}
		}
		radar_time = 120;
	}
}
//重力エリア
void Player::Grabity(int houkou) 
{
	if (houkou == UP) 
	{
		Grabity_move = Vector3(0, 1, 0);
	}
	else if (houkou == DOWN) 
	{
		Grabity_move = Vector3(0, -1, 0);
	}
	else 
	{
		Grabity_move = Vector3(0, 0, 0);
	}
}
void Player::Wiggler(float randam)
{
	main_camera->SetPosition(Vector3(ply_pos.x, ply_pos.y, -300.0f) + Vector3(MathHelper_Random(-randam, randam), MathHelper_Random(-randam, randam), 0));
}
//描画関係
void Player::Draw()	 
{
	if (!tenmetsu_flag) 
	{
		player->Draw();
		//player_prefab->Draw();
	}
	else 
	{
		count_++;
		if (count_ % 3 == 0) 
		{
			player->Draw();
		}
		if (count_ > 60) 
		{
			tenmetsu_flag = false;
			count_ = 0;
		}
	}

	//mouse->Draw();//マウス
	//バリア	
	barrier_pos = player->GetPosition();
	barrier_pos.z = 0.0f;
	barrier_pos = GraphicsDevice.WorldToScreen(barrier_pos);
}
void Player::Alpha_Draw()
{
	if (battery <= 0) 
	{
		efect.Draw();
	}
}
void Player::Ui()
{
	//SpriteBatch.DrawString(DefaultFont, Vector2(450.0f, 0.0f), Color(255, 255, 255), _T("バッテリー:%d％"), battery);
	//バリア
	if (barrier_flag) {
		count_++;
		if (count_ % 3 == 0)
		{
			SpriteBatch.Draw(*barrier_, barrier_pos + Vector3(-100.0f, -100.0f, 0.0f));
		}
		if (count_ > 60)
		{
			barrier_flag = false;
			count_ = 0;
		}
	}

	SpriteBatch.Draw(*radar_base, Vector3(0.0f, 0.0f, 0.0f));
	for (int i = 0; i < 3; i++)
	{
		if (dist[i] >= 4000) //索敵距離を越えたら
		{
			;
		}
		else
		{
			//光点(エネミー)の表示
			SpriteBatch.Draw(*radar_point[i], Vector3(68 - xxx[i], 68 + yyy[i], 0), (float)radar_time / 120);
			//((float)経過時間÷最大時間)
		}
	}

	Battery_Gauge.Draw(Player::BATTERY_UI_POSITION);//バッテリーゲージ
}