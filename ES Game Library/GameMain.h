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
	// �ϐ��錾
	//�Q�[���I�[�o�[
	//���C��
	int gamemode;
	int over_count;
	bool start_flag;
	//�G�t�F�N�g
	//�L�[�{�[�h&�}�E�X
	KeyboardBuffer key_buffer;
	KeyboardState key_state;
	MouseState mouse_state;
	MouseBuffer mouse_buffer;
	GamePadState pad_state;
	GamePadBuffer pad_buffer;


	Collision collision;//�����蔻��N���X
//----------------------------------------------------------------------------
	//�摜�E����
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
	//�v���C���[
	Player player;
	
//---------------------------------------------------------------------------------------------------------------------------
	//�G�l�~�[
	std::vector<Enemy_Base> enemy_array;

	bool enemy_flag[100];

	int in_ste;
	float in ;
//---------------------------------------------------------------------------------------------------------------------------

	//�O���E���h
	//Ground ground;
	Ground ground_array;
	std::vector<Haikei> hakei_array;
	Haikei haikei[50];
	std::vector<Grabity_Area>grabity_array;
	//�ł����}�b�v
	std::vector< std::vector<TCHAR> > map_data0;
	std::vector< std::vector<TCHAR> > map_data1;
	std::vector< std::vector<TCHAR> > map_data2;

	//�A�C�e���⊮�p�}�b�v(�K��4*4�ō쐬)
	std::vector< std::vector<TCHAR> >item_data0;
	std::vector< std::vector<TCHAR> >item_data1;
	std::vector< std::vector<TCHAR> >item_data2;
	std::vector< std::vector<TCHAR> >item_data3;
	std::vector< std::vector<TCHAR> >item_data4;
	std::vector< std::vector<TCHAR> >item_data5;

//---------------------------------------------------------------------------------------------------------------------------
    //�A�C�e��
	Coin_Item coin[3];
	Sigen_Item sigen[3];

	int item_number;
	int sigen_count;
	int item_sprite;
	bool sigen_get_mode;
	bool StageClearFlag;
	int sigen_mokuhyou;//���̐��Ɏ����J�E���g���B����ƃN���A����
	typedef std::shared_ptr<Item_base> Base;
	std::list<Base> base_List;
	void addList(Base i);

	//�V�O�i���A�C�e��
	std::vector<SOSSignal*> signal_array;
	std::vector<SOSHuman>human_array;
	int signal_number;
	int human_number;
//---------------------------------------------------------------------------------------------------------------------------

	//�I�u�W�F�N�g
	std::vector<Object_base*> object_array;
//--------------------------------------------------------------------------------------------------------------------------------
	//�}�b�v�f�[�^
	StreamReader map_csv;
//�V�O�i���G�t�F�N�g
	SignalGetEffect signal_eff;

//---------------------------------------------------------------------------------------------------------------------------
// �֐��錾
//---------------------------------------------------------------------------------------------------------------------------

//csv����}�b�v�f�[�^���擾
	void Get_Map_data(LPCTSTR file/*�ǂݍ��ރt�@�C��*/, std::vector< std::vector<TCHAR> > &map_data/*�㏑������ϐ�*/);
	//�擾�����}�b�v����n�`��ݒu
	void Generate_Map(std::vector< std::vector<TCHAR> > map_data/*�Z�b�g����}�b�v*/);
	//�}�b�v�̍��W�ɃA�C�e����z�u
	void Item_Set(float x,float y,/*�z��̕ϐ�*/ std::vector< std::vector<TCHAR> > item_data/*�A�C�e���̔z�u�f�[�^*/);
	void stage_move();
	int now_stage;
	//��ʑJ�ڂ��Ƃ̊֐�
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
	
	//�A�b�v�f�[�g
	//�v���C���[
	void PlayerUpdate();
	//�V�O�i��
	void signal_eff_Initialize(Vector3 end_pos);

	//�O���E���h
	//�G
	void EnemyUpdate();
	//�A�C�e��
	void ItemUpdate();
	//�����蔻��
	void Collision();
	//�J��������
	void CameraControl();
	//�I�u�W�F�N�g
	void ObjectUpdate();
	//�V�O�i��
	void SignalUpdate();
	void SignalDraw();
	//�q���[�}��
	void HumanStart();
	void HumanUpdate();
	void HumanDraw();
	//�h���[
	void PlayerDraw();
	void GroundDraw();
	void EnemyDraw();
	void ItemDraw();
	void ObjectDraw();
	void UIDraw();//UI

	void Reset();
};
