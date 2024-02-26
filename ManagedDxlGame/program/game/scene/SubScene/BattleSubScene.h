#pragma once
#include "../../base/SubSceneBase.h"

// 前方宣言
class ObjectBlockBase;
class TransformCamera;
class BattlePlayer;


// バトルシーンのサブクラス
// ScenePlay内で必要に応じてupdate, drawする
class BattleSubScene final : public SubSceneBase {
public :
	// コンストラクタ
	BattleSubScene();
	// デストラクタ
	~BattleSubScene();
	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw() override;



private :


	// ステージを生成する関数
	void CreateStage();

	// ステージのオブジェクトをソートする関数
	void SortObject(std::shared_ptr<dxe::Camera> camera);

	// キャラクターの座標を補正する関数
	// ステージの範囲外に出た場合範囲内に補正する
	void posCorrection();


	std::shared_ptr<BattlePlayer> player_ = nullptr;



	// バトルシーン用のカメラ(ThirdPersonCamera)
	std::shared_ptr< dxe::Camera > TPCamera_ = nullptr;


	// カメラのターゲットの座標
	tnl::Vector3 cameraTargetPos_ = { 0, 0, 0 };

	// バトルシーン用のステージの配列
	std::vector<std::vector<int>> battleStageArray_;
	// ステージに配置されているオブジェクトの配列
	std::vector<std::vector<std::shared_ptr<ObjectBlockBase>>> battleStageObjArray_;
	// バトルシーンで描画するステージのオブジェクトのリスト
	std::list< std::shared_ptr< ObjectBlockBase >> battleStageObjList_;

	// ステージを生成する際の基準となる座標
	tnl::Vector3 basePos_ = { 0, 0, 0 };

	// 1マスの縦横の大きさ
	float gridSize_ = 50;

	// プレイヤーの開始位置
	// コンストラクタで初期化
	// x...ステージの1/3の位置
	// z...ステージの半分の位置
	tnl::Vector3 startPosPlayer_;
	// 敵キャラクターの開始位置
	// コンストラクタで初期化
	// x...ステージの2/3の位置
	// z...ステージの半分の位置
	tnl::Vector3 startPosEnemy_;

	// ステージの床の高さ(床のオブジェクトの座標)
	// 下のstageSize～変数のyに入れる用
	float floorHeight_ = 0;

	// ステージの大きさ(最少値)
	// オブジェクトの配列の[0][0]のオブジェクトの座標とする
	// yは床のオブジェクトの座標
	tnl::Vector3 stageSizeMin_;
	// ステージの大きさ(最大値)
	// オブジェクトの配列の[max][max]のオブジェクトの座標とする
	// yは床のオブジェクトの座標
	tnl::Vector3 stageSizeMax_;

	// 動作を管理する用のシーケンス
	tnl::Sequence<BattleSubScene> seq_ = tnl::Sequence<BattleSubScene>(this, &BattleSubScene::seqBattle);

	// 戦闘を行えるシーケンス
	bool seqBattle(const float delta_time);

};