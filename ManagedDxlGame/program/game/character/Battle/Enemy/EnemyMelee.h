#pragma once
#include "../BattleEnemy.h"




// 逃げる敵キャラクターのクラス
// 
// ※以下注意点
// 自身のインスタンスをsharedポインタで取得するため、
// 使用する際は必ずstd::shared_ptr型で作成すること！
class BattleEnemyMelee final : public BattleEnemy {
public:

	// コンストラクタ
	// 引数はBattleEnemyの初期化用
	// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...貼り付けるテクスチャのファイル名
	// 移動前の座標は開始位置で初期化
	// SpriteObjectBaseの引数も入れる
	BattleEnemyMelee(tnl::Vector3 startPos, float objSize, std::string fileName);

	// デストラクタ
	~BattleEnemyMelee();

	// クラスの生成用の関数
	static std::shared_ptr<BattleEnemyMelee> Create(tnl::Vector3 startPos, float objSize, std::string fileName);

	// 更新用の関数
	void update(const float delta_time);

	// 描画用の関数
	// 引数：描画するカメラ
	void draw(std::shared_ptr< dxe::Camera > camera);


};