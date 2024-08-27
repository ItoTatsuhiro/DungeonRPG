#pragma once


namespace Enum {

	// --------------------------------------------------------------------------------
	// ������Enum

	// ������\���萔
	// +����ƍ����A-����ƉE���ƂȂ�
	// 1�ɂ�90�x���ω�����
	enum class eDir4 {
		UP = 0,		// �����
		LEFT,		// ������
		DOWN,		// ������
		RIGHT,		// �E����
		DIRMAX		// �����̐�
	};

	// operator

	// Dir4��+���Z�q
	inline eDir4 operator+(const eDir4& left, const eDir4& right) {

		return static_cast<eDir4>((static_cast<int>(left) + static_cast<int>(right)) % static_cast<int>(eDir4::DIRMAX));
	}

	// Dir4��+=���Z�q
	inline eDir4 operator+=( eDir4& left, const eDir4& right) {

		left = static_cast<eDir4>((static_cast<int>(left) + static_cast<int>(right)) % static_cast<int>(eDir4::DIRMAX));

		return left;
	}

	// Dir4��-���Z�q
	inline eDir4 operator-(const eDir4& left, const eDir4& right) {

		return static_cast<eDir4>( std::abs(static_cast<int>(left) - static_cast<int>(right)) % static_cast<int>(eDir4::DIRMAX) );
	}

	// Dir4��-=���Z�q
	inline eDir4 operator-=(eDir4& left, const eDir4& right) {

		left = static_cast<eDir4>( std::abs(static_cast<int>(left) - static_cast<int>(right)) % static_cast<int>(eDir4::DIRMAX) );

		return left;
	}

	






};