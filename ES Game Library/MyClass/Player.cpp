#include "Player.h"
//�̗͍ő�l�̐ݒ�
const int Player::BATTERY_MAX = 100;
const float Camera_Hikiguai = 500;

//�̗̓Q�[�W�֘A�̐ݒ�
const Vector3 Player::BATTERY_UI_POSITION = Vector3(950.0f, 30.0f, 0.0f); //�ʒu
const Vector3 Player::BATTERY_UI_INNER_RIVISION = Vector3(6.0f, 6.0f, 0.0f); //���g��`�悷��ۂ̈ʒu����̕␳
const Vector2 Player::BATTERY_UI_OUTER_SIZE = Vector2(299.0f, 38.0f);//�O�g�̃T�C�Y
const Vector2 Player::BATTERY_UI_INNER_SIZE = Vector2(278.0f, 26.0f);//���g�̃T�C�Y

void Player::Initialize() 
{
	//�r���[�|�[�g
	Viewport   view = GraphicsDevice.GetViewport();

	//�J����
	main_camera->SetView(Vector3(0.0f, 70.0f, -500.0f), Vector3(00.0f, 0.0f, 00.0f));
	main_camera->SetPerspectiveFieldOfView(45.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(main_camera);
	//���[�_�[
	radar_point[0] = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar2.png"));
	radar_point[1] = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar3.png"));
	radar_point[2] = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar4.png"));

	//���C�����C�g
	Main_light.Type = Light_Directional;
	Main_light.Diffuse = Color(1.0f, 1.0f, 1.0f); // �f�B�t���[�Y�F
	Main_light.Ambient = Color(1.0f, 1.0f, 1.0f); // �A���r�G���g�F
	Main_light.Specular = Color(1.0f, 1.0f, 1.0f); // �X�y�L�����[�F
	Main_light.Direction = Vector3(0, 90, 90);

	//�|�C���g���C�g(�v���C���[�̎�����Ƃ炷)
	point_light.Type = Light_Spot;
	point_light.Diffuse = Color(0.5f, 0.5f, 0.5f); // �f�B�t���[�Y�F
	point_light.Specular = Color(0.5f, 0.5f, 0.5f); // �X�y�L�����[�F
	point_light.Ambient = Color(0.3f, 0.3f, 0.3f); // �A���r�G���g�F
	point_light.Range = 30.0f; // ���C�g�̗L���͈�
	point_light.Attenuation0 = 1.0f; // �����萔
	point_light.Attenuation1 = 0.0f;
	point_light.Attenuation2 = 0.0f;
	point_light.Range = 1000.0f;
	point_light.Falloff = 1.0f;
	point_light.Direction = Vector3(0,90, 90);
	point_light_Theta = 80.0f;
	point_light.Theta = MathHelper_ToRadians(point_light_Theta);
	point_light.Phi = MathHelper_ToRadians(point_light_Theta+20.0f);

	//�X�|�b�g���C�g�I���I�t
	light_flag = false;

	//���C�g�͈̔͂�\�����郂�f��
	light_model = GraphicsDevice.CreateModelFromFile(_T("Player/Light.X"));
	light_model->SetScale(3);
	Material mat = light_model->GetMaterial();
	mat.Emissive = Color(0.5f, 0.5f, 0.5f);
	light_model->SetMaterial(mat);

	// �����蔻�萶��
	light_OBB = light_model->GetOBB();
	light_model_width = light_OBB.Radius.x;
	SimpleShape light_box;
	light_box.Type = Shape_Box;
	light_box.Width = light_OBB.Radius.x * 2;
	light_box.Height = light_OBB.Radius.y * 2;
	light_box.Depth = light_OBB.Radius.z * 3;
	light_prefab = GraphicsDevice.CreateModelFromSimpleShape(light_box);

    //�v���C���[
	player = GraphicsDevice.CreateAnimationModelFromFile(_T("Player/jiki8.X"));

	player->SetScale(0.15f);
	player->SetPosition(0,0,0);//���Ń|�W�V�������Z�b�g
	player->SetRotation(0, 0, 0);
	Material material;
	material.Diffuse = Color(0.5f, 0.5f, 0.5f);
	material.Ambient = Color(0.2f, 0.2f, 0.2f);
	material.Emissive = Color(1.0f, 1.0f, 1.0f);
	player->SetMaterial(material);
	tenp_material = material;
	//�q�[�����̃}�e����
	hit_material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	hit_material.Ambient = Color(1.0f, 1.0f, 1.0f);
	hit_material.Emissive = Color(1.0f, 1.0f, 1.0f);
	//�u�[�X�g
	boost = 0;
	boost_length = 0;
	boost_switch = 0;
	boost_recharge = 0;

	//�X�s�[�h
	speed = 0;

	//�}�E�X
	material.Diffuse = Color(1.0f, 0.0f, 0.0f);
	material.Ambient = Color(1.0f, 0.0f, 0.0f);

	material.Emissive = Color(1.0f, 0.0f, 0.0f);

	mouse = GraphicsDevice.CreateModelFromFile(_T("UI/Reticle.x"));
	mouse->SetMaterial(material);

	//�����蔻�萶��
	//�v���C���[
	OrientedBoundingBox pl_obb = player->GetOBB();//�Q�[�g��OBB�擾
	SimpleShape pl_box;//�{�b�N�X�𐶐�
	pl_box.Type = Shape_Box;
	pl_box.Width = pl_obb.Radius.x * 20;
	pl_box.Height = pl_obb.Radius.y * 5;
	pl_box.Depth = pl_obb.Radius.z * 3;//�Q�[�g�Ƒ傫�������킹��
	player_prefab = GraphicsDevice.CreateModelFromSimpleShape(pl_box);
	//���C�g

	DefaultFont = GraphicsDevice.CreateSpriteFont(_T("���C���I"),50);
	//�_��
	tenmetsu_flag = false;
	count_ = 0;
    //�_�łŎg���J�E���g
	//�G�t�F�N�g���J�����ɃZ�b�g	
	//---------------------------------------------------------------------
	//�o�b�e���[
	battery_mode = 0;

	battery = 500;
	battery = 100;
	battery_heal_time = 0;
	battery_count = 0;
	battery_time = 0;
	battery_sprite = GraphicsDevice.CreateSpriteFromFile(_T("UI/battery1.png"));
	battery_zanryou = GraphicsDevice.CreateSpriteFromFile(_T("UI/battery2.png"));
	speed_length = 0;
	speed_side = 0;
	mouse_pos = Vector3(player->GetPosition());

	//camera_stste = 0;
	plus_move = Vector3(0, 0, 0);
	minus_move = Vector3(0, 0, 0);
	move = Vector3(0, 0, 0);

	//���[�_�[
	radar_time = 120;
	radar_base = GraphicsDevice.CreateSpriteFromFile(_T("UI/radar/radar.png"));
	Grabity_move = Vector3(0, 0, 0);

	rising_downward = Vector3(0, 0, 0);
	fall_g  = 0;
	fall_up = 0;

	propeller_rotate = 0;
	//�o���A
	barrier_ = GraphicsDevice.CreateSpriteFromFile(_T("Efect/barrier3.png"));
	//�R�C���̓��萔
	coin_count = 0;
	around_    = 0;
	p_G        = 0;
	UD = Vector3(0, 0, 0);
	LR = Vector3(0, 0, 0);
	//�G�t�F�N�g������
	efect.Initialize(0.0625f, 10, (_T("Efect/exp.png")));
	exp_flame = 0;
	end_flag = false;
	BatteryGauge::LoadSprite();//�o�b�e���[�摜�ǂݍ���
	Battery_Gauge.Initialize();//�o�b�e���[������
	player->SetTrackEnable(1, FALSE);
	player->SetTrackEnable(2, FALSE);
	player->SetTrackLoopMode(0, AnimationLoopMode_Once);
	player_anim_statet = FALSE;
	track_mode_time = 0;	

}
void Player::Reset() {
	//�X�|�b�g���C�g�I���I�t
	light_flag = false;

	//���C�g�͈̔͂�\�����郂�f��b
	light_model->SetScale(3);
	Material mat = light_model->GetMaterial();
	mat.Emissive = Color(0.5f, 0.5f, 0.5f);
	light_model->SetMaterial(mat);

	// �����蔻�萶��

	player->SetScale(0.15f);
	player->SetPosition(0, 0, 0);//���Ń|�W�V�������Z�b�g
	player->SetRotation(0, 0, 0);

	//�u�[�X�g
	boost = 0;
	boost_length = 0;
	boost_switch = 0;
	boost_recharge = 0;

	//�X�s�[�h
	speed = 0;

	//�_��
	tenmetsu_flag = false;
	count_ = 0;
	//�_�łŎg���J�E���g
	//�G�t�F�N�g���J�����ɃZ�b�g	
	//---------------------------------------------------------------------
	//�o�b�e���[
	battery_mode = 0;

	battery = 500;
	battery = 100;
	battery_heal_time = 0;
	battery_count = 0;
	battery_time = 0;
	speed_length = 0;
	speed_side = 0;
	mouse_pos = Vector3(player->GetPosition());

	//camera_stste = 0;
	plus_move = Vector3(0, 0, 0);
	minus_move = Vector3(0, 0, 0);
	move = Vector3(0, 0, 0);

	//���[�_�[
	radar_time = 120;
	Grabity_move = Vector3(0, 0, 0);

	rising_downward = Vector3(0, 0, 0);
	fall_g = 0;
	fall_up = 0;

	propeller_rotate = 0;
	//�o���A
	//�R�C���̓��萔
	coin_count = 0;
	around_ = 0;
	p_G = 0;
	UD = Vector3(0, 0, 0);
	LR = Vector3(0, 0, 0);
	//�G�t�F�N�g������
	exp_flame = 0;
	end_flag = false;
	player->SetPosition(Start_Pos);
	main_camera->SetPosition(Vector3(Start_Pos.x, Start_Pos.y, Camera_Hikiguai));
	old_position = Start_Pos;
	ply_pos = Start_Pos;
	Battery_Gauge.Initialize();//�o�b�e���[������
}
//�}�b�v���珉�����W�𔽉f
void Player::SetPosition(Vector3 pos) 
{
	player->SetPosition(pos);
	old_position = pos;
	ply_pos      = pos;
	main_camera->SetPosition(Vector3(pos.x,pos.y,Camera_Hikiguai));
	Start_Pos = pos;
}
//�S�Ă𓝊�
void Player::PlayerUpdate(Ground &ground_,std::vector<Enemy_Base> &enemy, std::vector<SOSHuman>&human, Sigen_Item *item)
{
	key_buffer = Keyboard->GetBuffer();
	key_state = Keyboard->GetState();
	mouse_state = Mouse->GetState();
	mouse_buffer = Mouse->GetBuffer();
	pad_buffer = GamePad(0)->GetBuffer();
	pad_state = GamePad(0)->GetState();
	old_position = player->GetPosition();
	PlayerMove(ground_);
	radar(item);
	efect.Update((int)exp_flame, player->GetPosition()+Vector3(0,0,-100));//�G�t�F�N�g
	if (battery <= 0) 
	{
		Player_End();

		if (Battery_Gauge.GetChangingState() == CHANGING_STATE_NONE) 
		{
			;
		}
	}

	if (Battery_Gauge.GetChangingState() == CHANGING_STATE_UP) 
	{
		Heel_Efect();
	}
	else 
	{
		player->SetMaterial(tenp_material);
	}

	light_control();
	player_prefab->SetPosition(player->GetPosition());
	GraphicsDevice.SetCamera(main_camera);
	Battery_Gauge.Update();
	Battery_Gauge.SetTargetPersent((float)battery / (float)Player::BATTERY_MAX);
	
	if (battery >= 100) { battery = 100; }
}
//lerp���
Vector3 Vector3_Lerp(Vector3 A, Vector3 B, float t) {

	Vector3 YuiKyou = Vector3_Zero;

	YuiKyou.x = MathHelper_Lerp(A.x, B.x, t);
	YuiKyou.y = MathHelper_Lerp(A.y, B.y, t);
	YuiKyou.z = MathHelper_Lerp(A.z, B.z, t);

	return YuiKyou;
}

//�ړ��𓝊�
void Player::PlayerMove(Ground &ground_)
{
	battery_charge(heal_mode);

	//�o�b�e���[�Ǘ��e�X�g�p

	ply_pos = player->GetPosition();

	Vector3  up = player->GetUpVector();

	//----------------------------------------------------------------------------------------------
	//�㏸���~
	if (player_anim_statet == 0) //�㏸
	{
		anim_time += 0.02f;

		if (anim_time > 1.0f)
		{
			anim_time = 1.0f;
		}
		player->SetTrackPosition(0, anim_time);

		track_mode_time++;
		if (track_mode_time >= 120)
		{
			player_anim_statet = 1;
			anim_time = 0.7;
		}
	}
	else if (player_anim_statet == 1) //���~
	{
		anim_time -= 0.02f;
		if (anim_time < 0)
		{
			anim_time = 0;
		}
		player->SetTrackPosition(0, anim_time);
	}

	if (key_buffer.IsPressed(Keys_Up) || pad_buffer.IsPressed(GamePad_Button1) || pad_buffer.IsPressed(GamePad_Button2) ||
		pad_buffer.IsPressed(GamePad_Button3) || pad_buffer.IsPressed(GamePad_Button4))
	{
		if (anim_time >= 0) 
		{
			;
		}
		else 
		{
			anim_time = 0;

		}
		player_anim_statet = 0;
	}

	if (key_state.IsKeyDown(Keys_Up) || pad_state.Buttons[1]) 
	{
		track_mode_time = 0;
		if (anim_time >= 0.5)
		{
			player->SetTrackEnable(1, TRUE);
			player->SetTrackPosition(1, propeller_rotate / 7);
		}

		//�㏸���x�̉��Z
		p_G -= 0.045f;
		propeller_rotate += 0.15f;
		battery_time++;
		rising_downward.x++;
	}
	else
	{
		player->SetTrackEnable(1, FALSE);
		p_G += 0.0425f;
		propeller_rotate -= 0.015f;
		rising_downward.x--;
	}

    //�v���y���̉�]�̓}�C�i�X�ɂȂ�Ȃ�//
	if (propeller_rotate <= 0) { propeller_rotate = 0; }

	//�d�͂��v�Z  *1
	if (p_G < -2) { p_G = -2; }

	//�����ő呬�x�͂����ł��߂悤!
	p_G = min(p_G, 3.0f);

	//�v���C���[��y���ɏd�͂����Z
	ply_pos.y -= p_G;

	//�f�o�b�O----------------------------------------
	if (key_state.IsKeyDown(Keys_Left))
	{
		LR.x -= 0.5f;
	}
	if (key_state.IsKeyDown(Keys_Right))
	{
		LR.x += 0.5f;
	}

	if (Axis_Center != (float)pad_state.X) 
	{
		LR += Vector3_Right * (((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center)) / 10.0f;// / 20;
		if (Vector3_Length(LR) > 10.0f) 
		{
			LR = Vector3_Normalize(LR) * 10.0f;
		}
	}
	else 
	{
		LR *= 0.95f;
	}

	ply_pos += LR;

	rising_downward.z = -60.0f*(((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center));

	player->SetRotation(rising_downward);

	if (battery_time >= 180.0f) //�o�b�e���[�^�C�����������z������
	{
		battery_time = 0.0f;
		battery--; //�o�b�e���[��1���炷
	}

	player->SetPosition(ply_pos); //�㏸���~

	if (rising_downward.x >= 20.0f) //�㏸�p�x�ő�l
	{
		rising_downward.x = 20.f;
	}
	if (rising_downward.x <= -25.0f) //���~�p�x�ő�l
	{
		rising_downward.x = -25.0f;
	}

	//-------------------------------------------------------------------------

	//���E�p�x�ő�l
	rising_downward.z -= 10.0 * (((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center));

	//���E�p�x�ő�l
	if (rising_downward.z >= 45)
	{
		rising_downward.z = 45;
	}
	else if (rising_downward.z <= -45)
	{
		rising_downward.z = -45;
	}

	player->SetRotation(rising_downward);

	//���C�g�֌W---------------------------------------
	Reflection(ground_);

	//�h��
	YurePower = max(YurePower - 0.5f, 0.0f);
	YureYuri.x = MathHelper_Random(-1.0f, 1.0f)*YurePower;
	YureYuri.y = MathHelper_Random(-1.0f, 1.0f)*(YurePower*2.0f);

	//�J����
	main_camera->SetPosition(Vector3_Lerp(main_camera.GetPosition(), ply_pos - Vector3(-LR.x*30.0f, p_G * 20, Camera_Hikiguai), 0.05f) + YureYuri);
}

//�ǔ���
void Player::Reflection(Ground &ground_) {
	float kabe_r = FLT_MAX;
	float kabe_l = FLT_MAX;
	float kabe_u = FLT_MAX;
	float kabe_d = FLT_MAX;
	float  min_dist_r = FLT_MAX;
	float  min_dist_l = FLT_MAX;
	float  min_dist_u = FLT_MAX;
	float  min_dist_d = FLT_MAX;
	Vector3 hozon_r;
	Vector3 hozon_l;
	Vector3 hozon_u;
	Vector3 hozon_d;

	Vector3 N_R;
	Vector3 N_L;
	Vector3 N_U;
	Vector3 N_D;
	Vector3 N;

	Vector3   pos = player->GetPosition();
	pos.z = 0.0f;
	old_position.z = 0.0f;
	Vector3   dir = Vector3_Normalize(pos - old_position);//���̍��W��1f�O�̍��W�Ŋp�x�����߂�
  //���C���΂�------------------------------------------------------------------------------------------------------------------------------
		min_dist_u = FLT_MAX;
		hozon_u = Vector3_Zero;
		ground_.re_ground()->IntersectRay(pos, dir, &min_dist_u, &hozon_u);//�ǔ���
		if (min_dist_u < kabe_u) 
		{
			kabe_u = min_dist_u;
			N_U = hozon_u;
		}
	
	//�����������𒲂ׂ�------------------------------------------------------------------------------------------------------------------------------

	if (kabe_u < 15) 
	{
		N = N_U;
		F = dir;//�i�s�x�N�g��
		hansya = F + 2 * Vector3_Dot(-F, N)*N;//���˃x�N�g��
		reflection_count = 5;//���˂̋���
		if (!barrier_flag) //�o���A�𒣂��ĂȂ���΃_���[�W
		{
			battery -= 5;
		}
		LR = Vector3_Zero;
		p_G = 0;
		reflection_flag = true;
		barrier_flag = true;
	}

	//�����������̏���
	if (reflection_flag) 
	{
		//�h��Z�b�g
		YurePower = 5.0f;

		reflection_count--;
		hansya.z = 0;
		ply_pos += hansya * reflection_count;
		//���������������------------------------------------------------------------------------------------------------------------------------------

		if (kabe_u < 15) //�ǂ���Ȃ������瓮��
		{
			F = dir;//�i�s�x�N�g��

			hansya = F + 2 * Vector3_Dot(-F, N_U)*N_U;//���˃x�N�g��
			reflection_count = 5;
			reflection_flag = true;
			barrier_flag = true;
			LR = Vector3_Zero;
			p_G = 0;
		}

		if (reflection_count <= 0) {
			reflection_flag = false;

		}
	}
	player->SetPosition(ply_pos);
}
//�Q�[���I�[�o�[����
void Player::Player_End() {
	exp_flame += 0.2;

	if (exp_flame >= 9) 
	{
		end_flag = true;
	}
}
void Player::Heel_Efect() {
	heal_count++;
	if (heal_count % 6 == 0) 
	{
		player->SetMaterial(hit_material);
	}
	else 
	{
		player->SetMaterial(tenp_material);

	}

}
//���C�g�֌W
void Player::light_control() 
{

	//�|�C���g���C�g��(�v���C���[�̎�����Ƃ炷)
	point_light.Position = player->GetPosition() + Vector3(0, 0, -200);
	point_light.Direction = Vector3_Forward;
	point_light.Theta = MathHelper_ToRadians(point_light_Theta);
	point_light.Phi = MathHelper_ToRadians(point_light_Theta + 20.0f);

	//���C�g���Z�b�g
	
	if (light_flag) 
	{
		//���C�g�I�t
		GraphicsDevice.SetLight(point_light, 1,1);
		GraphicsDevice.SetLight(Main_light, 999999,0);

	}
	else
	{
		//���C�g�I��
		GraphicsDevice.SetLight(point_light, 1,0);
		GraphicsDevice.SetLight(Main_light, 999999,1);
	}
}

void Player::Light_Start(bool a) {
	light_flag = a;
}

//�U�����󂯂����̃��A�N�V����
void Player::Enemy_hit() 
{
	if (!tenmetsu_flag) 
	{
		tenmetsu_flag = true;
	}
}
void Player::Hit_Coin() {
	coin_count++;
}
//�o�b�e���[�֌W
void Player::battery_charge(int a)
{
	if (battery < 100)
	{
		if (a == 99)
		{
			;
		}
		if (a == 0) //�o�b�e���[��(�ɏ�)
		{
			battery_heal(); //�o�b�e���[��
			if (battery_count >= 2) //�o�b�e���[�񕜗�
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 1) //�o�b�e���[��(��)
		{
			battery_heal();
			if (battery_count >= 10)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 2) //�o�b�e���[��(�m�[�}��)
		{
			battery_heal();
			if (battery_count >= 20)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 3) //�o�b�e���S��(��)
		{
			battery_heal();
			if (battery_count >= 50)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 4) //�o�b�e���[�S��
		{
			battery_heal();
			if (battery_count >= 100)
			{
				battery_count = 0;
				heal_mode = 99;
			}
		}
		else if (a == 10) //�_���[�W�̔���
		{
			battery_damage();
			if (battery_count >= 25) 
			{
				battery_count = 0;
			}
		}
	}
}
void Player::battery_heal()
{
	battery_heal_time++;
	if (battery_heal_time >= 20)  //�񕜑��x
	{
		battery_count++;          //�J�E���g(�񕜗�)
		battery_heal_time = 0;
		battery++;                //��(�o�b�e���[)
	}
}
void Player::battery_damage()
{
	battery_heal_time++;
	if (battery_heal_time >= 20)  //�_���[�W���x
	{
		battery_count++;          //�J�E���g(�_���[�W)
		battery_heal_time = 0;
		battery--;                //�_���[�W(�o�b�e���[)
	}
}

void Player::battery_heal_state(int a) 
{	
	battery += a;
}
void Player::radar(Sigen_Item *item)
{
	//���[�_�[

	Vector3 item_pos[3];
	int get_end_flag[3];
	int get_start_flag[3];
	p_point = player->GetPosition();

	radar_time--;

	if (radar_time <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			item_pos[i] = item[i].GetPos();
			get_end_flag[i] = item[i].GetEndFlag();
			get_start_flag[i] = item[i].GetStartFlag();

			if (get_start_flag[i] && !get_end_flag[i])
			{
				dist[i] = Vector3_Distance(p_point, item_pos[i]);

				xxx[i] = (p_point.x - item_pos[i].x) / 8000 * 170.0f; //x�ɓ����ϐ� = (�v���C���[x - ����x) �� ���G(���[�_�[)�͈� �~ ���[�_�[(�摜)�̃T�C�Y
				yyy[i] = (p_point.y - item_pos[i].y) / 8000 * 170.0f; //����y���o�[�W����

			}
			else
			{
				xxx[i] = FLT_MAX;
				yyy[i] = FLT_MAX;
			}
		}
		radar_time = 120;
	}
}
//�d�̓G���A
void Player::Grabity(int houkou) 
{
	if (houkou == UP) 
	{
		Grabity_move = Vector3(0, 1, 0);
	}
	else if (houkou == DOWN) 
	{
		Grabity_move = Vector3(0, -1, 0);
	}
	else 
	{
		Grabity_move = Vector3(0, 0, 0);
	}
}
void Player::Wiggler(float randam)
{
	main_camera->SetPosition(Vector3(ply_pos.x, ply_pos.y, -300.0f) + Vector3(MathHelper_Random(-randam, randam), MathHelper_Random(-randam, randam), 0));
}
//�`��֌W
void Player::Draw()	 
{
	if (!tenmetsu_flag) 
	{
		player->Draw();
		//player_prefab->Draw();
	}
	else 
	{
		count_++;
		if (count_ % 3 == 0) 
		{
			player->Draw();
		}
		if (count_ > 60) 
		{
			tenmetsu_flag = false;
			count_ = 0;
		}
	}

	//mouse->Draw();//�}�E�X
	//�o���A	
	barrier_pos = player->GetPosition();
	barrier_pos.z = 0.0f;
	barrier_pos = GraphicsDevice.WorldToScreen(barrier_pos);
}
void Player::Alpha_Draw()
{
	if (battery <= 0) 
	{
		efect.Draw();
	}
}
void Player::Ui()
{
	//SpriteBatch.DrawString(DefaultFont, Vector2(450.0f, 0.0f), Color(255, 255, 255), _T("�o�b�e���[:%d��"), battery);
	//�o���A
	if (barrier_flag) {
		count_++;
		if (count_ % 3 == 0)
		{
			SpriteBatch.Draw(*barrier_, barrier_pos + Vector3(-100.0f, -100.0f, 0.0f));
		}
		if (count_ > 60)
		{
			barrier_flag = false;
			count_ = 0;
		}
	}

	SpriteBatch.Draw(*radar_base, Vector3(0.0f, 0.0f, 0.0f));
	for (int i = 0; i < 3; i++)
	{
		if (dist[i] >= 4000) //���G�������z������
		{
			;
		}
		else
		{
			//���_(�G�l�~�[)�̕\��
			SpriteBatch.Draw(*radar_point[i], Vector3(68 - xxx[i], 68 + yyy[i], 0), (float)radar_time / 120);
			//((float)�o�ߎ��ԁ��ő厞��)
		}
	}

	Battery_Gauge.Draw(Player::BATTERY_UI_POSITION);//�o�b�e���[�Q�[�W
}