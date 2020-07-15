/*! @file  SOSSignal.h
	@brief SOSシグナルクラス　ヘッダー
	@author So Fujimura
	@date No.0 Start 20190213
 */
#include "SOSSignal.h"

MODEL SOSSignal::model_ = nullptr;

//上る速度を調整できます。
//数を大きくするほど波が大きく、小さくするほど波が小さくなります。
const float SOSSignal::RISE_FLAME_MOVEMENT_ = 0.8f;
//波の数を調整できます。
//数を大きくするほど多く、小さくするほど少ない波ができます。
const float SOSSignal::THETA_FLAME_MOVEMENT_ = 10.0f;
//波の幅の大きさを調整できます。
const float SOSSignal::SIGNAL_RADIUS_ = 15.0f;

SOSSignal::SOSSignal() {
	this->startPos_ = Vector3_Zero;
	this->pos_ = Vector3_Zero;
	this->theta_ = 0.0f;

}

SOSSignal::~SOSSignal() {



}

/*!
		@brief モデル読み込み関数

		こっちはsimpleshapeの箱を読み込む、\n
		いわゆるデバッグ用の関数です。

		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- 変更する静的メンバ変数 SOSSignal::model_
		@return         なし
		@exception    none
*/
void SOSSignal::LoadModel() {

	SimpleShape shape = {};
	shape.Type = Shape_Teapot;

	SOSSignal::model_ = GraphicsDevice.CreateModelFromSimpleShape(shape);

	Material material = {};
	material.Emissive = Color(1.0f,0.0f,0.0f);
	SOSSignal::model_->SetScale(5.0f);

	SOSSignal::model_->SetMaterial(material);

}

/*!
		@brief モデル読み込み関数
		@param[in]      path   モデルのパスの場所を指定します。
		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- 変更する静的メンバ変数 SOSSignal::model_
		@return         なし
		@exception    none
*/
void SOSSignal::LoadModel(std::wstring path) {

	SOSSignal::model_ = GraphicsDevice.CreateModelFromFile(path.c_str());
	SOSSignal::model_->SetScale(5.0f);
	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	SOSSignal::model_->SetMaterial(material);

}

/*!
		@brief モデル解放関数

		LoadModel関数を呼んだ後、\n
		不必要になったら必ずこれを呼んでください。

		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- 変更する静的メンバ変数 SOSSignal::model_
		@return         なし
		@exception    none
*/
void SOSSignal::ReleaseModel() {

	if (SOSSignal::model_ == nullptr) return;

	GraphicsDevice.ReleaseModel(SOSSignal::model_);
	SOSSignal::model_ = nullptr;


}

/*!
		@brief 初期化関数
		@param[in]      statPosition   最初の位置を指定します。
		@param[in]      theta   何度から始めるか指定します。
		@param[in]      initMovement   最初にいくら動かすかを指定します。(1.0fで1フレーム分)
		@par            IsStatic
		- false
		@return         なし
		@exception    none
*/
void SOSSignal::Initialize(Vector3 startPosition, float theta, float initMovement) {

	this->startPos_ = startPosition;
	this->pos_ = startPosition;
	this->theta_ = theta;
	this->initMovement_ = initMovement;
	//最初にいくらか動かす場合はこっちでやる
	this->pos_.y += SOSSignal::RISE_FLAME_MOVEMENT_ * initMovement_;

	this->theta_ += SOSSignal::THETA_FLAME_MOVEMENT_ * initMovement_;
	float cos = MathHelper_Cos(this->theta_);

	this->pos_.x = this->startPos_.x + cos * SOSSignal::SIGNAL_RADIUS_;
	this->end_flag = false;
	this->start_flag = false;
}

void SOSSignal::Reset() {
	this->pos_.y += SOSSignal::RISE_FLAME_MOVEMENT_ * initMovement_;

	this->theta_ += SOSSignal::THETA_FLAME_MOVEMENT_ * initMovement_;
	float cos = MathHelper_Cos(this->theta_);

	this->pos_.x = this->startPos_.x + cos * SOSSignal::SIGNAL_RADIUS_;
	this->end_flag = false;
	this->start_flag = false;

}
/*!
		@brief 更新関数
		@par            IsStatic
		- false
		@return         なし
		@exception    none
*/
void SOSSignal::Update() {
	if (start_flag) {
		this->pos_.y += SOSSignal::RISE_FLAME_MOVEMENT_;

		this->theta_ += SOSSignal::THETA_FLAME_MOVEMENT_;
		float cos = MathHelper_Cos(this->theta_);

		this->pos_.x = this->startPos_.x + cos * SOSSignal::SIGNAL_RADIUS_;
	}
}
void SOSSignal::Hit() {
	this->end_flag = true;
}
void SOSSignal::Start() {
	this->start_flag = true;
}
/*!
		@brief 描画関数

		LoadModel関数が呼ばれていない場合は実行しません。\n
		（厳密にはSOSSignal::model_がnullptrの場合）

		@par            IsStatic
		- false
		@return         なし
		@exception    none
*/
void SOSSignal::Draw() {
	if (!end_flag) {
		SOSSignal::model_->SetPosition(this->pos_);
		SOSSignal::model_->Draw();
	}
}

/*!
		@brief 当たり判定の領域取得
		@par            IsStatic
		- false
		@return         OrientedBoundingBox
		@exception    none
*/
MODEL SOSSignal::GetModel(){

	SOSSignal::model_->SetPosition(this->pos_);
	return SOSSignal::model_;

}
bool SOSSignal::GetEndFlag() {
	return end_flag;
}