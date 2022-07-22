#include "../../include/ColorSpace/ColorSpace.h"
#include "../../include/ColorSpace/ColorSensor.h"
#include "../../include/ColorSpace/HSV.h"

ColorSpace::ColorSpace(){
    ColorSensor color = ColorSensor::getInstance();
    rgb=color.getRGB();
    HSV Hsv;
    hsv=Hsv.convert(rgb);
}

ColorSpace::~ColorSpace(){}


RGB_DATA ColorSpace::getRGB(){
    return rgb;
}

HSV_DATA ColorSpace::getHSV(){
    return hsv;
}


int8_t ColorSpace::update(){
    HSV Hsv;
    ColorSensor color = ColorSensor::getInstance();
    rgb=color.getRGB();
    hsv=Hsv.convert(rgb);
    return SYS_OK;
}