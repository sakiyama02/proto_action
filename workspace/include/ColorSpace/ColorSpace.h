#pragma once
#include <cstdint>
#include <string.h>
#include <memory>
#include <string>
#include "ev3api.h"
#include "../system/system.h"


class ColorSpace
{
private:
    RGB_DATA rgb;
    HSV_DATA hsv;
public:
	ColorSpace();

	~ColorSpace();
    HSV_DATA getHSV();
	RGB_DATA getRGB();
    int8 update();
	static ColorSpace& getInstance()
    {
        static ColorSpace ColorSpace_;	// インスタンスの生成 
        return ColorSpace_;
    }
}; 