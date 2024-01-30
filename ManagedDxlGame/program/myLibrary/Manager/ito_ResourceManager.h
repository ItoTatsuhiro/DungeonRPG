#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "../library/tnl_csv.h"


namespace ito {

	// �摜�A�A�j���[�V�����A�T�E���h���̃��\�[�X���Ǘ�����p�̃N���X
	// ���ꂼ���ǂݍ��ނ��߂̊֐�����
	// �R���X�g���N�^���ł��ꂼ��̏���ۊǂ���csv��ǂݍ��ޕK�v����

	class ResourceManager {
	private:

		// �R���X�g���N�^
		// ���\�[�X�̏�����������csv��ǂݍ���
		// GetInstance�֐�����̂݃C���X�^���X�����邽��private
		ResourceManager();

	public:

		// GraphicManager���C���X�^���X������֐�
		static ResourceManager* GetInstance_();

		// �f�X�g���N�^
		~ResourceManager();


	private:
		//--------------------------------------------------------------------------------------------------------------------------
		// �摜�֌W

		// �摜�̃p�X��csv�̓��e��ǂݍ��ޗp��vector
		std::vector<std::vector<std::string>> graphics_csv_;
		// �ǂݍ��񂾉摜��ۑ�����p��map
		std::unordered_map < std::string, int> graphics_map_;
		// �摜��csv�̍���(x����)
		enum class GPC_CSV_ITEM {
			FILE_NAME = 1,			// �摜�̃t�@�C����
			PATH,					// �摜�̃p�X
			MAX						// ���ڂ̐�+1
		};

		//--------------------------------------------------------------------------------------------------------------------------
		// �A�j���[�V�����֌W

		// �A�j���[�V������csv��ǂݍ��ޗp��vector
		std::vector<std::vector<tnl::CsvCell>> anim_csv_;
		// �ǂݍ��񂾃A�j���[�V�����摜��ۑ�����p��map
		std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animation_map_;
		// �A�j���[�V������csv�̍���(x����)
		enum class ANIM_CSV_ITEM {
			FILE_NAME = 1,			// �A�j���[�V�����̃t�@�C����
			PATH ,					// �摜�̃p�X
			TOTAL_FRAMES,			// ��������
			HOLIZONTAL_FRAMES,		// �������̕�����
			VERTICAL_FRAMES,		// �c�����̕�����
			WIDTH,					// �������̉���
			HEIGHT,					// �������̍���
			MAX						// ���ڂ̐�+1
		};


		//--------------------------------------------------------------------------------------------------------------------------
		// �T�E���h�֌W

		// �T�E���h�̃p�X��csv�̓��e��ǂݍ��ޗp��vector
		std::vector<std::vector<std::string>> sounds_csv_;
		// �ǂݍ��񂾃p�X��ۑ�����p��map
		std::unordered_map < std::string, int> sounds_map_;
		// �T�E���h��csv�̍���(x����)
		enum class SOUND_CSV_ITEM {
			FILE_NAME = 1,			// �T�E���h�̃t�@�C����
			PATH,					// �T�E���h�̃p�X
			MAX						// ���ڂ̐�+1
		};

	public:

		//--------------------------------------------------------------------------------------------------------------------------
		// �摜�֌W�̊֐�

		// �摜��ǂݍ��ފ֐�
		// �����F�摜�t�@�C���̖��O(std::string�^)
		int loadGraph_(std::string graphFileName);
		// �摜���폜����֐�
		// �����F�摜�̎�ނ�\��enum class, GRAPHIC_TYPE�^
		void deleteGraph_(std::string graphFileName);


		//--------------------------------------------------------------------------------------------------------------------------
		// �A�j���[�V�����֌W�̊֐�

		// �A�j���[�V�����摜��ǂݍ��ފ֐�
		// �����F�A�j���[�V�����̃t�@�C����
		std::shared_ptr<std::vector<int>> loadAnimGraph(std::string animFileName);
		// �A�j���[�V�������폜����֐�
		// �����F�A�j���[�V�����̃t�@�C����
		void deleteAnimGraph(std::string animFileName);


		//--------------------------------------------------------------------------------------------------------------------------
		// �T�E���h�֌W�̊֐�

		// �T�E���h��ǂݍ��ފ֐�
		// �����F�T�E���h�̃t�@�C����(std::string�^)
		int loadSoundMem_(std::string soundFileName);
		// �T�E���h���폜����֐�
		// �����F�T�E���h�̃t�@�C����(std::string�^)
		void deleteSoundMem_(std::string soundFileName);


		// ���\�[�X�}�l�[�W���[���̂�destroy���邽�߂̊֐�
		static void Destroy();

	};

}