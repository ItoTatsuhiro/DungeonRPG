#include "Stage.h"
#include "objectBlock/Wall.h"
#include "objectBlock/Floor.h"
#include "../object/Player.h"

// �R���X�g���N�^
// �����FstartStage	...�����X�e�[�W
// �@�@�@csvPath	...�X�e�[�W�}�b�v�̔z����L�ڂ���csv�̕ۊǐ�
//		 gridSize	...1�}�X�̑傫��
// ���s���e
// �}�b�v�̓ǂݍ��݁A���݂̃X�e�[�W��startStage�ɐ؂�ւ��A�V�[�P���X�̐؂�ւ�
Stage::Stage(std::string startStage, std::string csvPath, float gridSize) : gridSize_(gridSize) {

	LoadMap(startStage, csvPath);

	CreateStage(startStage);

	nowStage_ = startStage;
	seq_.change(&Stage::seqStageChange);

}

// Stage�N���X�̃C���X�^���X���Ǘ�����N���X
// ��������Ƃ��͈�����S�ē���
// �C���X�^���X�擾���͈����Ȃ��ŌĂяo��
// �����FstartStage...�����X�e�[�W
// �@�@�@csvPath...�X�e�[�W�}�b�v�̔z����L�ڂ���csv�̕ۊǐ�
std::shared_ptr<Stage> Stage::GetInstance(std::string startStage, std::string csvPath, float gridSize) {

	// Stage�N���X�̃C���X�^���X
	static std::shared_ptr<Stage> instance = nullptr;

	// ���ɐ�������Ă��Ȃ��Ƃ��̂ݐV��������
	if (!instance) {
		instance = std::shared_ptr<Stage>( new Stage(startStage, csvPath, gridSize) );
	}

	return instance;
}

// �f�X�g���N�^
Stage::~Stage() {

}


void Stage::update(float delta_time) {

	// ���݂̃X�e�[�W�����s�s�\�Ȏ���return����
	if (!existNowStage_) return;

	seq_.update(delta_time);
	DrawStringEx(50, 50, -1, "%s", nowStage_.c_str());
	DrawStringEx(100, 100, -1, "%s", nowSeq_.c_str());
}

void Stage::draw(std::shared_ptr<dxe::Camera> camera) {

	// ���݂̃X�e�[�W�����s�s�\�ȂƂ���return����
	if (!existNowStage_) return;




	sortObjectList(camera);

	auto it = drawObjectList_.begin();

	while (it != drawObjectList_.end()) {

		(*it)->draw(camera);

		++it;
	}


}


//-------------------------------------------------------------------------------------
// �X�e�[�W�}�b�v��csv��ǂݍ��݁A�ۑ��p��map�ɕۑ�����֐�
// �����Fname...�X�e�[�W��, csvPath...csv�t�@�C���̕ۑ���
void Stage::LoadMap(std::string name, std::string csvPath) {

	// ���ɓ����̃}�b�v���ۑ�����Ă���ꍇ���[�h���Ȃ�
	auto it = stageArrayMap_.find(name);
	if (it != stageArrayMap_.end()) return;

	// �p�X�̃}�b�v�����[�h����
	std::vector<std::vector<int>> loadMap;
	loadMap = tnl::LoadCsv<int>(csvPath);

	// �}�b�v�ɓo�^����
	stageArrayMap_.insert(std::make_pair(name, loadMap));

}

//-------------------------------------------------------------------------------------
// ���s����X�e�[�W��؂�ւ���֐�
// �����FnextStage...���̃X�e�[�W
void Stage::StageChange(std::string nextStage) {
	nowStage_ = nextStage;
	seq_.change(&Stage::seqStageChange);
}

//-------------------------------------------------------------------------------------
// �����̍��W�̃}�b�v�̐��l�𒲂ׂ�֐�
// �����FcheckGrid...�}�b�v�̔z�񂩂�m�F����v�f�ԍ�(x, y)
int Stage::CheckGridPosInt(tnl::Vector2i checkGrid) {

	// �z��͈̔͊O�̂Ƃ��A-1��Ԃ�
	if (stageArrayMap_[nowStage_].size() - 1 < checkGrid.y || stageArrayMap_[nowStage_][0].size() - 1 < checkGrid.x
		|| 0 > checkGrid.y || 0 > checkGrid.x) {
		return -1;
	}

	return stageArrayMap_[nowStage_][checkGrid.y][checkGrid.x];
}


//-------------------------------------------------------------------------------------
// �����̍��W�̃I�u�W�F�N�g���擾����֐�
// �����FcheckGrid...�}�b�v�̔z�񂩂�m�F����v�f�ԍ�(x, y)
std::shared_ptr<ObjectBlockBase> Stage::CheckGridPosObj(tnl::Vector2i checkGrid) {

	tnl::DebugTrace(" %d ", stageObjMap_[nowStage_][checkGrid.y][checkGrid.x]);

	return stageObjMap_[nowStage_][checkGrid.y][checkGrid.x];

}


// �����̃}�X�̍��W���擾����֐�
// �����Fgrid...���W���m�F����}�X�̗v�f�ԍ�
tnl::Vector3 Stage::getGridObjPos(tnl::Vector2i grid) {

	return tnl::Vector3(basePos_.x + grid.x * gridSize_, basePos_.y, basePos_.z - grid.y * gridSize_);

}


// �`�悷��I�u�W�F�N�g��`�悷��list�ɓ����֐�
void Stage::drawObjectInList() {

	// ���g������ꍇ�͍폜����
	if ( drawObjectList_.size() > 0 ) {
		drawObjectList_.clear();
	}

	// ���݂̃X�e�[�W�̔z��̒��g��`��p��list�ɓ����
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
// ���݂̃X�e�[�W�����s�\���m�F����V�[�P���X
// �X�e�[�W��؂�ւ����ۂɕK��������ʉ߂�����
// ����existNowStage_��؂�ւ���
bool Stage::seqCheckNowStage(const float delta_time) {

	nowSeq_ = "seqCheckNowStage";

	// ���݃X�e�[�W�̃I�u�W�F�N�g�����邩�m�F����
	auto it = stageObjMap_.find(nowStage_);
	// ���݂̃X�e�[�W�����s�\���m�F����
	// ���݂�������true�A���݂��Ȃ��Ƃ���false������
	existNowStage_ = ( it != stageObjMap_.end() ) ? true : false;

	seq_.change(&Stage::seqNowStageUpdate);

	return true;
}


//-------------------------------------------------------------------------------------
// ���݂̃X�e�[�W�̃A�b�v�f�[�g���s���V�[�P���X
// �ʏ펞�͂��̃V�[�P���X�����s
// �����ɉ����Ċe�V�[�P���X�Ɉڍs
bool Stage::seqNowStageUpdate(const float delta_time) {

	nowSeq_ = "seqNowStageUpdate";

	// ���݂̃X�e�[�W�����s�\�łȂ��Ƃ����^�[������
	if (!existNowStage_) return true;

	// �I�u�W�F�N�g��update�֐������s
	for (int y = 0; y < stageObjMap_[nowStage_].size(); ++y) {
		for (int x = 0; x < stageObjMap_[nowStage_][y].size(); ++x) {
			if(stageObjMap_[nowStage_][y][x])
			stageObjMap_[nowStage_][y][x]->update(delta_time);
		}
	}

	return true;
}


// �X�e�[�W��ύX����ۂ̃V�[�P���X
// ���̃X�e�[�W�̃I�u�W�F�N�g�����ɍ쐬����Ă���΁A���̂܂ܐ؂�ւ���
// ��������Ă��Ȃ���΍쐬���Ă���؂�ւ���
// �؂�ւ����̃V�[�P���X...seqNowStageUpdate
// �����FnextStade...���̃X�e�[�W���̃e�L�X�g
// (�^��string�łȂ�enum class�^�ɕύX�̉\������A������)
bool Stage::seqStageChange(const float delta_time) {

	nowSeq_ = "seqStageChange";

	// ���̃X�e�[�W�}�b�v�̃I�u�W�F�N�g���쐬���Ă��邩�m�F�m�F
	auto itObj = stageObjMap_.find(nowStage_);
	// �ǂݍ���ł���ꍇ
	if (itObj != stageObjMap_.end()) {

		// �V�[�P���X�����Ɉڂ�
		seq_.change(&Stage::seqCheckNowStage);
		return true;
	}

	CreateStage(nowStage_);

	// �X�e�[�W�����̃X�e�[�W�ɐ؂�ւ���
	// nowStage_ = nextStage;
	// ���̃V�[�P���X�ɐ؂�ւ���
	seq_.change(&Stage::seqCheckNowStage);

	return true;
}

// �X�e�[�W�̃I�u�W�F�N�g���쐬����֐�
// �����Fstage...�쐬����X�e�[�W��
void Stage::CreateStage(std::string stage) {

	// ���̃X�e�[�W�}�b�v�̃I�u�W�F�N�g���쐬���Ă��邩�m�F�m�F
	auto itObj = stageObjMap_.find(nowStage_);
	// �ǂݍ���ł���ꍇ
	if (itObj != stageObjMap_.end()) {

		return;
	}

	// ���̃X�e�[�W���쐬����Ă��Ȃ��ꍇ
	// �X�e�[�W�̔z���񂪓ǂݍ���ł��邩�m�F
	auto itArray = stageArrayMap_.find(nowStage_);
	if (itArray == stageArrayMap_.end()) {
		tnl::DebugTrace("�X�e�[�W�̔z�񂪓ǂݍ��݂ł��Ă��܂���\n");
		seq_.change(&Stage::seqCheckNowStage);
		return;
	}

	// �}�b�v�̃I�u�W�F�N�g��ۑ������d��vector
	std::vector<std::vector< std::shared_ptr<ObjectBlockBase> >> mapObjArray;


	// �X�e�[�W�̃I�u�W�F�N�g���쐬���邽�߂̌J��Ԃ�����
	for (int y = 0; y < stageArrayMap_[nowStage_].size(); ++y) {

		// x�����̃I�u�W�F�N�g���ꎞ�ۑ�����vector
		std::vector< std::shared_ptr<ObjectBlockBase> > mapObjX;

		for (int x = 0; x < stageArrayMap_[nowStage_][0].size(); ++x) {

			std::shared_ptr<ObjectBlockBase> floorObj;

			// �}�b�v�̏��ɂ���Đ�������I�u�W�F�N�g��ύX���鏈��
			// �����v�f��ǉ�����ꍇ��case��ǉ�����
			switch (stageArrayMap_[nowStage_][y][x]) {
			case 0:

				floorObj = std::shared_ptr<Floor>(new Floor(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));
				// x������vector�ɐ��������I�u�W�F�N�g��ǉ�
				mapObjX.emplace_back(floorObj);

				break;

			case 1:
				// 1�̎��ǂ̃I�u�W�F�N�g�𐶐�
				std::shared_ptr<ObjectBlockBase> wallObj = std::shared_ptr<Wall>(new Wall(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));
				// x������vector�ɐ��������I�u�W�F�N�g��ǉ�
				mapObjX.emplace_back(wallObj);

				break;

			}

		}
		// �z���1�񕪂�ǉ�����
		mapObjArray.emplace_back(mapObjX);

	}
	// ���������I�u�W�F�N�g�̔z��𖼑O�ƕR�Â��ĕۑ�
	stageObjMap_.insert(std::make_pair(nowStage_, mapObjArray));


	drawObjectInList();

	return;

}