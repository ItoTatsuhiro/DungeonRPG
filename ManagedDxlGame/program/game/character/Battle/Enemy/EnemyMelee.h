#pragma once
#include "../BattleEnemy.h"




// ������G�L�����N�^�[�̃N���X
// 
// ���ȉ����ӓ_
// ���g�̃C���X�^���X��shared�|�C���^�Ŏ擾���邽�߁A
// �g�p����ۂ͕K��std::shared_ptr�^�ō쐬���邱�ƁI
class BattleEnemyMelee final : public BattleEnemy {
public:

	// �R���X�g���N�^
	// ������BattleEnemy�̏������p
	// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string fileName...�\��t����e�N�X�`���̃t�@�C����
	// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
	// SpriteObjectBase�̈����������
	BattleEnemyMelee(tnl::Vector3 startPos, float objSize, std::string fileName);

	// �f�X�g���N�^
	~BattleEnemyMelee();

	// �N���X�̐����p�̊֐�
	static std::shared_ptr<BattleEnemyMelee> Create(tnl::Vector3 startPos, float objSize, std::string fileName);

	// �X�V�p�̊֐�
	void update(const float delta_time);

	// �`��p�̊֐�
	// �����F�`�悷��J����
	void draw(std::shared_ptr< dxe::Camera > camera);


};