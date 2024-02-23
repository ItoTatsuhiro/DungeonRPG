#pragma once
#include "../../dxlib_ext/mesh/dxlib_ext_mesh.h"
#include "ito_transform.h"


namespace ito {

	// �I�u�W�F�N�g3D�N���X
	// �Q�[������3D�̃I�u�W�F�N�g�Ɍp��,�܂��͌^�Ƃ��Ďg�p
	class Object3D {
	public :
		// �R���X�g���N�^
		Object3D(){}
		// �f�X�g���N�^
		virtual ~Object3D(){}


	protected :
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ������t���O
		bool isActive_ = true;
		// �I�u�W�F�N�g�̃��b�V��
		std::shared_ptr< dxe::Mesh > mesh_ = nullptr;
		// �I�u�W�F�N�g�̃e�N�X�`��
		std::shared_ptr< dxe::Texture > texture_ = nullptr;


	public :
		// ���z�֐��F�I�u�W�F�N�g�̍X�V�����p�֐�
		virtual void update(float delta_time) {}
		// ���z�֐��F�I�u�W�F�N�g�̕`�揈���p�֐�
		virtual void draw(std::shared_ptr<dxe::Camera> camera = nullptr){}

		// �Q�b�^�[...�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾����֐�
		// �߂�l...isActive_(bool�^�A�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�����)
		bool get_isActive_() const { return isActive_; }

		// �Z�b�^�[...�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ύX����֐�
		// �����F�ύX��̃I�u�W�F�N�g�̃A�N�e�B�u���
		void set_isActive_(bool isActive) { isActive_ = isActive; }

		// �Q�b�^�[...�I�u�W�F�N�g�̃��b�V�����擾����֐�
		// �߂�l...�I�u�W�F�N�g�̃��b�V��
		std::shared_ptr< dxe::Mesh > get_mesh_() { return mesh_; }

		// �Z�b�^�[...�I�u�W�F�N�g�̃��b�V����ݒ肷��֐�
		// �����F�ݒ肷�郁�b�V��
		void set_mesh_( std::shared_ptr< dxe::Mesh > mesh ) { 
			mesh_ = mesh;
		}


	};

}