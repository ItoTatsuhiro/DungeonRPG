#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// 前方宣言
class SubSceneBase;
class DungeonSubScene;
class BattleSubScene;
class Enemy;


class SubSceneManager final{
public :


	SubSceneManager();

	// この関数でインスタンスを取得
	// インスタンスを取得する際は引数なしでOK
	// 最初にインスタンスを生成する際は引数を入れる
	static std::shared_ptr<SubSceneManager> GetInstance();

	~SubSceneManager();

	// 更新用の関数
	// 現在のサブシーンをこの関数で更新する
	void update(float delta_time);
	// 描画用の関数
	// 現在のサブシーンをこの関数で描画する
	void draw();

	// シーンプレイのサブシーン
	enum class ScenePlaySubScene {
		DUNGEON,
		BATTLE
	};


	// サブシーンを切り替える関数
	// battlingEnemy...バトルする敵キャラクター
	// バトルシーンに移行するときは入れる
	void ChangeSubScene(ScenePlaySubScene nextSubScene, std::shared_ptr<Enemy> battlingEnemy = nullptr);


	// バトルシーンを新たに作成する関数
	// ダンジョンから遷移する際はサブシーン切り替え前にこれでバトルシーンを作成する
	void ChangeBattleScene( std::shared_ptr<Enemy> battlingEnemy);

	// 初期設定を行う関数
	void SetUp();

	// インスタンスを削除する関数
	void Destroy();

	// サブシーンを削除する関数
	void DeleteSubScene();

private:

	// 実行するサブシーン
	// この変数に入れているサブシーンを実行する
	std::weak_ptr<SubSceneBase> nowSubScene_;


	// 次に実行するサブシーン
	// サブシーン切り替えの際に使用
	ScenePlaySubScene nextSubScene_;



	// バトル中の敵キャラクター
	// バトルシーンに移動したときセットし、バトルシーンからかえって来た際に該当のキャラクターを消す
	std::shared_ptr<Enemy> battlingEnemy_ = nullptr;

	// ダンジョンのサブシーン
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;

	// バトルのサブシーン
	std::shared_ptr<BattleSubScene> battleSubScene_ = nullptr;


	// サブシーン切り替えの時間
	float transTime_ = 1.5f;
	// サブシーン切り替え時に表示する画像
	// 基本的に黒でフェードイン、フェードアウトさせる
	int transGpc_ = 0;


	bool debugMode_ = false;


	std::shared_ptr<dxe::ScreenEffect> screenEffect_ = nullptr;

	// シーケンス
	tnl::Sequence<SubSceneManager> seq_ = tnl::Sequence<SubSceneManager>(this, &SubSceneManager::seqSubSceneUpdate);

	// サブシーンをupdateするシーケンス
	bool seqSubSceneUpdate(const float delta_time);
	// サブシーンを切り替える際のシーケンス
	bool seqSubSceneChange(const float delta_time);
	// サブシーンを開始するシーケンス
	bool seqSubSceneStart(const float delta_time);
};