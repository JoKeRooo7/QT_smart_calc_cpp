#include <gtest/gtest.h>

#include "polish_notation.h"

TEST(TestPolishNotation, TestOne) {
    s21::PolishNotation obj("");
    EXPECT_EQ(obj.get_postfix_entry(), "");
}

TEST(TestPolishNotation, TestTwo) {
    s21::PolishNotation obj("1");
    EXPECT_EQ(obj.get_postfix_entry(), "1 ");
}

TEST(TestPolishNotation, TestThree) {
    s21::PolishNotation obj("-1");
    EXPECT_EQ(obj.get_postfix_entry(), "1- ");
}

TEST(TestPolishNotation, TestFour) {
    s21::PolishNotation obj("-1 + 1");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1 + ");
}

TEST(TestPolishNotation, TestFive) {
    s21::PolishNotation obj("-1 +- 1");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1- + ");
}

TEST(TestPolishNotation, TestSix) {
    s21::PolishNotation obj("-1 +- (1)");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1- 1 * + ");
}

TEST(TestPolishNotation, TestSeven) {
    s21::PolishNotation obj("-1 +- (-1)");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1- 1- * + ");
}

TEST(TestPolishNotation, TestEight) {
    s21::PolishNotation obj("-sin(-1)");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1- sin * ");
}

TEST(TestPolishNotation, TestNine) {
    s21::PolishNotation obj("- arcsin(-1)");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1- arcsin * ");
}

TEST(TestPolishNotation, TestTen) {
    s21::PolishNotation obj("sin(cos(tan(-0.12)))");
    EXPECT_EQ(obj.get_postfix_entry(), "0.12- tan cos sin ");
}

TEST(TestPolishNotation, TestEleven) {
    s21::PolishNotation obj("-(-(-(-(-(-5)))))");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1- 1- 1- 1- 5- * * * * * ");
}

TEST(TestPolishNotation, TestTwelve) {
    s21::PolishNotation obj("2 ^ 3 ^ 4 ^ 5");
    EXPECT_EQ(obj.get_postfix_entry(), "2 3 4 5 ^ ^ ^ ");
}

TEST(TestPolishNotation, TestFourteen) {
    s21::PolishNotation obj; 
    obj = ("(ln(0.01) - sqrt(0.912) *- cos(123)) mod(9.55)");
    EXPECT_EQ(obj.get_postfix_entry(), "0.01 ln 0.912 sqrt 1- 123 cos * * - 9.55 mod ");
}

TEST(TestPolishNotation, TestFifteen) {
    s21::PolishNotation obj("log(arctan(0.2) + 2 ^ -3 ^ sin(123.0))");
    EXPECT_EQ(obj.get_postfix_entry(), "0.2 arctan 2 3- 123.0 sin ^ ^ + log ");
}

TEST(TestPolishNotation, TestSexteen) {
    s21::PolishNotation obj("5 / 6 / 7 /- 8 ");
    EXPECT_EQ(obj.get_postfix_entry(), "5 6 / 7 / 8- / ");
}

TEST(TestPolishNotation, TestSeventeen) {
    EXPECT_THROW(s21::PolishNotation obj("av 1 "), std::invalid_argument);
}

TEST(TestPolishNotation, TestEighteen) {
    s21::PolishNotation obj("-1 -1 --1 +1");
    EXPECT_EQ(obj.get_postfix_entry(), "1- 1 - 1- - 1 + ");
}
