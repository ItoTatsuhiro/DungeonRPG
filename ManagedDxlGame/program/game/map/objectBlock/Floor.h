#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>


#include "../../base/ObjectBlockBase.h"

class Floor : public ObjectBlockBase {
public:
	// �ǃN���X�̃R���X�g���N�^
	// �����F�I�u�W�F�N�g�̍��W
	Floor(float gridSize, tnl::Vector3 pos);
	// �ǃN���X�̃f�X�g���N�^
	~Floor();

	// ���t���[���̏���
	void update(float delta_time) {};
	// �`��̏���
	void draw(std::shared_ptr<dxe::Camera> camera);



private:

	// �����\������I�u�W�F�N�g�𐶐�����֐�
	void CreateObj();


	std::shared_ptr<dxe::Texture> floorTexture_ = nullptr;


	// �����\������I�u�W�F�N�g�̃��X�g
	std::list<std::shared_ptr<ito::Object3D>> floorObjList_;



};