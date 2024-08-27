#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"

class BattleCharacterBase;

// �o�g���V�[���ɂ����āA��ɓG���g�p����s���̃N���X
// �ړ��A�U��������̍s���Ƃ��Ĉ������߂�,
// ���ꂼ��̍s���̃N���X�Ɍp�����Ďg�p����
class BattleActionBase {
public :

	// �R���X�g���N�^
	// �����F�s�����s���L�����N�^�[
	BattleActionBase(std::shared_ptr< BattleCharacterBase > actionCharacter);

	// ���z�֐�
	virtual ~BattleActionBase(){}


	// �������z�֐�
	// ���̊֐����p���������ꂼ��̍s���N���X�ł��̊֐���K���������邱�ƁI
	virtual void update(const float delta_time) = 0;


	// �������z�֐�
	// �s�������s����O�ɁA���l�����������邽�߂̊֐�
	// ���ꂼ��̍s���ŏ���������K�v�̂��鐔�l���قȂ邽�߁A���ꂼ��̍s���N���X�ŕK���쐬����
	virtual void setUpAction() = 0;


	//-----------------------------------------------------
	// �Q�b�^�[

	// isFinished_���擾���邽�߂̃Q�b�^�[
	// �s�����I�����Ă��邩�ǂ������O����擾���邽�߂Ɏg�p����
	inline bool getIsFinished() const { return isFinished_; }


	//-----------------------------------------------------
	// �Z�b�^�[

	// isFinished_��ύX���邽�߂̃Z�b�^�[
	// �L�����N�^�[���ōs���̌����A�s��������O��false�ɕύX����̂Ɏg�p����
	inline void setIsFinished(bool isFinished) { isFinished_ = isFinished; }


protected :

	// �s�����s���L�����N�^�[
	// �R���X�g���N�^�ŏ�����
	std::weak_ptr< BattleCharacterBase > actionCharacter_;

	// �s�����I�����Ă��邩�ǂ����̃t���O
	bool isFinished_ = false;

};