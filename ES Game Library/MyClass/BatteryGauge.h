/*! @file  BatteryGauge.h
	@brief BatteryGaugeクラス　ヘッダー
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
	//2D座標
	void Draw(Vector3 drawPos);

	//1.0 ~ 0.0 で！　1.0が100% 0.0が0%
	void SetTargetPersent(float persent);

	//この関数で減少中かどうかがわかります。
	//CHANGING_STATE_UPであれば増加中
	//CHANGING_STATE_DOWNであれば減少中です
	//CHANGING_STATE_NONEは増減がありません。
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
	static const Vector2	  OUTER_SIZE_; //外枠の大きさ

	static SPRITE			  innerSp_;
	static const std::wstring INNER_SPRITE_PATH_;
	static const Vector2	  INNER_SIZE_;  //中身の大きさ
	static const Vector3	  INNER_POSITION_REVISION_;//ゲージの中身の位置の調整

	static		 std::map<CHANGING_STATE, SPRITE>		  CONVERSION_QUANTITY_SPRITES_;
	static const std::map<CHANGING_STATE, std::wstring> CONVERSION_QUANTITY_SPRITES_PATH_;

	static const UINT CHANGING_MILLI_TIME_; //ミリ秒でどれくらいで変化するのか

	static const std::map<CHANGING_STATE, UINT> FLASH_MILLITIMES_; //点滅感覚　ミリ秒単位　片道の長さ


	CHANGING_STATE changingState_;
	FLASH_STATE	   flashState_;

	float oneMilliChangePersent_;

	float nowPersent_;    //今何%よ
	float targetPersent_; //目指してんのはどこ
	float flashRate_; //ﾌﾗｰｰｰｰｰｯｼｭ!

};