#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// 前方宣言
class SubSceneBase;
class DungeonSubScene;
class BattleSubScene;
class Enemy;


class SubSceneManager final{

private :

	SubSceneManager();

public :

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

	// インスタンスを削除する関数
	void Destroy();

private:
	// 実行するサブシーン
	// この変数に入れているサブシーンを実行する
	std::shared_ptr<SubSceneBase> nowSubScene_ = nullptr;

	// バトル中の敵キャラクター
	// バトルシーンに移動したときセットし、バトルシーンからかえって来た際に該当のキャラクターを消す
	std::shared_ptr<Enemy> battlingEnemy_ = nullptr;

	// ダンジョンのサブシーン
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;

	// バトルのサブシーン
	std::shared_ptr<BattleSubScene> battleSubScene_ = nullptr;

};