#pragma once
#include "../../base/SubSceneBase.h"

// �O���錾
class ObjectBlockBase;
class TransformCamera;
class BattleCharacterBase;
class BattlePlayer;
class BattleEnemy;
class SubSceneManager;
class UiHP;

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


	// �T�u�V�[���؂�ւ��̍ۂɌĂяo���֐�
	void ChangeSubScene() override;

private :

	// �X�e�[�W�𐶐�����֐�
	void CreateStage();

	// �X�e�[�W�̃I�u�W�F�N�g���\�[�g����֐�
	// �ŏ��Ɉ����s����
	void SortObject(std::shared_ptr<dxe::Camera> camera);

	// �L�����N�^�[���\�[�g����֐�
	// ���t���[�����s
	void SortCharacter(std::shared_ptr<dxe::Camera> camera);

	// �L�����N�^�[�̍��W��␳����֐�
	// �X�e�[�W�͈̔͊O�ɏo���ꍇ�͈͓��ɕ␳����
	void PosCorrection();

	// �U�����肪�������Ă��邩�ǂ����m�F����֐�
	void CheckHitAttack();

	// �o�g���V�[�����I�����Ă��邩�ǂ������m�F����֐�
	void CheckBattleEnd();


	// �o�g�������ǂ����𔻕ʂ��邽�߂̃t���O
	bool isBattling_ = true;

	//-------------------------------------------------------
	// �L�����N�^�[

	// �v���C���[�̃L�����N�^�[
	std::shared_ptr<BattlePlayer> player_ = nullptr;
	// �G�̃L�����N�^�[
	std::shared_ptr<BattleEnemy> enemy_ = nullptr;

	// �`�悷��L�����N�^�[�̃��X�g
	// �`��O�ɂ�����\�[�g���ď��Ԃɕ`�悷��
	std::shared_ptr< std::list< std::shared_ptr<BattleCharacterBase>> > battleCharaList_;


	//-------------------------------------------------------
	// �J����

	// �o�g���V�[���p�̃J����(ThirdPersonCamera)
	std::shared_ptr< dxe::Camera > TPCamera_ = nullptr;

	// �J�����̃^�[�Q�b�g�̍��W
	tnl::Vector3 cameraTargetPos_ = { 0, 0, 0 };


	//-------------------------------------------------------
	// �X�e�[�W�֌W

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


	//-----------------------------------------------------------------------
	// �\������摜�֌W


	// UI�֌W�𐶐�����֐�
	void CreateBattleUI();

	// �o�g����UI��\�����邽�߂̊֐�
	// draw�֐����ŌĂяo��
	void DisplayBattleUI();

	// �v���C���[��HP��\������UI
	std::shared_ptr< UiHP > playerHpUi_;
	// �v���C���[��HP�̕\���ʒu
	tnl::Vector3 playerHpPos_ = {180, 60, 0};

	// �G�L�����N�^�[��HP��\������UI
	std::shared_ptr< UiHP > enemyHpUi_;
	// �G�L�����N�^�[��HP�̕\���ʒu
	tnl::Vector3 enemyHpPos_ = { 600, 550, 0 };

	// ���C���ŕ\������摜�̈ʒu
	tnl::Vector3 mainGpcPos_ = { DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0 };

	// �`����s���摜�̃��X�g
	std::list< std::shared_ptr<ito::Graphic> > gpcList_;

	// �o�g���V�[���ł̑�������摜�֘A
	int battleControlExpGpc_ = 0;
	tnl::Vector3 battleControlExpPos_ = { 300, 650, 0 };
	float battleControlExpSize_ = 2.5f;


	//-------------------------------------------------------
	// �T�E���h�֌W

	// BGM�̃n���h��
	int battleBgmHdl_ = 0;

	// BGM���������Ă��邩�̃t���O
	bool isPlayingBGM_ = false;



	//-------------------------------------------------------
	// �V�[���؂�ւ��֌W

	// �V�[����؂�ւ���܂ł̎��Ԃ��J�E���g����p
	float sceneChangeCount_ = 0;
	// �V�[����؂�ւ��鎞��
	float sceneChangeTime_ = 3.0f;

	//-----------------------------------------------------------------------
	// �V�[�P���X�֌W

	// ������Ǘ�����p�̃V�[�P���X
	tnl::Sequence<BattleSubScene> seq_ = tnl::Sequence<BattleSubScene>(this, &BattleSubScene::seqBattle);

	// �퓬���s����V�[�P���X
	bool seqBattle(const float delta_time);

	// �o�g���V�[�����I��������V�[�P���X
	bool seqBattleEnd(const float delta_time);
};