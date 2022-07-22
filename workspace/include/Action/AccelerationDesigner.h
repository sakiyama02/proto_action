///
/// @file �S�������x�Ȑ����N���X
/// @note �S�����������������x�Ȑ������쐬����
/// @date 2022/06/29 �J����C
///


#ifndef ACELLDESIGNER_HEADER
#define ACELLDESIGNER_HEADER
#include "./AccelerationCurve.h"
#include <algorithm>
#include <array>


class AccelDesigner {
public:

	AccelDesigner();
	~AccelDesigner();

	void reset(const float j_max, const float a_max, const float v_sat,
		const float v_start, const float v_target, const float dist,
		const float x_start, const float t_start);

	/**
   * @brief ���� $t$ �ɂ�������x $j$
   * @param t ����[s]
   * @return j ���x[m/s/s/s]
   */
	float j(const float t) const {
		if (t < t2)
			return ac.j(t - t0);
		else
			return dc.j(t - t2);
	}
	/**
	 * @brief ���� $t$ �ɂ���������x $a$
	 * @param t ���� [s]
	 * @return a �����x [m/s/s]
	 */
	float a(const float t) const {
		if (t < t2)
			return ac.a(t - t0);
		else
			return dc.a(t - t2);
	}
	/**
	 * @brief ���� $t$ �ɂ����鑬�x $v$
	 * @param t ���� [s]
	 * @return v ���x [m/s]
	 */
	float v(const float t) const {
		if (t < t2)
			return ac.v(t - t0);
		else
			return dc.v(t - t2);
	}
	/**
	 * @brief ���� $t$ �ɂ�����ʒu $x$
	 * @param t ���� [s]
	 * @return x �ʒu [m]
	 */
	float x(const float t) const {
		if (t < t2)
			return x0 + ac.x(t - t0);
		else
			return x3 - dc.x_end() + dc.x(t - t2);
	}
	/**
	 * @brief �I�_���� [s]
	 */
	float t_end() const { return t3; }
	/**
	 * @brief �I�_���x [m/s]
	 */
	float v_end() const { return dc.v_end(); }
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
	
	/**
	 * @brief ���E�̃^�C���X�^���v���擾
	 * @return std::array<float, 8> ���E�̃^�C���X�^���v�̔z��
	 */
	const std::array<float, 8> getTimeStamp() const {
		return { {
			t0 + ac.t_0(),
			t0 + ac.t_1(),
			t0 + ac.t_2(),
			t0 + ac.t_3(),
			t2 + dc.t_0(),
			t2 + dc.t_1(),
			t2 + dc.t_2(),
			t2 + dc.t_3(),
		} };
	}

	
protected:
	float t0, t1, t2, t3;	/**< @brief ���E�_�̎��� [s] */
	float x0, x3;			/**< @brief ���E�_�̈ʒu [m] */
	AccelCurve ac, dc;		/**< @brief �Ȑ������C�Ȑ������I�u�W�F�N�g */
};

#endif