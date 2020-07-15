/*! @file  SignalGetEffect.cpp
	@brief SignalGetEffectクラス　実装部
	@author So Fujimura
	@date No.0 Start 20190214
 */
#include "SignalGetEffect.h"

SPRITE SignalGetEffect::sp_ = nullptr;

//目的地まで向かう速さ
const float SignalGetEffect::FLAME_MOVEMENT_ = 20.0f;
//大きくなる速さ
const float SignalGetEffect::FLAME_SCALE_VALUE_ = 0.5f;
//目標の大きさ
const float SignalGetEffect::SCALE_MAX_ = 10.0f;

SignalGetEffect::SignalGetEffect() {

	this->pos_ = Vector3_Zero;
	this->startPos_ = Vector3_Zero;
	this->goalPos_ = Vector3_Zero;

	this->length_ = 0.0f;
	this->totalMovement_ = 0.0f;
	this->scale_ = 1.0f;

}

SignalGetEffect::~SignalGetEffect(){



}

/*!
		@brief 画像読み込み関数
		@param[in]      path   画像のパスの場所を指定します。
		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- 変更する静的メンバ変数 SignalGetEffect::sp_
		@return         なし
		@exception    none
*/
void SignalGetEffect::LoadSprite(std::wstring path) {

	SignalGetEffect::sp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());

}

/*!
		@brief 画像解放関数

		LoadSprite関数を呼んだ後、\n
		不必要になったら必ずこれを呼んでください。

		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- 変更する静的メンバ変数 SignalGetEffect::sp_
		@return         なし
		@exception    none
*/
void SignalGetEffect::ReleaseSprite() {

	if (SignalGetEffect::sp_ == nullptr) return;

	GraphicsDevice.ReleaseSprite(SignalGetEffect::sp_);
	SignalGetEffect::sp_ = nullptr;

}

/*!
		@brief 初期化関数
		@param[in]      startPosition   最初の位置を指定します。
		@param[in]      goalPosition   どこに行きつくかを指定します。
		@par            IsStatic
		- false
		@return         なし
		@exception    none
*/
void SignalGetEffect::Initialize(Vector3 startPos, Vector3 goalPos) {

	this->pos_ = startPos;
	this->startPos_ = startPos;
	this->goalPos_ = goalPos;

	Vector3 dir = this->goalPos_ - this->startPos_;
	this->length_ = Vector3_Length(dir);
	this->totalMovement_ = 0.0f;
	this->scale_ = 1.0f;

}

/*!
		@brief 更新関数
		@par            IsStatic
		- false
		@return         なし
		@exception    none
*/
void SignalGetEffect::Update() {

	if (this->totalMovement_ < this->length_) {

		this->totalMovement_ += SignalGetEffect::FLAME_MOVEMENT_;
		if (this->totalMovement_ > this->length_) this->totalMovement_ = this->length_;

		Vector3 dir = this->goalPos_ - this->startPos_;
		dir = Vector3_Normalize(dir);
		this->pos_ = this->startPos_ + dir * this->totalMovement_;

	}
	else {

		this->scale_ += SignalGetEffect::FLAME_SCALE_VALUE_;
		if (this->scale_ > SignalGetEffect::SCALE_MAX_) this->scale_ = SignalGetEffect::SCALE_MAX_;

	}

}

/*!
		@brief 描画関数

		@par            IsStatic
		- false
		@return         なし
		@exception    none
*/
void SignalGetEffect::Draw() {

	//奥に行かないように調整
	this->pos_.z = 0.0f;

	float alpha = 1.0f;

	float a = fabsf(this->scale_ - 1.0f);
	float b = fabsf(this->SCALE_MAX_ - 1.0f);
	float c = a / b;

	alpha -= c;

	Color color = Color(1.0f, 1.0f, 1.0f, alpha);

	//がっつり定数ゾーン
	//いつか直してみたい
	Vector3 rivisionedPos = this->pos_;
	{

		Vector2 size = Vector2(37.0f,37.0f);
		size *= this->scale_;

		rivisionedPos.x -= size.x / 2.0f;
		rivisionedPos.y -= size.y / 2.0f;

	}

	SpriteBatch.Draw(*SignalGetEffect::sp_, rivisionedPos, color,Vector3_Zero,Vector3_Zero,this->scale_);

}

/*!
		@brief 再生終了したかどうか

		@par            IsStatic
		- false
		@return         bool 終わっていればtrue　再生中であればfalseです
		@exception    none
*/
bool SignalGetEffect::IsCompleted() {

	return (this->totalMovement_ >= this->length_) && (this->scale_ > SignalGetEffect::SCALE_MAX_);

}