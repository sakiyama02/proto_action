#pragma once
#include <cstdint>
#include <string.h>
#include <memory>
#include <string>
#include "ev3api.h"
#include "../system/system.h"

class Controller
{
protected:
    float motor_revision;
    float deviation;
    virtual int8 calc();
public:
    Controller();

    ~Controller();

    int8 run(float);
};