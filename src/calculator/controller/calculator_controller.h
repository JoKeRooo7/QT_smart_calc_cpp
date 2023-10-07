#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATOR_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_CALCULATOR_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include <string>

#include "../model/calculate_credit.h"
#include "../model/calculate_deposit.h"
#include "../model/polish_notation.h"

namespace s21 {

struct Models {
  PolishNotation polish_text;
  CalculateCredit credit_results;
  Deposit deposit_result;
};

class CalculatorController {
 public:
  explicit CalculatorController(Models& other_model) noexcept;

  CalculatorController& operator=(Models& other_model);

  std::pair<bool, double> CalculatingPolishNotation(std::string str,
                                                    const double value_x);
  std::pair<bool, double> CalculatingPolishNotation(const double value_x);
  ResultCredit Calculating(const CreditData& other, bool annuity) noexcept;
  DepositOutput Calculating(const DepositInput& other) noexcept;

 private:
  Models* calc_model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALCULATOR_CONTROLLER_CALCULATOR_CONTROLLER_H_
