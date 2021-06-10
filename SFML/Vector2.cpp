#include "Vector2.h"

Vector2::Vector2() : x(0), y(0)
{}

Vector2::Vector2(float value) {
    x = value;
    y = value;
}

Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vector2::~Vector2() {}

float Vector2::GetX() const {
    return x;
}

float Vector2::GetY() const {
    return y;
}

float Vector2::Get() const {
    return x, y;
}

void Vector2::SetX(const float _x) {
    x = _x;
}

void Vector2::SetY(const float _y) {
    y = _y;
}

void Vector2::Set(const float _x, const float _y)
{
    x = _x;
    y = _y;
}

Vector2 Vector2::operator+(const Vector2 &v) {
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) {
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const Vector2 &v) {
    return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator/(const Vector2 &v) {
    return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::operator+=(const Vector2 &v) {
    return Vector2(x += v.x, y += v.y);
}

Vector2 Vector2::operator-=(const Vector2 &v) {
    return Vector2(x -= v.x, y -= v.y);
}

Vector2 Vector2::operator*=(const Vector2 &v) {
    return Vector2(x *= v.x, y *= v.y);
}

Vector2 Vector2::operator/=(const Vector2 &v) {
    return Vector2(x /= v.x, y /= v.y);
}

Vector2 Vector2::Zero() {
    return Vector2(x = 0, y = 0);
}

Vector2 Vector2::One() {
    return Vector2(x = 1, y = 1);
}

float Vector2::Dot(Vector2 &v, Vector2 &v2) {
    return ((v.x * v2.x) + (v.y * v2.y));
}

void Vector2::Scale(float scaleFactor) {
    x *= scaleFactor;
    y *= scaleFactor;
}

void Vector2::Normalize() {
    x /= Length();
    y /= Length();
}

float Vector2::Length() {
    return sqrt((x * x) + (y * y));
}

float Vector2::LengthSquared()
{
    return sqrt((x * x) + (y * y)) * sqrt((x * x) + (y * y));
}

void Vector2::Rotate(float angle) {
    angle = (2 * PI) - angle;
    x = (x * cos(angle)) + (y * -sin(angle));
    y = (y * sin(angle)) + (y * cos(angle));
}

Vector2 Vector2::Rotate(Vector2 &v, float angle) {
    angle = (2 * PI) - angle;
    v.x = (v.x * cos(angle)) + (v.y * -sin(angle));
    v.y = (v.x * sin(angle)) + (v.y * cos(angle));
    return v;
}