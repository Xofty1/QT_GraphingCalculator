#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->radioButton_radian->setChecked(true);
  QRegExpValidator* validator = new QRegExpValidator(this);  // NEW!!!
  validator->setRegExp(QRegExp(
      "[^\\s]*"));  // Регулярное выражение, которое не допускает пробелы
  ui->lineEdit_expression->setValidator(validator);
  cursorPos = expression.length();
  creditWindow = new CreditWindow();
  // подключаем к слоту запуска главного окна по кнопке во втором окне
  connect(creditWindow, &CreditWindow::mainWindow, this, &MainWindow::show);

  depositWindow = new DepositWindow();
  // подключаем к слоту запуска главного окна по кнопке во втором окне
  connect(depositWindow, &DepositWindow::mainWindow, this, &MainWindow::show);

  QPixmap pixmap1(":/img/icon-delete.png");
  ui->pushButton_backSpace->setIcon(QIcon(pixmap1));
  ui->pushButton_backSpace->setIconSize(QSize(40, 40));

  QPixmap pixmap2(":/img/chart.png");
  ui->pushButton_plot->setIcon(QIcon(pixmap2));
  ui->pushButton_plot->setIconSize(QSize(40, 40));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateExpressions(const QString& symbol) {
  //    expression.append(symbol);
  expression.insert(cursorPos, symbol);
  cursorPos += symbol.length();
  ui->lineEdit_expression->setText(expression);
}
void MainWindow::on_pushButton_0_clicked() { updateExpressions("0"); }

void MainWindow::on_pushButton_1_clicked() { updateExpressions("1"); }

void MainWindow::on_pushButton_2_clicked() { updateExpressions("2"); }

void MainWindow::on_pushButton_3_clicked() { updateExpressions("3"); }

void MainWindow::on_pushButton_4_clicked() { updateExpressions("4"); }

void MainWindow::on_pushButton_5_clicked() { updateExpressions("5"); }

void MainWindow::on_pushButton_6_clicked() { updateExpressions("6"); }

void MainWindow::on_pushButton_7_clicked() { updateExpressions("7"); }

void MainWindow::on_pushButton_8_clicked() { updateExpressions("8"); }
void MainWindow::on_pushButton_9_clicked() { updateExpressions("9"); }

void MainWindow::on_pushButton_backSpace_clicked() {
  cursorPos--;
  if (cursorPos >= 0) {
    expression.remove(cursorPos, 1);
    //    expression.chop(1);
    ui->lineEdit_expression->setText(expression);
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  expression = "";
  cursorPos = 0;
  ui->lineEdit_expression->setText(expression);
}

void MainWindow::on_pushButton_div_clicked() { updateExpressions("÷"); }

void MainWindow::on_pushButton_mult_clicked() { updateExpressions("×"); }

void MainWindow::on_pushButton_minus_clicked() { updateExpressions("-"); }

void MainWindow::on_pushButton_plus_clicked() { updateExpressions("+"); }

void MainWindow::on_pushButton_bracketLeft_clicked() { updateExpressions("("); }

void MainWindow::on_pushButton_bracketRight_clicked() {
  updateExpressions(")");
}

void MainWindow::on_pushButton_mod_clicked() { updateExpressions(" mod "); }

void MainWindow::on_pushButton_sin_clicked() { updateExpressions("sin("); }

void MainWindow::on_pushButton_cos_clicked() { updateExpressions("cos("); }

void MainWindow::on_pushButton_tan_clicked() { updateExpressions("tan("); }

void MainWindow::on_pushButton_log_clicked() { updateExpressions("log("); }

void MainWindow::on_pushButton_sqrt_clicked() { updateExpressions("sqrt("); }

void MainWindow::on_pushButton_asin_clicked() { updateExpressions("asin("); }

void MainWindow::on_pushButton_acos_clicked() { updateExpressions("acos("); }

void MainWindow::on_pushButton_atan_clicked() { updateExpressions("atan("); }

void MainWindow::on_pushButton_ln_clicked() { updateExpressions("ln("); }
void MainWindow::on_pushButton_point_clicked() { updateExpressions("."); }
void MainWindow::on_pushButton_degree_clicked() { updateExpressions("^"); }
void MainWindow::on_pushButton_x_clicked() { updateExpressions("x"); }

void MainWindow::on_pushButton_res_clicked() {
  QString expressionWork = expression;
  expressionWork.replace("\u00D7", "*");
  expressionWork.replace("\u00F7", "/");
  QByteArray exp = expressionWork.toUtf8();
  exp.append('\0');
  // Получаем указатель на данные в виде массива char*
  const char* charExp = exp.constData();
  if (isValidExpression(charExp, 0) && exp.length() != 1) {
    int measure = ui->radioButton_radian->isChecked();
    // 1 - радианы
    // 0 - градусы
    int token_count;
    Token* tokens = parse_expression(charExp, &token_count);
    if (tokens != nullptr) {
      int new_token_coutn = 0;
      Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
      int error = OK;
      double result =
          calculateExpression(g, new_token_coutn, measure, &error, 0);
      if (error == ZERO_DIV)
        QMessageBox::information(nullptr, "Ошибка", "Деление на 0");
      else if (error == TRIGONOM_ERROR)
        QMessageBox::information(
            nullptr, "Ошибка",
            "Неправильный аргумент тригонометрической функции");
      else if (error == BAD_ARGUMENT)
        QMessageBox::information(nullptr, "Ошибка",
                                 "Неправильный аргумент функции");
      else {
        ui->label_answer->setNum(result);
      }

      free(g);
      free(tokens);
    }
  } else {
    QMessageBox::information(nullptr, "Ошибка",
                             "Введены некорректные значения");
  }
}

void MainWindow::on_lineEdit_expression_textChanged() {
  ui->label_answer->setText("");
  expression = ui->lineEdit_expression->text();
  if (expression.length() > 255) {
    // Обрезаем текст до 255 символов
    expression = expression.left(255);

    // Устанавливаем обновленный текст
    ui->lineEdit_expression->setText(expression);
  }
}

void MainWindow::on_lineEdit_expression_editingFinished() {
  cursorPos = ui->lineEdit_expression->cursorPosition();
}

void MainWindow::on_radioButton_radian_clicked() {
  ui->label_answer->setText("");
}

void MainWindow::on_radioButton_degree_clicked() {
  ui->label_answer->setText("");
}

void MainWindow::on_pushButton_plot_clicked() {
  QString expressionWork = expression;
  expressionWork.replace("\u00D7", "*");
  expressionWork.replace("\u00F7", "/");
  QByteArray exp = expressionWork.toUtf8();
  exp.append('\0');
  // Получаем указатель на данные в виде массива char*
  const char* charExp = exp.constData();

  if (isValidExpression(charExp, 1) && exp.length() != 1) {
    int measure = ui->radioButton_radian->isChecked();
    // 1 - радианы
    // 0 - градусы
    int token_count;
    Token* tokens = parse_expression(charExp, &token_count);
    if (tokens != nullptr) {
      int new_token_coutn = 0;
      Token* g = toPostfixNotation(tokens, token_count, &new_token_coutn);
      bool ok = true;
      bool conversionError = false;

      int min_x = ui->spinBox_minX->text().toInt(
          &ok);  //Начало интервала, где рисуем график по оси Ox
      conversionError |= !ok;

      int max_x = ui->spinBox_maxX->text().toInt(
          &ok);  //Конец интервала, где рисуем график по оси Ox
      conversionError |= !ok;

      int min_y = ui->spinBox_minY->text().toInt(
          &ok);  //Начало интервала, где рисуем график по оси Ox
      conversionError |= !ok;

      int max_y = ui->spinBox_maxY->text().toInt(
          &ok);  //Конец интервала, где рисуем график по оси Ox
      conversionError |= !ok;

      if (ui->lineEdit_step->text() == "") ui->lineEdit_step->setText("0.1");
      double h = ui->lineEdit_step->text().toDouble(
          &ok);  //Шаг, с которым будем пробегать по оси Ox
      conversionError |= !ok;

      if (conversionError || min_x > max_x || h <= 0 || min_y > max_y) {
        QMessageBox::information(nullptr, "Ошибка",
                                 "Неправильно заданы условия для графика");
      } else {
        int N = static_cast<int>((max_x - min_x) / h + 1.0);
        QVector<double> x(N), y(N);  //Массивы координат точек
        int error = OK;
        //Вычисляем наши данные
        int i = 0;
        for (double X = min_x; i < N; X += h) {
          if (X < EPSILON && X > -EPSILON) X = EPSILON;
          x[i] = X;
          y[i] = calculateExpression(g, new_token_coutn, measure, &error, X);
          i++;
        }
        if (error == ZERO_DIV) {
          QMessageBox::information(nullptr, "Ошибка", "Деление на 0");
        } else if (error == TRIGONOM_ERROR)
          QMessageBox::information(
              nullptr, "Ошибка",
              "Неправильный аргумент тригонометрической функции");
        else if (error == BAD_ARGUMENT)
          QMessageBox::information(nullptr, "Ошибка",
                                   "Неправильный аргумент функции");
        else {
          ui->widget_plot->clearGraphs();  // Очистить все существующие графики

          QVector<double> xSegment, ySegment;
          double maxDiff = 30.0;
          int currentGraphIndex = 0;  // Индекс текущего графика
          for (int i = 0; i < x.size() - 1; ++i) {
            double diff = std::abs(y[i + 1] - y[i]);

            if (diff <= maxDiff) {
              xSegment << x[i];
              ySegment << y[i];
            } else {
              xSegment << x[i];
              ySegment << y[i];
              ui->widget_plot->addGraph();
              // Задаем данные для текущего графика
              ui->widget_plot->graph(currentGraphIndex)
                  ->setData(xSegment, ySegment);

              // Увеличиваем индекс текущего графика
              currentGraphIndex++;
              xSegment.clear();
              ySegment.clear();
            }
          }
          ui->widget_plot->addGraph();
          // Задаем данные для текущего графика
          ui->widget_plot->graph(currentGraphIndex)
              ->setData(xSegment, ySegment);
          ui->widget_plot->xAxis->setRange(min_x, max_x);  //Для оси Ox
          ui->widget_plot->yAxis->setRange(min_y, max_y);  //Для оси Oy

          //                    //И перерисуем график на нашем widget
          ui->widget_plot->replot();

          ui->widget_plot->setInteraction(QCP::iRangeZoom, true);
          ui->widget_plot->setInteraction(QCP::iRangeDrag, true);
        }

        free(g);
        free(tokens);
      }
    } else {
      QMessageBox::information(nullptr, "Ошибка",
                               "Введены некорректные значения");
    }
  } else {
    QMessageBox::information(nullptr, "Ошибка",
                             "Введены некорректные значения");
  }
}

void MainWindow::on_pushButton_toCredit_clicked() {
  creditWindow->show();  // Показываем второе окно
  this->close();         // Закрываем основное окно
}

void MainWindow::on_pushButton_toDeposit_clicked() {
  depositWindow->show();  // Показываем второе окно
  this->close();          // Закрываем основное окно
}

void MainWindow::on_pushButton_whoami_clicked() {
  QMessageBox::information(nullptr, "Школа 21", "Создано пиром suzymarg");
}
