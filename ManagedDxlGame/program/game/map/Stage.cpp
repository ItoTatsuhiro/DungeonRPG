#include "Stage.h"
#include "objectBlock/Wall.h"
#include "objectBlock/Floor.h"
#include "../object/Player.h"

// コンストラクタ
// 引数：startStage	...初期ステージ
// 　　　csvPath	...ステージマップの配列を記載したcsvの保管先
//		 gridSize	...1マスの大きさ
// 実行内容
// マップの読み込み、現在のステージをstartStageに切り替え、シーケンスの切り替え
Stage::Stage(std::string startStage, std::string csvPath, float gridSize) : gridSize_(gridSize) {

	LoadMap(startStage, csvPath);

	CreateStage(startStage);

	nowStage_ = startStage;
	seq_.change(&Stage::seqStageChange);

}

// Stageクラスのインスタンスを管理するクラス
// 生成するときは引数を全て入力
// インスタンス取得時は引数なしで呼び出す
// 引数：startStage...初期ステージ
// 　　　csvPath...ステージマップの配列を記載したcsvの保管先
std::shared_ptr<Stage> Stage::GetInstance(std::string startStage, std::string csvPath, float gridSize) {

	// Stageクラスのインスタンス
	static std::shared_ptr<Stage> instance = nullptr;

	// 既に生成されていないときのみ新しく生成
	if (!instance) {
		instance = std::shared_ptr<Stage>( new Stage(startStage, csvPath, gridSize) );
	}

	return instance;
}

// デストラクタ
Stage::~Stage() {

}


void Stage::update(float delta_time) {

	// 現在のステージが実行不可能な時はreturnする
	if (!existNowStage_) return;

	seq_.update(delta_time);
	DrawStringEx(50, 50, -1, "%s", nowStage_.c_str());
	DrawStringEx(100, 100, -1, "%s", nowSeq_.c_str());
}

void Stage::draw(std::shared_ptr<dxe::Camera> camera) {

	// 現在のステージが実行不可能なときはreturnする
	if (!existNowStage_) return;




	sortObjectList(camera);

	auto it = drawObjectList_.begin();

	while (it != drawObjectList_.end()) {

		(*it)->draw(camera);

		++it;
	}


}


//-------------------------------------------------------------------------------------
// ステージマップのcsvを読み込み、保存用のmapに保存する関数
// 引数：name...ステージ名, csvPath...csvファイルの保存先
void Stage::LoadMap(std::string name, std::string csvPath) {

	// 既に同名のマップが保存されている場合ロードしない
	auto it = stageArrayMap_.find(name);
	if (it != stageArrayMap_.end()) return;

	// パスのマップをロードする
	std::vector<std::vector<int>> loadMap;
	loadMap = tnl::LoadCsv<int>(csvPath);

	// マップに登録する
	stageArrayMap_.insert(std::make_pair(name, loadMap));

}

//-------------------------------------------------------------------------------------
// 実行するステージを切り替える関数
// 引数：nextStage...次のステージ
void Stage::StageChange(std::string nextStage) {
	nowStage_ = nextStage;
	seq_.change(&Stage::seqStageChange);
}

//-------------------------------------------------------------------------------------
// 引数の座標のマップの数値を調べる関数
// 引数：checkGrid...マップの配列から確認する要素番号(x, y)
int Stage::CheckGridPosInt(tnl::Vector2i checkGrid) {

	// 配列の範囲外のとき、-1を返す
	if (stageArrayMap_[nowStage_].size() - 1 < checkGrid.y || stageArrayMap_[nowStage_][0].size() - 1 < checkGrid.x
		|| 0 > checkGrid.y || 0 > checkGrid.x) {
		return -1;
	}

	return stageArrayMap_[nowStage_][checkGrid.y][checkGrid.x];
}


//-------------------------------------------------------------------------------------
// 引数の座標のオブジェクトを取得する関数
// 引数：checkGrid...マップの配列から確認する要素番号(x, y)
std::shared_ptr<ObjectBlockBase> Stage::CheckGridPosObj(tnl::Vector2i checkGrid) {

	tnl::DebugTrace(" %d ", stageObjMap_[nowStage_][checkGrid.y][checkGrid.x]);

	return stageObjMap_[nowStage_][checkGrid.y][checkGrid.x];

}


// 引数のマスの座標を取得する関数
// 引数：grid...座標を確認するマスの要素番号
tnl::Vector3 Stage::getGridObjPos(tnl::Vector2i grid) {

	return tnl::Vector3(basePos_.x + grid.x * gridSize_, basePos_.y, basePos_.z - grid.y * gridSize_);

}


// 描画するオブジェクトを描画するlistに入れる関数
void Stage::drawObjectInList() {

	// 中身がある場合は削除する
	if ( drawObjectList_.size() > 0 ) {
		drawObjectList_.clear();
	}

	// 現在のステージの配列の中身を描画用のlistに入れる
	for (int y = 0; y < stageObjMap_[nowStage_].size(); ++y) {
		for (int x = 0; x < stageObjMap_[nowStage_][0].size(); ++x) {

			drawObjectList_.emplace_back(stageObjMap_[nowStage_][y][x]);

		}
	}

}


void Stage::sortObjectList(std::shared_ptr<dxe::Camera> camera ) {

	//drawObjectList_.sort((camera->pos_ - player_->getTransform().getPos_()).length());
	drawObjectList_.sort( [&](const std::shared_ptr<ObjectBlockBase>& left, const std::shared_ptr<ObjectBlockBase>& right){
		float l1 = (camera->pos_ - left->getPos_()).length();
		float l2 = (camera->pos_ - right->getPos_()).length();
		return (l1 > l2);
	});

	//int a = 0;
	//a++;

}




//-------------------------------------------------------------------------------------
// 現在のステージを実行可能か確認するシーケンス
// ステージを切り替えた際に必ずここを通過させる
// 中でexistNowStage_を切り替える
bool Stage::seqCheckNowStage(const float delta_time) {

	nowSeq_ = "seqCheckNowStage";

	// 現在ステージのオブジェクトがあるか確認する
	auto it = stageObjMap_.find(nowStage_);
	// 現在のステージが実行可能か確認する
	// 存在した時はtrue、存在しないときはfalseを入れる
	existNowStage_ = ( it != stageObjMap_.end() ) ? true : false;

	seq_.change(&Stage::seqNowStageUpdate);

	return true;
}


//-------------------------------------------------------------------------------------
// 現在のステージのアップデートを行うシーケンス
// 通常時はこのシーケンスを実行
// 条件に応じて各シーケンスに移行
bool Stage::seqNowStageUpdate(const float delta_time) {

	nowSeq_ = "seqNowStageUpdate";

	// 現在のステージが実行可能でないときリターンする
	if (!existNowStage_) return true;

	// オブジェクトのupdate関数を実行
	for (int y = 0; y < stageObjMap_[nowStage_].size(); ++y) {
		for (int x = 0; x < stageObjMap_[nowStage_][y].size(); ++x) {
			if(stageObjMap_[nowStage_][y][x])
			stageObjMap_[nowStage_][y][x]->update(delta_time);
		}
	}

	return true;
}


// ステージを変更する際のシーケンス
// 次のステージのオブジェクトが既に作成されていれば、そのまま切り替える
// 生成されていなければ作成してから切り替える
// 切り替える先のシーケンス...seqNowStageUpdate
// 引数：nextStade...次のステージ名のテキスト
// (型はstringでなくenum class型に変更の可能性あり、検討中)
bool Stage::seqStageChange(const float delta_time) {

	nowSeq_ = "seqStageChange";

	// 次のステージマップのオブジェクトを作成してあるか確認確認
	auto itObj = stageObjMap_.find(nowStage_);
	// 読み込んである場合
	if (itObj != stageObjMap_.end()) {

		// シーケンスを次に移す
		seq_.change(&Stage::seqCheckNowStage);
		return true;
	}

	CreateStage(nowStage_);

	// ステージを次のステージに切り替える
	// nowStage_ = nextStage;
	// 次のシーケンスに切り替える
	seq_.change(&Stage::seqCheckNowStage);

	return true;
}

// ステージのオブジェクトを作成する関数
// 引数：stage...作成するステージ名
void Stage::CreateStage(std::string stage) {

	// 次のステージマップのオブジェクトを作成してあるか確認確認
	auto itObj = stageObjMap_.find(nowStage_);
	// 読み込んである場合
	if (itObj != stageObjMap_.end()) {

		return;
	}

	// 次のステージが作成されていない場合
	// ステージの配列情報が読み込んであるか確認
	auto itArray = stageArrayMap_.find(nowStage_);
	if (itArray == stageArrayMap_.end()) {
		tnl::DebugTrace("ステージの配列が読み込みできていません\n");
		seq_.change(&Stage::seqCheckNowStage);
		return;
	}

	// マップのオブジェクトを保存する二重のvector
	std::vector<std::vector< std::shared_ptr<ObjectBlockBase> >> mapObjArray;


	// ステージのオブジェクトを作成するための繰り返し処理
	for (int y = 0; y < stageArrayMap_[nowStage_].size(); ++y) {

		// x方向のオブジェクトを一時保存するvector
		std::vector< std::shared_ptr<ObjectBlockBase> > mapObjX;

		for (int x = 0; x < stageArrayMap_[nowStage_][0].size(); ++x) {

			std::shared_ptr<ObjectBlockBase> floorObj;

			// マップの情報によって生成するオブジェクトを変更する処理
			// もし要素を追加する場合はcaseを追加する
			switch (stageArrayMap_[nowStage_][y][x]) {
			case 0:

				floorObj = std::shared_ptr<Floor>(new Floor(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));
				// x方向のvectorに生成したオブジェクトを追加
				mapObjX.emplace_back(floorObj);

				break;

			case 1:
				// 1の時壁のオブジェクトを生成
				std::shared_ptr<ObjectBlockBase> wallObj = std::shared_ptr<Wall>(new Wall(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));
				// x方向のvectorに生成したオブジェクトを追加
				mapObjX.emplace_back(wallObj);

				break;

			}

		}
		// 配列の1列分を追加する
		mapObjArray.emplace_back(mapObjX);

	}
	// 生成したオブジェクトの配列を名前と紐づけて保存
	stageObjMap_.insert(std::make_pair(nowStage_, mapObjArray));


	drawObjectInList();

	return;

}