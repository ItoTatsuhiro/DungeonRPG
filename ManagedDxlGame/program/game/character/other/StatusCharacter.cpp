#include "StatusCharacter.h"


// �R���X�g���N�^
// �����Flv...���x��, hp...�̗�, atk...�U����, def...�h���, spd...���x, crt...��S��
// ���������ۂɐݒ肷��l������ꍇ�͏������q�œ����
// �����l�����Ȃ��ꍇ�̓f�t�H���g�̒l������悤�ɂ���
StatusCharacter::StatusCharacter(int lv, float hp, float atk, float def, float spd, float crt)
	: lv_(lv), hp_(hp),  hpMax_(hp), atk_(atk), def_(def), spd_(spd), crt_(crt)
{


}

// �f�X�g���N�^
StatusCharacter::~StatusCharacter() {

}

