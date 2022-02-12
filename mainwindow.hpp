#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

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


public slots:
    void click_start_button();

private:
    Ui::MainWindow *ui;
    std::vector<int> magic_square_even(int);
    std::vector<int> magic_square_odd(int);

    void encode_magic_square(int n, std::vector<int>);
    void decode_magic_square(int n, std::vector<int>);
};
#endif // MAINWINDOW_HPP
