#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATOR_VIEW_CALCULATOR_VIEW_H_
#define CPP3_SMARTCALC_V2_0_1_CALCULATOR_VIEW_CALCULATOR_VIEW_H_

#include <QMainWindow>
#include <QString>
#include <cstddef>
#include <vector>

#include "../controller/calculator_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalculatorView;
}
QT_END_NAMESPACE

// in my project - pb is push button
namespace s21 {

class CalculatorView : public QMainWindow {
  Q_OBJECT

 public:
  CalculatorView(CalculatorController &other_processing,
                 QWidget *parent = nullptr);
  ~CalculatorView();

 private slots:

  // connect
  void ConnectOtherPushButton();
  void ConnectFunctions();
  void ConnectOperators();
  void ConnectConstant();
  void ConnectNums();
  // reading
  void ReadingPlusOrMinus();
  void ReadingOtherOperators();
  void ReadingRightBracket();
  void ReadingLeftBracket();
  void ReadingFunctions();
  void ReadingNumbers();
  void ReadingRadical();
  void ReadingPoint();
  void ReadingConst();
  void ReadingErasing();
  void ReadingExp();
  void ReadingMod();
  void ReadingDelete();
  void ReadingMeow();
  // result
  void GetResult();
  // create gtaphics
  void CreateGraphics();
  void ClearGraphics();
  // credit calc
  void GetCreditResult();
  // deposit calc
  void GetDepositResult();

 private:
  CalculatorController *processing_ = nullptr;
  Ui::CalculatorView *ui_;
  QString output_;
  /* mode input
   *  in calc was
   *  0 - any input is open
   *  1 - first num equal '0' (this none)
   *  2 - number
   *  3 - decimal number
   *  4 - was const
   *  5 - operators
   *  6 - was + or -
   *  7 - left bracket
   *  8 - right bracket
   *  9 - EXP
   * 10 - EXP with sight
   */
  size_t mode_{0};
  size_t need_rb_{0};  // Need right brackets
  static const int kOutputMaxSize_ = 255;

  size_t ReturnQuantity(int mode_index, size_t day_of_the_year,
                        size_t period_capitalization);
  void CalculateY(double &y, const double x);
  void CheckingY(double &y);
  bool ErasingZero() noexcept;
  bool IsNum(QChar symbol) noexcept;
  bool IsPoint(QChar symbol) noexcept;
  bool IsOperator(QChar symbol) noexcept;
  bool IsMinOrPlus(QChar symbol) noexcept;
  bool IsLetter(QChar symbol) noexcept;
  bool LastIsLn() noexcept;
  bool LastIsPi() noexcept;
  bool EndOfFunction(QChar symbol) noexcept;
  void SetModeBasedOnSymbol(QChar symbol) noexcept;
  void CalculateModeForNumericSymbol() noexcept;
  void CheckMode() noexcept;
  void ShowInUI();
  void FailView(QWidget *widget);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALCULATOR_VIEW_CALCULATOR_VIEW_H_
