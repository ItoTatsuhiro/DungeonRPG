#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../other/Enum.h"

// �o�g���V�[���ő��삷��v���C���[�̃N���X
// �_���W�����V�[���ƈقȂ�A���b�V��������
// �܂��A���_��1�l�̎��_�ł͂Ȃ�
class BattlePlayer : public ito::Object3D {
public :
	// �R���X�g���N�^
	// �����F�J�n�ʒu
	BattlePlayer( tnl::Vector3 startPos );
	// �f�X�g���N�^
	~BattlePlayer();
	// �X�V�p�̊֐�
	void update(float delta_time);
	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera);

	// �����蔻��̃��b�V�����擾����֐�
	std::shared_ptr<ito::Object3D> getHitBox() { return hitBox_; }

	// �ړ��O�̍��W���擾����֐�
	// ���W�̕␳���̍ۂɎg�p
	tnl::Vector3 getBeforePos() { return beforePos_; }


private :

	// �����蔻��ƂȂ郁�b�V��(Box)
	std::shared_ptr<ito::Object3D> hitBox_ = nullptr;
	// �摜��\�������郁�b�V��(Plane)
	std::vector<std::vector<std::shared_ptr<ito::Object3D>>> playerObjArray_;
	// �\��t����e�N�X�`���̕�����
	// �R���X�g���N�^�œǂݍ���
	tnl::Vector2i textureCutNum_ = { 0, 0 };
	// �\��t����e�N�X�`��
	std::shared_ptr<dxe::Texture> playerTexture_ = nullptr;
	// �ړ��O�̍��W
	// ���W�̕␳�̍ۂɂ��̍��W���g�p����
	tnl::Vector3 beforePos_;

	// �쐬���郁�b�V���̑傫��
	float meshSize_ = 50;

	// �����Ă������
	// �f�t�H���g�ł͉E����
	Enum::Dir4 frontDir = Enum::Dir4::RIGHT;
	
	// �摜�̌����Ă������
	// �摜�͍��E�̊G�����Ȃ����߁A���E���������ۂɌ����ɉ����Đ؂�ւ��
	// �㉺�̈ړ��ł͐؂�ւ��Ȃ�
	Enum::Dir4 animFrontDir = Enum::Dir4::RIGHT;

	// �A�j���[�V�����p�̃��b�V����؂�ւ��鎞��
	const float animChangeTime_ = 0.15;
	// ���݂̃A�j���[�V�������Đ����Ă��鎞��
	// �ړ����̃A�j���[�V�����͎~�߂��ۂ�0�Ƀ��Z�b�g����
	float animChangeCount_ = 0;

	// �\�����̃I�u�W�F�N�g�̔ԍ�
	tnl::Vector2i displayObj_ = { 0, 0 };

	// �ړ���
	float moveValue_ = 5;

	// �ړ����s���֐�
	void Move(float delta_time);

	// �U���̏����ɓ��邽�߂̊֐�
	// �U���̂��߂̃L�[���͂��������Ƃ��V�[�P���X��؂�ւ��鏈�����s��
	void OnAttackKey();

	// �U���̃��X�g
	std::list<std::shared_ptr<ito::Object3D>> attackList_;

	// �U���̑傫��
	// �R���X�g���N�^�ŏ�����
	float attackSize_ = 0;

	// �V�[�P���X�����p�̕ϐ�
	tnl::Sequence<BattlePlayer> seq_ = tnl::Sequence<BattlePlayer>(this, &BattlePlayer::seqIdle);

	// �ҋ@���̃V�[�P���X
	bool seqIdle(const float delta_time);
	// �U���̃V�[�P���X
	bool seqAttack(const float delta_time);

};
