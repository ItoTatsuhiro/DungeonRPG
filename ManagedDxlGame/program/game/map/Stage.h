#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <string>
#include <unordered_map>
#include "../base/ObjectBlockBase.h"



class Player;


// ダンジョンのステージを管理するクラス
// ステージと紐づくステージ名はstring型で、csvより読み取る予定
class Stage final{
private :

	// マップクラスのコンストラクタ
	// GetInstance関数を用いてインスタンス化、インスタンスの取得を行う
	Stage(std::string startStage, std::string csvPath, float gridSize);

public :

	// Stageクラスを生成・取得する用の関数
	// 生成するときは引数を全て入力
	// インスタンス取得時は引数なしで呼び出す
	// 引数：startStage...開始時のステージの名前, csvPath...ステージの配列のcsvファイルのパス
	static std::shared_ptr<Stage> GetInstance( std::string startStage = "", std::string csvPath = "", float gridSize = 50.0f);

	// マップクラスのデストラクタ
	~Stage();
	// 毎フレームの処理
	void update(float delta_time);
	// 描画の処理
	void draw(std::shared_ptr<dxe::Camera> camera);

	// プレイヤーをセットする関数
	void setPlayer(std::shared_ptr<Player> player) { player_ = player; }

	// 新たにマップを読み込む関数
	void LoadMap(std::string name, std::string csvPath);

	// ステージを切り替える際に呼び出す関数
	void StageChange(std::string nextStage);


	// 引数の座標のマップの数値を調べる関数
	// 引数：checkGrid...マップの配列から確認する要素番号(x, y)
	int CheckGridPosInt(tnl::Vector2i checkGrid);


	// 引数の座標のオブジェクトを取得する関数
	// 引数：checkGrid...マップの配列から確認する要素番号(x, y)
	std::shared_ptr<ObjectBlockBase> CheckGridPosObj(tnl::Vector2i checkGrid);

	// 描画するオブジェクトを描画するlistに入れる関数
	void drawObjectInList();

	// 描画するオブジェクトのlistをカメラからの距離でソートする関数
	void sortObjectList( std::shared_ptr<dxe::Camera> camera );

private :

	// プレイヤー
	std::shared_ptr<Player> player_ = nullptr;

	// 描画するオブジェクトのリスト
	// 描画前に毎回カメラからの距離でソートする
	std::list<std::shared_ptr<ObjectBlockBase>> drawObjectList_;

	// マップを生成する際の基準の座標
	tnl::Vector3 basePos_ = { 0, 0, 0 };
	// マップを構成するオブジェクトの基本の大きさ
	float gridSize_ = 50;

	// 現在のステージを実行可能かどうかのフラグ
	// ステージを切り替えた際に確認して切り替える
	bool existNowStage_ = true;

	//-------------------------------------------------------------------------------------
	// Stageの行うシーケンス処理関係
	
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

	// 現在のシーケンス
	std::string nowSeq_ = "";

};