#include "../../include/ColorSpace/HSV.h"
#include <algorithm>
#include <vector>
using namespace std;
HSV::HSV(){}

HSV::~HSV(){}

HSV_DATA HSV::convert(RGB_DATA _rgbData){
    HSV_DATA hsvTmp;

    hsvTmp.h=hConvert(_rgbData);
    hsvTmp.s=sConvert(_rgbData);
    hsvTmp.v=vConvert(_rgbData);
    
    return hsvTmp;
}


uint16 HSV::hConvert(RGB_DATA _rgbData){
    uint16 hdata=0;
    double htmp=0.0f;
    vector<int> vec;
    vector<int>::iterator itr;
    vec.push_back(_rgbData.r);
    vec.push_back(_rgbData.g);
    vec.push_back(_rgbData.b);
    
    auto minmax= minmax_element(vec.begin(), vec.end());
    size_t n_count = count(vec.begin(), vec.end(),*minmax.second);
    if(n_count==3){
        hdata=0;
        return hdata;
    }
    
    itr = std::find(vec.begin(), vec.end(),*minmax.second);
    const int wanted_index = std::distance(vec.begin(), itr);
    //r
    if(wanted_index==0){
        ++itr;
        htmp=(double)(60*((double)(*itr-*(++itr)))/(double)(*minmax.second-*minmax.first));
    }
    //g
    else if(wanted_index==1){
        ++itr;
        htmp=(double)(60*((double)(*itr-*vec.begin())/(double)(*minmax.second-*minmax.first)))+120;
    }
    //b
    else{
        --itr;
        htmp=(double)(60*((double)(*vec.begin()-*itr)/(double)(*minmax.second-*minmax.first)))+240;
    }
    if(htmp<0){
        htmp+=360;
    }
    hdata=round(htmp);
    printf("%d\n",hdata);
    return hdata;
}

uint16 HSV::sConvert(RGB_DATA _rgbData){
    uint16 sdata=0;
    float max_data = 0;
    float min_data = 0;

    //RGBの最大値を取得
    if(_rgbData.r >= _rgbData.g && _rgbData.r >= _rgbData.b)
    {
        max_data = _rgbData.r;
    }
    else if(_rgbData.g >= _rgbData.r && _rgbData.g >= _rgbData.b)
    {
        max_data = _rgbData.g;
    }
    else if(_rgbData.b >= _rgbData.r && _rgbData.b >= _rgbData.g)
    {
        max_data = _rgbData.b;
    }

    //RGBの最小値を取得
    if(_rgbData.r <= _rgbData.g && _rgbData.r <= _rgbData.b)
    {
        min_data = _rgbData.r;
    }
    else if(_rgbData.g <= _rgbData.r && _rgbData.g <=_rgbData.b)
    {
        min_data = _rgbData.g;
    }
    else if(_rgbData.b <= _rgbData.r && _rgbData.b <= _rgbData.g)
    {
        min_data = _rgbData.b;
    }

    sdata = ((max_data -min_data) / max_data) * 255 ;
    return sdata;
}

uint16 HSV::vConvert(RGB_DATA _rgbData){
    uint vdata=0;
    //hsvのv値を格納
    if(_rgbData.r >= _rgbData.g && _rgbData.r >= _rgbData.b)
    {
        vdata= _rgbData.r;
    }
    else if(_rgbData.g >= _rgbData.r && _rgbData.g >= _rgbData.b)
    {
        vdata= _rgbData.g;
    }
    else if(_rgbData.b >= _rgbData.r && _rgbData.b >= _rgbData.g)
    {
        vdata= _rgbData.b;
    }
    return vdata;
}