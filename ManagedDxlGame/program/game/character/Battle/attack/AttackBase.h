#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"
#include "../../../base/SpriteObjectBase.h"
#include "../action/BattleActionBase.h"
#include "../../other/CharacterTypeEnum.h"

// �U���̃N���X
// �����蔻��p�̃��b�V��������
// 
// �������ӓ_����
// �p����̃N���X�ł͈ȉ����������邱�ƁI
// �EOnHit�֐����I�[�o�[���C�h����֐�
class AttackBase : public SpriteObjectBase {
public:

	// �R���X�g���N�^
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����A�U���̃L�����N�^�[�����A�_���[�W
	AttackBase(tnl::Vector3 pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage = 1.0f);
	// �f�X�g���N�^
	virtual ~AttackBase();
	// �X�V�p�̊֐�
	virtual void update(float delta_time) override;
	// �`��p�̊֐�
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) override;


	// creatorAction_���Z�b�g����֐�
	// �U�����I�������ۂɃL�����N�^�[�̍s���V�[�P���X��؂�ւ���K�v������ꍇ�͂����ɃZ�b�g����
	inline void setCreatorAction(std::shared_ptr<BattleActionBase> creatorAction)
	{
		creatorAction_ = creatorAction;
	}



	// �U�����Փ˂����ۂɎ��s����֐�
	// ******************************************************
	// �p����̃N���X�ł̓I�[�o�[���C�h����֐���K���쐬���邱�ƁI
	// ******************************************************
	virtual void OnHit();



	//-------------------------------------------------------------
	// �Q�b�^�[

	// �_���[�W�̐��l���擾����֐�
	inline float getDamage() const { return damage_; }

	// �Q�[���̏I����Ԃ��擾����֐�
	inline bool getIsEnd() const { return isEnd_; }

	// �L�����N�^�[�̑������擾����֐�
	inline eCharaType getCharacterType() const { return charaType_; }


	// -------------------------------------------------------------
	// �Z�b�^�[

	// isHit�i�U�����g�������������ǂ����̃t���O�j�̃Z�b�^�[
	inline void setIsHit(const bool isHit) { isHit_ = isHit; }

	// �L�����N�^�[�������Z�b�g����֐�
	inline void setCharacterType(const eCharaType newType) { charaType_ = newType; }

protected:

	// �ǂ̃L�����N�^�[�̍U������\���ϐ�
	// ��{�I�ɓ��������̃L�����N�^�[�ɂ͓�����Ȃ��悤�ɂ���
	// �f�t�H���g�ł͑������ݒ�̂��߁A�K���e�p����̃R���X�g���N�^�Őݒ肷�邱��
	eCharaType charaType_ = eCharaType::NONE;


	// ���g��������s���̃N���X
	// �������I�������ۂɁA�U�����I���������Ƃ�`����K�v������ꍇ�͂����ɓ����
	std::weak_ptr<BattleActionBase> creatorAction_;



	// �U���q�b�g���ɍĐ����鉹�̃n���h��
	// �f�t�H���g�ł͐ݒ肵�Ă��Ȃ��̂ŁA�K�v�Ȏ��͂����Ƀ��[�h���Ďg�p����
	int hitSoundHdl_ = 0;



	// �_���[�W
	float damage_;

	// ���[�v���邩�ǂ���
	// ���[�v���Ȃ��ꍇ�̓A�j���[�V������1���[�v�Ŋ�{�폜����
	bool isLoop_;

	// �I�����Ă��邩�ǂ���
	// �f�t�H���g��false
	// �������I��������Ƃ��͂��̃t���O��true�ɂ���
	bool isEnd_;

	// �U���������������ǂ����̃t���O
	// �f�t�H���g��false�ŁAtrue�ɂȂ����ۂɓ��������ۂ̏������s��
	// �E�ߋ����U���͊�{�������Ȃ�
	// �E�������U���͊�{���������瓖�������ۂ̃G�t�F�N�g���o���ď���
	bool isHit_;

	// �X�e�[�W�Ƃ̓����蔻����Ƃ邩�ۂ��̕ϐ�
	// ��{�I�ɁA�ߋ����U����false�A�������U����true�ɂ���z��
	// �f�t�H���g��false�ɂ���i�R���X�g���N�^�j
	bool checkHitStage_;

};



