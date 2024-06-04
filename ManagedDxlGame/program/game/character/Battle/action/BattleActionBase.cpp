#include "BattleActionBase.h"

// コンストラクタ
// 引数：行動を行うキャラクター
BattleActionBase::BattleActionBase(std::shared_ptr< BattleCharacterBase > actionCharacter) 
	: actionCharacter_(actionCharacter)
{

}