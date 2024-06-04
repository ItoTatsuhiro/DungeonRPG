#include "BattleEnemy.h"
#include "action/BattleActionBase.h"

// �R���X�g���N�^
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string filePath...�e�N�X�`���̃t�@�C���̃p�X
// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
// SpriteObjectBase�̈����������
BattleEnemy::BattleEnemy(tnl::Vector3 startPos, float objSize, std::string fileName)
	: BattleCharacterBase(startPos, objSize, fileName) {


	// SpriteObjectBase�N���X�̊֐�
	// �e�N�X�`����\������p��plane�̔z����쐬����
	CreateSpriteObjArray(fileName);

	// �\�����郁�b�V���̏����ݒ�
	displayObj_ = tnl::Vector2i(1, textureCutNum_.y - 2);


	return;

}

// �f�X�g���N�^
// ���󏈗�����
BattleEnemy::~BattleEnemy() {

	return;
}

// �X�V�p�̊֐�
void BattleEnemy::update(float delta_time) {

	BattleCharacterBase::update(delta_time);

	seq_.update(delta_time);

}

// 
void BattleEnemy::draw(std::shared_ptr<dxe::Camera> camera) {

	BattleCharacterBase::draw(camera);


}


// �s�������肷��V�[�P���X
// �������Ă���s���̃��X�g����s���������_���ɑI�����A
// 
bool BattleEnemy::seqActDecade(const float delta_time) {

	// �s���̐����J�E���g
	actionNum_ = actionList_.size();

	// ���s����s���̔ԍ�������
	int selectActionNum = rand() % actionNum_;



	// �ȉ��Ŏ��s����s�����擾
	auto it = actionList_.begin();
	// ������肵���s���̔ԍ��܂ŃC�e���[�^�𑗂�
	for (int i = 0; i < selectActionNum; ++i) {
		++it;
	}

	// ���s����s���̕ϐ��ɑI�������s��������
	nowAction_ = (*it);

	// �s�������s�O�̐ݒ�ɍX�V����
	nowAction_->setUpAction();

	// ���s����V�[�P���X���s���̃V�[�P���X�ɕύX
	seq_.change(&BattleEnemy::seqAct);

	return true;
}


// �s�������s����V�[�P���X
bool BattleEnemy::seqAct(const float delta_time) {

	// �ȉ��̏����̎��s������߂čs���̑I���ɖ߂�
	// 1.�s���̕ϐ��̒��g�������Ƃ�
	// 2.�s�����I�����Ă��鎞
	if (nowAction_ == nullptr || nowAction_->getIsFinished()) {

		seq_.change(&BattleEnemy::seqActDecade);
		return true;
	}

	// ���݂̍s�������s
	nowAction_->update(delta_time);

}

