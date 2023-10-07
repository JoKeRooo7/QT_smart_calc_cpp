#include "calculator_controller.h"

#include <QDebug>
#include <string>

#include "../model/calculate_credit.h"
#include "../model/calculate_deposit.h"
#include "../model/polish_notation.h"

namespace s21 {

CalculatorController::CalculatorController(Models& other_model) noexcept {
  calc_model_ = &other_model;
}

CalculatorController& CalculatorController::operator=(Models& other_model) {
  calc_model_ = &other_model;
  return *this;
}

std::pair<bool, double> CalculatorController::CalculatingPolishNotation(
    std::string str, const double value_x) {
  bool fail(false);
  double result(0.0);
  try {
    result = calc_model_->polish_text.get_result(str, value_x);
  } catch (const std::invalid_argument& err) {
    qDebug() << err.what();
    fail = true;
  }

  return std::make_pair(fail, result);
}

std::pair<bool, double> CalculatorController::CalculatingPolishNotation(
    const double value_x) {
  bool fail(false);
  double result(0.0);
  try {
    result = calc_model_->polish_text.get_result(value_x);
  } catch (const std::invalid_argument& err) {
    qDebug() << err.what();
    fail = true;
  }

  return std::make_pair(fail, result);
}

ResultCredit CalculatorController::Calculating(const CreditData& other,
                                               bool annuity) noexcept {
  return calc_model_->credit_results.Calculate(other, annuity);
}

DepositOutput CalculatorController::Calculating(
    const DepositInput& other) noexcept {
  return calc_model_->deposit_result.Calculate(other);
}

}  // namespace s21
