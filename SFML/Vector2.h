#pragma once
#include <cmath>
#define PI 3.14159

class Vector2 {
private:
    float x;
    float y;
public:
    Vector2();
    Vector2(float value);
    Vector2(float _x, float _y);
    ~Vector2();

    void SetX(const float _x);
    void SetY(const float _y);
    void Set(const float _x, const float _y);

    float GetX() const;
    float GetY() const;
    Vector2 Get() const;

    Vector2 operator+(const Vector2& v);
    Vector2 operator-(const Vector2& v);
    Vector2 operator*(const Vector2& v);
    Vector2 operator/(const Vector2& v);

    Vector2 operator+=(const Vector2& v);
    Vector2 operator-=(const Vector2& v);
    Vector2 operator*=(const Vector2& v);
    Vector2 operator/=(const Vector2& v);

    Vector2 Zero();
    Vector2 One();

    float Dot(Vector2& v, Vector2& v2);
    void Scale(float scaleFactor);
    void Normalize();
    float Length();
    float LengthSquared();

    void Rotate(float angle);
    Vector2 Rotate(Vector2& v, float angle);
};
