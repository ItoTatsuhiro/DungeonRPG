#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <unordered_map>

// 3D�I�u�W�F�N�g���쐬����ۂ̃I���W�i�����쐬�A���L����N���X
// �����ŃI���W�i���̃I�u�W�F�N�g���쐬���A�N���[���Ƃ��đ��̃I�u�W�F�N�g���쐬����
// �I�u�W�F�N�g���쐬����ۂ́A���̃N���X�̊֐����o�R���č쐬���邱��
class ObjectManager{
public :

	// �I�u�W�F�N�g�}�l�[�W���[���C���X�^���X�����邽�߂̊֐�
	// ���̊֐���ʂ��ăI�u�W�F�N�g�}�l�[�W���[���擾����
	static ObjectManager* GetInstance();

	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃f�X�g���N�^
	~ObjectManager();

	//----------------------------------------------------------------------
	// �I�u�W�F�N�g�̃I���W�i���A�N���[�����쐬����֐�
	// �I�u�W�F�N�g���쐬����ۂ́A�ȉ��̊֐�����쐬���邱��
	// �֐��͐V���ȃ��b�V�����g�p���ɏ����ǉ��\��

	// Box�̃��b�V�������I�u�W�F�N�g�̃N���[�����쐬����֐�
	// �����̃I���W�i�����쐬����Ă���΃N���[����Ԃ��A
	// �쐬����Ă��Ȃ���΍쐬���Ă���N���[����Ԃ�
	// �����Fsize...Box�̑傫��, name...�I�u�W�F�N�g��
	std::shared_ptr<ito::Object3D> createCube(float size, std::string name);

	// Plane�̃��b�V�������I�u�W�F�N�g�̃I���W�i�����쐬����֐�
	// �����̃I���W�i�����쐬����Ă���΃N���[����Ԃ��A
	// �쐬����Ă��Ȃ���΍쐬���Ă���N���[����Ԃ�
	// �����Fsize...Plane�̑傫��(z�����͕s�g�p), name...�I�u�W�F�N�g��
	// ===========�ȉ��̕ϐ��̓A�j���[�V�������s���ꍇ�Ɏg�p===========
	// startPosOfCut...�e�N�X�`���̕����̊J�n�n�_(�f�t�H���g��{ 0, 0, 0 })
	// endPosOfCut...�e�N�X�`���̕����̏I���n�_(�f�t�H���g��{ 1, 1, 0 })
	std::shared_ptr<ito::Object3D> createPlane(tnl::Vector3 size, std::string name, tnl::Vector3 startPosOfCut = { 0, 0, 0 }, tnl::Vector3 endPosOfCut = { 1, 1, 0 });


	//----------------------------------------------------------------------
	// �I�u�W�F�N�g�̃I���W�i�����폜����֐�

	// ���ɑ��݂��Ă���I���W�i���̃I�u�W�F�N�g���폜����֐�
	// �����Fname...�폜����I�u�W�F�N�g�̖��O
	void deleteOriginal(std::string name);


private :


	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃R���X�g���N�^
	ObjectManager();


	// �I���W�i���̃I�u�W�F�N�g��ۑ�����map
	// ���O�ƃI�u�W�F�N�g��ۑ�����
	std::unordered_map<std::string, std::shared_ptr<ito::Object3D>> originObjList_;


};
