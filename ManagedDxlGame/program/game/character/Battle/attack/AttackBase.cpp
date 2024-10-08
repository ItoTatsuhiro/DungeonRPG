#include "AttackBase.h"
#include "../../../manager/ObjectManager.h"


// **************************************************************************
// おそらく現状で攻撃を発生させる処理ができているので、
// 攻撃の発生させる位置等の設定を行うこと！！！
// **************************************************************************



// コンストラクタ
// 引数：座標、大きさ、ファイル名、正面の方向(LEFTかRIGHT), ダメージ
// Object3Dのメッシュを当たり判定用のメッシュとして作成する
AttackBase::AttackBase(tnl::Vector3 pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage)
	: SpriteObjectBase(pos, size, fileName), charaType_(charaType), damage_(damage), isLoop_(false), isEnd_(false), isHit_(false), checkHitStage_(false)
{

	CreateSpriteObjArray(fileName);

	// 当たり判定を作成
	hitBox_ = ObjectManager::GetInstance()->createCube(size, fileName);
	hitBox_->get_mesh_()->pos_ = pos;


	displayObj_.y = (frontDir_ == Enum::eDir4::LEFT) ? 1 : 0;

}

// デストラクタ
AttackBase::~AttackBase() {

	// 行動の終了を伝える必要がある時は以下の処理を行う

	auto creatorAction = creatorAction_.lock();

	if (creatorAction) {

		// 行動の終了フラグをtrueにする
		creatorAction->setIsFinished(true);

	}


}


// 更新用の関数
void AttackBase::update(float delta_time) {

	// アクティブでないとき処理しない
	if (!isActive_) {
		return;
	}

	// 基底クラスの更新
	SpriteObjectBase::update(delta_time);

	if (animChangeCount_ > animChangeTime_ / 3) {
		// 次の画像のメッシュに切り替え
		++displayObj_.x;
		// 表示時間を0にリセットする
		animChangeCount_ = 0;



		// 以下の条件の時に状態を非アクティブ状態にする
		// ・攻撃アニメーションを再生し終わったとき
		// ・攻撃がヒットしたとき
		if ((displayObj_.x >= textureCutNum_.x && !isLoop_)) {

			// 状態を無効にする
			isActive_ = false;

		}



	}
	else {
		animChangeCount_ += delta_time;
	}




}

// 描画用の関数
void AttackBase::draw(const std::shared_ptr<dxe::Camera>& camera) {

	// アクティブでないとき処理しない
	if (!isActive_) {
		return;
	}

	SpriteObjectBase::draw(camera);


}


// 攻撃が衝突した際に実行する関数
// ******************************************************
// 継承先のクラスではオーバーライドする関数を必ず作成すること！
// ******************************************************
void AttackBase::OnHit() {

	// サウンドが設定されている時サウンドを再生
	if (hitSoundHdl_) {
		PlaySoundMem(hitSoundHdl_, DX_PLAYTYPE_BACK);
	}

	// ヒット時のエフェクトを出す処理を作成する
	// エフェクトのクラスを作成したら追加する

}
