#pragma once

#include "../other/BattleCharacterBase.h"

// 前方宣言
// 攻撃のクラス
class BattleActionBase;

// バトルシーンでの敵キャラクターのクラス
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...貼り付けるテクスチャのパス
class BattleEnemy : public BattleCharacterBase {
public :
	// コンストラクタ
	// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...貼り付けるテクスチャのパス
	// charaList...バトルシーンに存在しているキャラクターのリスト
	// 移動前の座標は開始位置で初期化
	// SpriteObjectBaseの引数も入れる
	BattleEnemy(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList);

	// デストラクタ
	~BattleEnemy();

	// 更新用の関数
	// 継承先ではこの関数をupdate内で呼び出すこと！
	virtual void update(const float delta_time) override;
	// 描画用の関数
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) override;




protected :

	

	// 移動する目標地点の座標
	tnl::Vector3 movePos_;


	
	
	// キャラクターのリスト
	// 生成した際にコンストラクタでバトルシーンから取得してくる
	std::weak_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList_;

	// 行動のターゲットのキャラクター
	// charaList_から対象を選択して中に入れる
	std::weak_ptr< BattleCharacterBase > targetCharacter_;



	// 行動の種類のリスト
	// 敵キャラクターが行う行動をこのリストに入れておくこと！
	std::list< std::shared_ptr< BattleActionBase > > actionList_;

	// 現在実行中の行動
	// 行動を選択後にこの変数に選択した行動を入れる
	std::shared_ptr< BattleActionBase > nowAction_ = nullptr;



	// シーケンス処理用の変数
	tnl::Sequence<BattleEnemy> seq_ = tnl::Sequence<BattleEnemy>(this, &BattleEnemy::seqActDecade);

	// 行動を決定するシーケンス
	bool seqActDecade(const float delta_time);

	// 行動を実行するシーケンス
	bool seqAct(const float delta_time);



};