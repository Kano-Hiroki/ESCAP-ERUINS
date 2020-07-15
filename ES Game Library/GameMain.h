#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"
#include "MyClass/Item.h"
#include "MyClass\Collision.h"
#include "MyClass\Player.h"
#include "MyClass\enum.h"
#include"MyClass\Ground.h"
#include "MyClass\Enemy.h"
#include "MyClass\Object.h"
#include"MyClass\SOSSignal.h"
#include"MyClass/SOSHuman.h"
#include"MyClass/SignalGetEffect.h"
class GameMain : public CGameScene {
public:
	GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~GameMain()
	{
#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;

private:
	// 変数宣言
	//ゲームオーバー
	//メイン
	int gamemode;
	int over_count;
	bool start_flag;
	//エフェクト
	//キーボード&マウス
	KeyboardBuffer key_buffer;
	KeyboardState key_state;
	MouseState mouse_state;
	MouseBuffer mouse_buffer;
	GamePadState pad_state;
	GamePadBuffer pad_buffer;


	Collision collision;//当たり判定クラス
//----------------------------------------------------------------------------
	//画像・動画
//----------------------------------------------------------------------------
	SPRITE black=GraphicsDevice.CreateSpriteFromFile(_T("Sprite/black.png"));
	SPRITE gameover_sprite= GraphicsDevice.CreateSpriteFromFile(_T("Sprite/gameover.png"));
	SPRITE title_sprite= GraphicsDevice.CreateSpriteFromFile(_T("Sprite/Title.png"));
	SPRITE manual_sprite= GraphicsDevice.CreateSpriteFromFile(_T("Sprite/manual.png"));
	SPRITE coin_count_sprite = GraphicsDevice.CreateSpriteFromFile(_T("Sprite/coin_ui.png"));
	SPRITE haikei_sprite = GraphicsDevice.CreateSpriteFromFile(_T("Sprite/BG_image01.png"));
	SPRITE box_get_sprite_red = GraphicsDevice.CreateSpriteFromFile(_T("Sprite/get_red.png"));
	SPRITE box_get_sprite_green = GraphicsDevice.CreateSpriteFromFile(_T("Sprite/get_green.png"));
	SPRITE box_get_sprite_blue = GraphicsDevice.CreateSpriteFromFile(_T("Sprite/get_blue.png"));
	SPRITE StageClearSprite= GraphicsDevice.CreateSpriteFromFile(_T("Sprite/gameclear.png"));
	SPRITE StartSprite1= GraphicsDevice.CreateSpriteFromFile(_T("Sprite/gamestart1.png"));
	SPRITE StartSprite2 = GraphicsDevice.CreateSpriteFromFile(_T("Sprite/gamestart2.png"));

	MEDIA demo_move;


//---------------------------------------------------------------------------------------------------------------------------
	//プレイヤー
	Player player;
	
//---------------------------------------------------------------------------------------------------------------------------
	//エネミー
	std::vector<Enemy_Base> enemy_array;

	bool enemy_flag[100];

	int in_ste;
	float in ;
//---------------------------------------------------------------------------------------------------------------------------

	//グラウンド
	//Ground ground;
	Ground ground_array;
	std::vector<Haikei> hakei_array;
	Haikei haikei[50];
	std::vector<Grabity_Area>grabity_array;
	//でかいマップ
	std::vector< std::vector<TCHAR> > map_data0;
	std::vector< std::vector<TCHAR> > map_data1;
	std::vector< std::vector<TCHAR> > map_data2;

	//アイテム補完用マップ(必ず4*4で作成)
	std::vector< std::vector<TCHAR> >item_data0;
	std::vector< std::vector<TCHAR> >item_data1;
	std::vector< std::vector<TCHAR> >item_data2;
	std::vector< std::vector<TCHAR> >item_data3;
	std::vector< std::vector<TCHAR> >item_data4;
	std::vector< std::vector<TCHAR> >item_data5;

//---------------------------------------------------------------------------------------------------------------------------
    //アイテム
	Coin_Item coin[3];
	Sigen_Item sigen[3];

	int item_number;
	int sigen_count;
	int item_sprite;
	bool sigen_get_mode;
	bool StageClearFlag;
	int sigen_mokuhyou;//この数に資源カウントが達するとクリア判定
	typedef std::shared_ptr<Item_base> Base;
	std::list<Base> base_List;
	void addList(Base i);

	//シグナルアイテム
	std::vector<SOSSignal*> signal_array;
	std::vector<SOSHuman>human_array;
	int signal_number;
	int human_number;
//---------------------------------------------------------------------------------------------------------------------------

	//オブジェクト
	std::vector<Object_base*> object_array;
//--------------------------------------------------------------------------------------------------------------------------------
	//マップデータ
	StreamReader map_csv;
//シグナルエフェクト
	SignalGetEffect signal_eff;

//---------------------------------------------------------------------------------------------------------------------------
// 関数宣言
//---------------------------------------------------------------------------------------------------------------------------

//csvからマップデータを取得
	void Get_Map_data(LPCTSTR file/*読み込むファイル*/, std::vector< std::vector<TCHAR> > &map_data/*上書きする変数*/);
	//取得したマップから地形を設置
	void Generate_Map(std::vector< std::vector<TCHAR> > map_data/*セットするマップ*/);
	//マップの座標にアイテムを配置
	void Item_Set(float x,float y,/*配列の変数*/ std::vector< std::vector<TCHAR> > item_data/*アイテムの配置データ*/);
	void stage_move();
	int now_stage;
	//画面遷移ごとの関数
	void TitleUpdate();
	void TitleDraw();

	void MainUpdate();
	void MainDraw();

	void ClearUpdate();
	void ClearDraw();

	void GameoverUpdate();
	void GameoverDraw();

	void MoveUpdate();
	void MoveDraw();

	void ManualUpadte();
	void ManualDraw();
	
	//アップデート
	//プレイヤー
	void PlayerUpdate();
	//シグナル
	void signal_eff_Initialize(Vector3 end_pos);

	//グラウンド
	//敵
	void EnemyUpdate();
	//アイテム
	void ItemUpdate();
	//当たり判定
	void Collision();
	//カメラ制御
	void CameraControl();
	//オブジェクト
	void ObjectUpdate();
	//シグナル
	void SignalUpdate();
	void SignalDraw();
	//ヒューマン
	void HumanStart();
	void HumanUpdate();
	void HumanDraw();
	//ドロー
	void PlayerDraw();
	void GroundDraw();
	void EnemyDraw();
	void ItemDraw();
	void ObjectDraw();
	void UIDraw();//UI

	void Reset();
};
