/// 2022/07/13
/// yoshitome
/// Curve

#include "./Action.h"

#define PAI         (3.14f)         // 円周率
#define LEFT_CURVE  (0)             // 左カーブ
#define RIGHT_CURVE (1)             // 右カーブ

#ifdef  EV3
#define CAR_WIDTH   (90)            // 車体幅(ごめんしらん)

#endif

#ifdef  SPIKE
#define CAR_WIDTH   (100)           // 車体幅(しらない)

#endif

class Curve : public Action{
private:
    float           radius;                 // 半径
    float           target_distance;        // 目標直線距離
    float           angle;                  // 角度
    float           circle;                 // 円周
    float           ratio_left;             // 左比率
    float           ratio_right;            // 右比率
    COORDINATE      target_coordinate;      // 目標座標
    COORDINATE      current_coordinate;     // 自己位置
    MOTOR_POWER     motor_power;            // モーターパワー
    int8_t          direction;              // カーブ方向

public:

    Curve();
    Curve(COORDINATE _coordenate, int8_t _direction);
    ~Curve();

    int8_t run(int32_t speed);
};