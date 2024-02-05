#pragma once


namespace Enum {

	// 方向を表す定数
	// +すると左回り、-すると右回りとなる
	// 1につき90度分変化する
	enum class Dir4 {
		UP = 0,		// 上方向
		LEFT,		// 左方向
		DOWN,		// 下方向
		RIGHT,		// 右方向
		DIRMAX		// 方向の数
	};

	// --------------------------------------------------------------------------------
	// operator

	// Dir4の+演算子
	inline Dir4 operator+(const Dir4& left, const Dir4& right) {

		return static_cast<Dir4>((static_cast<int>(left) + static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX));
	}

	// Dir4の+=演算子
	inline Dir4 operator+=( Dir4& left, const Dir4& right) {

		left = static_cast<Dir4>((static_cast<int>(left) + static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX));

		return left;
	}

	// Dir4の-演算子
	inline Dir4 operator-(const Dir4& left, const Dir4& right) {

		return static_cast<Dir4>( std::abs(static_cast<int>(left) - static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX) );
	}

	// Dir4の-=演算子
	inline Dir4 operator-=(Dir4& left, const Dir4& right) {

		left = static_cast<Dir4>( std::abs(static_cast<int>(left) - static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX) );

		return left;
	}

};