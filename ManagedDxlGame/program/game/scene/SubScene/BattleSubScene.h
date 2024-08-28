#pragma once
#include "../../base/SubSceneBase.h"

// 前方宣言
class ObjectBlockBase;
class TransformCamera;
class BattleCharacterBase;
class BattlePlayer;
class BattleEnemy;
class SubSceneManager;
class UiHP;

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


	// サブシーン切り替えの際に呼び出す関数
	void ChangeSubScene() override;

private :

	// ステージを生成する関数
	void CreateStage();

	// ステージのオブジェクトをソートする関数
	// 最初に一回実行する
	void SortObject(std::shared_ptr<dxe::Camera> camera);

	// キャラクターをソートする関数
	// 毎フレーム実行
	void SortCharacter(std::shared_ptr<dxe::Camera> camera);

	// キャラクターの座標を補正する関数
	// ステージの範囲外に出た場合範囲内に補正する
	void PosCorrection();

	// 攻撃判定が当たっているかどうか確認する関数
	void CheckHitAttack();

	// バトルシーンが終了しているかどうかを確認する関数
	void CheckBattleEnd();


	// バトル中かどうかを判別するためのフラグ
	bool isBattling_ = true;

	//-------------------------------------------------------
	// キャラクター

	// プレイヤーのキャラクター
	std::shared_ptr<BattlePlayer> player_ = nullptr;
	// 敵のキャラクター
	std::shared_ptr<BattleEnemy> enemy_ = nullptr;

	// 描画するキャラクターのリスト
	// 描画前にこれをソートして順番に描画する
	std::shared_ptr< std::list< std::shared_ptr<BattleCharacterBase>> > battleCharaList_;


	//-------------------------------------------------------
	// カメラ

	// バトルシーン用のカメラ(ThirdPersonCamera)
	std::shared_ptr< dxe::Camera > TPCamera_ = nullptr;

	// カメラのターゲットの座標
	tnl::Vector3 cameraTargetPos_ = { 0, 0, 0 };


	//-------------------------------------------------------
	// ステージ関係

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


	//-----------------------------------------------------------------------
	// 表示する画像関係


	// UI関係を生成する関数
	void CreateBattleUI();

	// バトルのUIを表示するための関数
	// draw関数内で呼び出す
	void DisplayBattleUI();

	// プレイヤーのHPを表示するUI
	std::shared_ptr< UiHP > playerHpUi_;
	// プレイヤーのHPの表示位置
	tnl::Vector3 playerHpPos_ = {180, 60, 0};

	// 敵キャラクターのHPを表示するUI
	std::shared_ptr< UiHP > enemyHpUi_;
	// 敵キャラクターのHPの表示位置
	tnl::Vector3 enemyHpPos_ = { 600, 550, 0 };

	// メインで表示する画像の位置
	tnl::Vector3 mainGpcPos_ = { DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0 };

	// 描画を行う画像のリスト
	std::list< std::shared_ptr<ito::Graphic> > gpcList_;

	// バトルシーンでの操作説明画像関連
	int battleControlExpGpc_ = 0;
	tnl::Vector3 battleControlExpPos_ = { 300, 650, 0 };
	float battleControlExpSize_ = 2.5f;


	//-------------------------------------------------------
	// サウンド関係

	// BGMのハンドル
	int battleBgmHdl_ = 0;

	// BGMがかかっているかのフラグ
	bool isPlayingBGM_ = false;



	//-------------------------------------------------------
	// シーン切り替え関係

	// シーンを切り替えるまでの時間をカウントする用
	float sceneChangeCount_ = 0;
	// シーンを切り替える時間
	float sceneChangeTime_ = 3.0f;

	//-----------------------------------------------------------------------
	// シーケンス関係

	// 動作を管理する用のシーケンス
	tnl::Sequence<BattleSubScene> seq_ = tnl::Sequence<BattleSubScene>(this, &BattleSubScene::seqBattle);

	// 戦闘を行えるシーケンス
	bool seqBattle(const float delta_time);

	// バトルシーンを終了させるシーケンス
	bool seqBattleEnd(const float delta_time);
};