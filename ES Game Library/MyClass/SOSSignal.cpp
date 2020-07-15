/*! @file  SOSSignal.h
	@brief SOS�V�O�i���N���X�@�w�b�_�[
	@author So Fujimura
	@date No.0 Start 20190213
 */
#include "SOSSignal.h"

MODEL SOSSignal::model_ = nullptr;

//��鑬�x�𒲐��ł��܂��B
//����傫������قǔg���傫���A����������قǔg���������Ȃ�܂��B
const float SOSSignal::RISE_FLAME_MOVEMENT_ = 0.8f;
//�g�̐��𒲐��ł��܂��B
//����傫������قǑ����A����������قǏ��Ȃ��g���ł��܂��B
const float SOSSignal::THETA_FLAME_MOVEMENT_ = 10.0f;
//�g�̕��̑傫���𒲐��ł��܂��B
const float SOSSignal::SIGNAL_RADIUS_ = 15.0f;

SOSSignal::SOSSignal() {
	this->startPos_ = Vector3_Zero;
	this->pos_ = Vector3_Zero;
	this->theta_ = 0.0f;

}

SOSSignal::~SOSSignal() {



}

/*!
		@brief ���f���ǂݍ��݊֐�

		��������simpleshape�̔���ǂݍ��ށA\n
		������f�o�b�O�p�̊֐��ł��B

		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- �ύX����ÓI�����o�ϐ� SOSSignal::model_
		@return         �Ȃ�
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
		@brief ���f���ǂݍ��݊֐�
		@param[in]      path   ���f���̃p�X�̏ꏊ���w�肵�܂��B
		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- �ύX����ÓI�����o�ϐ� SOSSignal::model_
		@return         �Ȃ�
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
		@brief ���f������֐�

		LoadModel�֐����Ă񂾌�A\n
		�s�K�v�ɂȂ�����K��������Ă�ł��������B

		@par            IsStatic
		- true
		@par            Modify_StaticMember
		- �ύX����ÓI�����o�ϐ� SOSSignal::model_
		@return         �Ȃ�
		@exception    none
*/
void SOSSignal::ReleaseModel() {

	if (SOSSignal::model_ == nullptr) return;

	GraphicsDevice.ReleaseModel(SOSSignal::model_);
	SOSSignal::model_ = nullptr;


}

/*!
		@brief �������֐�
		@param[in]      statPosition   �ŏ��̈ʒu���w�肵�܂��B
		@param[in]      theta   ���x����n�߂邩�w�肵�܂��B
		@param[in]      initMovement   �ŏ��ɂ����瓮���������w�肵�܂��B(1.0f��1�t���[����)
		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void SOSSignal::Initialize(Vector3 startPosition, float theta, float initMovement) {

	this->startPos_ = startPosition;
	this->pos_ = startPosition;
	this->theta_ = theta;
	this->initMovement_ = initMovement;
	//�ŏ��ɂ����炩�������ꍇ�͂������ł��
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
		@brief �X�V�֐�
		@par            IsStatic
		- false
		@return         �Ȃ�
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
		@brief �`��֐�

		LoadModel�֐����Ă΂�Ă��Ȃ��ꍇ�͎��s���܂���B\n
		�i�����ɂ�SOSSignal::model_��nullptr�̏ꍇ�j

		@par            IsStatic
		- false
		@return         �Ȃ�
		@exception    none
*/
void SOSSignal::Draw() {
	if (!end_flag) {
		SOSSignal::model_->SetPosition(this->pos_);
		SOSSignal::model_->Draw();
	}
}

/*!
		@brief �����蔻��̗̈�擾
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