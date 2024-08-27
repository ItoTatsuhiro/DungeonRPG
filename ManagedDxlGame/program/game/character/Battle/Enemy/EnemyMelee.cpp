#include "EnemyMelee.h"
#include "../action/BattleActionBase.h"
#include "../action/enemyAction/ActionMove.h"
#include "../action/enemyAction/ActionWait.h"

// �R���X�g���N�^
// ������BattleEnemy�̏������p
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string fileName...�\��t����e�N�X�`���̃p�X
// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
// SpriteObjectBase�̈����������
BattleEnemyMelee::BattleEnemyMelee(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList)
	: BattleEnemy(startPos, objSize, fileName, charaList)
{

	moveValue_ = 2.5;

}

// �f�X�g���N�^
BattleEnemyMelee::~BattleEnemyMelee() {

}


// �N���X�̐����p�̊֐�
std::shared_ptr<BattleEnemyMelee> BattleEnemyMelee::Create(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList) {

	// �N���X�̃C���X�^���X�𐶐�
	std::shared_ptr<BattleEnemyMelee> instance(new BattleEnemyMelee(startPos, objSize, fileName, charaList));
	instance->actionList_.emplace_back(std::shared_ptr<ActionMove>(new ActionMove(instance)));
	instance->actionList_.emplace_back(std::shared_ptr<ActionWait>(new ActionWait(instance)));
	

	return instance;
}



// �X�V�p�̊֐�
void BattleEnemyMelee::update(const float delta_time) {

	// BattleEnemy�̍X�V
	BattleEnemy::update(delta_time);

}

// �`��p�̊֐�
void BattleEnemyMelee::draw(const std::shared_ptr< dxe::Camera >& camera) {

	// BattleEnemy�̕`��
	BattleEnemy::draw(camera);

}
