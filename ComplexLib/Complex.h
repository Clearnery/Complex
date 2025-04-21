#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>

class Complex {
private:
    double real;
    double imaginary;

public:
    
    Complex();
    Complex(double r, double i = 0.0);
    Complex(const Complex& other);

    
    double getReal() const;
    double getImaginary() const;
    void setReal(double r);
    void setImaginary(double i);

    
    Complex& operator=(const Complex& other);
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    
    double abs() const;
    Complex pow(int n) const;
    Complex pow(double n) const;
    Complex pow(const Complex& exponent) const;
    Complex inverse() const;
    std::string trigonometricForm() const;

    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

#endif 