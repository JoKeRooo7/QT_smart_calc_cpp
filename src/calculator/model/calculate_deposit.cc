#include "calculate_deposit.h"

#include <cmath>
#include <cstddef>

namespace s21 {

Deposit::Deposit(const DepositInput& load_other) { LoadData(load_other); }

Deposit& Deposit::operator=(const DepositInput& load_other) noexcept {
  LoadData(load_other);
  return *this;
}

void Deposit::LoadData(const DepositInput& load_other) noexcept {
  data_.amount = load_other.amount;
  data_.procent = load_other.procent;
  data_.contribution = load_other.contribution;
  data_.withdrawal = load_other.withdrawal;
  data_.tax_rate = load_other.tax_rate;
  data_.days_of_the_year = load_other.days_of_the_year;
  data_.quantity_capitalization =
      ZeroidDouble(load_other.quantity_capitalization);
  data_.quantity_contribution = ZeroidDouble(load_other.quantity_contribution);
  data_.quantity_withdrawal = ZeroidDouble(load_other.quantity_withdrawal);
  data_.period_capitalization = load_other.period_capitalization;
  data_.capitalization = load_other.capitalization;
}

DepositOutput Deposit::Calculate(const DepositInput& load_other) noexcept {
  LoadData(load_other);
  return Calculate();
}

DepositOutput Deposit::Calculate() noexcept {
  ZeroidResult();
  result_.total_amount = std::round(data_.amount * 100) / 100;
  double accrued_interest = 0;
  for (size_t i = 0, j = 0; i <= data_.period_capitalization; ++i, ++j) {
    if (i != 0 &&
        i % (data_.period_capitalization / data_.quantity_contribution) == 0) {
      result_.total_amount += data_.contribution;
    }
    if (i != 0 &&
        i % (data_.period_capitalization / data_.quantity_withdrawal) == 0) {
      result_.total_amount -= data_.withdrawal;
    }
    if (i % (data_.period_capitalization / data_.quantity_capitalization) ==
        0) {
      result_.accrued_interest = result_.total_amount;
      result_.accrued_interest *= std::round(data_.procent * 100) / 100;
      result_.accrued_interest *= j;
      result_.accrued_interest /= data_.days_of_the_year;
      result_.accrued_interest /= 100;
      result_.accrued_interest = result_.accrued_interest;
      accrued_interest += std::round(result_.accrued_interest * 100) / 100;
      j = 0;
      if (data_.capitalization) {
        // result_.total_amount -= 1; // this magic dont clear !
        result_.total_amount += result_.accrued_interest;
      }
    }
  }
  result_.accrued_interest = accrued_interest;
  Tax();
  return result_;
}

void Deposit::Tax() noexcept {
  double nalog_sum =
      1000000 * 0.075;  // ключевая ставка центробанка на 1 января
  if (result_.accrued_interest > nalog_sum) {
    result_.tax = result_.accrued_interest - nalog_sum;
    result_.tax *= data_.tax_rate / 100;
  }
}

void Deposit::ZeroidResult() noexcept {
  result_.accrued_interest = 0;
  result_.tax = 0;
  result_.total_amount = 0;
}

double Deposit::ZeroidDouble(double num) noexcept {
  if (std::fabs(num) <= 1) {
    num = 1;
  }
  return num;
}

}  // namespace s21
