/*! @file  SOSSignal.h
	@brief SOS�V�O�i���N���X�@�w�b�_�[
	@author So Fujimura
	@date No.0 Start 20190213
 */
#pragma once
#include "../ESGLib.h"

class SOSSignal {

public:

	SOSSignal();
	~SOSSignal();

	//�������͓K����simpleshape��ǂݍ��݂�
	static void LoadModel();
	//�������͎w�肵���p�X��ǂݍ��݂܂�
	static void LoadModel(std::wstring path);
	static void ReleaseModel();

	void Initialize(Vector3 startPosition = Vector3_Zero, float theta = 0.0f, float initMovement = 0.0f);
	void Reset();
	void Update();
	void Draw();
	void Hit();
	void Start();
	MODEL GetModel();
	bool GetEndFlag();
private:

	// SOSSignal���g�����f���f�[�^�ł��B
	static MODEL model_;
	//�オ�鑬�x
	static const float RISE_FLAME_MOVEMENT_;
	// ���ɂ傤�ɂ�̑��x
	static const float THETA_FLAME_MOVEMENT_;
	//���ɂ傤�ɂ�̕�
	static const float SIGNAL_RADIUS_;
	
	bool end_flag;
	bool start_flag;
	Vector3 startPos_;
	Vector3 pos_;
	float initMovement_;
	//���ɂ傤�ɂ�Ŏg��
	float theta_;

};