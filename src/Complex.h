#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

////////////////////////////////////////////////////////////////
// Complex
////////////////////////////////////////////////////////////////
class Complex
{
public:
	Complex()
		: re(0), im(0)
	{}

	Complex(float _re)
		: re(_re), im(0)
	{}

	Complex(float _re, float _im)
		: re(_re), im(_im)
	{}

	Complex(const Complex& other)
		: re(other.re), im(other.im)
	{}

	inline const float real() const { return re; }
	inline float& real() { return re; }
	inline const float imag() const { return im; }
	inline float& imag() { return im; }

	// Complex OP Scale
	inline Complex& operator = (const float _val);
	inline Complex& operator += (const float _val);
	inline Complex& operator -= (const float _val);
	inline Complex& operator *= (const float _val);
	inline Complex& operator /= (const float _val);

	// Complex OP Complex
	inline Complex& operator = (const Complex& rhs);
	inline Complex& operator += (const Complex& rhs);
	inline Complex& operator -= (const Complex& rhs);
	inline Complex& operator *= (const Complex& rhs);
	inline Complex& operator /= (const Complex& rhs);

	// Conjuction
	inline Complex operator ~ ();

	// Norm
	inline float norm2();
	inline float norm();

public:
	union
	{
		struct { float _Val[2]; };
		struct { float re, im; };
	};
}; // Complex

// Complex OP Scale
inline Complex operator + (const Complex& _cmplx, const float _val);
inline Complex operator - (const Complex& _cmplx, const float _val);
inline Complex operator * (const Complex& _cmplx, const float _val);
inline Complex operator / (const Complex& _cmplx, const float _val);

// Scale OP Complex
inline Complex operator + (const float _val, const Complex& _cmplx);
inline Complex operator - (const float _val, const Complex& _cmplx);
inline Complex operator * (const float _val, const Complex& _cmplx);
/// Scale / Complex is undefined
/// inline Complex operator / (const float _val, const Complex& _cmplx);

// Complex OP Complex
inline Complex operator + (const Complex& lhs, const Complex& rhs);
inline Complex operator - (const Complex& lhs, const Complex& rhs);
inline Complex operator * (const Complex& lhs, const Complex& rhs);
inline Complex operator / (const Complex& lhs, const Complex& rhs);

// Norm
inline float norm2(const Complex& _cmplx);
inline float norm(const Complex& _cmplx);

////////////////////////////////////////////////////////////////
// Complex implementation
////////////////////////////////////////////////////////////////

// Complex OP Scale
inline Complex& Complex :: operator = (const float _val)
{
	re = _val;
	im = 0;
	return *this;
}

inline Complex& Complex :: operator += (const float _val)
{
	re += _val;
	return *this;
}

inline Complex& Complex :: operator -= (const float _val)
{
	re -= _val;
	return *this;
}

inline Complex& Complex :: operator *= (const float _val)
{
	re *= _val;
	im *= _val;
	return *this;
}

inline Complex& Complex :: operator /= (const float _val)
{
	re /= _val;
	im /= _val;
	return *this;
}

// Complex OP Complex
inline Complex& Complex :: operator = (const Complex& rhs)
{
	re = rhs.re;
	im = rhs.im;
	return *this;
}

inline Complex& Complex :: operator += (const Complex& rhs)
{
	re += rhs.re;
	im += rhs.im;
	return *this;
}

inline Complex& Complex :: operator -= (const Complex& rhs)
{
	re -= rhs.re;
	im -= rhs.im;
	return *this;
}

inline Complex& Complex :: operator *= (const Complex& rhs)
{
	float tr = re * rhs.re - im * rhs.im;
	float ti = re * rhs.im + im * rhs.re;
	re = tr;
	im = ti;
	return *this;
}

inline Complex& Complex :: operator /= (const Complex& rhs)
{
	float inv = 1.f / (rhs.re * rhs.re + rhs.im * rhs.im);
	float tr = inv * (re * rhs.re + im * rhs.im);
	float ti = inv * (im * rhs.re - re * rhs.im);
	re = tr;
	im = ti;
	return *this;
}

// Conjuction
inline Complex Complex :: operator ~ ()
{
	return Complex(re, -im);
}

// Norm
inline float Complex :: norm2()
{
	return re * re + im * im;
}

inline float Complex :: norm()
{
	return std::sqrtf(re * re + im * im);
}

// Complex OP Scale
inline Complex operator + (const Complex& _cmplx, const float _val)
{
	return Complex(_cmplx.re + _val, _cmplx.im);
}

inline Complex operator - (const Complex& _cmplx, const float _val)
{
	return Complex(_cmplx.re - _val, _cmplx.im);
}

inline Complex operator * (const Complex& _cmplx, const float _val)
{
	return Complex(_cmplx.re * _val, _cmplx.im * _val);
}

inline Complex operator / (const Complex& _cmplx, const float _val)
{
	return Complex(_cmplx.re / _val, _cmplx.im / _val);
}

// Scale OP Complex
inline Complex operator + (const float _val, const Complex& _cmplx)
{
	return Complex(_cmplx.re + _val, _cmplx.im);
}

inline Complex operator - (const float _val, const Complex& _cmplx)
{
	return Complex(_cmplx.re - _val, _cmplx.im);
}

inline Complex operator * (const float _val, const Complex& _cmplx)
{
	return Complex(_cmplx.re * _val, _cmplx.im * _val);
}

/// Scale / Complex is undefined
/// inline Complex operator / (const float _val, const Complex& _cmplx);

// Complex OP Complex
inline Complex operator + (const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.re + rhs.re, lhs.im + rhs.im);
}

inline Complex operator - (const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

inline Complex operator * (const Complex& lhs, const Complex& rhs)
{
	return Complex(
		lhs.re * rhs.re - lhs.im * rhs.im,
		lhs.re * rhs.im + lhs.im * rhs.re);
}

inline Complex operator / (const Complex& lhs, const Complex& rhs)
{
	float inv = 1.f / (rhs.re * rhs.re + rhs.im * rhs.im);
	return Complex(
		inv * (lhs.re * rhs.re + lhs.im * rhs.im),
		inv * (lhs.im * rhs.re - lhs.re * rhs.im));
}

// Norm
inline float norm2(const Complex& _cmplx)
{
	return _cmplx.re * _cmplx.re + _cmplx.im * _cmplx.im;
}

inline float norm(const Complex& _cmplx)
{
	return std::sqrtf(_cmplx.re * _cmplx.re + _cmplx.im * _cmplx.im);
}

#endif