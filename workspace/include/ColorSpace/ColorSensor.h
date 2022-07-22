//メンバー　なし
//メソッド　init()int8,getRGB() RGB_DATA
//
//  ColorSpace.h
//  カラーセンサークラス
//

#pragma once
#include <cstdint>
#include <string.h>
#include <memory>
#include <string>
#include "ev3api.h"
#include "../system/system.h"
class ColorSensor
{
private:
public:
    ColorSensor();

    ~ColorSensor();

    int8 init();

    RGB_DATA getRGB();

    static ColorSensor& getInstance()
    {
        static ColorSensor ColorSensor_;	// インスタンスの生成 
        return ColorSensor_;
    }
};