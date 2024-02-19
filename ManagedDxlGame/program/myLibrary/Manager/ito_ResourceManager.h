#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "../library/tnl_csv.h"
#include "../../dxlib_ext/dxlib_ext.h"

namespace ito {

	// 画像、アニメーション、サウンド等のリソースを管理する用のクラス
	// それぞれを読み込むための関数あり
	// コンストラクタ等でそれぞれの情報を保管するcsvを読み込む必要あり

	class ResourceManager {
	private:

		// コンストラクタ
		// リソースの情報を書き込んだcsvを読み込む
		// GetInstance関数からのみインスタンス化するためprivate
		ResourceManager();

	public:

		// GraphicManagerをインスタンス化する関数
		static ResourceManager* GetInstance();

		// デストラクタ
		~ResourceManager();


	private:
		//--------------------------------------------------------------------------------------------------------------------------
		// 画像関係

		// 画像のパスのcsvの内容を読み込む用のvector
		std::vector<std::vector<std::string>> gpcCsv_;
		// 読み込んだ画像を保存する用のmap
		std::unordered_map < std::string, int> gpcMap_;
		// 画像のcsvの項目(x方向)
		enum class GPC_CSV_ITEM {
			FILE_NAME = 1,			// 画像のファイル名
			PATH,					// 画像のパス
			MAX						// 項目の数+1
		};

		//--------------------------------------------------------------------------------------------------------------------------
		// アニメーション関係

		// アニメーションのcsvを読み込む用のvector
		std::vector<std::vector<tnl::CsvCell>> animCsv_;
		// 読み込んだアニメーション画像を保存する用のmap
		std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animMap_;
		// アニメーションのcsvの項目(x方向)
		enum class ANIM_CSV_ITEM {
			FILE_NAME = 1,			// アニメーションのファイル名
			PATH ,					// 画像のパス
			TOTAL_FRAMES,			// 総分割数
			HOLIZONTAL_FRAMES,		// 横方向の分割数
			VERTICAL_FRAMES,		// 縦方向の分割数
			WIDTH,					// 一つ当たりの横幅
			HEIGHT,					// 一つ当たりの高さ
			MAX						// 項目の数+1
		};


		//--------------------------------------------------------------------------------------------------------------------------
		// サウンド関係

		// サウンドのパスのcsvの内容を読み込む用のvector
		std::vector<std::vector<std::string>> soundsCsv_;
		// 読み込んだパスを保存する用のmap
		std::unordered_map < std::string, int> soundsMap_;
		// サウンドのcsvの項目(x方向)
		enum class SOUND_CSV_ITEM {
			FILE_NAME = 1,			// サウンドのファイル名
			PATH,					// サウンドのパス
			MAX						// 項目の数+1
		};


		//--------------------------------------------------------------------------------------------------------------------------
		// テクスチャ関係

		// テクスチャのパスのcsvの内容を読み込む用のvector
		std::vector<std::vector<tnl::CsvCell>> textureCsv_;
		// 読み込んだパスを保存する用のmap
		std::unordered_map < std::string, std::shared_ptr<dxe::Texture> > textureMap_;
		// テクスチャのcsvの項目(x方向)
		enum class TEXTURE_CSV_ITEM {
			FILE_NAME = 1,			// テクスチャ用画像のファイル名
			PATH,					// テクスチャのパス
			CUT_NUM_OF_U,			// U方向の分割数
			CUT_NUM_OF_V,			// V方向の分割数
			MAX						// 項目の数+1
		};




	public:

		//--------------------------------------------------------------------------------------------------------------------------
		// 画像関係の関数

		// 画像を読み込む関数
		// 引数：画像ファイルの名前(std::string型)
		int loadGraph(std::string graphFileName);
		// 画像を削除する関数
		// 引数：画像の種類を表すenum class, GRAPHIC_TYPE型
		void deleteGraph(std::string graphFileName);


		//--------------------------------------------------------------------------------------------------------------------------
		// アニメーション関係の関数

		// アニメーション画像を読み込む関数
		// 引数：アニメーションのファイル名
		std::shared_ptr<std::vector<int>> loadAnimGraph(std::string animFileName);
		// アニメーションを削除する関数
		// 引数：アニメーションのファイル名
		void deleteAnimGraph(std::string animFileName);


		//--------------------------------------------------------------------------------------------------------------------------
		// サウンド関係の関数

		// サウンドを読み込む関数
		// 引数：サウンドのファイル名(std::string型)
		int loadSoundMem(std::string soundFileName);
		// サウンドを削除する関数
		// 引数：サウンドのファイル名(std::string型)
		void deleteSoundMem(std::string soundFileName);






		//--------------------------------------------------------------------------------------------------------------------------
		// テクスチャ関係の関数

		// テクスチャを読み込む関数
		// 引数：テクスチャのファイル名(std::string型)
		std::shared_ptr<dxe::Texture> loadTexture(std::string textureFileName);
		// 読み込んだテクスチャを削除する関数
		// 引数：テクスチャの画像ファイル名(std::string型)
		void deleteTexture(std::string textureFileName);
		// 読み込んだテクスチャの分割数を取得する関数
		// 引数：テクスチャの画像ファイル名(std::string型)
		tnl::Vector2i getTextureCutNum(std::string textureFileName);

		// リソースマネージャー自体をdestroyするための関数
		static void Destroy();

	};

}