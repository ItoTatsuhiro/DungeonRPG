#include "DXLib.h"
#include "ito_ResourceManager.h"


namespace ito {

	// �R���X�g���N�^
	// ���\�[�X�̏����L������csv�t�@�C����ǂݍ���
	ito::ResourceManager::ResourceManager() {

		// ���\�[�X��csv�̓ǂݍ���
		graphics_csv_ = tnl::LoadCsv<std::string>("csv/Resource/graphData.csv");
		anim_csv_ = tnl::LoadCsv("csv/Resource/animData.csv");
		sounds_csv_ = tnl::LoadCsv<std::string>("csv/Resource/soundData.csv");

	}

	ito::ResourceManager::~ResourceManager() {

	}

	// 
	ResourceManager* ResourceManager::GetInstance_() {

		static ResourceManager* instance(nullptr);
		if (!instance) {
			instance = new ResourceManager();
		}
		return instance;
	}


	//----------------------------------------------------------------------------------------
	// �摜��ǂݍ��ފ֐�
	// �����F�ǂݍ��މ摜�̃t�@�C����
	int ito::ResourceManager::loadGraph_(std::string graphFileName) {

		// file_path�ɑΉ�����摜�n���h����T��
		auto it = graphics_map_.find(graphFileName);

		// ���Ƀ��[�h���Ă���ꍇ�A���̉摜�n���h����Ԃ�
		if (it != graphics_map_.end()) {
			return graphics_map_[graphFileName];
		}

		// �摜�̓ǂݍ���
		// int gpc_hdl = LoadGraph(graphics_csv_[static_cast<int>(gpc_type)][2].c_str(), true);

		for (int y = 1; y < graphics_csv_.size(); ++y) {
			if (graphics_csv_[y][static_cast<int>(GPC_CSV_ITEM::FILE_NAME)] == graphFileName) {
				int gpc_hdl = LoadGraph(graphics_csv_[y][static_cast<int>(GPC_CSV_ITEM::PATH)].c_str(), true);

				// graphics_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
				graphics_map_.insert(std::make_pair(graphFileName, gpc_hdl));

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
	void ito::ResourceManager::deleteGraph_(std::string graphFileName) {

		// file_path�ɑΉ�����摜�n���h����T��
		auto it = graphics_map_.find(graphFileName);

		// �摜�n���h�������
		DeleteGraph(it->second);

		// file_path�̉摜�p�X���폜����
		if (it != graphics_map_.end()) {
			graphics_map_.erase(graphFileName);
		}

	}

	//----------------------------------------------------------------------------------------
	// �A�j���[�V�����摜��ǂݍ��ފ֐�
	// �����F�A�j���[�V�����̎�ނ�\��enum class, ANIM_CSV_OBJ�^
	std::shared_ptr<std::vector<int>> ito::ResourceManager::loadAnimGraph(std::string animFileName) {

		// file_path�ɑΉ�����摜�A�j���[�V�����n���h����T��
		auto it = animation_map_.find(animFileName);


		if (it != animation_map_.end()) {
			return animation_map_[animFileName];
		}

		for (int y = 0; y < anim_csv_.size(); ++y) {

			if (anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::FILE_NAME)].getString() == animFileName) {

				// �摜�A�j���[�V�����̓ǂݍ���
				std::shared_ptr<std::vector<int>> anim_hdls
					= std::make_shared<std::vector<int>>(anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::TOTAL_FRAMES)].getInt());

				LoadDivGraph(
					anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::PATH)].getString().c_str(),
					anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::TOTAL_FRAMES)].getInt(),
					anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::HOLIZONTAL_FRAMES)].getInt(),
					anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::VERTICAL_FRAMES)].getInt(),
					anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::WIDTH)].getInt(),
					anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::HEIGHT)].getInt(),
					anim_hdls->data() );

				// �摜�A�j���[�V������animation_map_�Ƀp�X�ƕR�Â��ĕۑ�
				animation_map_.insert(std::make_pair(animFileName, anim_hdls));

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
		auto it = animation_map_.find(animFileName);

		if (it != animation_map_.end()) {

			std::shared_ptr<std::vector<int>> anim_hdls = it->second;

			for (int anim_hdl : (*anim_hdls)) {
				DeleteGraph(anim_hdl);
			}


			// ANIM_CSV_OBJ�ɑΉ�����p�X���폜����
			if (it != animation_map_.end()) {
				animation_map_.erase(animFileName);
			}

		}

	}

	//----------------------------------------------------------------------------------------
	// �T�E���h��ǂݍ��ފ֐�
	// �����F�T�E���h�̃t�@�C����
	int ResourceManager::loadSoundMem_(std::string soundFileName) {

		// SOUND_KINDS�ɑΉ�����T�E���h�n���h����T��
		auto it = sounds_map_.find(soundFileName);

		// ���Ƀ��[�h���Ă���ꍇ�A���̃T�E���h�n���h����Ԃ�
		if (it != sounds_map_.end()) {
			return sounds_map_[soundFileName];
		}

		// csv�ɕۑ����ꂽ�t�@�C�������瓯�����̂�T��
		for (int y = 1; y < sounds_csv_.size(); ++y) {
			if (sounds_csv_[y][static_cast<int>(SOUND_CSV_ITEM::FILE_NAME)] == soundFileName) {

				// �T�E���h�̓ǂݍ���
				int sound_hdl = LoadGraph(sounds_csv_[y][static_cast<int>(SOUND_CSV_ITEM::PATH)].c_str(), true);

				// sounds_map_�ɓǂݍ��񂾉摜���p�X�ƕR�Â��ĕۑ�
				sounds_map_.insert(std::make_pair(soundFileName, sound_hdl));

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
	void ResourceManager::deleteSoundMem_(std::string soundFileName) {

		// SOUND_KINDS�ɑΉ�����摜�n���h����T��
		auto it = sounds_map_.find(soundFileName);


		// �T�E���h�n���h�������
		DeleteSoundMem(it->second);

		// SOUND_KINDS�ɑΉ�����p�X���폜����
		if (it != sounds_map_.end()) {
			sounds_map_.erase(soundFileName);
		}

	}


	void ResourceManager::Destroy() {

		delete GetInstance_();
	}

}