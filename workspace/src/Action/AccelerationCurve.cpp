///
/// @file �����x�Ȑ��N���X
/// @note �����x�Ȑ������쐬����
/// @date 2022/06/29 �J����C
///
#include "../../include/Action/AccelerationCurve.h"

/**
	* @brief �R���X�g���N�^
*/
AccelCurve::AccelCurve()
{
	jm = am = t0 = t1 = t2 = t3 = v0 = v1 = v2 = v3 = x0 = x1 = x2 = x3 = 0;
}

/**
	* @brief �f�X�g���N�^
*/
AccelCurve::~AccelCurve()
{
}

/**
	 * @brief �Ȑ���������������
	 * @param j_max		�ő���x�̑傫�� [m/s/s/s], ���ł��邱��
	 * @param a_max		�ő�����x�̑傫�� [m/s/s], ���ł��邱��
	 * @param v_start	�n�_���x [m/s]
	 * @param v_target	�ڕW���x [m/s]
	 * @return �Ȃ�
 */
void AccelCurve::reset(const float j_max, const float a_max, const float v_start, const float v_end)
{
	float tc = 0.0f;							/* ����������				 */
	float tm = 0.0f;							/* ����������				 */

	/* �����t���ő�� */
	am = (v_end > v_start) ? a_max : -a_max;
	jm = (v_end > v_start) ? j_max : -j_max;

	/* �����l�ƍŏI�l���� */
	v0 = v_start;
	v3 = v_end;
	t0 = 0;
	x0 = 0;

	/* ���x���Ȑ��ƂȂ镔���̎��Ԃ����� */
	tc = a_max / j_max;

	/* �������x�����^���̎��Ԃ����� */
	tm = (v3 - v0) / am - tc;

	/* �������x�����^���̗L���ŕ��� */
	if (tm > 0) {
		/* ���x: �Ȑ� -> ���� -> �Ȑ� */
		t1 = t0 + tc;
		t2 = t1 + tm;
		t3 = t2 + tc;
		v1 = v0 + am * tc / 2;                //< v(t) ��ϕ�
		v2 = v1 + am * tm;                    //< v(t) ��ϕ�
		x1 = x0 + v0 * tc + am * tc * tc / 6; //< x(t) ��ϕ�
		x2 = x1 + v1 * tm;                    //< x(t) ��ϕ�
		x3 = x0 + (v0 + v3) / 2 * (t3 - t0); //< v(t) �O���t�̑�`�̖ʐς��
	}
	else {
		/* ���x: �Ȑ� -> �Ȑ� */
		const auto tcp = std::sqrt((v3 - v0) / jm); //< �ϋȂ܂ł̎���
		t1 = t2 = t0 + tcp;
		t3 = t2 + tcp;
		v1 = v2 = (v0 + v3) / 2; //< �Ώ̐���蒆�_�ƂȂ�
		x1 = x2 = x0 + v1 * tcp + jm * tcp * tcp * tcp / 6; //< x(t) ��ϕ�
		x3 = x0 + 2 * v1 * tcp; //< ���x v(t) �O���t�̖ʐς��
	}
}

/**
	* @brief ���s��������B������I�_���x���Z�o����֐�
	* @param j_max	�ő���x�̑傫�� [m/s/s/s], ���ł��邱��
	* @param a_max	�ő�����x�̑傫�� [m/s/s], ���ł��邱��
	* @param vs		�n�_���x [m/s]
	* @param vt		�ڕW���x [m/s]
	* @param d		���s���� [m]
	* @return �I�_���x
 */
float AccelCurve::calcVelocityEnd(const float j_max, const float a_max,
	const float vs, const float vt, const float d)
{
	float tc			= 0.0f;					/* ����������				 */
	float am			= 0.0f;					/* �ő�����x				 */
	float jm			= 0.0f;					/* �ő���x					 */
	float d_triangle	= 0.0f;					/* �������l					 */
	float v_triangle	= 0.0f;					/* �������l					 */
	float amtc			= 0.0f;					/* ���Z���x					 */
	float D				= 0.0f;					/* 2���������̓r�����Z�s	 */
	float sqrtD			= 0.0f;					/* 2����������2�捪			 */
	float a				= 0.0f;					/* 3���������p�����[�^		 */
	float b				= 0.0f;					/* 3���������p�����[�^		 */
	float aaa			= 0.0f;					/* 3���������p�����[�^		 */
	float c0			= 0.0f;					/* 3���������p�����[�^		 */
	float c1			= 0.0f;					/* 3���������p�����[�^		 */
	float c2			= 0.0f;					/* 3���������p�����[�^		 */

	/* ���x���Ȑ��ƂȂ镔���̎��Ԃ����� */
	tc = a_max / j_max;

	/* �ő�����x�̕��������� */
	am = (vt > vs) ? a_max : -a_max;
	jm = (vt > vs) ? j_max : -j_max;
	d_triangle = (vs + am * tc / 2) * tc;
	v_triangle = jm / am * d - vs;
	
	/* �������x�����^���̗L���ŕ��� */
	if (d * v_triangle > 0 && std::abs(d) > std::abs(d_triangle)) {
		/* �Ȑ��E�����E�Ȑ� */

		/* 2���������̉��̌��������� */
		amtc = am * tc;
		D = amtc * amtc - 4 * (amtc * vs - vs * vs - 2 * am * d);
		sqrtD = std::sqrt(D);
		return (-amtc + (d > 0 ? sqrtD : -sqrtD)) / 2;
	}

	/* �Ȑ��E�Ȑ� (���s�������Z������) */
	/* 3���������������āC�I�_���x���Z�o;
	 * �ȒP�̂��߁C�l����x���ׂĐ��ɕϊ����āC�v�Z���ʂɕ�����t�^���ĕԑ� */
	a = std::abs(vs);
	b = (d > 0 ? 1 : -1) * jm * d * d;
	aaa = a * a * a;
	c0 = 27 * (32 * aaa * b + 27 * b * b);
	c1 = 16 * aaa + 27 * b;
	if (c0 >= 0) {
		/* ���[�g�̒����񕉂̂Ƃ� */
		c2 = cbrt((std::sqrt(c0) + c1) / 2);
		return (d > 0 ? 1 : -1) * (c2 + 4 * a * a / c2 - a) / 3;
	}
	else {
		/* ���[�g�̒������̂Ƃ� */
		return (d > 0 ? 1 : -1) * (std::pow(std::complex<float>(c1 / 2, std::sqrt(-c0) / 2), float(1) / 3).real() * 2 - a) / 3;
	}
}

/**
 * @brief ���s��������B������ő呬�x���Z�o����֐�
 * @param j_max	�ő���x�̑傫�� [m/s/s/s], ���ł��邱��
 * @param a_max	�ő�����x�̑傫�� [m/s/s], ���ł��邱��
 * @param vs	�n�_���x [m/s]
 * @param ve	�I�_���x [m/s]
 * @param d		���s���� [m]
 * @return vm	�ő呬�x [m/s]
 */
float AccelCurve::calcVelocityMax(const float j_max, const float a_max,
	const float vs, const float ve, const float d)
{
	float tc = 0.0f;					/* ����������				 */
	float am = 0.0f;					/* �ő�����x				 */
	float amtc = 0.0f;					/* ���Z���x					 */
	float D = 0.0f;						/* 2���������̓r�����Z�s	 */
	float sqrtD = 0.0f;					/* 2����������2�捪			 */

	/* ���x���Ȑ��ƂȂ镔���̎��Ԃ����� */
	tc = a_max / j_max;
	am = (d > 0) ? a_max : -a_max; 

	/* 2���������̉��̌��������� */
	amtc = am * tc;
	D = amtc * amtc - 2 * (vs + ve) * amtc + 4 * am * d + 2 * (vs * vs + ve * ve);

	if (D < 0) {
		/* �S���������������� */
		/* ���͂̃`�F�b�N */
		if (vs * ve < 0) {
			return vs;
		}
	}
	sqrtD = std::sqrt(D);
	return (-amtc + (d > 0 ? sqrtD : -sqrtD)) / 2;
}

/**
 * @brief ���x������ψʂ��Z�o����֐�
 * @param j_max		�ő���x�̑傫�� [m/s/s/s], ���ł��邱��
 * @param a_max		�ő�����x�̑傫�� [m/s/s], ���ł��邱��
 * @param v_start	�n�_���x [m/s]
 * @param v_end		�I�_���x [m/s]
 * @return d		�ψ� [m]
 */
float AccelCurve::calcMinDistance(const float j_max, const float a_max,
	const float v_start, const float v_end)
{
	float tc	= 0.0f;					/* ����������				 */
	float tm	= 0.0f;					/* ����������				 */
	float t_all = 0.0f;					/* ������					 */
	float am	= 0.0f;					/* �ő�����x				 */
	float jm	= 0.0f;					/* �ő���x					 */

	/* �����t���ő�� */
	am = (v_end > v_start) ? a_max : -a_max;
	jm = (v_end > v_start) ? j_max : -j_max;
	/* ���x���Ȑ��ƂȂ镔���̎��Ԃ����� */
	tc = a_max / j_max;
	/* �������x�����^���̎��Ԃ����� */
	tm = (v_end - v_start) / am - tc;
	/* �n�_����I�_�܂ł̎��Ԃ����� */
	t_all = (tm > 0) ? (tc + tm + tc) : (2 * std::sqrt((v_end - v_start) / jm));
	return (v_start + v_end) / 2 * t_all;
}