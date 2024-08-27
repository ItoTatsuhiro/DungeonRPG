#pragma once

// キャラクターの種類の定数
enum class eCharaType {
	NONE = -1,				// 設定されていない状態、デフォルトはこれ
	PLAYER,					// プレイヤー
	ENEMY,					// 敵キャラクター
	CHARA_TYPE_COUNT		// キャラクターの種類の数
};