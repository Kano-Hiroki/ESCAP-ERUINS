#pragma once

//enum 定義用ファイル
enum GAME_MODE {
	TITLE,
	MAIN,
	GAMEOVER,
	CLEAR,
	MOVE,
	MANUAL
};
enum HOUKOU {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	START
};
enum SHOTMODE {
	NORMAL,
	MISSILE
};
enum GUN {
	HANDGUN,
	ASSAULT,
    SHOTGUN
};
enum ENEMY_PATTERN {
	ENEMY_0,
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_5,
	ENEMY_6,
	ENEMY_7,
	ENEMY_8,
	ENEMY_9,
	ENEMY_10,

};
enum Item {
	BATTERY,
	COIN,
    HITO
};
//配列の最大数
 enum { ENEMY_MAX = 5 };
 enum { OBJECT_MAX = 2 };
 enum { BLOCK_MAX = 6 };
 //マップの幅
 enum { LENGTH = 15 };//縦
 enum { WIDTH = 7 };//横

 enum CHANGING_STATE {

	 CHANGING_STATE_NONE,
	 CHANGING_STATE_UP,
	 CHANGING_STATE_DOWN

 };
 enum COIN_TYPE {
	 RED,
	 GREEN,
	 BLUE
 };