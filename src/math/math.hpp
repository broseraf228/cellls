#pragma once

#include <iostream>

inline int inr(int p, int s);

struct Vect {
public:
	Vect(int scallar);
	Vect(int x, int y);

	int x, y;

	Vect operator+(const Vect&);
	Vect operator-(const Vect&);
	Vect operator*(int);
	Vect operator/(int);

	const Vect& normolize();
	static Vect get_default();

	void print();
};

struct Matrix {
public:
	Matrix();
	Matrix(float ax, float ay, float bx, float by);
	float ax, ay, bx, by;

	Vect operator*(const Vect&);
	Matrix operator*(const Matrix&);

	static Matrix get_default();
	static Matrix get_rotation(int degrees);

	void print();
};