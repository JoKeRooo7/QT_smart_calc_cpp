#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_CALCULATE_CREDIT_H_
#define CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_CALCULATE_CREDIT_H_

namespace s21 {

// need date
struct CreditData {
  double amount_credit{0};
  double procent{0};  // procent in m
  int period_in_months{0};
};

// all res
struct ResultCredit {
  double full_amount{0};
  double overpayment{0};
  double mounthly_payment_max{0};
  double mounthly_payment_min{0};
};

class CalculateCredit {
 public:
  // amount credit , procent, perion in mounthly
  CalculateCredit() = default;
  CalculateCredit(const CalculateCredit& other) = default;
  CalculateCredit(CalculateCredit&& other) = default;
  ~CalculateCredit() = default;

  CalculateCredit& operator=(const CalculateCredit& other) = default;
  CalculateCredit& operator=(CalculateCredit&& other) = default;

  explicit CalculateCredit(const CreditData& other) noexcept;
  void LoadData(const CreditData& other) noexcept;
  ResultCredit Calculate(const CreditData& other, bool annuity) noexcept;
  ResultCredit Calculate(bool annuity) noexcept;
  ResultCredit get_result() noexcept;
  void ZeroingTheResult() noexcept;

 private:
  CreditData data_;
  ResultCredit results_;

  ResultCredit CalculateAnnuityCredit() noexcept;
  ResultCredit CalculateDifferentiatedCredit() noexcept;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_CALCULATE_CREDIT_H_
