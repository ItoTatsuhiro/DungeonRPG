#include "DXLib.h"
#include "ito_ResourceManager.h"


namespace ito {

	// �R���X�g���N�^
	// ���\�[�X�̏����L������csv�t�@�C����ǂݍ���
	ito::ResourceManager::ResourceManager() {

		// ���\�[�X��csv�̓ǂݍ���
		gpcCsv_ = tnl::LoadCsv<std::string>("csv/Resource/gpcData.csv");
		animCsv_ = tnl::LoadCsv("csv/Resource/animData.csv");
		soundsCsv_ = tnl::LoadCsv<std::string>("csv/Resource/soundData.csv");
		textureCsv_ = tnl::LoadCsv("csv/Resource/textureData.csv");
	}

	ito::ResourceManager::~ResourceManager() {

	}

	// 
	ResourceManager* ResourceManager::GetInstance() {

		static ResourceManager* instance(nullptr);
		if (!instance) {
			instance = new ResourceManager();
		}
		return instance;
	}


	//----------------------------------------------------------------------------------------
	// �摜��ǂݍ��ފ֐�
	// �����F�ǂݍ��މ摜�̃t�@�C����
	int ito::ResourceManager::loadGraph(std::string graphFileName) {

		// file_path�ɑΉ�����摜�n���h����T��
		auto it = gpcMap_.find(graphFileName);

		// ���Ƀ��[�h���Ă���ꍇ�A���̉摜�n���h����Ԃ�
		if (it != gpcMap_.end()) {
			return gpcMap_[graphFileName];
		}

		// �摜�̓ǂݍ���
		// int gpc_hdl = LoadGraph(graphics_csv_[static_cast<int>(gpc_type)][2].c_str(), true);

		for (int y = 1; y < gpcCsv_.size(); ++y) {
			if (gpcCsv_[y][static_cast<int>(GPC_CSV_ITEM::FILE_NAME)] == graphFileName) {
				int gpc_hdl = LoadGraph(gpcCsv_[y][static_cast<int>(GPC_CSV_ITEM::PATH)].c_str(), true);

				// graphics_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
				gpcMap_.insert(std::make_pair(graphFileName, gpc_hdl));

				// �摜�n���h����Ԃ�
				return gpc_hdl;
			}
		}
		// �ǂݍ��݂ł��Ȃ������ꍇ��-1��Ԃ�
		return -1;
	}

	//----------------------------------------------------------------------------------------
	// �摜���폜����֐�
	// �����F�폜����摜�̃t�@�C����
	void ito::ResourceManager::deleteGraph(std::string graphFileName) {

		// file_path�ɑΉ�����摜�n���h����T��
		auto it = gpcMap_.find(graphFileName);

		// �摜�n���h�������
		DeleteGraph(it->second);

		// file_path�̉摜�p�X���폜����
		if (it != gpcMap_.end()) {
			gpcMap_.erase(graphFileName);
		}

	}

	//----------------------------------------------------------------------------------------
	// �A�j���[�V�����摜��ǂݍ��ފ֐�
	// �����F�A�j���[�V�����̎�ނ�\��enum class, ANIM_CSV_OBJ�^
	std::shared_ptr<std::vector<int>> ito::ResourceManager::loadAnimGraph(std::string animFileName) {

		// file_path�ɑΉ�����摜�A�j���[�V�����n���h����T��
		auto it = animMap_.find(animFileName);


		if (it != animMap_.end()) {
			return animMap_[animFileName];
		}

		for (int y = 0; y < animCsv_.size(); ++y) {

			if (animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::FILE_NAME)].getString() == animFileName) {

				// �摜�A�j���[�V�����̓ǂݍ���
				std::shared_ptr<std::vector<int>> anim_hdls
					= std::make_shared<std::vector<int>>(animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::TOTAL_FRAMES)].getInt());

				LoadDivGraph(
					animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::PATH)].getString().c_str(),
					animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::TOTAL_FRAMES)].getInt(),
					animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::HOLIZONTAL_FRAMES)].getInt(),
					animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::VERTICAL_FRAMES)].getInt(),
					animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::WIDTH)].getInt(),
					animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::HEIGHT)].getInt(),
					anim_hdls->data() );

				// �摜�A�j���[�V������animation_map_�Ƀp�X�ƕR�Â��ĕۑ�
				animMap_.insert(std::make_pair(animFileName, anim_hdls));

				// �A�j���[�V�����n���h����Ԃ�
				return anim_hdls;
			}
		}

	}

	//----------------------------------------------------------------------------------------
	// �摜���폜����֐�
	// �����F�폜����A�j���[�V�����̃t�@�C����
	void ResourceManager::deleteAnimGraph(std::string animFileName) {

		// ANIM_CSV_OBJ�ɑΉ�����摜�n���h����T��
		auto it = animMap_.find(animFileName);

		if (it != animMap_.end()) {

			std::shared_ptr<std::vector<int>> anim_hdls = it->second;

			for (int anim_hdl : (*anim_hdls)) {
				DeleteGraph(anim_hdl);
			}


			// ANIM_CSV_OBJ�ɑΉ�����p�X���폜����
			if (it != animMap_.end()) {
				animMap_.erase(animFileName);
			}

		}

	}

	//----------------------------------------------------------------------------------------
	// �T�E���h��ǂݍ��ފ֐�
	// �����F�T�E���h�̃t�@�C����
	int ResourceManager::loadSoundMem(std::string soundFileName) {

		// SOUND_KINDS�ɑΉ�����T�E���h�n���h����T��
		auto it = soundsMap_.find(soundFileName);

		// ���Ƀ��[�h���Ă���ꍇ�A���̃T�E���h�n���h����Ԃ�
		if (it != soundsMap_.end()) {
			return soundsMap_[soundFileName];
		}

		// csv�ɕۑ����ꂽ�t�@�C�������瓯�����̂�T��
		for (int y = 0; y < soundsCsv_.size(); ++y) {
			if (soundsCsv_[y][static_cast<int>(SOUND_CSV_ITEM::FILE_NAME)] == soundFileName) {

				// �T�E���h�̓ǂݍ���
				int sound_hdl = LoadSoundMem(soundsCsv_[y][static_cast<int>(SOUND_CSV_ITEM::PATH)].c_str(), true);

				// sounds_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
				soundsMap_.insert(std::make_pair(soundFileName, sound_hdl));

				// �T�E���h�n���h����Ԃ�
				return sound_hdl;
			}
		}
		// �ǂݍ��݂ł��Ȃ������ꍇ��-1��Ԃ�
		return -1;

	}

	//----------------------------------------------------------------------------------------
	// �T�E���h���폜����֐�
	// �����F�폜����T�E���h�̃t�@�C����
	void ResourceManager::deleteSoundMem(std::string soundFileName) {

		// SOUND_KINDS�ɑΉ�����摜�n���h����T��
		auto it = soundsMap_.find(soundFileName);


		// �T�E���h�n���h�������
		DeleteSoundMem(it->second);

		// SOUND_KINDS�ɑΉ�����p�X���폜����
		if (it != soundsMap_.end()) {
			soundsMap_.erase(soundFileName);
		}

	}


	//----------------------------------------------------------------------------------------
	// �e�N�X�`����ǂݍ��ފ֐�
	// �����F�ǂݍ��ރe�N�X�`���p�摜�̃t�@�C����
	std::shared_ptr<dxe::Texture> ito::ResourceManager::loadTexture(std::string textureFileName) {

		// file_path�ɑΉ�����摜�n���h����T��
		auto it = textureMap_.find(textureFileName);

		// ���Ƀ��[�h���Ă���ꍇ�A���̉摜�n���h����Ԃ�
		if (it != textureMap_.end()) {
			return textureMap_[textureFileName];
		}



		for (int y = 1; y < textureCsv_.size(); ++y) {
			if (textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::FILE_NAME)].getString().c_str() == textureFileName) {
				std::shared_ptr<dxe::Texture> textureHdl = dxe::Texture::CreateFromFile(textureCsv_[y][static_cast<int>(GPC_CSV_ITEM::PATH)].getString().c_str());

				// graphics_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
				textureMap_.insert(std::make_pair(textureFileName, textureHdl));

				// �摜�n���h����Ԃ�
				return textureHdl;
			}
		}
		// �ǂݍ��݂ł��Ȃ������ꍇ��nullptr��Ԃ�
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	// �e�N�X�`�����폜����֐�
	// �����F�폜����摜�̃t�@�C����
	void ito::ResourceManager::deleteTexture(std::string textureFileName) {

		// file_path�ɑΉ�����摜�n���h����T��
		auto it = textureMap_.find(textureFileName);

		// �e�N�X�`���n���h�������
		it->second = nullptr;

		// file_path�̉摜�p�X���폜����
		if (it != textureMap_.end()) {
			textureMap_.erase(textureFileName);
		}

	}

	//----------------------------------------------------------------------------------------
	// �ǂݍ��񂾃e�N�X�`���̕��������擾����֐�
	// �����F�e�N�X�`���̉摜�t�@�C����(std::string�^)
	tnl::Vector2i ito::ResourceManager::getTextureCutNum(std::string textureFileName) {

		for (int y = 1; y < textureCsv_.size(); ++y) {
			if (textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::FILE_NAME)].getString().c_str() == textureFileName) {
				
				tnl::Vector2i textureCutNum;

				textureCutNum = { textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::CUT_NUM_OF_U)].getInt(),
									textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::CUT_NUM_OF_V)].getInt() };

				// �摜�n���h����Ԃ�
				return textureCutNum;
			}
		}

	}


	void ResourceManager::Destroy() {

		delete GetInstance();
	}

}