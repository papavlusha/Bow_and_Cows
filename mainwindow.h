#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <unordered_set>
#include <QRandomGenerator>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include "records.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void start();
    void check();
    void show_records() {
       Records rec;
       rec.setModal(true);
       rec.exec();
    }
private:
    QVBoxLayout *global;
    QGridLayout *bar;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QTableWidget *gametable;
    QLineEdit *edit;
    QLabel *info;
    QLabel *enterRec;
    int number_ = {0};
};


#endif // MAINWINDOW_H
