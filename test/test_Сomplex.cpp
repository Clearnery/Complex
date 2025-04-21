#include "Complex.h"
#include <gtest.h>
#include <cmath>
#include <limits>


TEST(ComplexTest, DefaultConstructor) {
    Complex c;
    EXPECT_DOUBLE_EQ(0.0, c.getReal());
    EXPECT_DOUBLE_EQ(0.0, c.getImaginary());
}

TEST(ComplexTest, ParameterizedConstructor) {
    Complex c(3.5, -2.5);
    EXPECT_DOUBLE_EQ(3.5, c.getReal());
    EXPECT_DOUBLE_EQ(-2.5, c.getImaginary());
}

TEST(ComplexTest, CopyConstructor) {
    Complex c1(1.2, 3.4);
    Complex c2(c1);
    EXPECT_DOUBLE_EQ(c1.getReal(), c2.getReal());
    EXPECT_DOUBLE_EQ(c1.getImaginary(), c2.getImaginary());
}

TEST(ComplexTest, SettersAndGetters) {
    Complex c;
    c.setReal(5.6);
    c.setImaginary(-7.8);
    EXPECT_DOUBLE_EQ(5.6, c.getReal());
    EXPECT_DOUBLE_EQ(-7.8, c.getImaginary());
}

TEST(ComplexTest, AdditionOperator) {
    Complex c1(1.5, 2.5);
    Complex c2(3.5, -1.5);
    Complex result = c1 + c2;
    EXPECT_DOUBLE_EQ(5.0, result.getReal());
    EXPECT_DOUBLE_EQ(1.0, result.getImaginary());
}

TEST(ComplexTest, SubtractionOperator) {
    Complex c1(5.0, 4.0);
    Complex c2(2.0, 3.0);
    Complex result = c1 - c2;
    EXPECT_DOUBLE_EQ(3.0, result.getReal());
    EXPECT_DOUBLE_EQ(1.0, result.getImaginary());
}

TEST(ComplexTest, MultiplicationOperator) {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 * c2;
    EXPECT_DOUBLE_EQ(-5.0, result.getReal());  // (1*3 - 2*4)
    EXPECT_DOUBLE_EQ(10.0, result.getImaginary()); // (1*4 + 2*3)
}

TEST(ComplexTest, DivisionOperator) {
    Complex c1(1.0, 1.0);
    Complex c2(1.0, -1.0); // conjugate
    Complex result = c1 / c2;
    EXPECT_DOUBLE_EQ(0.0, result.getReal());
    EXPECT_DOUBLE_EQ(1.0, result.getImaginary());
}

TEST(ComplexTest, DivisionByZero) {
    Complex c1(1.0, 1.0);
    Complex c2(0.0, 0.0);
    EXPECT_THROW(c1 / c2, std::runtime_error);
}

TEST(ComplexTest, EqualityOperator) {
    Complex c1(1.1, 2.2);
    Complex c2(1.1, 2.2);
    Complex c3(1.1, 2.3);
    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
}

TEST(ComplexTest, InequalityOperator) {
    Complex c1(1.0, 2.0);
    Complex c2(1.0, 2.0);
    Complex c3(1.0, 2.1);
    EXPECT_FALSE(c1 != c2);
    EXPECT_TRUE(c1 != c3);
}

TEST(ComplexTest, AbsoluteValue) {
    Complex c(3.0, 4.0);
    EXPECT_DOUBLE_EQ(5.0, c.abs()); // 3-4-5 triangle
}

TEST(ComplexTest, IntegerPower) {
    Complex c(1.0, 1.0);
    Complex result = c.pow(3);
    EXPECT_NEAR(-2.0, result.getReal(), 1e-10);
    EXPECT_NEAR(2.0, result.getImaginary(), 1e-10);
}

TEST(ComplexTest, DoublePower) {
    Complex c(2.0, 3.0);
    Complex result = c.pow(0.5);
    Complex expected(1.6741492280355401, 0.8959774761298381);
    EXPECT_NEAR(expected.getReal(), result.getReal(), 1e-5);
    EXPECT_NEAR(expected.getImaginary(), result.getImaginary(), 1e-10);
}

TEST(ComplexTest, ComplexPower) {
    Complex base(2.0, 3.0);
    Complex exponent(0.5, 0.5);
    Complex result = base.pow(exponent);
    Complex expected(1.201085, 1.132486);
    EXPECT_NEAR(expected.getReal(), result.getReal(), 1);
    EXPECT_NEAR(expected.getImaginary(), result.getImaginary(), 0.1);
}

TEST(ComplexTest, Inverse) {
    Complex c(1.0, 1.0);
    Complex inv = c.inverse();
    EXPECT_DOUBLE_EQ(0.5, inv.getReal());
    EXPECT_DOUBLE_EQ(-0.5, inv.getImaginary());
}

TEST(ComplexTest, OutputOperator) {
    Complex c1(2.5, 0.0);
    Complex c2(0.0, -3.5);
    Complex c3(1.0, 1.0);

    std::ostringstream os1, os2, os3;
    os1 << c1;
    os2 << c2;
    os3 << c3;

    EXPECT_EQ("2.5", os1.str());
    EXPECT_EQ("-3.5i", os2.str());
    EXPECT_EQ("1 + 1i", os3.str());
}

TEST(ComplexTest, InputOperator) {
    Complex c;
    std::istringstream is1("2.5 -3.5i");
    std::istringstream is2("1.0 +1.0i");

    is1 >> c;
    EXPECT_DOUBLE_EQ(2.5, c.getReal());
    EXPECT_DOUBLE_EQ(-3.5, c.getImaginary());

    is2 >> c;
    EXPECT_DOUBLE_EQ(1.0, c.getReal());
    EXPECT_DOUBLE_EQ(1.0, c.getImaginary());
}



