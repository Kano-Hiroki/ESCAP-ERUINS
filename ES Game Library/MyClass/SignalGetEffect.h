/*! @file  SignalGetEffect.h
	@brief SignalGetEffectクラス　ヘッダー
	@author So Fujimura
	@date No.0 Start 20190214
 */
#pragma once
#include "../ESGLib.h"

class SignalGetEffect {

public:

	SignalGetEffect();
	~SignalGetEffect();

	static void LoadSprite(std::wstring str);
	static void ReleaseSprite();

	void Initialize(Vector3 startPos, Vector3 goalPos);
	void Update();
	void Draw();

	bool IsCompleted();

private:
	
	static SPRITE sp_;
	static const float FLAME_MOVEMENT_; //1フレーム当たりどれくらい動くか
	static const float FLAME_SCALE_VALUE_; //1フレーム当たりどれくらい大きくなんの
	static const float SCALE_MAX_; //どこまで大きくなんの

	Vector3 pos_;
	Vector3 startPos_;
	Vector3 goalPos_;

	float length_;
	float totalMovement_;
	float scale_;


};