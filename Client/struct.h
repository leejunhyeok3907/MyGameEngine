#pragma once

struct Vec2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}


	//빗변의 길이(피타고라스 법칙)
	float Length()
	{
		return (float)sqrt((x * x) + (y * y));
	}

	//벡터의 정규화
	//빗변의 길이가 1일때 밑변과 높이는 얼마인가
	Vec2 Normalize()
	{
		float f_len = Length();

		//자신의 성분을 빗변의 길이로 나눔

		assert(f_len != 0.f);
		x /= f_len;
		y /= f_len;

		return *this;
	}

public:
	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}

	void operator=(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator+(Vec2 _vec)
	{
		return Vec2(x + _vec.x, y + _vec.y);
	}

	void operator+=(Vec2 _vec)
	{
		x += _vec.x;
		y += _vec.y;
	}

	Vec2 operator-(Vec2 _vec)
	{
		return Vec2(x - _vec.x, y - _vec.y);
	}

	void operator-=(Vec2 _vec)
	{
		x -= _vec.x;
		y -= _vec.y;
	}

	void operator-=(float _f)
	{
		x -= _f;
		y -= _f;
	}

	Vec2 operator*(Vec2 _vec)
	{
		return Vec2(x * _vec.x, y * _vec.y);
	}

	Vec2 operator*(int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator*(float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	void operator*=(float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vec2 operator/(float _f)
	{
		assert(!(0.f == _f));

		return Vec2(x / _f, y / _f);
	}

	Vec2 operator/(Vec2 _vec)
	{
		assert(!(0.f == _vec.x || 0.f == _vec.y));

		return Vec2(x / _vec.x, y / _vec.y);
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x(float(_x))
		, y(float(_y))
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

};