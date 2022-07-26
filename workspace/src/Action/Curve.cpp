/// 2022/07/13
/// yoshitome
/// Curve

#include "./Curve.h"

/// コンストラクタ引数なし
Curve::Curve(){};

/// コンストラクタ引数あり
Curve::Curve(COORDINATE _coordinate, int8_t _direction){
    target_coordinate   = _coordinate;
    direction           = _direction;
}

Curve::~Curve(){};

int8_t Curve::run(int32_t speed){
    if( speed < -100 || speed > 100 ) {
        return SYS_PARAM;
    }

    // 変数宣言
    CarData&            car_data    = CarData::getInstance();
    TrapezoidControl&   trapezoid   = TrapezoidControl::getInstance();

    // 変数初期化
    radius              = 0.0f;
    target_distance     = 0.0f;
    circle              = 0.0f;
    ratio_left          = 0.0f;
    ratio_right         = 0.0f;
    current_coordinate  = car_data.getPos();

    /// 走行距離計算
    // 自己位置、目標座標感の距離計算
    // 直線距離 = √ (x2-x)(x2-x) + (y2-y)(y2-y)
    target_distance = std::sqrt( std::pow(target_coordinate.x - current_coordinate.x, 2) + std::pow(target_coordinate.y - current_coordinate.y, 2) );
    // 半径 半径 目標座標までの距離　から角度計算
    //        b*b + c*c - a*a
    // cosA = ----------------
    //              2bc
    angle = std::cos(( std::pow(radius, 4) - std::pow(target_distance, 2) ) / (std::pow(radius,2) * 2));
    // 角度と辺の長さから扇形の円周を求める
    // 円周　＝　2πr * (角度 / 360)
    circle = 2 * PAI * radius * (angle / 360);


    /// 加減速どうこう


    /// 比率計算
    // 左カーブの比率
    if( direction == 0 ) {
        ratio_left = (radius - (CAR_WIDTH / 2)) / (radius + (CAR_WIDTH / 2));
        ratio_right = 1;
    } 
    // 左カーブの比率
    else if( directio == 1 ) {
        ratio_left  = 1;
        ratio_right = (radius - (CAR_WIDTH / 2)) / (radius + (CAR_WIDTH / 2));
    }
    // カーブの比率計算
    motor_power.left = speed * ratio_left;
    motor_power.right = speed * ratio_right;

    return SYS_OK;


}