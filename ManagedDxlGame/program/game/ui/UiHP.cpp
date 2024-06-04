#include "UiHP.h"


// �R���X�g���N�^
// �����F
// character...HP��\������L�����N�^�[
// hpIconFileName...�\������HP�A�C�R���̃t�@�C����
// nomalHpGpcFileName...�\������HP�摜�̃t�@�C����
// damagedHpGpcFileName...�\������HP�摜�i��_���[�W���j�̃t�@�C����
// pos...�\���ʒu
UiHP::UiHP(std::shared_ptr<BattleCharacterBase> character, std::string hpIconFileName, std::string nomalHpGpcFileName, std::string damagedHpGpcFileName, tnl::Vector3 pos)
	: character_(character), ito::Transform(pos)
{
	// �A�C�R���摜�̃N���X�̍쐬
	hpIcon_ = std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph(hpIconFileName)));
	hpIcon_->setPos_(hpIconPos_);
	// �摜�̑傫����ݒ�
	hpIcon_->setSizeMag(0.8);



	// �L�����N�^�[��HP�ő�l�̒l�܂ŃN���X���쐬
		for (int i = 0; i < character_->status_->getHpMax(); ++i) {


			// �����HP�̉摜�̔z��
			// �z��̈�ڂ�ʏ��HP�p�̉摜�A��ڂ���ꂽHP�p�̉摜�Ƃ��Ďg�p����
			std::vector< std::shared_ptr< ito::Graphic> > hpGpc;

			// �ʏ�̗̑͂̉摜
			std::shared_ptr< ito::Graphic > nomalHpGpc = 
				std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph(nomalHpGpcFileName)));
			// ���W�ݒ�
			nomalHpGpc->setPos_(hpGpcPos_ + tnl::Vector3{ hpGpcSpaceWidth_ * i, 0, 0 });
			// �{���ݒ�
			nomalHpGpc->setSizeMag(1);

			// ��_���[�W���̗͉̑摜
			std::shared_ptr< ito::Graphic > damagedHpGpc = 
				std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph(damagedHpGpcFileName)));
			// ���W�ݒ�
			damagedHpGpc->setPos_(hpGpcPos_ + tnl::Vector3{ hpGpcSpaceWidth_ * i, 0, 0 });
			// �{���ݒ�
			damagedHpGpc->setSizeMag(1);

			// �z��ɂ��ꂼ��ǉ�
			hpGpc.emplace_back( nomalHpGpc );
			hpGpc.emplace_back( damagedHpGpc );

			// �N���X��vector�ɒǉ�
			hpGpcArray_.emplace_back( hpGpc );

		}

}


// �f�X�g���N�^
UiHP::~UiHP() {

}


//void update(float delta_time) {
//
//}


// �`��p�̊֐�
void UiHP::draw() {

	hpIcon_->draw(ito::Transform::pos_);

	for (int i = 0; i < character_->status_->getHpMax(); ++i) {

		if (i < character_->status_->getHp()) {

			hpGpcArray_[i][ static_cast<int>(HPGPC_CONTENT::NOMAL_HP)]->draw(ito::Transform::pos_);

		}
		else {

			hpGpcArray_[i][static_cast<int>(HPGPC_CONTENT::DAMAGED_HP)]->draw(ito::Transform::pos_);

		}

	}

}