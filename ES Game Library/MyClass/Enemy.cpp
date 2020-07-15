#include"Enemy.h"
//動かない
//void Enemy_0::Move(std::vector<Ground> &ground, Player player){
//	enemy_pattern = ENEMY_0;
//}
////左に流れてく
//void Enemy_1::Move(std::vector<Ground> &ground,Player player) {
//	enemy->SetRotation(0, 270, 0);
//	enemy->Move(0, 0, speed);
//	enemy_pattern = ENEMY_1;
//}
////右に流れてく
//void Enemy_2::Move(std::vector<Ground> &ground, Player player) {
//	enemy->SetRotation(0, 90, 0);
//	enemy->Move(0, 0, speed);
//	enemy_pattern = ENEMY_2;
//}
////下に流れてく
//void Enemy_3::Move(std::vector<Ground> &ground, Player player) {
//	enemy->Move(0, -speed, 0.0f);
//	enemy_pattern = ENEMY_3;
//}
////上に流れてく
//void Enemy_4::Move(std::vector<Ground> &ground, Player player) {
//	enemy->Move(0, speed, 0.0f);
//	enemy_pattern = ENEMY_4;
//}
////波移動　右から左
//void Enemy_5::Move(std::vector<Ground> &ground, Player player) {
//	float r = 3;
//	enemy_pattern = ENEMY_5;
//	Vector3 pos = enemy->GetPosition();
//	thetai += 3;
//	pos.x -= 2;
//	pos.y = r * MathHelper_Cos(thetai) + 100;
//	enemy->SetPosition(pos);
//}
////ついてくる
//void Enemy_6::Move(std::vector<Ground> &ground,Player player) {
//	Vector3 diy;
//	Vector3 p_pos = player.re_player()->GetPosition();
//	Vector3 e_pos = enemy->GetPosition();
//	diy = Vector3_Normalize(p_pos - e_pos);
//	enemy->SetPosition(e_pos += diy * speed);
//	enemy_pattern = ENEMY_6;
//}
//void Enemy_7::Initialize(Vector3 pos, float scale, int speed_, LPCTSTR model_file) {
//	Enemy_Base::Initialize(pos, scale, speed_, model_file);
//	move_state = 1;
//	move_count = 0;
//	rotation_count = 0;
//	move_random = MathHelper_Random(100, 300);
//	rotation_random = MathHelper_Random(100, 300);
//}
////ゴキブリムーブ
//void Enemy_7::Move(std::vector<Ground> &ground, Player player) {
//	float kabe = FLT_MAX; 
//	float min_dist = FLT_MAX;
//	
//	if (move_state == 0) {//移動状態
//		enemy->Move(0, 1, 0);
//		move_count += 1;
//		for (int s = 0; s < ground.size(); s++) {
//			ground[s].re_ground()->IntersectRay(enemy->GetPosition(), enemy->GetFrontVector(), &min_dist);//壁判定
//			if (min_dist < kabe)
//				kabe = min_dist;
//
//		}
//		if (move_count >= move_random || kabe <= 20) {
//			move_state = 1;
//			rotation_count = 0;
//			rotation_random = MathHelper_Random(10, 360);
//		}
//	}
//	else if (move_state == 1) {//回転状態
//		enemy->Rotation(0, 0, 1);
//		rotation_count += 1;
//		if (rotation_count >= rotation_random) {
//			move_state = 0;
//			move_count = 0;
//			move_random = MathHelper_Random(30, 200);
//		}
//		
//	}
//    
//}
//
