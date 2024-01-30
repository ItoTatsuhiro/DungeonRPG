#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>

#include "../../base/ObjectBlockBase.h"

class Wall : public ObjectBlockBase{
public :
	// �ǃN���X�̃R���X�g���N�^
	// �����F�I�u�W�F�N�g�̍��W
	Wall(float gridSize, tnl::Vector3 pos);
	// �ǃN���X�̃f�X�g���N�^
	~Wall();

	// ���t���[���̏���
	void update(float delta_time) {};
	// �`��̏���
	void draw(std::shared_ptr<dxe::Camera> camera);



private :

	// �ǂ��\������I�u�W�F�N�g�𐶐�����֐�
	void CreateObj();


	std::shared_ptr<dxe::Texture> wallTexture_ = nullptr;


	// �ǂ��\������I�u�W�F�N�g�̃��X�g
	std::list<std::shared_ptr<ito::Object3D>> wallObjList_;

	// �ǂ�1�u���b�N���̃I�u�W�F�N�g
	// ������������ςݏd�˂Ďg�p����
	// std::shared_ptr<ito::Object3D> wallObj_ = nullptr;



};