#include "Vector2.h"

Vector2::Vector2() : x(0), y(0)
{}

Vector2::Vector2(float value) {
    this->x = value;
    this->y = value;
}

Vector2::Vector2(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

Vector2::~Vector2() {};

void Vector2::SetX(const float _x) {
    this->x = _x;
}

void Vector2::SetY(const float _y) {
    this->y = _y;
}

void Vector2::Set(const float _x, const float _y)
{
    this->x = _x;
    this->y = _y;
}

float Vector2::GetX() const {
    return this->x;
}

float Vector2::GetY() const {
    return this->y;
}

Vector2 Vector2::Get() const {
    return Vector2(this->x, this->y);
}

Vector2 Vector2::operator+(const Vector2 &v) {
    return Vector2(this->x + v.x, this->y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) {
    return Vector2(this->x - v.x, this->y - v.y);
}

Vector2 Vector2::operator*(const Vector2 &v) {
    return Vector2(this->x * v.x, this->y * v.y);
}

Vector2 Vector2::operator/(const Vector2 &v) {
    return Vector2(this->x / v.x, this->y / v.y);
}

Vector2 Vector2::operator+=(const Vector2 &v) {
    return Vector2(this->x += v.x, this->y += v.y);
}

Vector2 Vector2::operator-=(const Vector2 &v) {
    return Vector2(this->x -= v.x, this->y -= v.y);
}

Vector2 Vector2::operator*=(const Vector2 &v) {
    return Vector2(this->x *= v.x, this->y *= v.y);
}

Vector2 Vector2::operator/=(const Vector2 &v) {
    return Vector2(this->x /= v.x, this->y /= v.y);
}

Vector2 Vector2::Zero() {
    return Vector2(this->x = 0, this->y = 0);
}

Vector2 Vector2::One() {
    return Vector2(this->x = 1, this->y = 1);
}

float Vector2::Dot(Vector2 &v, Vector2 &v2) {
    return ((v.x * v2.x) + (v.y * v2.y));
}

void Vector2::Scale(float scaleFactor) {
    this->x *= scaleFactor;
    this->y *= scaleFactor;
}

void Vector2::Normalize() {
    this->x /= Length();
    this->y /= Length();
}

float Vector2::Length() {
    return sqrt((this->x * this->x) + (this->y * this->y));
}

float Vector2::LengthSquared()
{
    return sqrt((this->x * this->x) + (this->y * this->y)) * sqrt((this->x * this->x) + (this->y * this->y));
}

void Vector2::Rotate(float angle) {
    angle = (2 * PI) - angle;
    this->x = (this->x * cos(angle)) + (this->y * -sin(angle));
    this->y = (this->y * sin(angle)) + (this->y * cos(angle));
}

Vector2 Vector2::Rotate(Vector2 &v, float angle) {
    angle = (2 * PI) - angle;
    v.x = (v.x * cos(angle)) + (v.y * -sin(angle));
    v.y = (v.x * sin(angle)) + (v.y * cos(angle));
    return v;
}