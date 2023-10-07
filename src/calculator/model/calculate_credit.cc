#include "calculate_credit.h"

#include <cmath>

namespace s21 {

CalculateCredit::CalculateCredit(const CreditData& other) noexcept {
  LoadData(other);
}

void CalculateCredit::LoadData(const CreditData& other) noexcept {
  data_.amount_credit = other.amount_credit;
  data_.procent = other.procent;
  data_.period_in_months = other.period_in_months;
}

ResultCredit CalculateCredit::get_result() noexcept { return results_; }

ResultCredit CalculateCredit::Calculate(const CreditData& other,
                                        bool annuity) noexcept {
  LoadData(other);
  return Calculate(annuity);
}

ResultCredit CalculateCredit::Calculate(bool annuity) noexcept {
  if (annuity) {
    return CalculateAnnuityCredit();
  }
  return CalculateDifferentiatedCredit();
}

ResultCredit CalculateCredit::CalculateAnnuityCredit() noexcept {
  ZeroingTheResult();
  data_.procent /= 100;
  double k = data_.procent * std::pow(1 + data_.procent,
                                      data_.period_in_months);  // koefficient
  k = k / (std::pow(1 + data_.procent, data_.period_in_months) - 1);
  results_.mounthly_payment_max = k * data_.amount_credit;
  results_.mounthly_payment_max =
      std::round(results_.mounthly_payment_max * 100) / 100;
  results_.mounthly_payment_min = results_.mounthly_payment_max;
  results_.full_amount = results_.mounthly_payment_min * data_.period_in_months;
  results_.overpayment = results_.full_amount - data_.amount_credit;
  return results_;
}

ResultCredit CalculateCredit::CalculateDifferentiatedCredit() noexcept {
  ZeroingTheResult();
  data_.procent /= 100;
  double temp_overpayment = data_.amount_credit / data_.period_in_months;

  for (int i = 0; i < data_.period_in_months; i++) {
    if (i == 0) {
      results_.mounthly_payment_max =
          temp_overpayment +
          (data_.amount_credit - temp_overpayment * i) * data_.procent;
    } else if (i == data_.period_in_months - 1) {
      results_.mounthly_payment_min =
          temp_overpayment +
          (data_.amount_credit - temp_overpayment * i) * data_.procent;
    }
    results_.full_amount +=
        temp_overpayment +
        (data_.amount_credit - temp_overpayment * i) * data_.procent;
  }
  results_.overpayment = results_.full_amount - data_.amount_credit;
  return results_;
}

void CalculateCredit::ZeroingTheResult() noexcept {
  results_.full_amount = 0;
  results_.overpayment = 0;
  results_.mounthly_payment_max = 0;
  results_.mounthly_payment_min = 0;
}

}  // namespace s21
