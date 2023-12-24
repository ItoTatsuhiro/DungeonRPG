#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <string>
#include <unordered_map>
#include "../base/ObjectBlockBase.h"

// ダンジョンのマップに関するクラス
// ステージと紐づくステージ名はstring型で、csvより読み取る予定
class Stage {
public :
	// マップクラスのコンストラクタ
	Stage(std::string startStage, std::string csvPath);
	// マップクラスのデストラクタ
	~Stage();

	void update(float delta_time);

	void draw(std::shared_ptr<dxe::Camera> camera);


	// 新たにマップを読み込む関数
	void LoadMap(std::string name, std::string csvPath);

	// ステージを切り替える際に呼び出す関数
	void StageChange(std::string nextStage);

private :

	// マップを生成する際の基準の座標
	tnl::Vector3 basePos_ = { 0, 0, 0 };
	// マップを構成するオブジェクトの基本の大きさ
	int blockSize_ = 50;

	// 現在のステージを実行可能かどうかのフラグ
	// ステージを切り替えた際に確認して切り替える
	bool existNowStage_ = true;

	//-------------------------------------------------------------------------------------
	// Stageの行うシーケンス処理関係
	// 
	// 現在のシーケンス
	tnl::Sequence<Stage> seq_ = tnl::Sequence<Stage>(this, &Stage::seqStageChange);

	// 現在のステージを実行可能か確認するシーケンス
	// ステージを切り替えた際に必ずここを通過させる
	// 中でexistNowStage_を切り替える
	bool seqCheckNowStage(const float delta_time);

	// 現在のステージのアップデートを行うシーケンス
	// 通常時はこのシーケンスを実行
	// 条件に応じて各シーケンスに移行
	bool seqNowStageUpdate(const float delta_time);

	// ステージを次のステージに切り替えるシーケンス
	// ステージのオブジェクトを作成してあればシーンを切り替え、
	// 作成していなければステージ情報の配列からステージのオブジェクトを作成する
	// 終了するとseqCheckNowStageに移る
	// 引数：nextStage...次に切り替えるステージ
	bool seqStageChange(const float delta_time);



	// ステージの配列を保存するunordered_map
	// 引数：string...名前, std::vector～<int>>>...マップの配列
	std::unordered_map<std::string, std::vector<std::vector<int>>> stageArrayMap_;

	// ステージを構成するオブジェクトを保存するunordered_map
	// 引数：string...名前, std::vector～<ObjectBlockBase>>>...マップのオブジェクト
	std::unordered_map<std::string, std::vector<std::vector< std::shared_ptr<ObjectBlockBase> >>> stageObjMap_;

	// 現在のステージ名を表すstring
	// ステージを読み込む際、切り替える際などに使用する
	// ステージ名を表すenum classに変更する可能性あり
	std::string nowStage_ = "";


	std::string nowSeq_ = "";

};