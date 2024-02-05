#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/CharacterBase.h"


// �O���錾
class Player;

// �X�e�[�W��ł̓G�L�����N�^�[�̃N���X
// �����FcellSize...�X�e�[�W��1�}�X�̑傫��
// startGridPos...�������̏����ʒu
class Enemy : public CharacterBase {
public :
	// �R���X�g���N�^
	// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
	// �����FcellSize...�X�e�[�W��1�}�X�̑傫��
	// startGridPos...�������̏����ʒu
	Enemy(float gridSize, tnl::Vector2i startGridPos, std::shared_ptr<Player> player);

	// �f�X�g���N�^
	~Enemy();

	// ���t���[�����s����֐�
	void update(float delta_time);

	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera );


	// �V�[�P���X��Idle����؂�ւ��鏈��
	void ChangeSeqFromIdle();

	// �V�[�P���X��Wait���玟�̏����ɐ؂�ւ��鏈��
	void ChangeSeqFromWait();



private :
	// �O�ɂ����}�X
	// �ړ������肷��ꍇ�͍s���~�܂�ȊO�ł͑O�̃}�X�ȊO�ɍs���悤�ɂ���
	tnl::Vector2i beforeGrid_ = { 0, 0 };

	// Enemy��Mesh
	// 2D�̉摜��\��t����Plane��p�ӂ���p
	std::vector< std::vector< std::shared_ptr<ito::Object3D>>> enemyObjArray_;

	// �\��t����e�N�X�`��
	std::shared_ptr<dxe::Texture> enemyTexture_;

	// �e�N�X�`���̕�����
	tnl::Vector2i textureCutNum_;

	// �\�����̃I�u�W�F�N�g�̔ԍ�
	tnl::Vector2i displayObj_ = { 0, 0 };

	// ���݂̃A�j���[�V������\�����Ă��鎞��
	float animCount_ = 0;
	// �A�j���[�V������؂�ւ��鎞��
	float animTime_ = 0.5f;

	tnl::Vector3 size;

	std::shared_ptr<Player> player_ = nullptr;
	




	//// �v���C���[�̏�ԗp�̃V�[�P���X
	//tnl::Sequence<Enemy> seq_ = tnl::Sequence<Enemy>(this, &Enemy::seqIdle);

	//// �ҋ@���̃V�[�P���X
	//bool seqIdle(const float delta_time);
	//// �s�����e�����肷��V�[�P���X
	//bool seqActionDecide(const float delta_time);
	//// �ړ�����������V�[�P���X
	//bool seqMoveCheck(const float delta_time);
	//// ��]����������V�[�P���X
	//bool seqRotateCheck(const float delta_time);
	//// �ҋ@����V�[�P���X
	//bool seqWait(const float delta_time);
	//// �ړ����s���V�[�P���X
	//bool seqMoving(const float delta_time);
	//// ��]���s���V�[�P���X
	//bool seqRotating(const float delta_time);



};