/*! @file  SignalGetEffect.h
	@brief SignalGetEffect�N���X�@�w�b�_�[
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
	static const float FLAME_MOVEMENT_; //1�t���[��������ǂꂭ�炢������
	static const float FLAME_SCALE_VALUE_; //1�t���[��������ǂꂭ�炢�傫���Ȃ��
	static const float SCALE_MAX_; //�ǂ��܂ő傫���Ȃ��

	Vector3 pos_;
	Vector3 startPos_;
	Vector3 goalPos_;

	float length_;
	float totalMovement_;
	float scale_;


};