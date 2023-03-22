//
// Created by Phineas on 3/20/23.
//
#include <cmath>
#include <iostream>
#include "ComplexNumber.h"

// Constants
#define PI 3.14159265

// Constructors
ComplexNumber::ComplexNumber() {
    this->a = 0.0;
    this->b = 0.0;
}

ComplexNumber::ComplexNumber(double a, double b) {
    this->a = a;
    this->b = b;
}

ComplexNumber::ComplexNumber(const ComplexNumber& z) {
    this->a = z.a;
    this->b = z.b;
}

// Angle functions. Returns [0, 2pi]
double ComplexNumber::angle(double a, double b) {
    double theta = atan2(b, a);
    return theta < 0 ? theta + 2 * PI : theta;
}

double ComplexNumber::angle(const ComplexNumber& z) {
    return ComplexNumber::angle(z.a, z.b);
}

double ComplexNumber::angle() const {
    return ComplexNumber::angle(this->a, this->b);
}

// Magnitude functions.
double ComplexNumber::magnitude(double a, double b) {
    return sqrt(a * a + b  * b);
}

double ComplexNumber::magnitude(const ComplexNumber& z) {
    return sqrt(z.a * z.a + z.b * z.b);
}

double ComplexNumber::magnitude() const {
    return ComplexNumber::magnitude(*this);
}

// Complex exponential functions. (e ^ xi)
ComplexNumber ComplexNumber::ComplexExp(double a, double b) {
    return exp(a) * ComplexNumber(cos(b), sin(b));
}

ComplexNumber ComplexNumber::ComplexExp(const ComplexNumber& z) {
    return ComplexNumber::ComplexExp(z.a, z.b);
}

ComplexNumber ComplexNumber::ComplexExp() const {
    return ComplexNumber::ComplexExp(this->a, this->b);
}

// OPERATOR OVERLOADS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// operator+ (addition)
ComplexNumber operator+(const ComplexNumber& z1, const ComplexNumber& z2) {
    return ComplexNumber(z1.a + z2.a, z1.b + z2.b);
}

ComplexNumber operator+(const double& z1, const ComplexNumber& z2) {
    return ComplexNumber(z1 + z2.a, z2.b);
}

ComplexNumber operator+(const ComplexNumber& z1, const double& z2) {
    return ComplexNumber(z1.a + z2, z1.b);
}

// operator+=
ComplexNumber& operator+=(ComplexNumber& z1, const ComplexNumber& z2) {
    z1.a += z2.a;
    z1.b += z2.b;

    return z1;
}

ComplexNumber& operator+=(ComplexNumber& z1, const double& z2) {
    z1.a += z2;

    return z1;
}

// operator- (subtraction)
ComplexNumber operator-(const ComplexNumber& z1, const ComplexNumber& z2) {
    return ComplexNumber(z1.a - z2.a, z1.b - z2.b);
}

ComplexNumber operator-(const double& z1, const ComplexNumber& z2) {
    return ComplexNumber(z1 - z2.a, -z2.b);
}

ComplexNumber operator-(const ComplexNumber& z1, const double& z2) {
    return ComplexNumber(z1.a - z2, z1.b);
}

// operator-=
ComplexNumber& operator-=(ComplexNumber& z1, const ComplexNumber& z2) {
    z1.a -= z2.a;
    z1.b -= z2.b;

    return z1;
}

ComplexNumber& operator-=(ComplexNumber& z1, const double& z2) {
    z1.a -= z2;

    return z1;
}

// operator*  (multiplication)
ComplexNumber operator*(const ComplexNumber& z1, const ComplexNumber& z2) {
    return ComplexNumber(z1.a * z2.a - z1.b * z2.b, z1.a * z2.b + z1.b * z2.a);
}

ComplexNumber operator*(const double& z1, const ComplexNumber& z2) {
    return ComplexNumber(z1 * z2.a, z1 * z2.b);
}

ComplexNumber operator*(const ComplexNumber& z1, const double& z2) {
    return ComplexNumber(z1.a * z2, z1.b * z2);
}

// operator *=
ComplexNumber& operator*=(ComplexNumber& z1, const ComplexNumber& z2) {
    z1 = z1 * z2;

    return z1;
}

ComplexNumber& operator*=(ComplexNumber& z1, const double& z2) {
    z1 = z1 * z2;

    return z1;
}

// operator / (division)
ComplexNumber operator/(const ComplexNumber& z1, const ComplexNumber& z2) {
    double m = z2.a * z2.a + z2.b * z2.b;

    return ComplexNumber((z1.a * z2.a + z1.b * z2.b) / m, (z1.b * z2.a - z1.a * z2.b) / m);
}

ComplexNumber operator/(const double& z1, const ComplexNumber& z2) {
    double m = z2.a * z2.a + z2.b * z2.b;

    return ComplexNumber(z1 * z2.a / m, -z1 * z2.b / m);
}

ComplexNumber operator/(const ComplexNumber& z1, const double& z2) {
    return ComplexNumber(z1.a / z2, z1.b / z2);
}

// operator /=
ComplexNumber& operator/=(ComplexNumber& z1, const ComplexNumber& z2) {
    z1 = z1 / z2;

    return z1;
}

ComplexNumber& operator/=(ComplexNumber& z1, const double& z2) {
    z1 = z1 / z2;

    return z1;
}

// operator^ (power)
ComplexNumber operator^(const ComplexNumber& z1, const ComplexNumber& z2) {
    return (z2 * ComplexNumber(log(ComplexNumber::magnitude(z1)), ComplexNumber::angle(z1))).ComplexExp();
}

ComplexNumber operator^(const double& z1, const ComplexNumber& z2) {
    return pow(z1, z2.a) * ComplexNumber(cos(z2.b * log(z1)), sin(z2.b * log(z1)));
}

ComplexNumber operator^(const ComplexNumber& z1, const double& z2) {
    double r = ComplexNumber::magnitude(z1.a, z1.b);
    double theta = ComplexNumber::angle(z1.a, z1.b);

    return pow(r, z2) * ComplexNumber(cos(z2 * theta), sin(z2 * theta));
}

// operator^=
ComplexNumber& operator^=(ComplexNumber& z1, const ComplexNumber& z2) {
    z1 = z1 ^ z2;

    return z1;
}

ComplexNumber& operator^=(ComplexNumber& z1, const double& z2) {
    z1 = z1 ^ z2;

    return z1;
}

// operator~ (conjugate)
ComplexNumber operator~(const ComplexNumber& z) {
    return ComplexNumber(z.a, -z.b);
}

// operator== (equal comparison)
bool operator==(const ComplexNumber& z1, const ComplexNumber& z2) {
    return z1.a == z2.a && z1.b == z2.b;
}

bool operator==(const double& z1, const ComplexNumber& z2) {
    return z1 == z2.a && z2.b == 0.0;
}

bool operator==(const ComplexNumber& z1, const double& z2) {
    return z1.a == z2 && z1.b == 0.0;
}

// operator!= (not equal comparison)
bool operator!=(const ComplexNumber& z1, const ComplexNumber& z2) {
    return z1.a != z2.a || z1.b != z2.b;
}

bool operator!=(const double& z1, const ComplexNumber& z2) {
    return z1 != z2.a || z2.b != 0.0;
}

bool operator!=(const ComplexNumber& z1, const double& z2) {
    return z1.a != z2 || z1.b != 0.0;
}

// operator<< (for printing)
std::ostream& operator<<(std::ostream& os, ComplexNumber& z) {
    return os << "(" << z.a << (z.b >= 0 ? " + " : " - ") << fabs(z.b) << "i)";
}