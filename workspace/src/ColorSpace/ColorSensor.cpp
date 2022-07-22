#include "../../include/ColorSpace/ColorSensor.h"
ColorSensor::ColorSensor(){
    ER errChk = ev3_sensor_config(static_cast<sensor_port_t>(SENSOR_COLOR), COLOR_SENSOR);

}

ColorSensor::~ColorSensor(){}


RGB_DATA ColorSensor::getRGB(){
    rgb_raw_t rgbTmp;
    RGB_DATA rgbData;
    memset(&rgbTmp,0,sizeof(rgb_raw_t));
    ev3_color_sensor_get_rgb_raw(static_cast<sensor_port_t>(SENSOR_COLOR), &rgbTmp);
    rgbData.r = rgbTmp.r;
    rgbData.g = rgbTmp.g;
    rgbData.b = rgbTmp.b;
    return rgbData;
}
