#include "DXLib.h"
#include "ito_ResourceManager.h"


namespace ito {

	// コンストラクタ
	// リソースの情報を記入したcsvファイルを読み込む
	ito::ResourceManager::ResourceManager() {

		// リソースのcsvの読み込み
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
	// 画像を読み込む関数
	// 引数：読み込む画像のファイル名
	int ito::ResourceManager::loadGraph(std::string graphFileName) {

		// file_pathに対応する画像ハンドルを探す
		auto it = gpcMap_.find(graphFileName);

		// 既にロードしてある場合、その画像ハンドルを返す
		if (it != gpcMap_.end()) {
			return gpcMap_[graphFileName];
		}

		// 画像の読み込み
		// int gpc_hdl = LoadGraph(graphics_csv_[static_cast<int>(gpc_type)][2].c_str(), true);

		for (int y = 1; y < gpcCsv_.size(); ++y) {
			if (gpcCsv_[y][static_cast<int>(GPC_CSV_ITEM::FILE_NAME)] == graphFileName) {
				int gpc_hdl = LoadGraph(gpcCsv_[y][static_cast<int>(GPC_CSV_ITEM::PATH)].c_str(), true);

				// graphics_map_に読み込んだ画像をパスと紐づけて保存
				gpcMap_.insert(std::make_pair(graphFileName, gpc_hdl));

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
	void ito::ResourceManager::deleteGraph(std::string graphFileName) {

		// file_pathに対応する画像ハンドルを探す
		auto it = gpcMap_.find(graphFileName);

		// 画像ハンドルを解放
		DeleteGraph(it->second);

		// file_pathの画像パスを削除する
		if (it != gpcMap_.end()) {
			gpcMap_.erase(graphFileName);
		}

	}

	//----------------------------------------------------------------------------------------
	// アニメーション画像を読み込む関数
	// 引数：アニメーションの種類を表すenum class, ANIM_CSV_OBJ型
	std::shared_ptr<std::vector<int>> ito::ResourceManager::loadAnimGraph(std::string animFileName) {

		// file_pathに対応する画像アニメーションハンドルを探す
		auto it = animMap_.find(animFileName);


		if (it != animMap_.end()) {
			return animMap_[animFileName];
		}

		for (int y = 0; y < animCsv_.size(); ++y) {

			if (animCsv_[y][static_cast<int>(ANIM_CSV_ITEM::FILE_NAME)].getString() == animFileName) {

				// 画像アニメーションの読み込み
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

				// 画像アニメーションをanimation_map_にパスと紐づけて保存
				animMap_.insert(std::make_pair(animFileName, anim_hdls));

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
		auto it = animMap_.find(animFileName);

		if (it != animMap_.end()) {

			std::shared_ptr<std::vector<int>> anim_hdls = it->second;

			for (int anim_hdl : (*anim_hdls)) {
				DeleteGraph(anim_hdl);
			}


			// ANIM_CSV_OBJに対応するパスを削除する
			if (it != animMap_.end()) {
				animMap_.erase(animFileName);
			}

		}

	}

	//----------------------------------------------------------------------------------------
	// サウンドを読み込む関数
	// 引数：サウンドのファイル名
	int ResourceManager::loadSoundMem(std::string soundFileName) {

		// SOUND_KINDSに対応するサウンドハンドルを探す
		auto it = soundsMap_.find(soundFileName);

		// 既にロードしてある場合、そのサウンドハンドルを返す
		if (it != soundsMap_.end()) {
			return soundsMap_[soundFileName];
		}

		// csvに保存されたファイル名から同じものを探す
		for (int y = 0; y < soundsCsv_.size(); ++y) {
			if (soundsCsv_[y][static_cast<int>(SOUND_CSV_ITEM::FILE_NAME)] == soundFileName) {

				// サウンドの読み込み
				int sound_hdl = LoadSoundMem(soundsCsv_[y][static_cast<int>(SOUND_CSV_ITEM::PATH)].c_str(), true);

				// sounds_map_に読み込んだ画像をパスと紐づけて保存
				soundsMap_.insert(std::make_pair(soundFileName, sound_hdl));

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
	void ResourceManager::deleteSoundMem(std::string soundFileName) {

		// SOUND_KINDSに対応する画像ハンドルを探す
		auto it = soundsMap_.find(soundFileName);


		// サウンドハンドルを解放
		DeleteSoundMem(it->second);

		// SOUND_KINDSに対応するパスを削除する
		if (it != soundsMap_.end()) {
			soundsMap_.erase(soundFileName);
		}

	}


	//----------------------------------------------------------------------------------------
	// テクスチャを読み込む関数
	// 引数：読み込むテクスチャ用画像のファイル名
	std::shared_ptr<dxe::Texture> ito::ResourceManager::loadTexture(std::string textureFileName) {

		// file_pathに対応する画像ハンドルを探す
		auto it = textureMap_.find(textureFileName);

		// 既にロードしてある場合、その画像ハンドルを返す
		if (it != textureMap_.end()) {
			return textureMap_[textureFileName];
		}



		for (int y = 1; y < textureCsv_.size(); ++y) {
			if (textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::FILE_NAME)].getString().c_str() == textureFileName) {
				std::shared_ptr<dxe::Texture> textureHdl = dxe::Texture::CreateFromFile(textureCsv_[y][static_cast<int>(GPC_CSV_ITEM::PATH)].getString().c_str());

				// graphics_map_に読み込んだ画像をパスと紐づけて保存
				textureMap_.insert(std::make_pair(textureFileName, textureHdl));

				// 画像ハンドルを返す
				return textureHdl;
			}
		}
		// 読み込みできなかった場合はnullptrを返す
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	// テクスチャを削除する関数
	// 引数：削除する画像のファイル名
	void ito::ResourceManager::deleteTexture(std::string textureFileName) {

		// file_pathに対応する画像ハンドルを探す
		auto it = textureMap_.find(textureFileName);

		// テクスチャハンドルを解放
		it->second = nullptr;

		// file_pathの画像パスを削除する
		if (it != textureMap_.end()) {
			textureMap_.erase(textureFileName);
		}

	}

	//----------------------------------------------------------------------------------------
	// 読み込んだテクスチャの分割数を取得する関数
	// 引数：テクスチャの画像ファイル名(std::string型)
	tnl::Vector2i ito::ResourceManager::getTextureCutNum(std::string textureFileName) {

		for (int y = 1; y < textureCsv_.size(); ++y) {
			if (textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::FILE_NAME)].getString().c_str() == textureFileName) {
				
				tnl::Vector2i textureCutNum;

				textureCutNum = { textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::CUT_NUM_OF_U)].getInt(),
									textureCsv_[y][static_cast<int>(TEXTURE_CSV_ITEM::CUT_NUM_OF_V)].getInt() };

				// 画像ハンドルを返す
				return textureCutNum;
			}
		}

	}


	void ResourceManager::Destroy() {

		delete GetInstance();
	}

}