#pragma once
#include <vector>
#include <string>


// �Q�[���}�l�[�W���[�N���X
// �Q�[���̎��s�������Ǘ����邽�߂̃N���X
// �����ɃQ�[�����J�n����ۂ̍ŏ��̃V�[��������
// �g�p���@(�Q�l��)

/*
//------------------------------------------------------------------------------------------------------------
void gameStart() {

	srand(time(0));

	// �Q�[���}�l�[�W���[�̃C���X�^���X��
	GameManager* gmr = GameManager::GetInstance_(new SceneTitle());
}

//------------------------------------------------------------------------------------------------------------
void gameMain(float delta_time) {

	// ���݂̃V�[���ł�update�֐������s
	GameManager::GetInstance_()->update(delta_time);
}
*/

namespace ito {

	class SceneBase;

	class GameManager {
	private :

		// �R���X�g���N�^
		// �����F�Q�[�����J�n����ۂɏ��߂Ɏ��s����V�[��
		GameManager(SceneBase* startScene);

	public:

		// �Q�[���}�l�[�W���[���C���X�^���X������ۂɎg�p����֐��B
		// �����F�Q�[�����J�n����ۂɏ��߂Ɏ��s����V�[��
		static GameManager* GetInstance_(SceneBase* startScene = nullptr);

		~GameManager();

		// �V�[���؂�ւ��p�֐�
		// �����F�J�ڂ����̃V�[��
		void changeScene(SceneBase* nextScene);

		void update(float delta_time);

		// ���݂̃V�[�����擾����֐�
		SceneBase* get_nowScene() const { return nowScene_; }

		//--------------------------------------------------------------------------------------------------------------------------
		// csv�t�@�C���ǂݍ��݂Ɋւ�����e
		// ���ݎd�l�������̂��ߎg�p�s��

		// std::vector<std::vector<std::string>> csvAddress;		// �ǂݍ���csv�t�@�C���̃A�h���X���i�[����p

		// void Load_CsvAddress();			// �ǂݍ���csv�t�@�C���̃A�h���X���i�[����csv�t�@�C����ǂݍ��ފ֐�


		//// csv�t�@�C���̃A�h���X
		//enum class CSV_NAME {	
		//	GRAPH_ADDRESS,		// �摜�̕ۑ���̃A�h���X�p
		//	CHARACTER_BASE,		// �L�����N�^�[�x�[�X�p
		//	PLAYER_DATA,		// �v���C���[�Ɋւ���l������p
		//	STAGE_DATA,			// �X�e�[�W�Ɋւ���l������p
		//	CSV_MAX				// CSV�t�@�C���̐�

		//}csv_name;

		//CSV_NAME csv_name = GameManager::CSV_NAME::GRAPH_ADDRESS;

		//--------------------------------------------------------------------------------------------------------------------------


	private:

		// ���ݎ��s���̃V�[��������ϐ�
		SceneBase* nowScene_ = nullptr;
		// ���ɑJ�ڂ���V�[��������ϐ�
		SceneBase* nextScene_ = nullptr;

	};

}
