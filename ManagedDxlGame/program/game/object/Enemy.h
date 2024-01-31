#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/CharacterBase.h"


// �X�e�[�W��ł̓G�L�����N�^�[�̃N���X
// �����FcellSize...�X�e�[�W��1�}�X�̑傫��
// startGridPos...�������̏����ʒu
class Enemy : public CharacterBase {
public :
	// �R���X�g���N�^
	// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
	// �����FcellSize...�X�e�[�W��1�}�X�̑傫��
	// startGridPos...�������̏����ʒu
	Enemy(float gridSize, tnl::Vector2i startGridPos);

	// �f�X�g���N�^
	~Enemy();

	// ���t���[�����s����֐�
	void update(float delta_time);

	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera );


private :

	// Enemy��Mesh
	// 2D�̉摜��\��t����Plane��p�ӂ���p
	std::shared_ptr<ito::Object3D> enemyObj_;


	//// �v���C���[�̏�ԗp�̃V�[�P���X
	//tnl::Sequence<Enemy> seq_ = tnl::Sequence<Enemy>(this, &Enemy::seqIdle);

	//// �ҋ@���̃V�[�P���X
	//bool seqIdle(const float delta_time);
	//// �ړ�����������V�[�P���X
	//bool seqMoveCheck(const float delta_time);
	//// ��]����������V�[�P���X
	//bool seqRotateCheck(const float delta_time);
	//// �ړ����s���V�[�P���X
	//bool seqMoving(const float delta_time);
	//// ��]���s���V�[�P���X
	//bool seqRotating(const float delta_time);



};