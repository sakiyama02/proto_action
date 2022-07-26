COPTS += -DMAKE_EV3
COPTS += -DMAKE_EV3
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += \

APPL_CXXOBJS += \
				system.o\
				LineTrace.o\
				Action.o\
				Controller.o\
				PIDControl.o\
				ColorSensor.o\
				ColorSpace.o\
				HSV.o\
				CarData.o\
				LeftMotor.o\
				Motor.o\
				RightMotor.o\
				Steering.o\
				AccelerationCurve.o\
				AccelerationDesigner.o\
				TrapezoidControl.o\
				Curve.o\
#
SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries


#include $(mkfile_path)/workspace/library/RyujiEv3/Makefile

endif 

# COPTS += -DMAKE_BT_DISABLE

APPL_DIRS +=\
	$(mkfile_path)workspace/src/Action\
	$(mkfile_path)workspace/src/ColorSpace\
	$(mkfile_path)workspace/src/Steering\
	$(mkfile_path)workspace/src/system\
	$(mkfile_path)workspace/src/CarData\

INCLUDES +=\
	-I$(mkfile_path)workspace/include/Action\
	-I$(mkfile_path)workspace/include/ColorSpace\
	-I$(mkfile_path)workspace/include/Steering\
	-I$(mkfile_path)workspace/include/system\
	-I$(mkfile_path)workspace/include/CarData\

COPTS += -I$(ETROBO_HRP3_WORKSPACE)/etroboc_common
COPTS += -DMAKE_EV3
COPTS += -std=gnu++11
COPTS += -fno-threadsafe-statics
