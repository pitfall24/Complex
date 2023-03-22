//
// Created by Phineas on 3/20/23.
//

#ifndef COMPLEX_COMPLEXNUMBER_H
#define COMPLEX_COMPLEXNUMBER_H

#pragma once
#include <iostream>

class ComplexNumber {

    // a + bi
    double a;
    double b;

public:

    // Constructors
    ComplexNumber();
    explicit ComplexNumber(double a, double b = 0.0);
    ComplexNumber(const ComplexNumber& z);

    // Angle functions. Returns [0, 2pi]
    static double angle(double a, double b = 0.0);
    static double angle(const ComplexNumber& z);
    [[nodiscard]] double angle() const;

    // Magnitude functions.
    static double magnitude(double a, double b = 0.0);
    static double magnitude(const ComplexNumber& z);
    [[nodiscard]] double magnitude() const;

    // Complex exponential functions. (e ^ xi)
    static ComplexNumber ComplexExp(double a, double b = 0.0);
    static ComplexNumber ComplexExp(const ComplexNumber& z);
    [[nodiscard]] ComplexNumber ComplexExp() const;

    // OPERATOR OVERLOADS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // operator+ (addition)
    friend ComplexNumber operator+(const ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber operator+(const double& z1, const ComplexNumber& z2);
    friend ComplexNumber operator+(const ComplexNumber& z1, const double& z2);

    // operator+=
    friend ComplexNumber& operator+=(ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber& operator+=(ComplexNumber& z1, const double& z2);

    // operator- (subtraction)
    friend ComplexNumber operator-(const ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber operator-(const double& z1, const ComplexNumber& z2);
    friend ComplexNumber operator-(const ComplexNumber& z1, const double& z2);

    // operator-=
    friend ComplexNumber& operator-=(ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber& operator-=(ComplexNumber& z1, const double& z2);

    // operator*  (multiplication)
    friend ComplexNumber operator*(const ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber operator*(const double& z1, const ComplexNumber& z2);
    friend ComplexNumber operator*(const ComplexNumber& z1, const double& z2);

    // operator *=
    friend ComplexNumber& operator*=(ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber& operator*=(ComplexNumber& z1, const double& z2);

    // operator / (division)
    friend ComplexNumber operator/(const ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber operator/(const double& z1, const ComplexNumber& z2);
    friend ComplexNumber operator/(const ComplexNumber& z1, const double& z2);

    // operator /=
    friend ComplexNumber& operator/=(ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber& operator/=(ComplexNumber& z1, const double& z2);

    // operator^ (power)
    friend ComplexNumber operator^(const ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber operator^(const double& z1, const ComplexNumber& z2);
    friend ComplexNumber operator^(const ComplexNumber& z1, const double& z2);

    // operator^=
    friend ComplexNumber& operator^=(ComplexNumber& z1, const ComplexNumber& z2);
    friend ComplexNumber& operator^=(ComplexNumber& z1, const double& z2);

    // operator~ (conjugate)
    friend ComplexNumber operator~(const ComplexNumber& z);

    // operator== (equal comparison)
    friend bool operator==(const ComplexNumber& z1, const ComplexNumber& z2);
    friend bool operator==(const double& z1, const ComplexNumber& z2);
    friend bool operator==(const ComplexNumber& z1, const double& z2);

    // operator!= (not equal comparison)
    friend bool operator!=(const ComplexNumber& z1, const ComplexNumber& z2);
    friend bool operator!=(const double& z1, const ComplexNumber& z2);
    friend bool operator!=(const ComplexNumber& z1, const double& z2);

    // operator<< (for printing)
    friend std::ostream& operator<<(std::ostream& os, ComplexNumber& z);
};

#endif //COMPLEX_COMPLEXNUMBER_H
