#include "math.hpp"

inline int inr(int p, int s){
	if (p < 0)
		return 0;
	if (p > s)
		return s;
	return p;
}

Vect::Vect(int scallar) {
	x = scallar, y = scallar;
}
Vect::Vect(int x, int y) : x{ x }, y{y}
{

}
void Vect::print(){
	std::cout << "x: " << x << "	y: " << y << std::endl;
}

Vect Vect::operator*(int scallar) {
	return Vect(x * scallar, y * scallar);
}
Vect Vect::operator/(int scallar) {
	return Vect(x / scallar, y / scallar);
}
Vect Vect::operator+(const Vect& vect) {
	return Vect(x + vect.x, y + vect.y);
}
Vect Vect::operator-(const Vect& vect) {
	return Vect(x - vect.x, y - vect.y);
}
const Vect& Vect::normolize() {
	x = x > 0.5 ? 1 : 0;
	y = y > 0.5 ? 1 : 0;
	return *this;
}
Vect Vect::get_default() {
	return Vect(0, 1);
}

Matrix::Matrix(float ax, float ay, float bx, float by)
	: ax{ ax }, ay{ ay }, bx{bx}, by{by} {}
Matrix::Matrix() 
	: ax{ 0 }, ay{ 0 }, bx{ 0 }, by{ 0 } {}
void Matrix::print(){
	std::cout << "| " << ax << " " << bx << " |" << std::endl;
	std::cout << "| " << ay << " " << by << " |" << std::endl;
}

Vect Matrix::operator*(const Vect& v)
{
	return Vect(round(ax * v.x + bx * v.y), round(ay * v.x + by * v.y));
}
Matrix Matrix::operator*(const Matrix& m){
	return Matrix(
		round((ax * m.ax + bx * m.ay) * 1000) * 0.001,
		round((ay * m.ax + by * m.ay) * 1000) * 0.001,
		round((ax * m.bx + bx * m.by) * 1000) * 0.001,
		round((ay * m.bx + by * m.by) * 1000) * 0.001);
}

Matrix Matrix::get_default() {
	return Matrix(1, 0, 0, 1);
}
Matrix Matrix::get_rotation(int deg) {
	float rad = deg * 3.14 / 180.0;
	return Matrix(
		cos(rad), 
		sin(rad),
		- sin(rad),
		cos(rad));
}