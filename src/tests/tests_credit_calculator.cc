#include <gtest/gtest.h>

#include "calculate_credit.h" 

const double kEps = 0.01;
// https://calcus.ru/kreditnyj-kalkulyator

TEST(Credit, TestAnnuityOne) {
    s21::CalculateCredit calc;
    s21::CreditData input;
    input.amount_credit = 1369712.93;
    input.procent = 12.18/12;
    input.period_in_months = 32;
    s21::ResultCredit output = calc.Calculate(input, true);
    EXPECT_NEAR(output.full_amount, 1611053.76, kEps);
    EXPECT_NEAR(output.overpayment, 241340.83, kEps);
    EXPECT_NEAR(output.mounthly_payment_max, 50345.43, kEps);
}

TEST(Credit, TestDiffOne) {
    s21::CalculateCredit calc;
    s21::CreditData input;
    input.amount_credit = 1369712.93;
    input.procent = 12.18/12;
    input.period_in_months = 32;
    s21::ResultCredit output = calc.Calculate(input, false);
    EXPECT_NEAR(output.full_amount, 1599105.60 , kEps);
    EXPECT_NEAR(output.overpayment, 229392.67, kEps);
    EXPECT_NEAR(output.mounthly_payment_max, 56706.12, kEps);
    EXPECT_NEAR(output.mounthly_payment_min, 43237.98, kEps);
}

TEST(Credit, TestAnnuityTwo) {
    s21::CalculateCredit calc;
    s21::CreditData input;
    input.amount_credit = 91239123912.12;
    input.procent = 0.1/12;
    input.period_in_months = 12;
    s21::ResultCredit output = calc.Calculate(input, true);
    EXPECT_NEAR(output.full_amount, 91288552654.32, kEps);
    EXPECT_NEAR(output.overpayment, 49428742.20, kEps);
    EXPECT_NEAR(output.mounthly_payment_max, 7607379387.86, kEps);
}

TEST(Credit, TestDiffTwo) {
     s21::CalculateCredit calc;
    s21::CreditData input;
    input.amount_credit = 91239123912.12;
    input.procent = 0.1/12;
    input.period_in_months = 12;
    s21::ResultCredit output = calc.Calculate(input, false);
    EXPECT_NEAR(output.full_amount, 91288545104.24, kEps);
    EXPECT_NEAR(output.overpayment, 49421192.12, kEps);
    EXPECT_NEAR(output.mounthly_payment_max,7610863586.34, kEps);
    EXPECT_NEAR(output.mounthly_payment_min, 7603893931.04, kEps);
}

TEST(Credit, TestAnnuityThree) {
    s21::CalculateCredit calc;
    s21::CreditData input;
    input.amount_credit = 12345;
    input.procent = 93.4/12;
    input.period_in_months = 99;
    s21::ResultCredit output = calc.Calculate(input, true);
    EXPECT_NEAR(output.full_amount, 95181.57, kEps);
    EXPECT_NEAR(output.overpayment, 82836.57, kEps);
    EXPECT_NEAR(output.mounthly_payment_max, 961.43, kEps);
}

TEST(Credit, TestDiffThree) {
    s21::CalculateCredit calc;
    s21::CreditData input;
    input.amount_credit = 12345;
    input.procent = 93.4/12;
    input.period_in_months = 99;
    s21::ResultCredit output = calc.Calculate(input, false);
    EXPECT_NEAR(output.full_amount, 60387.63, kEps);
    EXPECT_NEAR(output.overpayment, 48042.63, kEps);
    EXPECT_NEAR(output.mounthly_payment_max, 1085.55, kEps);
    EXPECT_NEAR(output.mounthly_payment_min, 134.40, kEps);
}