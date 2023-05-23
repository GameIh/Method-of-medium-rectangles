#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->ResultGroupBox->setVisible(false);
    ui->widget->setVisible(false);
    ui->KeyboardRadioButton->setChecked(true);
    ui->KeyboardRadioButton->clicked(true);
    this->setFixedHeight(400);
    this->setFixedWidth(513);
    FunctionFlag=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_KeyboardRadioButton_clicked()
{
    ui->FileGroupBox->setVisible(false);
}


void MainWindow::on_FileRadioButton_clicked()
{
    ui->FileGroupBox->setVisible(true);
}


void MainWindow::on_F1RadioButton_clicked()
{
    FunctionFlag=1;
}


void MainWindow::on_F2RadioButton_clicked()
{
    FunctionFlag=2;
}


void MainWindow::on_F3RadioButton_clicked()
{
    FunctionFlag=3;
}


void MainWindow::on_FileInputPushButton_clicked()
{
    if (ui->FileNamelineEdit->text()=="")
    {
        QMessageBox msgBox;
        msgBox.setText("Введите название файла");
        msgBox.exec();
        return;
    }
    QFile file(ui->FileNamelineEdit->text());
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox msgBox;
        msgBox.setText("Файл не был найден");
        msgBox.exec();
        return;
    }
    QString str;
    ui->ALineEdit->setText(file.readLine());
    ui->BLineEdit->setText(file.readLine());
    ui->CLineEdit->setText(file.readLine());
    ui->LeftLineEdit->setText(file.readLine());
    ui->RightLineEdit->setText(file.readLine());
    ui->NLineEdit->setText(file.readLine());
    file.close();
}

void MainWindow::plot()
{
    QVector<double> x(N), y(N); // initialize with entries 0..100
    double h = (right - left) / N; // Шаг
    double yMax=f(left);
    double yMin=yMax;
    for (int i=0; i<N; ++i)
    {
      x[i] = left+i*h; // x goes from -1 to 1
      y[i] = f(x[i]); // let's plot a quadratic function
      if (y[i]>yMax)
          yMax=y[i];
      if (y[i]<yMin)
          yMin=y[i];
    }
    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(left-1, right+1);
    ui->widget->yAxis->setRange(yMin, yMax);
    ui->widget->replot();
}

void MainWindow::on_CalculatePushButton_clicked()
{
    if (ui->ALineEdit->text()=="" || ui->BLineEdit->text()==""|| ui->CLineEdit->text()==""||
            ui->LeftLineEdit->text()==""|| ui->RightLineEdit->text()==""|| ui->NLineEdit->text()=="")
    {
        QMessageBox msgBox;
        msgBox.setText("Введите все данные");
        msgBox.exec();
        return;
    }
    if (FunctionFlag==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Не выбрана функция");
        msgBox.exec();
        return;
    }
    a=ui->ALineEdit->text().toDouble();
    b=ui->BLineEdit->text().toDouble();
    c=ui->CLineEdit->text().toDouble();
    left=ui->LeftLineEdit->text().toDouble();
    right=ui->RightLineEdit->text().toDouble();
    N=ui->NLineEdit->text().toInt();
    if (left>=right||left<-1000||right>1000)
    {
        QMessageBox msgBox;
        msgBox.setText("Неправильный интервал");
        msgBox.exec();
        return;
    }
    if (N<1 || N>500)
    {
        QMessageBox msgBox;
        msgBox.setText("Неправильное количество разбиений");
        msgBox.exec();
        return;
    }
    double integral=pr_s();
    plot();
    N*=100;
    double integralTrue=pr_s();
    double AbsEps=qAbs(integral-integralTrue);
    double RelativeEps=(AbsEps/integral)*100;
    this->setFixedHeight(480);
    this->setFixedWidth(513);
    ui->ResultGroupBox->setVisible(true);
    ui->widget->setVisible(true);
    ui->CloseLineEdit->setText(QString::number(integral));
    ui->CorrectLineEdit->setText(QString::number(integralTrue));
    ui->AbsLineEdit->setText(QString::number(AbsEps));
    ui->RelativeLineEdit->setText(QString::number(RelativeEps));
}

double MainWindow::f(double x)
{
    if (FunctionFlag==1)
    {
        return a*qPow(x,3)+b*x+c;
    }
    if (FunctionFlag==2)
    {
        return a*qSin(x+b)+c;
    }
    if (FunctionFlag==3)
    {
        return a*qLn(x+b)+c;
    }
}

double MainWindow::pr_s()
{
    double h = (right - left) / N; // Шаг
    double sum = 0.0;

    // Вычисление суммы значений функции в средних точках прямоугольников
    for (int i = 0; i < N; i++) {
         double x = left + (i + 0.5) * h; // Средняя точка прямоугольника
         sum += f(x);
    }

    double integral = h * sum;
    return integral;
}
