#include <gtest/gtest.h>

#include "calculate_deposit.h" 


const double kEps = 0.01;
/* https://calcus.ru/kalkulyator-vkladov
* correctly counts up to whole c only in the current year
* 10/9/23 - 10/10/23 - 30 day
* 10/9/23 - 10/12/23 - 91 day
*/
TEST(Depois, TestOneWithoutCapitalization) {
    s21::DepositInput data;
    data.amount = 100000000;
    data.procent = 60;
    data.tax_rate = 13;
    data.days_of_the_year = 365;
    data.period_capitalization = 91;
    data.quantity_capitalization = 91;
    s21::Deposit calc;
    s21::DepositOutput result = calc.Calculate(data);
    EXPECT_NEAR(result.accrued_interest, 14958903.96 , 1);
    EXPECT_NEAR(result.tax, 1934907.51, 1);
    EXPECT_NEAR(result.total_amount, 100000000.00, 1);
}

TEST(Depois, TestOneWithCapitalization) {
    s21::DepositInput data;
    data.amount = 1000;
    data.procent = 3.5;
    data.tax_rate = 13;
    data.days_of_the_year = 365;
    data.period_capitalization = 30;
    data.quantity_capitalization = 30;
    data.capitalization = true;
    s21::Deposit calc;
    s21::DepositOutput result = calc.Calculate(data);
    EXPECT_NEAR(result.accrued_interest, 3, 1);
    EXPECT_NEAR(result.tax, 0, 1);
    EXPECT_NEAR(result.total_amount, 1002.88, 1);
}

TEST(Depois, TestTwoWithoutCapitalization) {
    s21::DepositInput data;
    data.amount = 33333;
    data.procent = 33;
    data.tax_rate = 13;
    data.days_of_the_year = 365;
    data.period_capitalization = 30;
    data.quantity_capitalization = 30;
    s21::Deposit calc;
    s21::DepositOutput result = calc.Calculate(data);
    EXPECT_NEAR(result.accrued_interest, 904.2, 1);
    EXPECT_NEAR(result.tax, 0, 1);
    EXPECT_NEAR(result.total_amount, 33333, 1);
}

TEST(Depois, TestTwoWithCapitalization) {
    s21::DepositInput data;
    data.amount = 33333;
    data.procent = 33;
    data.tax_rate = 13;
    data.days_of_the_year = 365;
    data.period_capitalization = 30;
    data.quantity_capitalization = 30;
    data.capitalization = true;
    s21::Deposit calc;
    s21::DepositOutput result = calc.Calculate(data);
    EXPECT_NEAR(result.accrued_interest, 916.07, 1);
    EXPECT_NEAR(result.tax, 0, 1);
    EXPECT_NEAR(result.total_amount, 34249.05, 1);
}

TEST(Depois, TestThreeWithoutCapitalization) {
    s21::DepositInput data;
    data.amount = 12354;
    data.procent = 12.3;
    data.tax_rate = 13;
    data.days_of_the_year = 365;
    data.period_capitalization = 30;
    data.quantity_capitalization = 30;
    s21::Deposit calc;
    s21::DepositOutput result = calc.Calculate(data);
    EXPECT_NEAR(result.accrued_interest, 124.8, 1);
    EXPECT_NEAR(result.tax, 0, 1);
    EXPECT_NEAR(result.total_amount, 12354, 1);
}

TEST(Depois, TestThreeWithCapitalization) {
    s21::DepositInput data;
    data.amount = 12354;
    data.procent = 12.3;
    data.tax_rate = 13;
    data.days_of_the_year = 365;
    data.period_capitalization = 30;
    data.quantity_capitalization = 30;
    data.capitalization = true;
    s21::Deposit calc;
    s21::DepositOutput result = calc.Calculate(data);
    EXPECT_NEAR(result.accrued_interest, 125.50, 1);
    EXPECT_NEAR(result.tax, 0, 1);
    EXPECT_NEAR(result.total_amount, 12479.51, 1);
}
