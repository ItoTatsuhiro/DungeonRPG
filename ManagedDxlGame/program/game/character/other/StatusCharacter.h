#pragma once

// キャラクターのステータス用のクラス
class StatusCharacter {
public :

	// コンストラクタ
	// 引数：lv...レベル, hp...体力, atk...攻撃力, def...防御力, spd...速度, crt...会心率
	// 生成した際に設定する値がある場合は初期化子で入れる
	// 初期値を入れない場合はデフォルトの値が入るようにする
	StatusCharacter(int lv = 1, float hp = 6, float atk = 1, float def = 0, float spd = 5, float crt = 0.1);
	// デストラクタ
	~StatusCharacter();


	//--------------------------------------------------------------------
	// ゲッター

	// レベルのゲッター
	inline const int getLv() const { return lv_; }
	// 体力のゲッター
	inline const float getHp() const { return hp_; }
	// 最大体力のゲッター
	inline const float getHpMax() const { return hpMax_; }
	// 攻撃力のゲッター
	inline const float getAtk() const { return atk_; }
	// 防御力のゲッター
	inline const float getDef() const { return def_; }
	// 速度のゲッター
	inline const float getSpd() const { return spd_; }
	// 会心率のゲッター
	inline const float getCrt() const { return crt_; }


	//--------------------------------------------------------------------
	// セッター

	// レベルのセッター
	inline void setLv(int lv) { lv_ = lv; }
	// 体力のセッター
	inline void setHp(float hp) { hp_ = hp; }
	// 最大体力のセッター
	inline void setHpMax(float hpMax) { hpMax_ = hpMax; }
	// 攻撃力のセッター
	inline void setAtk(float atk) { atk_ = atk; }
	// 防御力のセッター
	inline void setDef(float def) { def_ = def; }
	// 速度のセッター
	inline void setSpd(float spd) { spd_ = spd; }
	// 会心率のセッター
	inline void setCrt(float crt) { crt_ = crt; }


protected :

	//**********************************************
	// 以下はキャラクターのステータスの変数
	// 小数点以下の計算を切り捨てないようfloat型で定義
	//**********************************************

	// レベル
	int lv_;
	// 体力
	float hp_;
	// 最大体力
	float hpMax_;
	// 攻撃力
	float atk_;
	// 防御力
	float def_;
	// 速度	
	float spd_;
	// 会心率
	float crt_;

};