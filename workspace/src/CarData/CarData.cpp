#include "../../include/CarData/CarData.h"

/* -------------------------------------------------------------------------	*/
/* �֐���		�F CarPosition				              	    				*/
/* �@�\��		�F �R���X�g���N�^                                  				*/
/* �@�\�T�v		�F ���W�ƌ����̏�����                          					*/
/* ����			�F �Ȃ�															*/
/* �߂�l		�F �Ȃ�                                     					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	:�V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
CarData::CarData( )
{
	car_angle = 0.0f;

	position.x = 0 * 0.3527 * 2;
	position.y = 0 * 0.3527 * 2;
}

CarData::~CarData( ) {}
/* -------------------------------------------------------------------------	*/
/* �֐���		�F update									    				*/
/* �@�\��		�F �X�V       													*/
/* �@�\�T�v		�F ���Ȉʒu���X�V����                   						*/
/* ����			�F �Ȃ�															*/
/* �߂�l		�F int8				:0				:����I��					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	:�V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
int8 CarData::update( void )
{
	//frLog &msg = frLog::GetInstance( );
	int8 retChk = SYS_NG;
	Steering &steering = Steering::getInstance( );
	MOTOR_ANGLE preAngle;
	MOTOR_ANGLE nowAngle;
	WheelDist wheelDist;

	memset( &preAngle, 0, sizeof( MOTOR_ANGLE ) );
	memset( &nowAngle, 0, sizeof( MOTOR_ANGLE ) );
	memset( &wheelDist, 0, sizeof( WheelDist ) );

	/* ���[�^�̊p�x���َ擾 -------------------------------------------- */

	// �O�񃂁[�^�p�x�擾
	preAngle = steering.getMotorAngle( );
	
	// ���[�^�p�x�X�V
	retChk = steering.update( );
	if ( retChk != SYS_OK ) {
		//msg.LOG( LOG_ID_ERR, "CarPos::update updateAngle err\n" );
		return retChk;
	}

	// �ŐV���[�^�p�x�擾
	nowAngle = steering.getMotorAngle( );

	wheelDist.left = (float)(nowAngle.left - preAngle.left);
	wheelDist.right = (float)(nowAngle.right - preAngle.right);

	wheelDist.left *= DIST;
	wheelDist.right *= DIST;

	/* �v�Z���X�V */
	retChk = calcOdometry( &wheelDist );
	if ( retChk != SYS_OK ) {
		//msg.LOG( LOG_ID_ERR, "CarPos::update calcOdometry err\n" );
		return retChk;
	}
	
	if ( car_angle >= 600 || car_angle <= -600 ) {
		//msg.LOG( LOG_ID_ERR, "�ԑ̊p�x���ُ�̂��ߋ����I��\n" );
		
		//act_tsk( END_TASK );
		return SYS_NG;
	}
	return SYS_OK;
}

/* -------------------------------------------------------------------------	*/
/* �֐���		�F calcOdometry								    				*/
/* �@�\��		�F �I�h���g���v�Z 												*/
/* �@�\�T�v		�F �I�h���g���v�Z���s��                   	   					*/
/* ����			�F WheelDist*       :wheel_dist     :�����[�^�̍���				*/
/* �߂�l		�F int8				:0				:����I��					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	:�V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
int8 CarData::calcOdometry( WheelDist* wheel_dist )
{
	//frLog &msg = frLog::GetInstance( );
	if ( wheel_dist == NULL ) {
		//msg.LOG( LOG_ID_ERR, "CarPosition::calcOdometry �����G���[\n" );
		return SYS_PARAM;
	}
	float  angle = 0.0f;
	double dist = 0.0f;
	double rad = 0.0f;
	double addRad = 0.0f;
	COORDINATE addPos;

	memset( &addPos, 0, sizeof( COORDINATE ) );

	/* ���W�v�Z */
	dist = (double)(wheel_dist->right + wheel_dist->left) / 2.0;
	angle = (360.0f / (2.0f * PI * CAR_WIDTH)) * (wheel_dist->left - wheel_dist->right);

	/* �p�x�����W�A���ϊ� */
	addRad = ((double)(angle)) * (PI / 180.0f);
	rad = ((double)(angle)) * (PI / 180.0f);

	/* /2.0f���邩�킩��Ȃ� */
	addPos.x = (float)-(dist * std::sin( rad + addRad / 2.0f ));
	addPos.y = (float)(dist * std::cos( rad + addRad / 2.0f ));

	/* ���W�X�V */
	position.x += addPos.x;
	position.y += addPos.y;

	/* �p�x�X�V */
	car_angle += angle;

	return SYS_OK;
}

/* -------------------------------------------------------------------------	*/
/* �֐���		�F getPos							    	    				*/
/* �@�\��		�F ���Ȉʒu���W���擾 											*/
/* �@�\�T�v		�F ���Ȉʒu���W��Ԃ�                   	   		   			*/
/* ����			�F none															*/
/* �߂�l		�F PositionData    :car_pos        :���W�i�[�p					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	 �V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
COORDINATE CarData::getPos( void )
{
	return position;
}
/* -------------------------------------------------------------------------	*/
/* �֐���		�F setPos							    	    				*/
/* �@�\��		�F ���Ȉʒu���W(x,y)���㏑�� 									*/
/* �@�\�T�v		�F ���Ȉʒu���W(x,y)���㏑������                   				*/
/* ����			�F PositionData     :set_pos        :���W						*/
/* �߂�l		�F int8				:0				:����I��					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	:�V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
int8 CarData::setPos( COORDINATE coordinate )
{
	//frLog &msg = frLog::GetInstance();
	position = coordinate;
	return SYS_OK;
}

/* -------------------------------------------------------------------------	*/
/* �֐���		�F getAngle							    	    				*/
/* �@�\��		�F ���Ȉʒu�p�x���擾		            	    				*/
/* �@�\�T�v		�F ���Ȉʒu�p�x���擾����                                       */
/* ����			�F none															*/
/* �߂�l		�F float*           :angle        :�p�x�i�[�p					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	:�V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
float CarData::getAngle( void )
{
	return car_angle;
}
/* -------------------------------------------------------------------------	*/
/* �֐���		�F setAngle							    	    				*/
/* �@�\��		�F ���Ȉʒu�p�x���㏑��		            	    				*/
/* �@�\�T�v		�F ���Ȉʒu�p�x���㏑������                                     */
/* ����			�F float            :angle          :�p�x						*/
/* �߂�l		�F int8				:0				:����I��					*/
/* �쐬��		�F 2021/07/23		 ��R�@�E�l		 �V�K�쐬					*/
/* �쐬��		�F 2022/07/16		 �R�c�@���V��	:�V�K�쐬					*/
/* -------------------------------------------------------------------------	*/
int8 CarData::setAngle( float angle )
{
	//frLog &msg = frLog::GetInstance();

	/* �����`�F�b�N */
	/* �͈͂ň����`�F�b�N���K�v
		return SYS_NG;
	*/

	/*���@�͈͂��킩��Ȃ����߈����`�F�b�N���ł��Ȃ� 
	0~-179? or 0~360?�@�ǋL�@�R�c	*/

	car_angle = angle;

	return SYS_OK;
}
