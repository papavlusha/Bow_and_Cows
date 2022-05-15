#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QFile>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextStream>
#include <QDebug>

class Records : public QDialog
{
    Q_OBJECT

public:
    explicit Records(QDialog *parent = nullptr);
private:
    QTableWidget *recTable;
    QHBoxLayout *list;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QDialog *parent = nullptr);
    void setMoves(int a) {
        movs_ = a;
    }
private slots:
    void  ok();
    void NO() {
        close();
    }
private:
    QHBoxLayout *HBox;
    QPushButton *OkButton;
    QLineEdit *enter;
    QPushButton *cancelButton;
    QLabel *inf;
    int movs_;
};


#endif // RECORDS_H
