#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../other/Enum.h"
#include "../base/CharacterBase.h"
#include "../map/Stage.h"

// ������s���v���C���[�̃N���X
// �����F
class Player final : public CharacterBase {
public :

	// �v���C���[�N���X�̃R���X�g���N�^
	// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
	// �����FcellSize, startGridPos
	Player( float gridSize, tnl::Vector2i startGridPos );

	// �v���C���[�N���X�̃f�X�g���N�^
	~Player();

	void update(float delta_time);

	
private :


	std::string seqNow_ = "seqIdle";



	// �v���C���[�̏�ԗp�̃V�[�P���X
	tnl::Sequence<Player> seq_ = tnl::Sequence<Player>(this, &Player::seqIdle);

	// �ҋ@���̃V�[�P���X
	bool seqIdle(const float delta_time);
	// �ړ�����������V�[�P���X
	bool seqMoveCheck(const float delta_time);
	// ��]����������V�[�P���X
	bool seqRotateCheck(const float delta_time);
	// �ړ����s���V�[�P���X
	bool seqMoving(const float delta_time);
	// ��]���s���V�[�P���X
	bool seqRotating(const float delta_time);
};
