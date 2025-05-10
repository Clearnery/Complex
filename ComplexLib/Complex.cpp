#include "Complex.h"
#include <cmath>
#include <stdexcept>


Complex::Complex() : real(0.0), imaginary(0.0) {}
Complex::Complex(double r, double i) : real(r), imaginary(i) {}
Complex::Complex(const Complex& other) : real(other.real), imaginary(other.imaginary) {}


double Complex::getReal() const { return real; }
double Complex::getImaginary() const { return imaginary; }
void Complex::setReal(double r) { real = r; }
void Complex::setImaginary(double i) { imaginary = i; }


Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {
        real = other.real;
        imaginary = other.imaginary;
    }
    return *this;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imaginary + other.imaginary);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imaginary - other.imaginary);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imaginary * other.imaginary,
        real * other.imaginary + imaginary * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Complex((real * other.real + imaginary * other.imaginary) / denominator,
        (imaginary * other.real - real * other.imaginary) / denominator);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imaginary == other.imaginary;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}


double Complex::abs() const {
    return sqrt(real * real + imaginary * imaginary);
}

Complex Complex::pow(int n) const {
    if (n == 0) return Complex(1.0);

    Complex result(1.0);
    Complex base = (n > 0) ? *this : this->inverse();
    int power = (n > 0) ? n : -n;

    for (int i = 0; i < power; ++i) {
        result = result * base;
    }
    return result;
}

Complex Complex::pow(double n) const {
    double r = abs();
    double theta = atan2(imaginary, real);
    double new_r = std::pow(r, n);
    double new_theta = theta * n;

    return Complex(new_r * cos(new_theta), new_r * sin(new_theta));
}

Complex Complex::pow(const Complex& exponent) const {
    if (real == 0 && imaginary == 0) {
        if (exponent.real == 0 && exponent.imaginary == 0) {
            return Complex(1.0);
        }
        return Complex(0.0);
    }

    double r = abs();
    double theta = atan2(imaginary, real);
    double c = exponent.real;
    double d = exponent.imaginary;

    double ln_r = log(r);
    double new_r = exp(c * ln_r - d * theta);
    double new_theta = c * theta + d * ln_r;

    return Complex(new_r * cos(new_theta), new_r * sin(new_theta));
}

Complex Complex::inverse() const {
    double denominator = real * real + imaginary * imaginary;
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Complex(real / denominator, -imaginary / denominator);
}

std::string Complex::trigonometricForm() const {
    double r = abs();
    double theta = atan2(imaginary, real);
    return std::to_string(r) + "(cos(" + std::to_string(theta) + ") + i*sin(" + std::to_string(theta) + "))";
}


std::ostream& operator<<(std::ostream& os, const Complex& c) {
    if (c.imaginary == 0) {
        os << c.real;
    }
    else if (c.real == 0) {
        os << c.imaginary << "i";
    }
    else {
        os << c.real << (c.imaginary > 0 ? " + " : " - ") << std::abs(c.imaginary) << "i";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    char sign, i;
    is >> c.real >> sign >> c.imaginary >> i;
    if (sign == '-') {
        c.imaginary = -c.imaginary;
    }
    if (i != 'i') {
        is.setstate(std::ios::failbit);
    }
    return is;
}