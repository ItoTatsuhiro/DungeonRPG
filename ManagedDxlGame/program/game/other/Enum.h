#pragma once


namespace Enum {

	// ������\���萔
	// +����ƍ����A-����ƉE���ƂȂ�
	// 1�ɂ�90�x���ω�����
	enum class Dir4 {
		UP = 0,		// �����
		LEFT,		// ������
		DOWN,		// ������
		RIGHT,		// �E����
		DIRMAX		// �����̐�
	};

	// --------------------------------------------------------------------------------
	// operator

	// Dir4��+���Z�q
	inline Dir4 operator+(const Dir4& left, const Dir4& right) {

		return static_cast<Dir4>((static_cast<int>(left) + static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX));
	}

	// Dir4��+=���Z�q
	inline Dir4 operator+=( Dir4& left, const Dir4& right) {

		left = static_cast<Dir4>((static_cast<int>(left) + static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX));

		return left;
	}

	// Dir4��-���Z�q
	inline Dir4 operator-(const Dir4& left, const Dir4& right) {

		return static_cast<Dir4>( std::abs(static_cast<int>(left) - static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX) );
	}

	// Dir4��-=���Z�q
	inline Dir4 operator-=(Dir4& left, const Dir4& right) {

		left = static_cast<Dir4>( std::abs(static_cast<int>(left) - static_cast<int>(right)) % static_cast<int>(Dir4::DIRMAX) );

		return left;
	}

};