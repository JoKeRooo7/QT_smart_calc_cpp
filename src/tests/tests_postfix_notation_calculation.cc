#include <gtest/gtest.h>

#include "polish_notation.h"
#include <cmath>

TEST(TestPolishNotation, TestOnlyOperationOne) {
    EXPECT_THROW(s21::PolishNotation obj("+"), std::invalid_argument); 
}

TEST(TestPolishNotation, TestOnlyOperationTwo) {
    EXPECT_THROW(s21::PolishNotation obj("-"), std::invalid_argument); 
}

TEST(TestPolishNotation, TestOnlyOperationThree) {
    EXPECT_THROW(s21::PolishNotation obj("arccos("), std::invalid_argument); 
}

TEST(TestPolishNotation, TestEmptyOne) {
    s21::PolishNotation obj("");
    EXPECT_NEAR(obj.result(), 0.0, 1e-6);
}

TEST(TestPolishNotation, TestNumOne) {
    s21::PolishNotation obj("1");
    EXPECT_NEAR(obj.result(), 1.0, 1e-6);
}

TEST(TestPolishNotation, TestNumTwo) {
    s21::PolishNotation obj("12");
    EXPECT_NEAR(obj.result(), 12.0, 1e-6);
}

TEST(TestPolishNotation, TestNumThree) {
    s21::PolishNotation obj("123");
    EXPECT_NEAR(obj.result(), 123.0, 1e-6);
}

TEST(TestPolishNotation, TestNumFour) {
    s21::PolishNotation obj("123456");
    EXPECT_NEAR(obj.result(), 123456.0, 1e-6);
}

TEST(TestPolishNotation, TestNumFive) {
    s21::PolishNotation obj(".0123456");
    EXPECT_NEAR(obj.result(), 0.0123456, 1e-6);
}

TEST(TestPolishNotation, TestNumSix) {
    s21::PolishNotation obj("12345678.7654321");
    EXPECT_NEAR(obj.result(), 12345678.7654321, 1e-7);
}

TEST(TestPolishNotation, TestNumSeven) {
    s21::PolishNotation obj("12345678.7654321");
    EXPECT_NEAR(obj.result(), 12345678.7654321, 1e-7);
} 

TEST(TestPolishNotation, TestNumEight) {
    s21::PolishNotation obj("-1");
    EXPECT_NEAR(obj.result(), -1.0, 1e-6);
}

TEST(TestPolishNotation, TestNumNine) {
    s21::PolishNotation obj("-(-(-(-(-(-5)))))");
    EXPECT_NEAR(obj.result(), 5.0, 1e-6);
}

TEST(TestPolishNotation, TestSumOne) {
    s21::PolishNotation obj("12345678.7654321 + 987.789");
    EXPECT_NEAR(obj.result(), 12345678.7654321 + 987.789, 1e-7);
}

TEST(TestPolishNotation, TestSumTwo) {
    s21::PolishNotation obj("-1 + 1");
    EXPECT_NEAR(obj.result(), -1 + 1, 1e-6);
}

TEST(TestPolishNotation, TestSumThree) {
    s21::PolishNotation obj("-1 +(- 1)");
    EXPECT_NEAR(obj.result(), -1 +- 1, 1e-6);
}

TEST(TestPolishNotation, TestSumFour) {
    s21::PolishNotation obj("-1 +(- (1))");
    EXPECT_NEAR(obj.result(), -1 +- (1), 1e-6);
}

TEST(TestPolishNotation, TestSumFive) {
    s21::PolishNotation obj("-1 +(- (-1))");
    EXPECT_NEAR(obj.result(), -1 +- (-1), 1e-6);
}

TEST(TestPolishNotation, TestSumSix) {
    s21::PolishNotation obj("12345678.7654321 +- 987.789");
    EXPECT_NEAR(obj.result(), 12345678.7654321 +- 987.789, 1e-7);
}

TEST(TestPolishNotation, TestFunctionOne) {
    s21::PolishNotation obj("-sin(-1)");
    EXPECT_NEAR(obj.result(), -std::sin(-1), 1e-10);
}

TEST(TestPolishNotation, TestFunctionTwo) {
    s21::PolishNotation obj("- arcsin(-1)");
    EXPECT_NEAR(obj.result(), -std::asin(-1), 1e-8);
}

TEST(TestPolishNotation, TestFunctionThree) {
    s21::PolishNotation obj("sin(cos(tan(-0.12)))");
    EXPECT_NEAR(obj.result(), std::sin(std::cos(std::tan(-0.12))), 1e-11);
}

TEST(TestPolishNotation, TestFunctionFour) {
    s21::PolishNotation obj("42.1 mod (12.9)");
    EXPECT_NEAR(obj.result(), std::fmod(42.1, 12.9), 1e-11);
}

TEST(TestPolishNotation, TestFunctionFive) {
    s21::PolishNotation obj("ln (12.9)");
    EXPECT_NEAR(obj.result(), std::log(12.9), 1e-11);
}

TEST(TestPolishNotation, TestFunctionSix) {
    s21::PolishNotation obj("log(13.9)");
    EXPECT_NEAR(obj.result(), std::log10(13.9), 1e-11);
}

TEST(TestPolishNotation, TestFunctionSeven) {
    s21::PolishNotation obj("arccos(0.9)");
    EXPECT_NEAR(obj.result(), std::acos(0.9), 1e-11);
}

TEST(TestPolishNotation, TestPowOne) {
    s21::PolishNotation obj("2 ^ 3 ^ 4 ^ 5");
    EXPECT_DOUBLE_EQ(obj.result(), std::numeric_limits<double>::infinity());
}

TEST(TestPolishNotation, TestPowTwo) {
    s21::PolishNotation obj("2 ^ 3 ^ 4");
    EXPECT_DOUBLE_EQ(obj.result(), std::pow(2, std::pow(3, 4)));
}

TEST(TestPolishNotation, TestPowThree) {
    s21::PolishNotation obj("4 ^ 3 ^ 2");
    EXPECT_DOUBLE_EQ(obj.result(), std::pow(4, std::pow(3, 2)));
}

TEST(TestPolishNotation, TestPowFour) {
    s21::PolishNotation obj("4 ^ -3 ^ 2");
    EXPECT_DOUBLE_EQ(obj.result(), std::pow(4, 9));
}

TEST(TestPolishNotation, TestFunctionNine) {
    s21::PolishNotation obj; 
    obj = ("(ln(0.01) - sqrt(0.912) *- cos(123)) mod(9.55)");
    EXPECT_NEAR(obj.result(), std::fmod((std::log(0.01) - std::sqrt(0.912) * -std::cos(123)), 9.55), 1e-11);
}

TEST(TestPolishNotation, TestFunctionTen) {
    s21::PolishNotation obj; 
    obj = ("(ln(0.01) - sqrt(0.912) * cos(123)) mod(9.55)");
    EXPECT_NEAR(obj.result(), std::fmod((std::log(0.01) - std::sqrt(0.912) * std::cos(123)), 9.55), 1e-11);
}

TEST(TestPolishNotation, TestFunctionEleven) {
    s21::PolishNotation obj; 
    obj = ("(ln(0.01) - sqrt(0.912) *- cos(123)) mod(9.55)");
    EXPECT_NEAR(obj.result(), std::fmod((std::log(0.01) - std::sqrt(0.912) * -std::cos(123)), 9.55), 1e-11);
}

TEST(TestPolishNotation, TestFunctionTwelve) {
    s21::PolishNotation obj("log(arctan(0.2) + 2 ^ (-3) ^ sin(123.0))");
    EXPECT_TRUE(std::isnan(obj.result()));
}

TEST(TestPolishNotation, TestFunctionThirteen) {
    s21::PolishNotation obj("-1 * (-cos(-3.1))");
    EXPECT_NEAR(obj.result(), -1 * (-cos(-3.1)), 1e-10);
}

TEST(TestPolishNotation, TestFunctionFourteen) {
    s21::PolishNotation obj("-cos(-3.1) * (-1)");
    EXPECT_NEAR(obj.result(), -1 * (-cos(-3.1)), 1e-10);
}

TEST(TestPolishNotation, TestFunctionFifteen) {
    s21::PolishNotation obj("2 ^ (-3) ^ 0.1");
    EXPECT_TRUE(std::isnan(obj.result()));
}

TEST(TestPolishNotation, TestFunctionSixteen) {
    s21::PolishNotation obj("log(arctan(0.2) + 2 ^ (-3) ^ 0.1)");
    EXPECT_TRUE(std::isnan(obj.result()));
}

TEST(TestPolishNotation, TestDeleteOne) {
    s21::PolishNotation obj("5 / 6 / 7 /- 8 ");
    EXPECT_NEAR(obj.result(), -0.014880952380952382, 1e-11);
}

TEST(TestPolishNotation, ThrowOne) {
    EXPECT_THROW(s21::PolishNotation obj("av 1 "), std::invalid_argument);
}

TEST(TestPolishNotation, ThrowTwo) {
    EXPECT_THROW(s21::PolishNotation obj("1 + 2 +"), std::invalid_argument);
}

TEST(TestPolishNotation, ThrowThree) {
    EXPECT_THROW(s21::PolishNotation obj("arctan()"), std::invalid_argument);
}

TEST(TestPolishNotation, MinusOneMinusOneMinusMinusOnePlusOne) {
    s21::PolishNotation obj("-1 -1 --1 +1");
    EXPECT_NEAR(obj.result(), 0.0, 1e-6);
}

TEST(TestPolishNotation, TestBracketsOne) {
    s21::PolishNotation obj("66.8 + cos(arctan((((8)))))");
    EXPECT_NEAR(obj.result(), 66.8  +std::cos(std::atan(8)), 1e-6);
}

TEST(TestPolishNotation, TestExponentOne) {
    s21::PolishNotation obj("1E-12");
    EXPECT_NEAR(obj.result(), 1e-12, 1e-6);
}

TEST(TestPolishNotation, TestExponentTwo) {
    s21::PolishNotation obj("-1E-12");
    EXPECT_NEAR(obj.result(), -1e-12, 1e-6);
}

TEST(TestPolishNotation, TestExponentThree) {
    s21::PolishNotation obj("(-1E-12)/(-1E-12)");
    EXPECT_NEAR(obj.result(), 1, 1e-6);
}

TEST(TestPolishNotation, TestConstOne) {
    s21::PolishNotation obj("pi/(-pi)");
    EXPECT_NEAR(obj.result(), -1, 1e-6);
}

TEST(TestPolishNotation, TestConstTwo) {
    s21::PolishNotation obj("-pi/-(-pi)");
    EXPECT_NEAR(obj.result(), -1, 1e-6);
}

TEST(TestPolishNotation, TestConstFour) {
    s21::PolishNotation obj("-pi/(-pi)");
    EXPECT_NEAR(obj.result(), 1, 1e-6);
}

TEST(TestPolishNotation, TestConstFive) {
    s21::PolishNotation obj("-pi/-pi");
    EXPECT_NEAR(obj.result(), 1, 1e-6);
}

TEST(TestPolishNotation, TestConstSix) {
    s21::PolishNotation obj("pi/-pi");
    EXPECT_NEAR(obj.result(), -1, 1e-6);
}

TEST(TestPolishNotation, TestConstSeven) {
    s21::PolishNotation obj("-pi/pi");
    EXPECT_NEAR(obj.result(), -1, 1e-6);
}

TEST(TestPolishNotation, TestXOne) {
    s21::PolishNotation obj("x");
    EXPECT_NEAR(obj.get_result(-1), -1, 1e-6);
}

TEST(TestPolishNotation, TestXTwo) {
    s21::PolishNotation obj("-x");
    EXPECT_NEAR(obj.get_result(-1), 1, 1e-6);
}

TEST(TestPolishNotation, TestXThree) {
    s21::PolishNotation obj("-(-x)");
    EXPECT_NEAR(obj.get_result(-1), -1, 1e-6);
}

TEST(TestPolishNotation, TestXFour) {
    s21::PolishNotation obj("-(-x)/x");
    EXPECT_NEAR(obj.get_result(-1), 1, 1e-6);
}

TEST(TestPolishNotation, TestXFive) {
    s21::PolishNotation obj("-(-x)/-x");
    EXPECT_NEAR(obj.get_result(-1), -1, 1e-6);
}

TEST(TestPolishNotation, TestXSix) {
    s21::PolishNotation obj("-(-x)/-(-x)");
    EXPECT_NEAR(obj.get_result(-1), 1, 1e-6);
}

TEST(TestPolishNotation, TestXSeven) {
    s21::PolishNotation obj("-x/(-x)");
    EXPECT_NEAR(obj.get_result(-1), 1, 1e-6);
}

TEST(TestPolishNotation, TestXEight) {
    s21::PolishNotation obj("-x/-(-x)");
    EXPECT_NEAR(obj.get_result(-1), -1, 1e-6);
}

