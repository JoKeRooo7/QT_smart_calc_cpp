#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_CALCULATE_DEPOSIT_H_
#define CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_CALCULATE_DEPOSIT_H_

#include <cstddef>

namespace s21 {

struct DepositInput {
  double amount{0};
  double procent{0};  // in year
  double contribution{0};
  double withdrawal{0};
  double tax_rate{0};
  size_t days_of_the_year{365};
  size_t period_capitalization{0};    // in days
  size_t quantity_capitalization{0};  // how much in year
  size_t quantity_contribution{0};
  size_t quantity_withdrawal{0};
  bool capitalization{false};
};

struct DepositOutput {
  double accrued_interest;
  double tax;
  double total_amount;
};

class Deposit {
 public:
  Deposit() = default;
  Deposit(const Deposit& other) = default;
  Deposit(Deposit&& other) = default;
  explicit Deposit(const DepositInput& load_other);
  ~Deposit() = default;

  Deposit& operator=(const Deposit& other) = default;
  Deposit& operator=(Deposit&& other) = default;
  Deposit& operator=(const DepositInput& load_other) noexcept;
  void LoadData(const DepositInput& load_other) noexcept;
  DepositOutput Calculate(const DepositInput& load_other) noexcept;
  DepositOutput Calculate() noexcept;

 private:
  DepositInput data_;
  DepositOutput result_;
  void ZeroidResult() noexcept;
  double ZeroidDouble(double num) noexcept;
  void Tax() noexcept;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALCULATOR_MODEL_CALCULATE_DEPOSIT_H_
