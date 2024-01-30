#include "DXLib.h"
#include "ito_ResourceManager.h"


namespace ito {

	// コンストラクタ
	// リソースの情報を記入したcsvファイルを読み込む
	ito::ResourceManager::ResourceManager() {

		// リソースのcsvの読み込み
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
	// 画像を読み込む関数
	// 引数：読み込む画像のファイル名
	int ito::ResourceManager::loadGraph_(std::string graphFileName) {

		// file_pathに対応する画像ハンドルを探す
		auto it = graphics_map_.find(graphFileName);

		// 既にロードしてある場合、その画像ハンドルを返す
		if (it != graphics_map_.end()) {
			return graphics_map_[graphFileName];
		}

		// 画像の読み込み
		// int gpc_hdl = LoadGraph(graphics_csv_[static_cast<int>(gpc_type)][2].c_str(), true);

		for (int y = 1; y < graphics_csv_.size(); ++y) {
			if (graphics_csv_[y][static_cast<int>(GPC_CSV_ITEM::FILE_NAME)] == graphFileName) {
				int gpc_hdl = LoadGraph(graphics_csv_[y][static_cast<int>(GPC_CSV_ITEM::PATH)].c_str(), true);

				// graphics_map_に読み込んだ画像をパスと紐づけて保存
				graphics_map_.insert(std::make_pair(graphFileName, gpc_hdl));

				// 画像ハンドルを返す
				return gpc_hdl;
			}
		}
		// 読み込みできなかった場合は-1を返す
		return -1;
	}

	//----------------------------------------------------------------------------------------
	// 画像を削除する関数
	// 引数：削除する画像のファイル名
	void ito::ResourceManager::deleteGraph_(std::string graphFileName) {

		// file_pathに対応する画像ハンドルを探す
		auto it = graphics_map_.find(graphFileName);

		// 画像ハンドルを解放
		DeleteGraph(it->second);

		// file_pathの画像パスを削除する
		if (it != graphics_map_.end()) {
			graphics_map_.erase(graphFileName);
		}

	}

	//----------------------------------------------------------------------------------------
	// アニメーション画像を読み込む関数
	// 引数：アニメーションの種類を表すenum class, ANIM_CSV_OBJ型
	std::shared_ptr<std::vector<int>> ito::ResourceManager::loadAnimGraph(std::string animFileName) {

		// file_pathに対応する画像アニメーションハンドルを探す
		auto it = animation_map_.find(animFileName);


		if (it != animation_map_.end()) {
			return animation_map_[animFileName];
		}

		for (int y = 0; y < anim_csv_.size(); ++y) {

			if (anim_csv_[y][static_cast<int>(ANIM_CSV_ITEM::FILE_NAME)].getString() == animFileName) {

				// 画像アニメーションの読み込み
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

				// 画像アニメーションをanimation_map_にパスと紐づけて保存
				animation_map_.insert(std::make_pair(animFileName, anim_hdls));

				// アニメーションハンドルを返す
				return anim_hdls;
			}
		}

	}

	//----------------------------------------------------------------------------------------
	// 画像を削除する関数
	// 引数：削除するアニメーションのファイル名
	void ResourceManager::deleteAnimGraph(std::string animFileName) {

		// ANIM_CSV_OBJに対応する画像ハンドルを探す
		auto it = animation_map_.find(animFileName);

		if (it != animation_map_.end()) {

			std::shared_ptr<std::vector<int>> anim_hdls = it->second;

			for (int anim_hdl : (*anim_hdls)) {
				DeleteGraph(anim_hdl);
			}


			// ANIM_CSV_OBJに対応するパスを削除する
			if (it != animation_map_.end()) {
				animation_map_.erase(animFileName);
			}

		}

	}

	//----------------------------------------------------------------------------------------
	// サウンドを読み込む関数
	// 引数：サウンドのファイル名
	int ResourceManager::loadSoundMem_(std::string soundFileName) {

		// SOUND_KINDSに対応するサウンドハンドルを探す
		auto it = sounds_map_.find(soundFileName);

		// 既にロードしてある場合、そのサウンドハンドルを返す
		if (it != sounds_map_.end()) {
			return sounds_map_[soundFileName];
		}

		// csvに保存されたファイル名から同じものを探す
		for (int y = 1; y < sounds_csv_.size(); ++y) {
			if (sounds_csv_[y][static_cast<int>(SOUND_CSV_ITEM::FILE_NAME)] == soundFileName) {

				// サウンドの読み込み
				int sound_hdl = LoadGraph(sounds_csv_[y][static_cast<int>(SOUND_CSV_ITEM::PATH)].c_str(), true);

				// sounds_map_に読み込んだ画像をパスと紐づけて保存
				sounds_map_.insert(std::make_pair(soundFileName, sound_hdl));

				// サウンドハンドルを返す
				return sound_hdl;
			}
		}
		// 読み込みできなかった場合は-1を返す
		return -1;

	}

	//----------------------------------------------------------------------------------------
	// サウンドを削除する関数
	// 引数：削除するサウンドのファイル名
	void ResourceManager::deleteSoundMem_(std::string soundFileName) {

		// SOUND_KINDSに対応する画像ハンドルを探す
		auto it = sounds_map_.find(soundFileName);


		// サウンドハンドルを解放
		DeleteSoundMem(it->second);

		// SOUND_KINDSに対応するパスを削除する
		if (it != sounds_map_.end()) {
			sounds_map_.erase(soundFileName);
		}

	}


	void ResourceManager::Destroy() {

		delete GetInstance_();
	}

}