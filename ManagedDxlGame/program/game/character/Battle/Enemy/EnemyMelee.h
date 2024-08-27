#pragma once
#include "../BattleEnemy.h"




// �ߐڍU�����s���G�L�����N�^�[�̃N���X
// 
// ���ȉ����ӓ_
// ���g�̃C���X�^���X��shared�|�C���^�Ŏ擾���邽�߁A
// �g�p����ۂ͕K��std::shared_ptr�^�ō쐬���邱�ƁI
class BattleEnemyMelee final : public BattleEnemy, std::enable_shared_from_this<BattleEnemyMelee> {
public:

	// �R���X�g���N�^
	// ������BattleEnemy�̏������p
	// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string fileName...�\��t����e�N�X�`���̃t�@�C����
	// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
	// SpriteObjectBase�̈����������
	BattleEnemyMelee(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList);

	// �f�X�g���N�^
	~BattleEnemyMelee();

	// �N���X�̐����p�̊֐�
	static std::shared_ptr<BattleEnemyMelee> Create(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList);

	// �X�V�p�̊֐�
	void update(const float delta_time);

	// �`��p�̊֐�
	// �����F�`�悷��J����
	void draw(const std::shared_ptr< dxe::Camera >& camera);


};