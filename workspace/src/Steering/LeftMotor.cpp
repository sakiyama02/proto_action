#include "../../include/Steering/LeftMotor.h"
#include "../../include/Steering/LeftMotor.h"
#include "../../include/Steering/Motor.h"

LeftMotor::LeftMotor()
{
	portNum = EV3_PORT_C;
	ev3_motor_config( static_cast<motor_port_t>(portNum), LARGE_MOTOR );
}

LeftMotor::~LeftMotor()
{
}
