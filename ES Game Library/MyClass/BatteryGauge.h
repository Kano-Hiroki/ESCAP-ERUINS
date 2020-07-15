/*! @file  BatteryGauge.h
	@brief BatteryGauge�N���X�@�w�b�_�[
	@author So Fujimura
	@date No.0 Start 20190218
 */
#pragma once
#include "../ESGLib.h"
#include "enum.h"
#include <map>

class BatteryGauge {

public:


	BatteryGauge();
	~BatteryGauge();

	static void LoadSprite();
	static void ReleaseSprite();

	void Initialize();
	void Update();
	//2D���W
	void Draw(Vector3 drawPos);

	//1.0 ~ 0.0 �ŁI�@1.0��100% 0.0��0%
	void SetTargetPersent(float persent);

	//���̊֐��Ō��������ǂ������킩��܂��B
	//CHANGING_STATE_UP�ł���Α�����
	//CHANGING_STATE_DOWN�ł���Ό������ł�
	//CHANGING_STATE_NONE�͑���������܂���B
	CHANGING_STATE GetChangingState() { return this->changingState_; }

private:

	static inline void SafeReleaseSprite(SPRITE* sp)
	{

		if (*sp == nullptr) return;

		GraphicsDevice.ReleaseSprite(*sp);
		*sp = nullptr;

	}

	void StopChanging();


	enum FLASH_STATE {

		FLASH_STATE_NONE,
		FLASH_STATE_ON,
		FLASH_STATE_OFF

	};

	static SPRITE			  outerSp_;
	static const std::wstring OUTER_SPRITE_PATH_;
	static const Vector2	  OUTER_SIZE_; //�O�g�̑傫��

	static SPRITE			  innerSp_;
	static const std::wstring INNER_SPRITE_PATH_;
	static const Vector2	  INNER_SIZE_;  //���g�̑傫��
	static const Vector3	  INNER_POSITION_REVISION_;//�Q�[�W�̒��g�̈ʒu�̒���

	static		 std::map<CHANGING_STATE, SPRITE>		  CONVERSION_QUANTITY_SPRITES_;
	static const std::map<CHANGING_STATE, std::wstring> CONVERSION_QUANTITY_SPRITES_PATH_;

	static const UINT CHANGING_MILLI_TIME_; //�~���b�łǂꂭ�炢�ŕω�����̂�

	static const std::map<CHANGING_STATE, UINT> FLASH_MILLITIMES_; //�_�Ŋ��o�@�~���b�P�ʁ@�Г��̒���


	CHANGING_STATE changingState_;
	FLASH_STATE	   flashState_;

	float oneMilliChangePersent_;

	float nowPersent_;    //����%��
	float targetPersent_; //�ڎw���Ă�̂͂ǂ�
	float flashRate_; //�װ�������!

};