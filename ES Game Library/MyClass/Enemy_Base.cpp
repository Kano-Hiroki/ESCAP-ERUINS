#include"Enemy.h"

void Enemy_Base::Initialize(Vector3 pos,float scale,int speed_,LPCTSTR model_file) {
	efect.Initialize(0.0625f, 10, (_T("Efect/exp.png")));
	enemy = GraphicsDevice.CreateModelFromFile(model_file);
	enemy->SetScale(scale);//大きさ
	enemy->SetPosition(pos);
	//マテリアル
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(0.2f, 0.2f, 0.2f);
	enemy->SetMaterial(material);
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	//当たった時のマテリアル
	hit_material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	hit_material.Ambient = Color(0.3f, 0.5f, 0.2f);
	hit_material.Emissive = Color(0.5f, 0.5f, 0.0f);
	//当たり判定生成
	OrientedBoundingBox obb = enemy->GetOBB();//ゲートのOBB取得
	SimpleShape box;//ボックスを生成
	box.Type = Shape_Box;
	box.Width = obb.Radius.x * 1;
	box.Height = obb.Radius.y * 1;
	box.Depth = obb.Radius.z * 1;
	enemy_prefab = GraphicsDevice.CreateModelFromSimpleShape(box);
	//パラメータ初期化
	end_flag = false;
	count = 0;
	hit_flag = false;
	thetai = 0;
	exp_flag = false;
	exp_flame = 0;
	tenp_material = enemy->GetMaterial();
	tenp_sprite = enemy->GetTexture();
	move_state = 0;
}
void Enemy_Base::Reset() {
	//パラメータ初期化
	end_flag = false;
	count = 0;
	hit_flag = false;
	thetai = 0;
	exp_flag = false;
	exp_flame = 0;
	tenp_material = enemy->GetMaterial();
	tenp_sprite = enemy->GetTexture();
	move_state = 0;

}
void Enemy_Base::Main(Ground &ground,Player &player) {
	if (!end_flag) {
	}
	Move(ground, player);//移動処理

	//攻撃食らった時のリアクション
	if (hit_flag) {
		Hit_Reaction();
	}
	//HPが0以下になったら爆発して消える
	if (end_flag) {
		exp();
		efect.Update((int)exp_flame,enemy->GetPosition());
	}

}

//◆ラジアン→度数変換
//(rad 変換したい度数) 戻り値 変換されたラジアン
float Deg(float rad) {
	return rad * (180 / __PI__);//(配列を使ってのメモリ削減無し)
}

//◆度数→ラジアン変換
//(deg 変換したいラジアン) 戻り値 変換された度数
float Rad(float deg) {
	return deg * (__PI__ / 180);
}

//◆数値の符号を調べる
//戻り値 正　1 
//　　　　  負 -1 
//　　　　　0
int Sgn(int a) {
	if (a > 0) return 1;
	if (a < 0) return -1;
	return 0;
}

//動き
void Enemy_Base::Move(Ground &ground, Player &player) {
	//速度制御
	SpeedControl();

	//ホーミング時間を減らす
	HomingFrame = max(HomingFrame-1,0.0f);

	//移動量
	Vector3 MovePower = Vector3_Zero;
	//移動量を指定
	MovePower.x = cos(Rad(Kyou_x_Aya)) * Speed;
	MovePower.y = sin(Rad(Kyou_x_Aya)) * Speed;

	//動かす
	enemy->Move(MovePower);

	//ホーミング時間が切れているならホーミング処理をカット
	if (HomingFrame <= 0)  return;

	//※計算用
	Vector3 PlayerPos = player.re_ply_prefab()->GetPosition();
	Vector3 EnemyPos = enemy->GetPosition();

	//移動する角度
	float TagetDir = Deg(atan2f( PlayerPos.y - EnemyPos.y , PlayerPos.x - EnemyPos.x ));
	
	//旋回量調整用
	float Saku_x_Hima = TagetDir - Kyou_x_Aya;
	if (Saku_x_Hima >= 180) Saku_x_Hima -= 360;
	if (Saku_x_Hima <= -180) Saku_x_Hima += 360;

	//最終的な移動角度
	Kyou_x_Aya += (Sgn(Saku_x_Hima)*SEIYASEIYA);
}

//スピード制御
void Enemy_Base::SpeedControl() {
	if (MaxSpeed>0.0f) {
		Speed = min(Speed + AddSpeed, MaxSpeed);
	}
	else {
		Speed = max(Speed + AddSpeed, MaxSpeed);
	}
}

//食らった時のリアクション
void Enemy_Base::Hit_Reaction() {
	count++;
	if (count % 6 == 0) {
		enemy->SetTexture((IDirect3DBaseTexture9*)nullptr);//無のテクスチャーをセットする
		enemy->SetMaterial(hit_material);
	}
	else {
		enemy->SetTexture(tenp_sprite);//元のテクスチャーを入れる
		enemy->SetMaterial(tenp_material);

	}
	if (count > 30) {
		enemy->SetTexture(tenp_sprite);
		enemy->SetMaterial(tenp_material);
		hit_flag = false;
		count = 0;
	}
}
//弾が当たった時の処理
void Enemy_Base::Shot_Hit() {
	if (!hit_flag) {
		hit_flag = true;
		//hit_effeck->Play(enemy->GetPosition());

	}
}
//爆発
void Enemy_Base::exp() {
	exp_flame += 0.2;

	if (exp_flame >= 9) {
		exp_flag = false;
	}
}
//描画
void Enemy_Base::Draw() {
	if (!end_flag) {
		enemy->Draw();
		enemy_prefab->SetPosition(enemy->GetPosition());
		enemy_prefab->SetDirection(enemy->GetDirectionQuaternion());

	}
}
void Enemy_Base::Efect_Draw() {
	if (end_flag) {
		efect.Draw();
	}

}


