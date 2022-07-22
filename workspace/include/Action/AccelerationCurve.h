///
/// @file 加速度曲線クラス
/// @note 加速度曲線式を作成する
/// @date 2022/06/29 谷口拓海
///
#ifndef ACELLCURVE_HEADER
#define ACELLCURVE_HEADER

#include <cmath>
#include <complex>
#include <iostream>
#include <ostream>


class AccelCurve
{
public:
	AccelCurve();
	~AccelCurve();

	void reset(const float j_max, const float a_max, const float v_start, const float v_end);

	static float calcVelocityEnd(const float j_max, const float a_max,
		const float vs, const float vt, const float d);

	static float calcVelocityMax(const float j_max, const float a_max,
		const float vs, const float ve, const float d);

	static float calcMinDistance(const float j_max, const float a_max,
		const float v_start, const float v_end);

	// コンストメンバ変数
	/**
	* @brief 躍度
	*/
	float j(const float t)const {
		if (t <= t0)
			return 0;
		else if (t <= t1)
			return jm;
		else if (t <= t2)
			return 0;
		else if (t <= t3)
			return -jm;
		else
			return 0;
	}

	/**
	* @brief 加速度
	*/
	float a(const float t) const {
		if (t <= t0)
			return 0;
		else if (t <= t1)
			return jm * (t - t0);
		else if (t <= t2)
			return am;
		else if (t <= t3)
			return -jm * (t - t3);
		else
			return 0;
	}

	/**
	* @brief 速度
	*/
	float v(const float t) const {
		if (t <= t0)
			return v0;
		else if (t <= t1)
			return v0 + jm / 2 * (t - t0) * (t - t0);
		else if (t <= t2)
			return v1 + am * (t - t1);
		else if (t <= t3)
			return v3 - jm / 2 * (t - t3) * (t - t3);
		else
			return v3;
	}

	/**
	* @brief 位置
	*/
	float x(const float t) const {
		if (t <= t0)
			return x0 + v0 * (t - t0);
		else if (t <= t1)
			return x0 + v0 * (t - t0) + jm / 6 * (t - t0) * (t - t0) * (t - t0);
		else if (t <= t2)
			return x1 + v1 * (t - t1) + am / 2 * (t - t1) * (t - t1);
		else if (t <= t3)
			return x3 + v3 * (t - t3) - jm / 6 * (t - t3) * (t - t3) * (t - t3);
		else
			return x3 + v3 * (t - t3);
	}

	/**
	* @brief 終点時刻 [s]
	*/
	float t_end() const { return t3; }
	/**
	 * @brief 終点速度 [m/s]
	 */
	float v_end() const { return v3; }
	/**
	 * @brief 終点位置 [m]
	 */
	float x_end() const { return x3; }
	/**
	 * @brief 境界の時刻
	 */
	float t_0() const { return t0; }
	float t_1() const { return t1; }
	float t_2() const { return t2; }
	float t_3() const { return t3; }

private:


protected:
	float jm;									/* 躍度定数 [m/s/s/s]		 */
	float am;									/* 加速度定数 [m/s/s]		 */
	float t0, t1, t2, t3;						/* 時刻定数 [s]				 */
	float v0, v1, v2, v3;						/* 速度定数 [m/s]			 */
	float x0, x1, x2, x3;						/* 位置定数 [m]				 */
};

#endif