#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "../library/tnl_csv.h"
#include "../../dxlib_ext/dxlib_ext.h"

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
		static ResourceManager* GetInstance();

		// �f�X�g���N�^
		~ResourceManager();


	private:
		//--------------------------------------------------------------------------------------------------------------------------
		// �摜�֌W

		// �摜�̃p�X��csv�̓��e��ǂݍ��ޗp��vector
		std::vector<std::vector<std::string>> gpcCsv_;
		// �ǂݍ��񂾉摜��ۑ�����p��map
		std::unordered_map < std::string, int> gpcMap_;
		// �摜��csv�̍���(x����)
		enum class GPC_CSV_ITEM {
			FILE_NAME = 1,			// �摜�̃t�@�C����
			PATH,					// �摜�̃p�X
			MAX						// ���ڂ̐�+1
		};

		//--------------------------------------------------------------------------------------------------------------------------
		// �A�j���[�V�����֌W

		// �A�j���[�V������csv��ǂݍ��ޗp��vector
		std::vector<std::vector<tnl::CsvCell>> animCsv_;
		// �ǂݍ��񂾃A�j���[�V�����摜��ۑ�����p��map
		std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animMap_;
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
		std::vector<std::vector<std::string>> soundsCsv_;
		// �ǂݍ��񂾃p�X��ۑ�����p��map
		std::unordered_map < std::string, int> soundsMap_;
		// �T�E���h��csv�̍���(x����)
		enum class SOUND_CSV_ITEM {
			FILE_NAME = 1,			// �T�E���h�̃t�@�C����
			PATH,					// �T�E���h�̃p�X
			MAX						// ���ڂ̐�+1
		};


		//--------------------------------------------------------------------------------------------------------------------------
		// �e�N�X�`���֌W

		// �e�N�X�`���̃p�X��csv�̓��e��ǂݍ��ޗp��vector
		std::vector<std::vector<tnl::CsvCell>> textureCsv_;
		// �ǂݍ��񂾃p�X��ۑ�����p��map
		std::unordered_map < std::string, std::shared_ptr<dxe::Texture> > textureMap_;
		// �e�N�X�`����csv�̍���(x����)
		enum class TEXTURE_CSV_ITEM {
			FILE_NAME = 1,			// �e�N�X�`���p�摜�̃t�@�C����
			PATH,					// �e�N�X�`���̃p�X
			CUT_NUM_OF_U,			// U�����̕�����
			CUT_NUM_OF_V,			// V�����̕�����
			MAX						// ���ڂ̐�+1
		};




	public:

		//--------------------------------------------------------------------------------------------------------------------------
		// �摜�֌W�̊֐�

		// �摜��ǂݍ��ފ֐�
		// �����F�摜�t�@�C���̖��O(std::string�^)
		int loadGraph(std::string graphFileName);
		// �摜���폜����֐�
		// �����F�摜�̎�ނ�\��enum class, GRAPHIC_TYPE�^
		void deleteGraph(std::string graphFileName);


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
		int loadSoundMem(std::string soundFileName);
		// �T�E���h���폜����֐�
		// �����F�T�E���h�̃t�@�C����(std::string�^)
		void deleteSoundMem(std::string soundFileName);






		//--------------------------------------------------------------------------------------------------------------------------
		// �e�N�X�`���֌W�̊֐�

		// �e�N�X�`����ǂݍ��ފ֐�
		// �����F�e�N�X�`���̃t�@�C����(std::string�^)
		std::shared_ptr<dxe::Texture> loadTexture(std::string textureFileName);
		// �ǂݍ��񂾃e�N�X�`�����폜����֐�
		// �����F�e�N�X�`���̉摜�t�@�C����(std::string�^)
		void deleteTexture(std::string textureFileName);
		// �ǂݍ��񂾃e�N�X�`���̕��������擾����֐�
		// �����F�e�N�X�`���̉摜�t�@�C����(std::string�^)
		tnl::Vector2i getTextureCutNum(std::string textureFileName);

		// ���\�[�X�}�l�[�W���[���̂�destroy���邽�߂̊֐�
		static void Destroy();

	};

}