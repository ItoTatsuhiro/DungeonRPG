#include "BattleEnemy.h"
#include "action/BattleActionBase.h"

// コンストラクタ
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string filePath...テクスチャのファイルのパス
// 移動前の座標は開始位置で初期化
// SpriteObjectBaseの引数も入れる
BattleEnemy::BattleEnemy(tnl::Vector3 startPos, float objSize, std::string fileName)
	: BattleCharacterBase(startPos, objSize, fileName) {


	// SpriteObjectBaseクラスの関数
	// テクスチャを表示する用のplaneの配列を作成する
	CreateSpriteObjArray(fileName);

	// 表示するメッシュの初期設定
	displayObj_ = tnl::Vector2i(1, textureCutNum_.y - 2);


	return;

}

// デストラクタ
// 現状処理無し
BattleEnemy::~BattleEnemy() {

	return;
}

// 更新用の関数
void BattleEnemy::update(float delta_time) {

	BattleCharacterBase::update(delta_time);

	seq_.update(delta_time);

}

// 
void BattleEnemy::draw(std::shared_ptr<dxe::Camera> camera) {

	BattleCharacterBase::draw(camera);


}


// 行動を決定するシーケンス
// 所持している行動のリストから行動をランダムに選択し、
// 
bool BattleEnemy::seqActDecade(const float delta_time) {

	// 行動の数をカウント
	actionNum_ = actionList_.size();

	// 実行する行動の番号を決定
	int selectActionNum = rand() % actionNum_;



	// 以下で実行する行動を取得
	auto it = actionList_.begin();
	// 先程決定した行動の番号までイテレータを送る
	for (int i = 0; i < selectActionNum; ++i) {
		++it;
	}

	// 実行する行動の変数に選択した行動を入れる
	nowAction_ = (*it);

	// 行動を実行前の設定に更新する
	nowAction_->setUpAction();

	// 実行するシーケンスを行動のシーケンスに変更
	seq_.change(&BattleEnemy::seqAct);

	return true;
}


// 行動を実行するシーケンス
bool BattleEnemy::seqAct(const float delta_time) {

	// 以下の条件の時行動をやめて行動の選択に戻る
	// 1.行動の変数の中身が無いとき
	// 2.行動が終了している時
	if (nowAction_ == nullptr || nowAction_->getIsFinished()) {

		seq_.change(&BattleEnemy::seqActDecade);
		return true;
	}

	// 現在の行動を実行
	nowAction_->update(delta_time);

}

