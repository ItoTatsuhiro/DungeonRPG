#pragma once
#include "../../base/SubSceneBase.h"

// �O���錾
class ObjectBlockBase;
class TransformCamera;
class BattlePlayer;


// �o�g���V�[���̃T�u�N���X
// ScenePlay���ŕK�v�ɉ�����update, draw����
class BattleSubScene final : public SubSceneBase {
public :
	// �R���X�g���N�^
	BattleSubScene();
	// �f�X�g���N�^
	~BattleSubScene();
	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw() override;



private :


	// �X�e�[�W�𐶐�����֐�
	void CreateStage();

	// �X�e�[�W�̃I�u�W�F�N�g���\�[�g����֐�
	void SortObject(std::shared_ptr<dxe::Camera> camera);

	// �L�����N�^�[�̍��W��␳����֐�
	// �X�e�[�W�͈̔͊O�ɏo���ꍇ�͈͓��ɕ␳����
	void posCorrection();


	std::shared_ptr<BattlePlayer> player_ = nullptr;



	// �o�g���V�[���p�̃J����(ThirdPersonCamera)
	std::shared_ptr< dxe::Camera > TPCamera_ = nullptr;


	// �J�����̃^�[�Q�b�g�̍��W
	tnl::Vector3 cameraTargetPos_ = { 0, 0, 0 };

	// �o�g���V�[���p�̃X�e�[�W�̔z��
	std::vector<std::vector<int>> battleStageArray_;
	// �X�e�[�W�ɔz�u����Ă���I�u�W�F�N�g�̔z��
	std::vector<std::vector<std::shared_ptr<ObjectBlockBase>>> battleStageObjArray_;
	// �o�g���V�[���ŕ`�悷��X�e�[�W�̃I�u�W�F�N�g�̃��X�g
	std::list< std::shared_ptr< ObjectBlockBase >> battleStageObjList_;

	// �X�e�[�W�𐶐�����ۂ̊�ƂȂ���W
	tnl::Vector3 basePos_ = { 0, 0, 0 };

	// 1�}�X�̏c���̑傫��
	float gridSize_ = 50;

	// �v���C���[�̊J�n�ʒu
	// �R���X�g���N�^�ŏ�����
	// x...�X�e�[�W��1/3�̈ʒu
	// z...�X�e�[�W�̔����̈ʒu
	tnl::Vector3 startPosPlayer_;
	// �G�L�����N�^�[�̊J�n�ʒu
	// �R���X�g���N�^�ŏ�����
	// x...�X�e�[�W��2/3�̈ʒu
	// z...�X�e�[�W�̔����̈ʒu
	tnl::Vector3 startPosEnemy_;

	// �X�e�[�W�̏��̍���(���̃I�u�W�F�N�g�̍��W)
	// ����stageSize�`�ϐ���y�ɓ����p
	float floorHeight_ = 0;

	// �X�e�[�W�̑傫��(�ŏ��l)
	// �I�u�W�F�N�g�̔z���[0][0]�̃I�u�W�F�N�g�̍��W�Ƃ���
	// y�͏��̃I�u�W�F�N�g�̍��W
	tnl::Vector3 stageSizeMin_;
	// �X�e�[�W�̑傫��(�ő�l)
	// �I�u�W�F�N�g�̔z���[max][max]�̃I�u�W�F�N�g�̍��W�Ƃ���
	// y�͏��̃I�u�W�F�N�g�̍��W
	tnl::Vector3 stageSizeMax_;

	// ������Ǘ�����p�̃V�[�P���X
	tnl::Sequence<BattleSubScene> seq_ = tnl::Sequence<BattleSubScene>(this, &BattleSubScene::seqBattle);

	// �퓬���s����V�[�P���X
	bool seqBattle(const float delta_time);

};