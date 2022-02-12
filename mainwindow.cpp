#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

size_t size_square(size_t n) {
    size_t k = 1;
    size_t res = 1;
    while (res < n) {
        k++;
        res = k*k;
    }
    return k;
}

std::vector<int> MainWindow::magic_square_even(int n) {
    int **arr = new int *[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new int [n];

    int k = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = k;
            k++;
        }
    }
    //Метод Рауз-Болла
    for (int i = 0; i < n / 2; i++) {
        std::swap(arr[i][i], arr[n-i-1][n-i-1]);
        std::swap(arr[i][n-i-1], arr[n-i-1][i]);
    }

    std::vector<int> res;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res.push_back(arr[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        delete [] arr[i];
    }
    delete [] arr;

    return res;
}

std::vector<int> MainWindow::magic_square_odd(int n)
{
    int **arr = new int *[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new int [n];

    int nsqr = n * n;
    int i = 0, j = n / 2;

    for (int k = 1; k <= nsqr; ++k) {
        arr[i][j] = k;
        i--;
        j++;
        if (k % n == 0) {
            i += 2;
            --j;
        }
        else {
            if (j == n) {
                j -= n;
            }
            else if (i < 0) {
                i += n;
            }
        }
    }

    std::vector<int> res;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res.push_back(arr[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        delete [] arr[i];
    }
    delete [] arr;

    return res;
}

void MainWindow::encode_magic_square(int n, std::vector<int> magic_square)
{
    QString enter_line = ui->enterLine->text();
    int nsqr = n * n;
    QString res = "";
    for (int i = 0; i < nsqr; i++) {
        if (magic_square[i] > enter_line.size())
            res += " ";
        else
            res += enter_line[magic_square[i] - 1];
    }
    ui->resLine->setText(res);
}

void MainWindow::decode_magic_square(int n, std::vector<int> magic_square)
{
    QString enter_line = ui->enterLine->text();
    int nsqr = n * n;
    QString res = "";
    int i, k = 1;
    for (i = 0; i < nsqr; ++i) {
        if (magic_square[i] == k) {
            res += enter_line[i];
            ++k;
            i = -1;
        }
    }
    ui->resLine->setText(res);
}

void MainWindow::click_start_button() {
    if (ui->enterLine->text().isEmpty()) {
        QMessageBox::information(this, "Ошибка", "Введите текст, который нужно зашифровать/расшифровать.");
        return;
    }
    if (!ui->encodeButton->isChecked() && !ui->decodeButton->isChecked()) {
        QMessageBox::information(this, "Ошибка", "Выберите действие.");
        return;
    }
    ui->enterLine->setReadOnly(true);
    ui->resLine->setText("");
    std::vector<int> magic_square;
    int n = size_square(ui->enterLine->text().size());

    if (n % 2 == 0)
        magic_square = magic_square_even(n);
    else
        magic_square = magic_square_odd(n);

    if (ui->encodeButton->isChecked())
        encode_magic_square(n, magic_square);
    else
        decode_magic_square(n, magic_square);

    QMessageBox::information(this, "Успех", "Программа успешно выполнена!");
    ui->enterLine->setReadOnly(false);
}
