#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>

#include "../../base/ObjectBlockBase.h"

class Goal final : public ObjectBlockBase {
public:
	// �ǃN���X�̃R���X�g���N�^
	// �����F�I�u�W�F�N�g�̍��W
	Goal(float gridSize, tnl::Vector3 pos);
	// �ǃN���X�̃f�X�g���N�^
	~Goal();

	// ���t���[���̏���
	void update(float delta_time) {};
	// �`��̏���
	void draw(std::shared_ptr<dxe::Camera> camera);



private:

	// �ǂ��\������I�u�W�F�N�g�𐶐�����֐�
	void CreateObj();


	int displayObjNum_ = 0;

	std::shared_ptr<dxe::Texture> goalTexture_ = nullptr;


	// �ǂ��\������I�u�W�F�N�g�̃��X�g
	std::list<std::shared_ptr<ito::Object3D>> goalObjList_;

};