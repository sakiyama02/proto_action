///
/// @file �����x�Ȑ��N���X
/// @note �����x�Ȑ������쐬����
/// @date 2022/06/29 �J����C
///
#ifndef ACELLCURVE_HEADER
#define ACELLCURVE_HEADER

#include <cmath>
#include <complex>

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

	// �R���X�g�����o�ϐ�
	/**
	* @brief ���x
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
	* @brief �����x
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
	* @brief ���x
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
	* @brief �ʒu
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
	* @brief �I�_���� [s]
	*/
	float t_end() const { return t3; }
	/**
	 * @brief �I�_���x [m/s]
	 */
	float v_end() const { return v3; }
	/**
	 * @brief �I�_�ʒu [m]
	 */
	float x_end() const { return x3; }
	/**
	 * @brief ���E�̎���
	 */
	float t_0() const { return t0; }
	float t_1() const { return t1; }
	float t_2() const { return t2; }
	float t_3() const { return t3; }

private:


protected:
	float jm;									/* ���x�萔 [m/s/s/s]		 */
	float am;									/* �����x�萔 [m/s/s]		 */
	float t0, t1, t2, t3;						/* �����萔 [s]				 */
	float v0, v1, v2, v3;						/* ���x�萔 [m/s]			 */
	float x0, x1, x2, x3;						/* �ʒu�萔 [m]				 */
};

#endif