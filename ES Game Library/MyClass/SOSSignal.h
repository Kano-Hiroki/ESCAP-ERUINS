/*! @file  SOSSignal.h
	@brief SOSシグナルクラス　ヘッダー
	@author So Fujimura
	@date No.0 Start 20190213
 */
#pragma once
#include "../ESGLib.h"

class SOSSignal {

public:

	SOSSignal();
	~SOSSignal();

	//こっちは適当にsimpleshapeを読み込みま
	static void LoadModel();
	//こっちは指定したパスを読み込みます
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

	// SOSSignalが使うモデルデータです。
	static MODEL model_;
	//上がる速度
	static const float RISE_FLAME_MOVEMENT_;
	// うにょうにょの速度
	static const float THETA_FLAME_MOVEMENT_;
	//うにょうにょの幅
	static const float SIGNAL_RADIUS_;
	
	bool end_flag;
	bool start_flag;
	Vector3 startPos_;
	Vector3 pos_;
	float initMovement_;
	//うにょうにょで使う
	float theta_;

};