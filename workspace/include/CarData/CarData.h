#pragma once
#include"../system/system.h"
#include"../Steering/Steering.h"

#include <math.h>
#include <cmath>

#define PI 3.141592653589793
#define DIST (((PI) * (double)CAR_WHEEL_WIDTH) / 360.0f)

typedef struct WheelDist_s
{
	float left;
	float right;
} WheelDist;

class CarData
{
private:
	CORDINATE position;
	float car_angle;

	CarData( );
	~CarData( );
	CarData( const CarData &x );
	CarData&operator=( const CarData & ) { return *this; };

	int8 calcOdometry( WheelDist* wheel_dist );
public:
	static CarData &getInstance( )
	{
		static CarData carPosition;
		return carPosition;
	}

	int8 update( );

	CORDINATE getPos( void );

	int8 setPos( CORDINATE coordinate );

	float getAngle( void );

	int8 setAngle( float angle );
};