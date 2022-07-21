#pragma once
#include <cstdint>
#include <string.h>
#include <memory>
#include <string>
#include <math.h>
//#include "ev3api.h"


#define SYS_OK 0    //正常終了
#define SYS_NG 1    //異常終了
#define SYS_PARAM 2 //引数エラー

#define CAR_WIDTH       //車体の幅(mm)
#define CAR_WHEEL_WIDTH  //車輪の直径(mm)

// integer 8bit
using int8 = int8_t;

// integer 16bit
using int16 = int16_t;

// integer 32bit
using int32 = int32_t;

// integer 64bit
using int64 = int64_t;

// unsigned integer 8bit
using uint8 = uint8_t;

// unsigned integer 16bit
using uint16 = uint16_t;

// unsigned integer 32bit
using uint32 = uint32_t;

// unsigned integer 64bit
using uint64 = uint64_t;

// int pointer
using intptr = intptr_t;

// uint pointer
using uintptr = uintptr_t;

/* 列挙型の定義 */
enum SensorPort
{
  SENSOR_TOUCH, //タッチセンサー
  SENSOR_COLOR, //カラーセンサー
  SENSOR_SONAR, //超音波センサー
  SENSOR_GYRO,  //ジャイロセンサー
};


/* 構造体定義 */
// RGBの構造体
typedef struct RGB_TAG {	
	uint16 r;
	uint16 g;
	uint16 b;
}RGB_DATA;

//HSVの構造体
typedef struct HSV_TAG {	
	uint16 h;
	uint16 s;
	uint16 v;
}HSV_DATA;

typedef struct MOTOR_POWER_TAG {
	int32_t right;
	int32_t left;
}MOTOR_POWER;

typedef struct COORDINATE_TAG {
	float x;
	float y;
}COORDINATE;

typedef struct GAIN_TAG {
	float p;
	float i;
	float d;
}GAIN;