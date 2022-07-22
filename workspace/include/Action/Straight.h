#pragma once

#include "./Action.h"
#include "./system.h"
#include <cmath>
#include <iostream>
// #include 自己位置
// #include 台形制御
// #include 


/// 7/20 new
/// sakiyama
/// Straight
class Straight : public Action{
	private:
	COORDINATE 	target_coordinate;	// 目標座標

	public:
	Straight();
	Straight(COORDINATE target_coordinate);
	~Straight();

	virtual int8_t run(int32_t speed);
};