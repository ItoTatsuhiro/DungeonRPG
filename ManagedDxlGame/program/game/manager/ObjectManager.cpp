#include "ObjectManager.h"

// �R���X�g���N�^
ObjectManager::ObjectManager() {

}

// �f�X�g���N�^
ObjectManager::~ObjectManager() {

}

// ObjectManager���C���X�^���X������p�̊֐�
// ObjectManager�͂��̊֐���ʂ��Ď擾����
ObjectManager* ObjectManager::GetInstance() {
	static ObjectManager* instance = nullptr;

	if (instance == nullptr) {
		instance = new ObjectManager;
	}

	return instance;
}


//----------------------------------------------------------------------
// �I�u�W�F�N�g�̃I���W�i���A�N���[�����쐬����֐�

// Box�̃��b�V�������I�u�W�F�N�g�̃N���[�����쐬����֐�
// �����̃I���W�i�����쐬����Ă���΃N���[����Ԃ��A
// �쐬����Ă��Ȃ���΍쐬���Ă���N���[����Ԃ�
// �����Fsize...Box�̑傫��, name...�I�u�W�F�N�g��
std::shared_ptr<ito::Object3D> ObjectManager::createCube(float size, std::string name) {

	// �����̃I���W�i���I�u�W�F�N�g��T��
	auto it = originObjList_.find(name);

	// �ۑ�����Ă����ꍇ�A����̃N���[�������I�u�W�F�N�g���쐬���Areturn����
	if (it != originObjList_.end()) {
		std::shared_ptr<ito::Object3D> boxObj = std::make_shared< ito::Object3D >();
		boxObj->set_mesh_(originObjList_[name]->get_mesh_()->createClone());
		return boxObj;
	}

	// �ۑ�����Ă��Ȃ������ꍇ�A�I���W�i���̃I�u�W�F�N�g���쐬����
	std::shared_ptr<ito::Object3D> boxObj = std::make_shared< ito::Object3D >();
	boxObj->set_mesh_(dxe::Mesh::CreateCubeMV(size) );
	originObjList_.insert(std::make_pair(name, boxObj));

	// �I���W�i���̃N���[���̃��b�V�������I�u�W�F�N�g���쐬����
	std::shared_ptr<ito::Object3D> boxObj_clone = std::make_shared< ito::Object3D >();
	boxObj_clone->set_mesh_(boxObj->get_mesh_()->createClone());

	// �쐬�����I�u�W�F�N�g��Ԃ�
	return boxObj_clone;

}


// Plane�̃��b�V�������I�u�W�F�N�g�̃I���W�i�����쐬����֐�
// �����̃I���W�i�����쐬����Ă���΃N���[����Ԃ��A
// �쐬����Ă��Ȃ���΍쐬���Ă���N���[����Ԃ�
// �����Fsize...Plane�̑傫��(z�����͕s�g�p), name...�I�u�W�F�N�g��
std::shared_ptr<ito::Object3D> ObjectManager::createPlane(tnl::Vector3 size, std::string name) {

	// �����̃I���W�i���I�u�W�F�N�g��T��
	auto it = originObjList_.find(name);

	// �ۑ�����Ă����ꍇ�A����̃N���[�������I�u�W�F�N�g���쐬���Areturn����
	if (it != originObjList_.end()) {
		std::shared_ptr<ito::Object3D> planeObj = std::make_shared< ito::Object3D >();
		planeObj->set_mesh_(originObjList_[name]->get_mesh_()->createClone());
		return planeObj;
	}

	// �ۑ�����Ă��Ȃ������ꍇ�A�I���W�i���̃I�u�W�F�N�g���쐬����
	std::shared_ptr<ito::Object3D> planeObj = std::make_shared< ito::Object3D >();
	planeObj->set_mesh_(dxe::Mesh::CreatePlaneMV(size));
	originObjList_.insert(std::make_pair(name, planeObj));

	// �I���W�i���̃N���[���̃��b�V�������I�u�W�F�N�g���쐬����
	std::shared_ptr<ito::Object3D> planeObj_clone = std::make_shared< ito::Object3D >();
	planeObj_clone->set_mesh_(planeObj->get_mesh_()->createClone());

	// �쐬�����I�u�W�F�N�g��Ԃ�
	return planeObj_clone;

}


//----------------------------------------------------------------------
// �I�u�W�F�N�g�̃I���W�i�����폜����֐�

// ���ɑ��݂��Ă���I���W�i���̃I�u�W�F�N�g���폜����֐�
// �����Fname...�폜����I�u�W�F�N�g�̖��O
void ObjectManager::deleteOriginal(std::string name) {

	// �����̃I���W�i���I�u�W�F�N�g��T��
	auto it = originObjList_.find(name);

	// ���X�g�ɓ����̃I���W�i�������݂���ꍇ�폜����
	if (it != originObjList_.end()) {
		originObjList_.erase(name);
		return;
	}

	// ���݂��Ȃ������ꍇ�폜�ł��Ȃ������|��\������
	tnl::DebugTrace("%s�̃I���W�i�������݂��Ȃ��������߁A�폜�ł��܂���ł���", name);
	return;
}