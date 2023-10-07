#include "calculator_view.h"

#include "../controller/calculator_controller.h"
#include "qcustomplot.h"
#include "ui_calculator_view.h"
// for the data entry format
#include <QMainWindow>
#include <QString>
#include <cmath>  //fabs
#include <vector>

#include "../model/calculate_credit.h"
#include "../model/calculate_deposit.h"
// Для ссылки
#include <QDesktopServices>
#include <QUrl>
// Для времени изменения цвета при ошибке
#include <QTimer>
// Для даты
#include <QDate>
#include <QDateEdit>
// size_t
#include <cstddef>

namespace s21 {

CalculatorView::CalculatorView(CalculatorController &other_processing,
                               QWidget *parent)
    : QMainWindow(parent),
      processing_(&other_processing),
      ui_(new Ui::CalculatorView) {
  ui_->setupUi(this);
  ConnectFunctions();
  ConnectOperators();
  ConnectConstant();
  ConnectNums();
  ConnectOtherPushButton();

  setFixedSize(498, 466);
}

CalculatorView::~CalculatorView() { delete ui_; }

void CalculatorView::ConnectOtherPushButton() {
  connect(ui_->pb_right_bracket, SIGNAL(clicked()), this,
          SLOT(ReadingRightBracket()));
  connect(ui_->pb_left_bracket, SIGNAL(clicked()), this,
          SLOT(ReadingLeftBracket()));
  connect(ui_->pb_credit_result, SIGNAL(clicked()), this,
          SLOT(GetCreditResult()));
  connect(ui_->deposit_result, SIGNAL(clicked()), this,
          SLOT(GetDepositResult()));
  connect(ui_->pb_delete_all, SIGNAL(clicked()), this, SLOT(ReadingDelete()));
  connect(ui_->pb_backspace, SIGNAL(clicked()), this, SLOT(ReadingErasing()));
  connect(ui_->pb_radical, SIGNAL(clicked()), this, SLOT(ReadingRadical()));
  connect(ui_->clear_graph, SIGNAL(clicked()), this, SLOT(ClearGraphics()));
  connect(ui_->add_graph, SIGNAL(clicked()), this, SLOT(CreateGraphics()));
  connect(ui_->pb_equally, SIGNAL(clicked()), this, SLOT(GetResult()));
  connect(ui_->pb_meow, SIGNAL(clicked()), this, SLOT(ReadingMeow()));
  connect(ui_->pb_exp, SIGNAL(clicked()), this, SLOT(ReadingExp()));
  connect(ui_->pb_mod, SIGNAL(clicked()), this, SLOT(ReadingMod()));
}

void CalculatorView::ConnectFunctions() {
  for (auto button : ui_->group_functions->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(ReadingFunctions()));
  }
}

void CalculatorView::ConnectOperators() {
  for (auto button : ui_->group_operators->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(ReadingOtherOperators()));
  }
  connect(ui_->pb_addition, SIGNAL(clicked()), this,
          SLOT(ReadingPlusOrMinus()));
  connect(ui_->pb_subtraction, SIGNAL(clicked()), this,
          SLOT(ReadingPlusOrMinus()));
}

void CalculatorView::ConnectConstant() {
  for (auto button : ui_->group_const->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(ReadingConst()));
  }
}

void CalculatorView::ConnectNums() {
  for (auto button : ui_->group_nums->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(ReadingNumbers()));
  }
  connect(ui_->pb_point, SIGNAL(clicked()), this, SLOT(ReadingPoint()));
}

void CalculatorView::ReadingPlusOrMinus() {
  if (output_.size() < kOutputMaxSize_) {
    if (mode_ == 6 || mode_ == 10) {
      ReadingErasing();
    }
    QPushButton *button = (QPushButton *)sender();
    output_ += button->text();
    ShowInUI();
    if (mode_ == 9) {
      mode_ = 10;
    } else {
      mode_ = 6;
    }
  }
}

void CalculatorView::ReadingOtherOperators() {
  if (output_.size() < kOutputMaxSize_) {
    if (!(mode_ > 5 && mode_ <= 7) && (mode_ < 9) && mode_ != 0) {
      if (mode_ == 5) {
        ReadingErasing();
      }
      QPushButton *button = (QPushButton *)sender();
      output_ += button->text();
      ShowInUI();
      mode_ = 5;
    }
  }
}

void CalculatorView::ReadingRightBracket() {
  if (mode_ < 9 && !(mode_ >= 5 && mode_ <= 7) && need_rb_ > 0) {
    if (output_.size() < kOutputMaxSize_) {
      output_ += ')';
      ShowInUI();
      mode_ = 8;
      --need_rb_;
    }
  }
}

void CalculatorView::ReadingLeftBracket() {
  if (mode_ < 9) {
    long long size_limit = kOutputMaxSize_;
    if ((mode_ >= 2 && mode_ <= 4) || (mode_ == 8)) {
      size_limit -= 1;
    }
    if (output_.size() < size_limit) {
      if (!ErasingZero() && size_limit == kOutputMaxSize_ - 1) {
        output_ += '*';
      }
      output_ += '(';
      ShowInUI();
      mode_ = 7;
      ++need_rb_;
    }
  }
}

void CalculatorView::ReadingFunctions() {
  long long limit_label = kOutputMaxSize_ - 3;
  QPushButton *button = (QPushButton *)sender();
  QString text_num = button->text();

  if (text_num[0] == 'a') {
    limit_label =
        (mode_ >= 5 && mode_ <= 7) ? kOutputMaxSize_ - 4 : kOutputMaxSize_ - 5;
  } else if (text_num[1] == 'n') {
    limit_label =
        (mode_ >= 5 && mode_ <= 7) ? kOutputMaxSize_ - 2 : kOutputMaxSize_ - 3;
  }

  if (output_.size() < limit_label && mode_ < 9) {
    if (!ErasingZero() && mode_ != 0 && (mode_ < 5 || mode_ == 8)) {
      output_ += '*';
    }
    output_ += text_num;
    output_ += '(';
    ShowInUI();
    mode_ = 7;
    ++need_rb_;
  }
}

void CalculatorView::ReadingNumbers() {
  if (output_.size() < kOutputMaxSize_ && mode_ != 9 && mode_ != 4) {
    QPushButton *button = (QPushButton *)sender();
    if (mode_ == 8) {
      output_ += '*';
    }
    output_ += button->text();
    ShowInUI();
    if (mode_ != 2 && mode_ != 3) {
      if (ErasingZero() && button->text() == '0') {
        mode_ = 1;
      } else if (mode_ == 10) {
        mode_ = 3;
      } else {
        mode_ = 2;
      }
    }
  }
}

void CalculatorView::ReadingRadical() {
  if (output_.size() < kOutputMaxSize_ - 4 && mode_ < 9) {
    if (!ErasingZero() && (mode_ < 5 || mode_ == 8)) {
      output_ += '*';
    }
    output_ += "sqrt(";
    ShowInUI();
    ++need_rb_;
    mode_ = 7;
  }
}

void CalculatorView::ReadingPoint() {
  if (output_.size() < kOutputMaxSize_) {
    if (mode_ == 1 || mode_ == 2) {
      output_ += '.';
      ShowInUI();
      mode_ = 3;
    }
  }
}

void CalculatorView::ReadingConst() {
  QPushButton *button = (QPushButton *)sender();
  long long time_limit =
      (button->text() == "pi") ? kOutputMaxSize_ - 1 : kOutputMaxSize_;
  if (output_.size() < time_limit && mode_ < 9) {
    if (ErasingZero() || (mode_ >= 4 && mode_ <= 8) || mode_ == 0) {
      if (mode_ == 4) {
        ReadingErasing();
      } else if (mode_ == 8) {
        output_ += '*';
      }
      output_ += button->text();
      ShowInUI();
      mode_ = 4;
    }
  }
}

void CalculatorView::ReadingErasing() {
  if (output_.size() == 0) {
    mode_ = 0;
  } else if (output_.size() > 0) {
    size_t need_to_erase = 1;
    if (output_.size() > 1 && output_[output_.size() - 1] == '(') {
      if (output_[output_.size() - 2] == 't') {
        need_to_erase = 5;
      } else if (EndOfFunction(output_[output_.size() - 2])) {
        need_to_erase = 4;
      }
      --need_rb_;
    } else if (LastIsLn() || LastIsPi()) {
      need_to_erase = 2;
    } else if (output_[output_.size() - 1] == ')') {
      ++need_rb_;
    }
    output_.chop(need_to_erase);
    if (output_.size() > 0 && EndOfFunction(output_[output_.size() - 1])) {
      output_.chop(need_to_erase);
    }
    CheckMode();
    ShowInUI();
  }
}

void CalculatorView::ReadingExp() {
  if (output_.size() < kOutputMaxSize_) {
    if (mode_ == 2 || mode_ == 3 || mode_ == 8) {
      output_ += "e";
      ShowInUI();
      mode_ = 9;
    }
  }
}

void CalculatorView::ReadingMod() {
  if (output_.size() < kOutputMaxSize_ && mode_ < 9) {
    if ((mode_ >= 2 && mode_ <= 4) || mode_ == 8) {
      if (mode_ == 4) {
        output_ += ' ';
      }
      output_ += "mod(";
      ShowInUI();
      ++need_rb_;
      mode_ = 7;
    }
  }
}

void CalculatorView::ReadingDelete() {
  output_.clear();
  ShowInUI();
  need_rb_ = mode_ = 0;
}

void CalculatorView::ReadingMeow() {
  QUrl url("https://www.youtube.com/watch?v=SaA_cs4WZHM&ab_channel=SteveIbsen");
  QDesktopServices::openUrl(url);
}

void CalculatorView::GetResult() {
  double value_x = ui_->value_x->text().toDouble();
  std::pair<bool, double> result =
      processing_->CalculatingPolishNotation(output_.toStdString(), value_x);
  if (!result.first) {
    if (std::isnan(result.second)) {
      ui_->output->setText("ERROR");
      output_.clear();
    } else if (std::isinf(result.second) && result.second < 0.0) {
      ui_->output->setText("-infinity");
      output_.clear();
    } else if (std::isinf(result.second)) {
      ui_->output->setText("infinity");
      output_.clear();
    } else {
      output_ = QString::number(result.second, 'g', 15);
      ShowInUI();
      CheckMode();
    }
  } else {
    FailView(ui_->output);
  }
}

void CalculatorView::CreateGraphics() {
  double x_min, x_max, y_min, y_max, eps;
  x_min = ui_->x_min->text().toDouble();
  x_max = ui_->x_max->text().toDouble();
  y_min = ui_->y_min->text().toDouble();
  y_max = ui_->y_max->text().toDouble();
  eps = ui_->eps->text().toDouble();
  if (x_max - x_min <= eps) {
    FailView(ui_->x_min);
    FailView(ui_->x_max);
  } else if (y_max - y_min <= eps) {
    FailView(ui_->y_min);
    FailView(ui_->y_max);
  } else if (processing_->CalculatingPolishNotation(output_.toStdString(), 0.0)
                 .first) {  // if there is an error in the expression
    FailView(ui_->add_graph);
  } else {
    QVector<double> x_data, y_data;
    for (double x = x_min, y = 0; x <= x_max; x += eps) {
      CalculateY(y, x);
      CheckingY(y);
      x_data.append(x);
      y_data.append(y);
    }
    QCPGraph *graph = ui_->my_graphic->addGraph();
    graph->setData(x_data, y_data);
    QColor color(rand() % 256, rand() % 256, rand() % 256);
    QCPScatterStyle scatter_style;                      // points
    scatter_style.setShape(QCPScatterStyle::ssCircle);  // form point - circle
    scatter_style.setPen(QPen(color));                  // outline color
    scatter_style.setBrush(QBrush(color));
    graph->setScatterStyle(scatter_style);
    QPen graph_pen;             // line
    graph_pen.setColor(color);  // color line
    graph_pen.setWidth(2);      // weight line
    graph->setPen(graph_pen);
    ui_->my_graphic->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                     QCP::iSelectPlottables);
    ui_->my_graphic->rescaleAxes();
    ui_->my_graphic->replot();
  }
}

void CalculatorView::ClearGraphics() {
  ui_->my_graphic->clearPlottables();
  ui_->my_graphic->replot();
}

// converting for credit
void CalculatorView::GetCreditResult() {
  CreditData input_data;
  input_data.amount_credit = ui_->credit_amount_value->text().toDouble();
  input_data.period_in_months = ui_->credit_period_value->text().toInt();
  input_data.procent =
      (ui_->credit_interest_rate_value->text().toDouble()) / 12;
  if (ui_->menu_period->currentIndex() != 0) {
    input_data.period_in_months *= 12;
  }
  bool annuity(false);
  if (ui_->credit_menu_type->currentIndex() == 0) {
    annuity = true;
  }
  ResultCredit output_data = processing_->Calculating(input_data, annuity);
  QString output_info;
  if (annuity) {
    output_info = QString::number(output_data.mounthly_payment_min, 'c', 2);
  } else {
    output_info = QString::number(output_data.mounthly_payment_max, 'c', 2);
    output_info += "...";
    output_info += QString::number(output_data.mounthly_payment_min, 'c', 2);
  }
  ui_->mounthly_payment_value->setText(output_info);
  ui_->overpayment_value->setText(
      QString::number(output_data.overpayment, 'c', 2));
  ui_->total_payout_value->setText(
      QString::number(output_data.full_amount, 'c', 2));
}

// converting for deposit
void CalculatorView::GetDepositResult() {
  DepositInput data;
  QDate begin_date = ui_->begin_date->date();
  QDate end_date = ui_->ending_date->date();
  data.amount = ui_->deposit_amount_value->text().toDouble();
  data.procent = ui_->deposit_interest_rate->text().toDouble();
  data.contribution = ui_->deposit_value->text().toDouble();
  data.withdrawal = ui_->deposit_withdrawal->text().toDouble();
  data.tax_rate = ui_->deposit_tax_rate->text().toDouble();
  data.days_of_the_year = QDate::isLeapYear(begin_date.year()) ? 366 : 365;
  data.period_capitalization = begin_date.daysTo(end_date);
  data.quantity_capitalization =
      ReturnQuantity(ui_->frequenct_mode->currentIndex(), data.days_of_the_year,
                     data.period_capitalization);
  data.quantity_contribution =
      ReturnQuantity(ui_->deposit_mode->currentIndex(), data.days_of_the_year,
                     data.period_capitalization);
  data.quantity_withdrawal =
      ReturnQuantity(ui_->withdrawal_mode->currentIndex(),
                     data.days_of_the_year, data.period_capitalization);
  data.capitalization = ui_->capitalization->isChecked();
  DepositOutput result = processing_->Calculating(data);
  ui_->accrued_interest_result->setText(
      QString::number(result.accrued_interest, 'c', 2));
  ui_->tax_result->setText(QString::number(result.tax, 'c', 2));
  ;
  ui_->total_amount_result->setText(
      QString::number(result.total_amount, 'c', 2));
}

size_t CalculatorView::ReturnQuantity(int mode_index, size_t day_of_the_year,
                                      size_t period_capitalization) {
  double how_much{0};     // how much in year
  if (mode_index == 0) {  // every day
    return period_capitalization;
  } else if (mode_index == 1) {  // every month
    how_much = day_of_the_year / 12;
  } else if (mode_index == 2) {  // quartet year
    how_much = day_of_the_year / 4;
  } else if (mode_index == 3) {  // year/2
    how_much = day_of_the_year / 2;
  } else {  // every year
    how_much = day_of_the_year;
  }
  how_much = period_capitalization / how_much;
  return (std::fabs(how_much) <= 1.0) ? 1 : how_much;
}

void CalculatorView::CalculateY(double &y, const double x) {
  if (ui_->open_value_x->isChecked()) {
    y = (processing_->CalculatingPolishNotation(
             ui_->value_x->text().toDouble()))
            .second;
  } else {
    y = (processing_->CalculatingPolishNotation(x)).second;
  }
}

void CalculatorView::CheckingY(double &y) {
  if (std::isinf(y) || std::isnan(y)) {
    y = std::numeric_limits<double>::quiet_NaN();
  }
}

bool CalculatorView::ErasingZero() noexcept {
  if (mode_ == 1) {
    output_.chop(1);
    return true;
  }
  return false;
}

bool CalculatorView::IsNum(QChar symbol) noexcept {
  return (symbol >= '0' && symbol <= '9');
}

bool CalculatorView::IsPoint(QChar symbol) noexcept { return symbol == '.'; }

bool CalculatorView::IsOperator(QChar symbol) noexcept {
  return symbol == '^' || symbol == '*' || symbol == '/';
}

bool CalculatorView::IsMinOrPlus(QChar symbol) noexcept {
  return symbol == '+' || symbol == '-';
}

bool CalculatorView::IsLetter(QChar symbol) noexcept {
  return symbol >= 'a' && symbol <= 'z';
}

bool CalculatorView::EndOfFunction(QChar symbol) noexcept {
  return (symbol == 'n' || symbol == 's' || symbol == 'd' || symbol == 'g' ||
          symbol == 'c');
}

bool CalculatorView::LastIsLn() noexcept {
  return (output_[output_.size() - 1] == 'n' &&
          output_[output_.size() - 2] == 'l');
}

bool CalculatorView::LastIsPi() noexcept {
  return (output_[output_.size() - 1] == 'i' &&
          output_[output_.size() - 2] == 'p');
}

void CalculatorView::CheckMode() noexcept {
  if (output_.size() == 0) {
    mode_ = 0;
  } else {
    SetModeBasedOnSymbol(output_[output_.size() - 1]);
  }
}

void CalculatorView::SetModeBasedOnSymbol(QChar symbol) noexcept {
  if (output_.size() && output_[output_.size() - 1] == '0') {
    mode_ = 1;
  } else if (symbol == '(') {
    mode_ = 7;
  } else if (symbol == ')') {
    mode_ = 8;
  } else if (IsMinOrPlus(symbol)) {
    if (output_.size() > 1 && output_[output_.size() - 2] == 'e') {
      mode_ = 10;
    } else {
      mode_ = 6;
    }
  } else if (IsOperator(symbol)) {
    mode_ = 5;
  } else if (IsNum(symbol) || IsPoint(symbol)) {
    CalculateModeForNumericSymbol();
  } else if (symbol == 'e') {
    mode_ = 9;
  } else {
    mode_ = 4;
  }
}

void CalculatorView::CalculateModeForNumericSymbol() noexcept {
  size_t i = output_.size() - 1;
  while (i != 0 && IsNum(output_[i])) --i;
  if (IsPoint(output_[i])) {
    mode_ = 3;
  } else {
    if (mode_ != 3) mode_ = 2;
  }
}

void CalculatorView::ShowInUI() {
  ui_->size_symbols->setText(QString::number(output_.size()));
  ui_->output->setText(output_);
}

void CalculatorView::FailView(QWidget *widget) {
  QString original_style = widget->styleSheet();  // Сохраняем исходный стиль
  QString new_style =
      "background-color: rgba(255, 0, 0, 0.3); color: palette(WindowText); "
      "border: 5px solid red; padding-top: 13px;";

  widget->setStyleSheet(new_style);

  QTimer::singleShot(100, [=]() { widget->setStyleSheet(original_style); });
}

}  // namespace s21
