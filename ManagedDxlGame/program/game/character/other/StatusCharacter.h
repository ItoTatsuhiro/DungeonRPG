#pragma once

// �L�����N�^�[�̃X�e�[�^�X�p�̃N���X
class StatusCharacter {
public :

	// �R���X�g���N�^
	// �����Flv...���x��, hp...�̗�, atk...�U����, def...�h���, spd...���x, crt...��S��
	// ���������ۂɐݒ肷��l������ꍇ�͏������q�œ����
	// �����l�����Ȃ��ꍇ�̓f�t�H���g�̒l������悤�ɂ���
	StatusCharacter(int lv = 1, float hp = 6, float atk = 1, float def = 0, float spd = 5, float crt = 0.1);
	// �f�X�g���N�^
	~StatusCharacter();


	//--------------------------------------------------------------------
	// �Q�b�^�[

	// ���x���̃Q�b�^�[
	inline const int getLv() const { return lv_; }
	// �̗͂̃Q�b�^�[
	inline const float getHp() const { return hp_; }
	// �ő�̗͂̃Q�b�^�[
	inline const float getHpMax() const { return hpMax_; }
	// �U���͂̃Q�b�^�[
	inline const float getAtk() const { return atk_; }
	// �h��͂̃Q�b�^�[
	inline const float getDef() const { return def_; }
	// ���x�̃Q�b�^�[
	inline const float getSpd() const { return spd_; }
	// ��S���̃Q�b�^�[
	inline const float getCrt() const { return crt_; }


	//--------------------------------------------------------------------
	// �Z�b�^�[

	// ���x���̃Z�b�^�[
	inline void setLv(int lv) { lv_ = lv; }
	// �̗͂̃Z�b�^�[
	inline void setHp(float hp) { hp_ = hp; }
	// �ő�̗͂̃Z�b�^�[
	inline void setHpMax(float hpMax) { hpMax_ = hpMax; }
	// �U���͂̃Z�b�^�[
	inline void setAtk(float atk) { atk_ = atk; }
	// �h��͂̃Z�b�^�[
	inline void setDef(float def) { def_ = def; }
	// ���x�̃Z�b�^�[
	inline void setSpd(float spd) { spd_ = spd; }
	// ��S���̃Z�b�^�[
	inline void setCrt(float crt) { crt_ = crt; }


protected :

	//**********************************************
	// �ȉ��̓L�����N�^�[�̃X�e�[�^�X�̕ϐ�
	// �����_�ȉ��̌v�Z��؂�̂ĂȂ��悤float�^�Œ�`
	//**********************************************

	// ���x��
	int lv_;
	// �̗�
	float hp_;
	// �ő�̗�
	float hpMax_;
	// �U����
	float atk_;
	// �h���
	float def_;
	// ���x	
	float spd_;
	// ��S��
	float crt_;

};