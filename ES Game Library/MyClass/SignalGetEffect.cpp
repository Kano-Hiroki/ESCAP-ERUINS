/*! @file  SignalGetEffect.cpp
	@brief SignalGetEffect�N���X�@������
	@author So Fujimura
	@date No.0 Start 20190214
 */
#include "SignalGetEffect.h"

SPRITE SignalGetEffect::sp_ = nullptr;

//�ړI�n�܂Ō���������
const float SignalGetEffect::FLAME_MOVEMENT_ = 20.0f;
//�傫���Ȃ鑬��
const float SignalGetEffect::FLAME_SCALE_VALUE_ = 0.5f;
//�ڕW�̑傫��
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
		@brief �摜�ǂݍ��݊֐�
		@param[in]      path   �摜�̃p�X�̏ꏊ���w�肵�܂��B
		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- �ύX����ÓI�����o�ϐ� SignalGetEffect::sp_
		@return         �Ȃ�
		@exception    none
*/
void SignalGetEffect::LoadSprite(std::wstring path) {

	SignalGetEffect::sp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());

}

/*!
		@brief �摜����֐�

		LoadSprite�֐����Ă񂾌�A\n
		�s�K�v�ɂȂ�����K��������Ă�ł��������B

		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- �ύX����ÓI�����o�ϐ� SignalGetEffect::sp_
		@return         �Ȃ�
		@exception    none
*/
void SignalGetEffect::ReleaseSprite() {

	if (SignalGetEffect::sp_ == nullptr) return;

	GraphicsDevice.ReleaseSprite(SignalGetEffect::sp_);
	SignalGetEffect::sp_ = nullptr;

}

/*!
		@brief �������֐�
		@param[in]      startPosition   �ŏ��̈ʒu���w�肵�܂��B
		@param[in]      goalPosition   �ǂ��ɍs���������w�肵�܂��B
		@par            IsStatic
		- false
		@return         �Ȃ�
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
		@brief �X�V�֐�
		@par            IsStatic
		- false
		@return         �Ȃ�
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
		@brief �`��֐�

		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void SignalGetEffect::Draw() {

	//���ɍs���Ȃ��悤�ɒ���
	this->pos_.z = 0.0f;

	float alpha = 1.0f;

	float a = fabsf(this->scale_ - 1.0f);
	float b = fabsf(this->SCALE_MAX_ - 1.0f);
	float c = a / b;

	alpha -= c;

	Color color = Color(1.0f, 1.0f, 1.0f, alpha);

	//������萔�]�[��
	//���������Ă݂���
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
		@brief �Đ��I���������ǂ���

		@par            IsStatic
		- false
		@return         bool �I����Ă����true�@�Đ����ł����false�ł�
		@exception    none
*/
bool SignalGetEffect::IsCompleted() {

	return (this->totalMovement_ >= this->length_) && (this->scale_ > SignalGetEffect::SCALE_MAX_);

}