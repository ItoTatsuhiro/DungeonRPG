#include "StatusCharacter.h"


// コンストラクタ
// 引数：lv...レベル, hp...体力, atk...攻撃力, def...防御力, spd...速度, crt...会心率
// 生成した際に設定する値がある場合は初期化子で入れる
// 初期値を入れない場合はデフォルトの値が入るようにする
StatusCharacter::StatusCharacter(float lv, float hp, float atk, float def, float spd, float crt)
	: lv_(lv), hp_(hp), atk_(atk), def_(def), spd_(spd), crt_(crt)
{


}

// デストラクタ
StatusCharacter::~StatusCharacter() {

}

