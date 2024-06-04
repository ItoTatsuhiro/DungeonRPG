#include "Enemy_Escape.h"
#include "../action/BattleActionBase.h"
#include "../action/enemyAction/ActionMove.h"
#include "../action/enemyAction/ActionWait.h"

// �R���X�g���N�^
// ������BattleEnemy�̏������p
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string fileName...�\��t����e�N�X�`���̃p�X
// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
// SpriteObjectBase�̈����������
BattleEnemyEscape::BattleEnemyEscape(tnl::Vector3 startPos, float objSize, std::string fileName) 
	: BattleEnemy(startPos, objSize, fileName)
{

	moveValue_ = 2.5;

}

// �f�X�g���N�^
BattleEnemyEscape::~BattleEnemyEscape() {

}


// �N���X�̐����p�̊֐�
std::shared_ptr<BattleEnemyEscape> BattleEnemyEscape::Create(tnl::Vector3 startPos, float objSize, std::string fileName) {

	// �N���X�̃C���X�^���X�𐶐�
	std::shared_ptr<BattleEnemyEscape> instance(new BattleEnemyEscape(startPos, objSize, fileName));
	instance->actionList_.emplace_back(std::shared_ptr<ActionMove>( new ActionMove(instance) ));
	instance->actionList_.emplace_back(std::shared_ptr<ActionWait>( new ActionWait(instance) ));

	return instance;
}



// �X�V�p�̊֐�
void BattleEnemyEscape::update(const float delta_time) {

	// BattleEnemy�̍X�V
	BattleEnemy::update(delta_time);

}

// �`��p�̊֐�
void BattleEnemyEscape::draw( std::shared_ptr< dxe::Camera > camera ) {

	// BattleEnemy�̕`��
	BattleEnemy::draw( camera );

}
