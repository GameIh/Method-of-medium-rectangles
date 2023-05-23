#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_KeyboardRadioButton_clicked();

    void on_FileRadioButton_clicked();

    void on_F1RadioButton_clicked();

    void on_F2RadioButton_clicked();

    void on_F3RadioButton_clicked();

    void on_FileInputPushButton_clicked();

    void on_CalculatePushButton_clicked();

private:
    Ui::MainWindow *ui;
    int FunctionFlag;
    double a,b,c,left,right;
    int N;
    double f(double);
    double pr_s();
    void plot();

};
#endif // MAINWINDOW_H
