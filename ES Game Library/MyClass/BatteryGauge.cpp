/*! @file  BatteryGauge.cpp
	@brief BatteryGauge�N���X�@������
	@author So Fujimura
	@date No.0 Start 20190218
 */
#include "BatteryGauge.h"

	  SPRITE	   BatteryGauge::outerSp_			= nullptr;
const Vector2	   BatteryGauge::OUTER_SIZE_	    = Vector2(299.0f, 38.0f);//�O�g�̃T�C�Y
const std::wstring BatteryGauge::OUTER_SPRITE_PATH_ = _T("UI/battery4.png");

	  SPRITE	   BatteryGauge::innerSp_				  = nullptr;
const Vector2	   BatteryGauge::INNER_SIZE_			  = Vector2(278.0f, 26.0f);//���g�̃T�C�Y
const std::wstring BatteryGauge::INNER_SPRITE_PATH_		  = _T("UI/battery2.png");
const Vector3	   BatteryGauge::INNER_POSITION_REVISION_ = Vector3(6.0f, 6.0f, 0.0f); //���g��`�悷��ۂ̈ʒu����̕␳

//�������̂���
	  std::map<CHANGING_STATE, SPRITE>	   BatteryGauge::CONVERSION_QUANTITY_SPRITES_      = {

	{CHANGING_STATE_NONE,nullptr},
	{CHANGING_STATE_UP,  nullptr},
	{CHANGING_STATE_DOWN,nullptr}

};
//�ω������̉摜�̃p�X�ł�
const std::map<CHANGING_STATE, std::wstring> BatteryGauge::CONVERSION_QUANTITY_SPRITES_PATH_ = {

	//�Ȃ�ł��Ȃ��Ƃ�
	{CHANGING_STATE_NONE,_T("UI/battery_white.png")},
	//������
	{CHANGING_STATE_UP,  _T("")},
	//������
	{CHANGING_STATE_DOWN,_T("")}
	
};

//�ڕW�l�܂łǂꂭ�炢�̎��Ԃ������ē�������
//�P�ʂ̓~���b
const UINT BatteryGauge::CHANGING_MILLI_TIME_ = 5000;

//�������⌸�����A�ǂꂭ�炢�̃X�s�[�h�œ_�ł��邩
//���Ԃ̓~���b�P�ʁ@�Г��̎���
const std::map<CHANGING_STATE, UINT> BatteryGauge::FLASH_MILLITIMES_ = {

	//�Ȃ�ł��˂����
	{CHANGING_STATE_NONE, 0},
	//������
	{CHANGING_STATE_UP,   500},
	//������
	{CHANGING_STATE_DOWN, 50}

};

BatteryGauge::BatteryGauge() {

	this->changingState_ = CHANGING_STATE_NONE;
	this->flashState_    = FLASH_STATE_NONE;

	this->oneMilliChangePersent_ = 0.0f;

	this->nowPersent_ = 0.0f;
	this->targetPersent_ = 0.0f;
	this->flashRate_ = 0.0f;

}

BatteryGauge::~BatteryGauge() {



}

/*!
		@brief �X�v���C�g�ǂݍ��݊֐�
		@par            IsStatic
		- true
		@return         �Ȃ�
		@exception    none
*/
void BatteryGauge::LoadSprite() {

	BatteryGauge::ReleaseSprite();

	BatteryGauge::outerSp_ = GraphicsDevice.CreateSpriteFromFile(BatteryGauge::OUTER_SPRITE_PATH_.c_str());
	BatteryGauge::innerSp_ = GraphicsDevice.CreateSpriteFromFile(BatteryGauge::INNER_SPRITE_PATH_.c_str());

	//��قǑ������̃X�v���C�g���ǂݍ��ݗ\��
	std::wstring str = BatteryGauge::CONVERSION_QUANTITY_SPRITES_PATH_.at(CHANGING_STATE_NONE);
	SPRITE sp = GraphicsDevice.CreateSpriteFromFile(str.c_str());
	BatteryGauge::CONVERSION_QUANTITY_SPRITES_[CHANGING_STATE_NONE] = sp;

}

/*!
		@brief �X�v���C�g����֐�
		@par            IsStatic
		- true
		@return         �Ȃ�
		@exception    none
*/
void BatteryGauge::ReleaseSprite() {

	BatteryGauge::SafeReleaseSprite(&BatteryGauge::outerSp_);
	BatteryGauge::SafeReleaseSprite(&BatteryGauge::innerSp_);

	//��قǑ������̃X�v���C�g���Ή��\��
	BatteryGauge::SafeReleaseSprite(&BatteryGauge::CONVERSION_QUANTITY_SPRITES_[CHANGING_STATE_NONE]);

}	
/*!
		@brief �������֐�
		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void BatteryGauge::Initialize() {

	this->changingState_ = CHANGING_STATE_NONE;
	this->flashState_    = FLASH_STATE_NONE;

	this->oneMilliChangePersent_ = 0.0f;

	this->nowPersent_ = 1.0f;
	this->targetPersent_ = 1.0f;
	this->flashRate_ = 0.0f;

}

/*!
		@brief �X�V�֐�

		���̊֐����Ă�ł���Ԃ��������܂��B���Ӂ`

		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void BatteryGauge::Update() {

	//�������Ȃ��̂ł���ΏI��
	if (this->changingState_ == CHANGING_STATE_NONE) return;

	UINT elapsedTime = GameTimer.GetElapsedMilliSecond();
	this->nowPersent_ += this->oneMilliChangePersent_ * (float)elapsedTime;

	switch (this->changingState_) {

	case CHANGING_STATE_UP:

		if (this->nowPersent_ >= this->targetPersent_) {

			this->StopChanging();
			return;

		}
		break;


	case CHANGING_STATE_DOWN:

		if (this->nowPersent_ <= this->targetPersent_) {

			this->StopChanging();
			return;

		}

		break;

	default:

#ifdef DEBUG

		::OutputDebugString(_T("�Ȃɂ���@BatteryGauge::Update switch�� \n"));

#endif

		break;

	}

	UINT flashLength = BatteryGauge::FLASH_MILLITIMES_.at(this->changingState_);
	float changeFlashRate = (float)elapsedTime / (float)flashLength;

	switch (this->flashState_) {

	case FLASH_STATE_ON:

		this->flashRate_ += changeFlashRate;
		if (this->flashRate_ > 1.0f) {

			this->flashRate_ = 1.0f;
			this->flashState_ = FLASH_STATE_OFF;

		}

		break;

	case FLASH_STATE_OFF:

		this->flashRate_ -= changeFlashRate;
		if (this->flashRate_ < 0.0f) {

			this->flashRate_ = 0.0f;
			this->flashState_ = FLASH_STATE_ON;

		}

		break;

	}

}

/*!
		@brief �`��֐�
		@param[in]      drawPos   �`��ʒu���w�肵�܂��B
		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void BatteryGauge::Draw(Vector3 drawPos) {

	Vector3 outerPos = drawPos;
	Vector3 innerPos = drawPos + BatteryGauge::INNER_POSITION_REVISION_;

	SpriteBatch.Draw(*BatteryGauge::outerSp_,outerPos);

	Rect innerRect = {};
	SPRITE addSprite = BatteryGauge::CONVERSION_QUANTITY_SPRITES_[CHANGING_STATE_NONE];

	switch (this->changingState_) {

	case CHANGING_STATE_UP:

	{

		float f_right = BatteryGauge::INNER_SIZE_.x * this->nowPersent_;
		innerRect = RectWH(0, 0, (int)f_right, (int)BatteryGauge::INNER_SIZE_.y);

	}

	{

		Rect addSpRect = {};
		float f_right = BatteryGauge::INNER_SIZE_.x * this->targetPersent_;
		addSpRect = RectWH(0, 0, (int)f_right, (int)BatteryGauge::INNER_SIZE_.y);

		//�����̃X�v���C�g�͌�قǐ؂�ւ�邩��
		Color color = Color(0.0f,1.0f,0.0f,1.0f);
		SpriteBatch.Draw(*addSprite, innerPos, addSpRect, color);
		SpriteBatch.Draw(*addSprite, innerPos, addSpRect, this->flashRate_ * 0.5f);
		SpriteBatch.Draw(*BatteryGauge::innerSp_, innerPos, innerRect);

	}

		break;


	case CHANGING_STATE_DOWN:

	{

		float f_right = BatteryGauge::INNER_SIZE_.x * this->targetPersent_;
		innerRect = RectWH(0, 0, (int)f_right, (int)BatteryGauge::INNER_SIZE_.y);

	}

	{

		Rect addSpRect = {};
		float f_right = BatteryGauge::INNER_SIZE_.x * this->nowPersent_;
		addSpRect = RectWH(0, 0, (int)f_right, (int)BatteryGauge::INNER_SIZE_.y);

		//�����̃X�v���C�g�͌�قǐ؂�ւ�邩��
		Color color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		SpriteBatch.Draw(*addSprite, innerPos, addSpRect, color);
		SpriteBatch.Draw(*addSprite, innerPos, addSpRect, this->flashRate_ * 0.7f);
		SpriteBatch.Draw(*BatteryGauge::innerSp_, innerPos, innerRect);

	}

		break;

	default:

	{

		float f_right = BatteryGauge::INNER_SIZE_.x * this->nowPersent_;
		innerRect = RectWH(0, 0, (int)f_right, (int)BatteryGauge::INNER_SIZE_.y);

	}
		SpriteBatch.Draw(*BatteryGauge::innerSp_, innerPos,innerRect);

		break;

	}

}

/*!
		@brief �ڕW�l�ݒ�

		persent�ł����A100.0 ~ 0.0�ł͂Ȃ�\n
		1.0 ~ 0.0�@�ł��B

		@param[in]      persent   �ڕW�̃o�b�e���[�e�ʂł��B
		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void BatteryGauge::SetTargetPersent(float persent) {

	if (persent < 0.0f) persent = 0.0f;
	if (persent > 1.0f) persent = 1.0f;

	//�ڕW�l���ς��Ȃ��̂ł���ΕύX�̕K�v�Ȃ�
	if (persent == this->targetPersent_) return;

	this->targetPersent_ = persent;

	float dir = this->targetPersent_ - this->nowPersent_;

	if (dir == 0.0f) return;

	CHANGING_STATE  state = CHANGING_STATE_UP;
	if (dir < 0.0f) state = CHANGING_STATE_DOWN;

	this->oneMilliChangePersent_ = dir / (float)BatteryGauge::CHANGING_MILLI_TIME_;

	//�Q�[�W�̐i�s�������ꏏ�Ȃ�_�ł̏������͂���Ȃ��̂ł����Ńo�C�o�C
	if (this->changingState_ == state) return;

	this->changingState_ = state;

	this->flashState_ = FLASH_STATE_ON;
	this->flashRate_ = 0.0f;

}

void BatteryGauge::StopChanging(){

	this->nowPersent_ = this->targetPersent_;
	this->changingState_ = CHANGING_STATE_NONE;

	this->flashState_ = FLASH_STATE_NONE;
	this->flashRate_ = 0.0f;

}