#pragma once
#include <vector>
#include <string>


// ゲームマネージャークラス
// ゲームの実行部分を管理するためのクラス
// 引数にゲームを開始する際の最初のシーンを入れる
// 使用方法(参考例)

/*
//------------------------------------------------------------------------------------------------------------
void gameStart() {

	srand(time(0));

	// ゲームマネージャーのインスタンス化
	GameManager* gmr = GameManager::GetInstance_(new SceneTitle());
}

//------------------------------------------------------------------------------------------------------------
void gameMain(float delta_time) {

	// 現在のシーンでのupdate関数を実行
	GameManager::GetInstance_()->update(delta_time);
}
*/

namespace ito {

	class SceneBase;

	class GameManager {
	private :

		// コンストラクタ
		// 引数：ゲームを開始する際に初めに実行するシーン
		GameManager(SceneBase* startScene);

	public:

		// ゲームマネージャーをインスタンス化する際に使用する関数。
		// 引数：ゲームを開始する際に初めに実行するシーン
		static GameManager* GetInstance_(SceneBase* startScene = nullptr);

		~GameManager();

		// シーン切り替え用関数
		// 引数：遷移する先のシーン
		void changeScene(SceneBase* nextScene);

		void update(float delta_time);

		// 現在のシーンを取得する関数
		SceneBase* get_nowScene() const { return nowScene_; }

		//--------------------------------------------------------------------------------------------------------------------------
		// csvファイル読み込みに関する内容
		// 現在仕様検討中のため使用不可

		// std::vector<std::vector<std::string>> csvAddress;		// 読み込むcsvファイルのアドレスを格納する用

		// void Load_CsvAddress();			// 読み込むcsvファイルのアドレスを格納したcsvファイルを読み込む関数


		//// csvファイルのアドレス
		//enum class CSV_NAME {	
		//	GRAPH_ADDRESS,		// 画像の保存先のアドレス用
		//	CHARACTER_BASE,		// キャラクターベース用
		//	PLAYER_DATA,		// プレイヤーに関する値を入れる用
		//	STAGE_DATA,			// ステージに関する値を入れる用
		//	CSV_MAX				// CSVファイルの数

		//}csv_name;

		//CSV_NAME csv_name = GameManager::CSV_NAME::GRAPH_ADDRESS;

		//--------------------------------------------------------------------------------------------------------------------------


	private:

		// 現在実行中のシーンを入れる変数
		SceneBase* nowScene_ = nullptr;
		// 次に遷移するシーンを入れる変数
		SceneBase* nextScene_ = nullptr;

	};

}
