#pragma once
#include <cstdint>
#include <string.h>
#include <memory>
#include <string>
#include "ev3api.h"
#include "../system/system.h"

class HSV
{
private:
    uint16 hConvert(RGB_DATA);

    uint16 sConvert(RGB_DATA);

    uint16 vConvert(RGB_DATA);
public:
    HSV();

    ~HSV();

    HSV_DATA convert(RGB_DATA);
};