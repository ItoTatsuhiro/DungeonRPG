#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../character/other/BattleCharacterBase.h"

// �L�����N�^�[��HP��\������UI
class UiHP : public ito::Transform {
public :

	// �R���X�g���N�^
	// �����F
	// character...HP��\������L�����N�^�[
	// hpIconFileName...�\������HP�A�C�R���̃t�@�C����
	// nomalHpGpcFileName...�\������HP�摜�̃t�@�C����
	// damagedHpGpcFileName...�\������HP�摜�i��_���[�W���j�̃t�@�C����
	// pos...�\���ʒu
	UiHP(std::shared_ptr<BattleCharacterBase> character, std::string hpIconFileName, std::string nomalHpGpcFileName, std::string damagedHpGpcFileName, tnl::Vector3 pos = {0, 0, 0});

	// �f�X�g���N�^
	~UiHP();

	//// �X�V�p�̊֐�
	//// �摜�̍X�V���Aupdate���������Ȃ������Ɏ���
	//void update(const float delta_time);

	// �`��p�̊֐�
	void draw();



private :

	// HP��\������L�����N�^�[
	std::shared_ptr<BattleCharacterBase> character_;

	// HP�̉��ɕ\������A�C�R��
	std::shared_ptr< ito::Graphic > hpIcon_;

	// �A�C�R���̑��΍��W
	tnl::Vector3 hpIconPos_ = { -100, 0, 0 };

	// HP��\���摜
	// HP�̐��l���摜����ׂ�z��Ȃ̂Ŕz��ɂ��ĊǗ�����
	std::vector< std::vector< std::shared_ptr< ito::Graphic> > > hpGpcArray_;


	// HP�̉摜�̔z��̗v�f�ԍ��Ƃ��Ďg�p����p��enum class
	enum class HPGPC_CONTENT {
		NOMAL_HP,			// ���Ă��Ȃ��ʏ��HP
		DAMAGED_HP			// ��ꂽHP
	};



	// ��ڂ�HP�̉摜�̑��΍��W
	tnl::Vector3 hpGpcPos_ = { 0, 0, 0 };

	// HP�̉摜���m�̉��̊Ԋu
	float hpGpcSpaceWidth_ = 30;

};