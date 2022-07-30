/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 二輪差動型ライントレースロボットのTOPPERS/HRP3用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/
#include "ev3api.h"
#include "app.h"
#include "etroboc_ext.h"
#include "./workspace/include/Action/LineTrace.h"
#include "./workspace/include/Action/Curve.h"
#include "./workspace/include/Action/Straight.h"
#include "./workspace/include/CarData/CarData.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif
bool flag = false;
/**
 * EV3システム生成
 * モーター設定
 */
static void user_system_create()
{

}
static void user_system_destroy()
{

}
/*  スタート処理タスク */
void start_task(intptr_t unused)
{
    char command[] = {"logon -section -trace \n"};
    
    uint16 index = 0;
    ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
    /* 動的に生成するインスタンスの初期化 */
    user_system_create();
    //フライング
    while (1)
    {
        if (ev3_touch_sensor_is_pressed(EV3_PORT_1) == 1)
        {
            break;
        }
        tslp_tsk(10 * 1000U);
    }

    act_tsk(MAIN_TASK);
    ext_tsk();
}

/* メインタスク */
void main_task(intptr_t unused)
{
	CarData&            car_data    = CarData::getInstance();
	
	COORDINATE coor;
	COORDINATE now_coor;
	coor.x=0;
	coor.y=1570;
	/*
	GAIN gain;
	gain.p =0.5;
	gain.i = 0.5;
	gain.d = 0;
	
	Action* action = new LineTrace(gain,85,LEFT_LINE,coor);

	action->run(50);
	*/

	//Action* action = new Curve(200,LEFT_CURVE,coor);
	


	Action* action = new Straight(coor);
	while(1){
		car_data.update();
        action->run(0);
		now_coor = car_data.getPos();
		printf("x=%f,y=%f\n",now_coor.x,now_coor.y);
		if (now_coor.y > ((93 * 0.3527 * 2) + 1570)){
			printf("x=%f,y=%f\n",now_coor.x,now_coor.y);
			break;
		}
		tslp_tsk(10 * 1000U);
	}
	
   	
	ETRoboc_notifyCompletedToSimulator();
    ext_tsk();
}
