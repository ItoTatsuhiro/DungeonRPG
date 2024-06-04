#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../other/Enum.h"
#include "../../base/SpriteObjectBase.h"
#include "../other/BattleCharacterBase.h"


// �o�g���V�[���ő��삷��v���C���[�̃N���X
// �_���W�����V�[���ƈقȂ�A���b�V��������
// CharacterBaseBattle���p��
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string objectName...�I�u�W�F�N�g��
class BattlePlayer : public BattleCharacterBase {
public :
	// �R���X�g���N�^
	// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string objectName...�I�u�W�F�N�g��
	// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
	// SpriteObjectBase�̈����������
	BattlePlayer( tnl::Vector3 startPos,float objSize, std::string objName );
	// �f�X�g���N�^
	~BattlePlayer();
	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera) override;


protected :


	// �ړ����s���֐�
	void Move(float delta_time);

	// �U���̏����ɓ��邽�߂̊֐�
	// �U���̂��߂̃L�[���͂��������Ƃ��V�[�P���X��؂�ւ��鏈�����s��
	void OnAttackKey();


	//// �U���̑傫��
	//// �R���X�g���N�^�ŏ�����
	//float attackSize_;

	// �V�[�P���X�����p�̕ϐ�
	tnl::Sequence<BattlePlayer> seq_ = tnl::Sequence<BattlePlayer>(this, &BattlePlayer::seqIdle);

	// �ҋ@���̃V�[�P���X
	bool seqIdle(const float delta_time);
	// �U���̃V�[�P���X
	bool seqAttack(const float delta_time);

};
