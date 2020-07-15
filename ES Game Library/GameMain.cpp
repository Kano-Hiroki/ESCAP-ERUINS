// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
void GameMain::addList(Base i) {
	base_List.push_back(i);
}

bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("3rd Project"));


	//ライトの当たり方
	GraphicsDevice.SetRenderState(NormalizeNormals_Enable);
	//ゲームパット
	InputDevice.CreateGamePad(1);

	//マウス
	InputDevice.CreateMouse();
	MediaManager.Attach(GraphicsDevice);
	//現在のゲームモード
	gamemode = MAIN;
	for (int i = 0; i < 100; i++) {
		enemy_flag[i] = false;
	}
	for (int i = 0; i < 3; i++) {
		coin[i].Initialize(Vector3(0, 0, 0), i);
		sigen[i].Initialize(Vector3(0, 0, 0), i);

	}
	//プレイヤー
	player.Initialize();//プレイヤー初期地点

	SOSSignal::LoadModel(_T("Item/sos.X"));
	////おおもとのでかいマップ
	Get_Map_data((_T("map/stage01.txt")),map_data0);
	Get_Map_data((_T("map/stage02.txt")), map_data1);


	////アイテム補完用のマップ
	////
	////地形生成

		//オブジェクトのライトをセット
	

	//アイテム　

	//エフェクト初期化
	GraphicsDevice.SetRenderState(CullMode_None);
	SignalGetEffect::LoadSprite(_T("UI/radar/radar2.png"));
	now_stage = 0;
	over_count = 0;
	sigen_count = 0;
	in_ste = 0;
	in = 0;
	start_flag = false;
	return true;
}
void GameMain::stage_move() {
	sigen_count = 0;
	start_flag = false;
	sigen_get_mode = true;
	StageClearFlag = true;
	player.Reset();
	switch (now_stage) {
	case 0:
		player.Light_Start(false);
		Generate_Map(map_data0);
		sigen_mokuhyou = 3;
		break;
	case 1:
		player.Light_Start(true);
		Generate_Map(map_data1);
		sigen_mokuhyou = 3;

		break;
	}
}
void GameMain::Reset() {
	now_stage = 0;
	stage_move();
	over_count = 0;
	in_ste = 0;
	in = 0;
	start_flag = false;
	sigen_count = 0;

}
//テキストからマップをコピー
void GameMain::Get_Map_data(LPCTCH file, std::vector< std::vector<TCHAR> > &map_data) {
	map_csv.Open(file);
	TCHAR buffer[500 + 1];
	
	while (true) {	
		map_csv.ReadLine(buffer);//一行読む
		if (map_csv.IsEOF())
			break;//最後まで読んだらブレイク

		std::vector<TCHAR>  data;

		for (int m = 0; buffer[m] != '\0'; m++) {
			if (buffer[m] == ',')
				continue;//コンマだったら次の文字に進む

			data.push_back(buffer[m]);
		}

		map_data.push_back(data);
	}

}
//コピーしたマップを地形として生成
void GameMain::Generate_Map(std::vector< std::vector<TCHAR> > map_data) {
	human_array.clear();
	signal_array.clear();
	enemy_array.clear();

	int e = 0;//敵
	int h = 0;//背景
	int g = 0;//重力エリア
	int a = 0;
	item_number = 0;//アイテム
	human_number = 0;
	signal_number = 0;
	for (int y = map_data.size() - 1; y >= 0; y--) {
		for (int x = 1; x < map_data[y].size(); x++) {
			Coin_Item item;
			Enemy_Base   enemy;
			Object_base* object;
			Ground ground;
			Grabity_Area Grabity;
			SOSHuman human;
			switch (map_data[y][x]) {
			case '1'://壁
				break;
			case '2'://プレイヤー
				player.SetPosition(Vector3(x * 64, y * -64, 0));
				ground_array.Initialize(Vector3(x * 64, y * -64, 0), now_stage);
				break;
			case '3'://救助者
				human_array.push_back(human);
				human_array[human_number].Initialize(Vector3(x * 64, y*-64, 0.0f));
				human_number++;
				break;
			case '4':
				coin[0].Setpos(Vector3((x * 64), (y*-64), 0));

				break;
			case '5':
				coin[1].Setpos(Vector3((x * 64), (y*-64), 0));
				break;
			
			case '6'://壁(左)
				coin[2].Setpos(Vector3((x * 64), (y*-64), 0));

				break;
			case '7'://壁(左)
				sigen[0].Setpos(Vector3((x * 64), (y*-64), 0));

				break;
			case '8'://壁(右)
				sigen[1].Setpos(Vector3((x * 64), (y*-64), 0));
				break;
			case '9':
				sigen[2].Setpos(Vector3((x * 64), (y*-64), 0));
				break;
			case 'a':
				enemy_array.push_back(enemy);
				enemy_array[e].Initialize(Vector3(x * 64, y*-64, 0), 2, 1, (_T("Enemy/enemy.x")));
				e++;
				break;
			case '99'://岩{
				break;
			case'u'://重力エリア
				grabity_array.push_back(Grabity);
				grabity_array[g].Initialize(Vector3(x * 64, y*-64, 0), UP);
				g++;
				break;
			}
		}
	}
}
//アイテムの座標を補完
void GameMain::Item_Set(float x,float y, std::vector< std::vector<TCHAR> > item_data) {
	for (int i_y = item_data.size() - 1; i_y >= 0; i_y--) {
		for (int i_x = 0; i_x < item_data[i_y].size(); i_x++) {
			Coin_Item coin_item;
			SOSHuman human;
			switch (item_data[i_y][i_x]) {
			case '1':
				break;

			case'2':
				{
					SOSSignal* signal = new SOSSignal();

					signal_array.push_back(signal);
					signal_array[signal_number]->Initialize(Vector3(x * 64 + i_x * 16, y*-64 + i_y * -16, 0.0f), 0.5f, 0.0f);
					signal_number++;
					break;
				}
			case '3':
				human_array.push_back(human);
				human_array[human_number].Initialize(Vector3(x * 64 + i_x * 16, y*-64 + i_y * -16, 0.0f));
				human_number++;
				break;
			case '4':
				//coin_array.push_back(coin_item);
				//coin_array[item_number].Initialize(Vector3((x * 64) + (i_x * 16), (y*-64) + (i_y*-16), 0));
				//item_number++;
				break;

			}
			
		}
	}

}
//エフェクト初期化
void GameMain::signal_eff_Initialize(Vector3 end_pos) {
	Vector3 startPos = GraphicsDevice.WorldToScreen(player.re_player()->GetPosition());
	Vector3 endPos = Vector3(85, 85, 0); //player.re_radar();
	signal_eff.Initialize(startPos, end_pos);
}
void GameMain::Finalize()
{
	for (auto& object : object_array)
		delete object;
	for (auto& signal : signal_array)
		delete signal;
}

int GameMain::Update()
{
	key_state = Keyboard->GetState();
	mouse_state = Mouse->GetState();

	switch (gamemode) {
	case TITLE:
		TitleUpdate();
		key_buffer = Keyboard->GetBuffer();
		mouse_buffer = Mouse->GetBuffer();
		pad_buffer = GamePad(0)->GetBuffer();
		break;
	case MAIN:  
		MainUpdate();
		break;

	case GAMEOVER:
		GameoverUpdate();
		pad_buffer = GamePad(0)->GetBuffer();
		key_buffer = Keyboard->GetBuffer();
		mouse_buffer = Mouse->GetBuffer();
		break;
	case CLEAR:
		pad_buffer = GamePad(0)->GetBuffer();
		key_buffer = Keyboard->GetBuffer();
		mouse_buffer = Mouse->GetBuffer();
		break;
	case MOVE:
		break;
	case MANUAL:
		pad_buffer = GamePad(0)->GetBuffer();
		key_buffer = Keyboard->GetBuffer();
		mouse_buffer = Mouse->GetBuffer();
		ManualUpadte();
		break;
	}

	

	return 0;
}

void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();
	switch (gamemode) {
	case MAIN:
		MainDraw();
		break;

	} 


	SpriteBatch.Begin();//2D描画
	switch (gamemode) {
	case TITLE:
		TitleDraw();
		break;
	case MAIN:
		UIDraw();
		break;
	case GAMEOVER:
		GameoverDraw();
		break;
	case CLEAR:
		break;
	case MOVE:
		break;
	case MANUAL:
		ManualDraw();
		break;

	}
	SpriteBatch.End();

	GraphicsDevice.BeginAlphaBlend();
	switch (gamemode) {
	case MAIN:
		if (start_flag) {
			for (int i = 0; i < enemy_array.size(); i++) {
				enemy_array[i].Efect_Draw();
			}
			for (int i = 0; i < human_array.size(); i++) {
				human_array[i].Efect_Draw();
			}

			ItemDraw();
			player.Alpha_Draw();
			SignalDraw();
		}
		break;

	}
	GraphicsDevice.EndAlphaBlend();


	GraphicsDevice.EndScene();
}
//タイトル------------------------------------------------------------------------------------------------------------------
void GameMain::TitleUpdate() {

	if (pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) || pad_buffer.IsPressed(GamePad_Button3)
		|| pad_buffer.IsPressed(GamePad_Button4)||key_buffer.IsPressed(Keys_Enter))  {
		in_ste = 1;
	}
	if (in_ste == 1) {
		in += 0.01;
	}
	if (in >= 1) {
		in_ste = 0;
		in = 0;
		gamemode =MANUAL;
	}

}
void GameMain::TitleDraw() {
	SpriteBatch.Draw(*title_sprite, Vector3(0, 0, 0));
	SpriteBatch.Draw(*black, Vector3(0, 0, -1), in, Vector3(0, 0, 0), Vector3(0, 0, 0), 1);

}
//マニュアル------------------------------------------------------------------------------------------------------------------
void GameMain::ManualUpadte() {

	if (pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) || pad_buffer.IsPressed(GamePad_Button3)
		|| pad_buffer.IsPressed(GamePad_Button4)||key_buffer.IsPressed(Keys_Enter)) {
		in_ste = 1;
	}
	if (in_ste == 1) {
		in += 0.01;
	}
	if (in >= 1) {
		in_ste = 0;
		in = 0;
		gamemode = MAIN;
	}

}
void GameMain::ManualDraw() {
	SpriteBatch.Draw(*manual_sprite, Vector3(0, 0, 0));
	SpriteBatch.Draw(*black, Vector3(0, 0, -1), in, Vector3(0, 0, 0), Vector3(0, 0, 0), 1);

}
//画面------------------------------------------------------------------------------------------------------------------
void GameMain::MoveUpdate() {

	if (key_buffer.IsPressed(Keys_Enter)) {
		gamemode = MAIN;
	}
}
void GameMain::MoveDraw() {

}
bool StageClear(int a, int b) {
	bool clear = false;
	if (a == b) {
		clear = true;
	}
	return clear;
}

//メイン-----------------------------------------------------------------------------------------------------------------------
void GameMain::MainUpdate() {
	if (StageClearFlag) {
		if (sigen_get_mode) {
			if (start_flag) {
				PlayerUpdate();
				EnemyUpdate();
				ItemUpdate();
				Collision();
				SignalUpdate();
				HumanUpdate();
				ground_array.Update();

				for (int i = 0; i < object_array.size(); i++) {
					object_array[i]->Update();
					GraphicsDevice.SetLight(object_array[i]->re_light(), i + 20, true);
				}

				if (player.GetEndFlag()) {
					over_count++;
					if (over_count > 120) {
						gamemode = GAMEOVER;
					}

				}
			}
		}
	}
	if(!start_flag) {
		key_buffer = Keyboard->GetBuffer();
		pad_buffer = GamePad(0)->GetBuffer();
		if (pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) || pad_buffer.IsPressed(GamePad_Button3)
			|| pad_buffer.IsPressed(GamePad_Button4)||key_buffer.IsPressed(Keys_Enter)) {
			stage_move();
			start_flag = true;
		}
	}

	if (!sigen_get_mode) {
		key_buffer = Keyboard->GetBuffer();
		pad_buffer = GamePad(0)->GetBuffer();
		if (pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) || pad_buffer.IsPressed(GamePad_Button3)
		|| pad_buffer.IsPressed(GamePad_Button4) || key_buffer.IsPressed(Keys_Enter)) {
			sigen_get_mode =true;
			sigen_count++;
		}

	}
	if (!StageClearFlag) {
		key_buffer = Keyboard->GetBuffer();
		pad_buffer = GamePad(0)->GetBuffer();
		if (pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) || pad_buffer.IsPressed(GamePad_Button3)
			|| pad_buffer.IsPressed(GamePad_Button4) || key_buffer.IsPressed(Keys_Enter)) {
			sigen_count = 0;
			StageClearFlag = true;
			start_flag = false;

		}

	}


	if (StageClearFlag) {
		if (StageClear(sigen_count, sigen_mokuhyou)) {
			now_stage++;
			if (now_stage == 2) {

			}
			StageClearFlag = false;
		}
	}
	std::for_each(base_List.begin(), base_List.end(), [](Base i) {i->move(); });

}
void GameMain::MainDraw() {
	if (start_flag) {
		GroundDraw();
		ObjectDraw();
		EnemyDraw();
		HumanDraw();
		player.Draw();
	}
}
//UI 
void GameMain::UIDraw() {
	player.Ui();//UI表示
	for (int i = 0; i < enemy_array.size(); i++) {//エネミーのエフェクト再生
		enemy_array[i].Efect_Draw();
	}
	for (int i = 0; i < 3; i++) {
		coin[i].Efect_Draw();
	}
	signal_eff.Draw();
	SpriteBatch.Draw(*coin_count_sprite, Vector3(0, 0, 0));
	SpriteBatch.DrawString(DefaultFont, Vector2(1150.0f, 90.0f), Color(255, 255, 255), _T("%03d"), sigen_count);

	SpriteBatch.Draw(*haikei_sprite, Vector3(0, 0, 10000));
	if (!start_flag) {
		if (now_stage == 0) {
			SpriteBatch.Draw(*StartSprite1, Vector3(0, 0, -10));

		}
		else if (now_stage == 1) {
			SpriteBatch.Draw(*StartSprite2, Vector3(0, 0, -10));

		}
	}
	if (!sigen_get_mode) {
		if (item_sprite == RED) {
			SpriteBatch.Draw(*box_get_sprite_red, Vector3(0, 0, -10));
		}
		else if (item_sprite == GREEN) {
			SpriteBatch.Draw(*box_get_sprite_green, Vector3(0, 0, -10));
		}
		else if (item_sprite == BLUE) {
			SpriteBatch.Draw(*box_get_sprite_blue, Vector3(0, 0, -10));
		}
	}
	if (!StageClearFlag) {
		SpriteBatch.Draw(*StageClearSprite, Vector3(0, 0, -10));

	}
}
//----------------------------------------------------------------------------------------------------------------------------------
//プレイヤー
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::PlayerUpdate() {
	player.PlayerUpdate(ground_array,enemy_array,human_array,sigen);
}
//----------------------------------------------------------------------------------------------------------------------------------
//エネミー
//---------------------------------------------------------------------------------------------------------------------------------
void GameMain::EnemyUpdate() {

	Vector3 player_pos=player.re_player()->GetPosition();
	OrientedBoundingBox Light_OBB = player.re_right_model()->GetOBB();
	player_pos.z = 0.0f;
	Vector3 enemy_pos;
	
	for (int i = 0; i < enemy_array.size(); i++) {
		enemy_pos = enemy_array[i].re_enemy()->GetPosition();
		enemy_pos.z = 0.0f;
		float   distance = Vector3_Distance(player_pos, enemy_pos);//プレイヤーと敵の距離
		if(distance <= 600&&sigen_count>=1) {//プレイヤーと敵が近づいたらメインが起動する
			enemy_flag[i] = true;
		}
		if (enemy_flag[i]) {
				enemy_array[i].Main(ground_array, player);
		}
	}
}
void GameMain::EnemyDraw() {
	for (int i = 0; i <enemy_array.size(); i++) {
		enemy_array[i].Draw();
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
//フィールド
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::GroundDraw() {
	//座標を入れる入れ物
	Vector3 ply_pos = player.re_player()->GetPosition();//座標を取得
	ply_pos.z = 0;//座標を平面化
	ground_array.Draw();//描画関数
	std::vector<Vector3> haikei_pos(hakei_array.size());
	for (int i = 0; i < hakei_array.size(); i++) {
		haikei_pos[i] = hakei_array[i].re_pos();//座標を取得
		haikei_pos[i].z = 0;//座標を平面化
		if (Vector3_Distance(haikei_pos[i], ply_pos) <= 800) {//描画距離
			hakei_array[i].Draw();
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
//アイテム
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::ItemUpdate() {
	

}
void GameMain::ItemDraw() {
	for (int i = 0; i < 3; i++) {
		coin[i].Draw();
		sigen[i].Draw();
	}
	std::for_each(base_List.begin(), base_List.end(), [](Base i) {i->Draw(); });
}
//---------------------------------------------------------------------------------------------------------------------------------
//コリジョン
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::Collision() {
	for (int i = 0; i < grabity_array.size(); i++) {
		if (collision.collision(player.re_player(), grabity_array[i].re_model()))
		{
			player.Grabity(grabity_array[i].re_houkou());
		}
		else {
			player.Grabity(99);
		}
	}
	//コインと資源ボックス
	for (int i = 0; i < 3; i++) {
		if (!coin[i].re_flag()) {
			if (collision.collision(player.re_ply_prefab(), coin[i].re_model())) {
				sigen[i].Start();
				coin[i].Hit();
				signal_eff_Initialize(Vector3(85, 85, 0));
			}

		}
		if (sigen[i].GetStartFlag()) {
			if (!sigen[i].GetEndFlag()) {
				if (collision.collision(player.re_ply_prefab(), sigen[i].GetModel())) {
					sigen[i].Hit();
					item_sprite = sigen[i].GetItemType();
					sigen_get_mode = false;
				}
			}
		}
	}
	//シグナル
	for (int i = 0; i < signal_array.size(); i++) {
		if (!signal_array[i]->GetEndFlag()) {
			if (collision.collision(player.re_ply_prefab(), signal_array[i]->GetModel() ) ) {
				signal_array[i]->Hit();
				signal_eff_Initialize(Vector3(85, 85, 0));
				HumanStart();
				
			}
		}
	}
	for (int i = 0; i < human_array.size(); i++) {
		if (!human_array[i].GetEndFlag()) {

			if (human_array[i].GetStartFlag()) {
				if (collision.collision(player.re_ply_prefab(), human_array[i].GetModel())) {
					human_array[i].Hit();
					for (int j = 0; j < ItemBattery::NUM; j++) {
						Base battery(new ItemBattery());
						addList(battery);
						battery->SetPosAndSetScale(human_array[i].GetModel()->GetPosition(), 1.0f);
					}

				}
			}
		}
	}
	//電池
	/*for (int i = 0; i < base_List.size(); i++) {
		if (collision.collision(player.re_ply_prefab(), base_List[i])) {
		}
	}*/
	std::for_each(base_List.begin(), base_List.end(), [&](Base &i) {
		if (!i->GetEndFlag()) {
			if (collision.collision(player.re_ply_prefab(), i->GetModel())) {
				i->hit();
				player.battery_heal_state(10);
			}
		}
	});
	
}
//----------------------------------------------------------------------------------------------------------------------------------
//オブジェクト
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::ObjectDraw(){
	for (int i = 0; i < object_array.size(); i++) {
		object_array[i]->Draw();
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
//シグナル
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::SignalUpdate() {
	Vector3 ply_pos = player.re_player()->GetPosition();//座標を取得
	std::vector<bool> Signal_Start(signal_array.size());
	std::vector<Vector3> Signal_Pos(signal_array.size());
	for (int i = 0; i < signal_array.size(); i++) {
		Signal_Pos[i] = signal_array[i]->GetModel()->GetPosition();
		if (Vector3_Distance(Signal_Pos[i], ply_pos) <= 1000	) {
			signal_array[i]->Start();
		}
		signal_array[i]->Update();
	}
	signal_eff.Update();
}
void GameMain::SignalDraw() {
	for (int i = 0; i < signal_array.size(); i++) {
		signal_array[i]->Draw();
	}

}
//----------------------------------------------------------------------------------------------------------------------------------
//ヒューマン
//----------------------------------------------------------------------------------------------------------------------------------
void GameMain::HumanUpdate() {
	for (int i = 0; i < human_array.size(); i++) {
		human_array[i].Update();
	}
}
void GameMain::HumanStart() {
	float   distance = FLT_MAX;
	int     index = -1;
	for (int i = 0; i < human_array.size(); i++)
	{
		if (!human_array[i].GetStartFlag()) {
			float   dist = Vector3_Distance(player.re_player()->GetPosition(), human_array[i].GetModel()->GetPosition());
			if (distance > dist) {
				distance = dist;
				index = i;
			}
		}
	}
	if (index != -1) {
		human_array[index].Start();
	}

}
void GameMain::HumanDraw() {
	for (int i = 0; i < human_array.size(); i++)
	{
		human_array[i].Draw();
	}

}
//ゲームオーバー------------------------------------------------------------------------------------------------------------------
void GameMain::GameoverUpdate() {
	if (pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) || pad_buffer.IsPressed(GamePad_Button3)
		|| pad_buffer.IsPressed(GamePad_Button4) || key_buffer.IsPressed(Keys_Enter)) {
		in_ste = 1;
	}
	if (in_ste == 1) {
		in += 0.01;
	}
	if (in >= 1) {
		in_ste = 0;
		in = 0;
		Reset();
		gamemode = TITLE;
	}

}
void GameMain::GameoverDraw() {
	SpriteBatch.Draw(*gameover_sprite, Vector3(0, 0, 0));
}


