#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <string>
#include <unordered_map>
#include "../base/ObjectBlockBase.h"



class Player;


// �_���W�����̃X�e�[�W���Ǘ�����N���X
// �X�e�[�W�ƕR�Â��X�e�[�W����string�^�ŁAcsv���ǂݎ��\��
class Stage final{
private :

	// �}�b�v�N���X�̃R���X�g���N�^
	// GetInstance�֐���p���ăC���X�^���X���A�C���X�^���X�̎擾���s��
	Stage(std::string startStage, std::string csvPath, float gridSize);

public :

	// Stage�N���X�𐶐��E�擾����p�̊֐�
	// ��������Ƃ��͈�����S�ē���
	// �C���X�^���X�擾���͈����Ȃ��ŌĂяo��
	// �����FstartStage...�J�n���̃X�e�[�W�̖��O, csvPath...�X�e�[�W�̔z���csv�t�@�C���̃p�X
	static std::shared_ptr<Stage> GetInstance( std::string startStage = "", std::string csvPath = "", float gridSize = 50.0f);

	// �}�b�v�N���X�̃f�X�g���N�^
	~Stage();
	// ���t���[���̏���
	void update(float delta_time);
	// �`��̏���
	void draw(std::shared_ptr<dxe::Camera> camera);

	// �v���C���[���Z�b�g����֐�
	void setPlayer(std::shared_ptr<Player> player) { player_ = player; }

	// �V���Ƀ}�b�v��ǂݍ��ފ֐�
	void LoadMap(std::string name, std::string csvPath);

	// �X�e�[�W��؂�ւ���ۂɌĂяo���֐�
	void StageChange(std::string nextStage);


	// �����̍��W�̃}�b�v�̐��l�𒲂ׂ�֐�
	// �����FcheckGrid...�}�b�v�̔z�񂩂�m�F����v�f�ԍ�(x, y)
	int CheckGridPosInt(tnl::Vector2i checkGrid);


	// �����̍��W�̃I�u�W�F�N�g���擾����֐�
	// �����FcheckGrid...�}�b�v�̔z�񂩂�m�F����v�f�ԍ�(x, y)
	std::shared_ptr<ObjectBlockBase> CheckGridPosObj(tnl::Vector2i checkGrid);

	// �`�悷��I�u�W�F�N�g��`�悷��list�ɓ����֐�
	void drawObjectInList();

	// �`�悷��I�u�W�F�N�g��list���J��������̋����Ń\�[�g����֐�
	void sortObjectList( std::shared_ptr<dxe::Camera> camera );

private :

	// �v���C���[
	std::shared_ptr<Player> player_ = nullptr;

	// �`�悷��I�u�W�F�N�g�̃��X�g
	// �`��O�ɖ���J��������̋����Ń\�[�g����
	std::list<std::shared_ptr<ObjectBlockBase>> drawObjectList_;

	// �}�b�v�𐶐�����ۂ̊�̍��W
	tnl::Vector3 basePos_ = { 0, 0, 0 };
	// �}�b�v���\������I�u�W�F�N�g�̊�{�̑傫��
	float gridSize_ = 50;

	// ���݂̃X�e�[�W�����s�\���ǂ����̃t���O
	// �X�e�[�W��؂�ւ����ۂɊm�F���Đ؂�ւ���
	bool existNowStage_ = true;

	//-------------------------------------------------------------------------------------
	// Stage�̍s���V�[�P���X�����֌W
	
	// ���݂̃V�[�P���X
	tnl::Sequence<Stage> seq_ = tnl::Sequence<Stage>(this, &Stage::seqStageChange);

	// ���݂̃X�e�[�W�����s�\���m�F����V�[�P���X
	// �X�e�[�W��؂�ւ����ۂɕK��������ʉ߂�����
	// ����existNowStage_��؂�ւ���
	bool seqCheckNowStage(const float delta_time);

	// ���݂̃X�e�[�W�̃A�b�v�f�[�g���s���V�[�P���X
	// �ʏ펞�͂��̃V�[�P���X�����s
	// �����ɉ����Ċe�V�[�P���X�Ɉڍs
	bool seqNowStageUpdate(const float delta_time);

	// �X�e�[�W�����̃X�e�[�W�ɐ؂�ւ���V�[�P���X
	// �X�e�[�W�̃I�u�W�F�N�g���쐬���Ă���΃V�[����؂�ւ��A
	// �쐬���Ă��Ȃ���΃X�e�[�W���̔z�񂩂�X�e�[�W�̃I�u�W�F�N�g���쐬����
	// �I�������seqCheckNowStage�Ɉڂ�
	// �����FnextStage...���ɐ؂�ւ���X�e�[�W
	bool seqStageChange(const float delta_time);



	// �X�e�[�W�̔z���ۑ�����unordered_map
	// �����Fstring...���O, std::vector�`<int>>>...�}�b�v�̔z��
	std::unordered_map<std::string, std::vector<std::vector<int>>> stageArrayMap_;

	// �X�e�[�W���\������I�u�W�F�N�g��ۑ�����unordered_map
	// �����Fstring...���O, std::vector�`<ObjectBlockBase>>>...�}�b�v�̃I�u�W�F�N�g
	std::unordered_map<std::string, std::vector<std::vector< std::shared_ptr<ObjectBlockBase> >>> stageObjMap_;

	// ���݂̃X�e�[�W����\��string
	// �X�e�[�W��ǂݍ��ލہA�؂�ւ���ۂȂǂɎg�p����
	// �X�e�[�W����\��enum class�ɕύX����\������
	std::string nowStage_ = "";

	// ���݂̃V�[�P���X
	std::string nowSeq_ = "";

};