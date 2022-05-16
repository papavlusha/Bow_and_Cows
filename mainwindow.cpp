#include "mainwindow.h"
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto w = new QWidget;
    global =  new QVBoxLayout(this);
    bar = new QGridLayout;
    button1 = new QPushButton;
    button2 = new QPushButton;
    button3 = new QPushButton;
    edit = new QLineEdit;
    info = new QLabel;
    info->setAlignment(Qt::AlignCenter);
    enterRec = new QLabel;
    info->setText("Игра не начата");
    button1->setText("Новая Игра");
    button2->setText("Рекорды");
    button3->setText("Проверить");
    enterRec->setText("Введите число");
    gametable = new QTableWidget;
    gametable->setColumnCount(2);
    gametable->setHorizontalHeaderItem(0,new QTableWidgetItem("Число"));
    gametable->setHorizontalHeaderItem(1,new QTableWidgetItem("Результат"));
    gametable->setColumnWidth(0,231);
    gametable->setColumnWidth(1,231);
    bar->addWidget(button1,0,0);
    bar->addWidget(info,0,1);
    bar->addWidget(button2,0,2);
    bar->addWidget(enterRec, 1, 0);
    bar->addWidget(edit, 1,1);
    bar->addWidget(button3, 1, 2);
    global->addLayout(bar);
    global->addWidget(gametable);
    setCentralWidget(w);
    w->setLayout(global);
    setMaximumSize(505,900);
    setMinimumSize(505,505);
    button3->setEnabled(false);
    edit->setReadOnly(true);
    gametable->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    gametable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(button1,SIGNAL(clicked()),this,SLOT(start()));
    connect(button3,SIGNAL(clicked()),this,SLOT(check()));
    connect(edit,SIGNAL(textChanged()),this,SLOT(valid()));
    connect(button2,SIGNAL(clicked()),this,SLOT(show_records()));
}

void MainWindow::start() {
    number_ = 0;
    info->setText("Игра идет");
    button3->setEnabled(true);
    edit->setReadOnly(false);
    edit->setInputMask("9999;X");
    edit->clear();
    QRandomGenerator *now;
    now = QRandomGenerator::global();
    std::unordered_set<int> num;
    for(int i=0;i<100;i++)
    while(num.size() != 4) {
        int x = now->bounded(0,10);
        num.insert(x);
    }
    int i = 1;
    for (auto now: num) {
        number_+=now*i;
        i*=10;
    }
    while (gametable->rowCount() > 0) {
        gametable->removeRow(0);
    }
}

void MainWindow::check() {
    QString value = QString::number(number_);
    QString inEdit = edit->text();
    if(inEdit.size() < 4) {
        QMessageBox::warning(this,"Ошибочка","число должно быть в диапазоне от 0123 до 9876");
        return;
    }
    if(value.size() == 3) {
        value = '0' + value;
    }
    edit->clear();
    int mas[10] = {0};
    int right_all = 0;
    int right_only = 0;
    for(int i = 0; i < 4; i++) {
       mas[inEdit[i].digitValue()]++;
    }
    for(int i =0; i < 10; i++) {
        if(mas[i] > 1) {
            QMessageBox::warning(this,"Ошибочка","Все цифры должны быть различны");
            return;
        }
    }
    for (int i = 0 ; i < 4 ; i++) {
        if(inEdit[i] == value[i]) right_all++;
        if(value.contains(inEdit[i])) right_only++;
    }
    right_only -= right_all;
    gametable->insertRow(gametable->rowCount());
    gametable->setItem(gametable->rowCount()-1, 0, new QTableWidgetItem(inEdit));
    QString setter = "Быков:" + QString::number(right_all)
            + " Коров:" + QString::number(right_only);
    gametable->setItem(gametable->rowCount()-1, 1, new QTableWidgetItem(setter));
    if(right_all == 4) {
        edit->setReadOnly(true);
        info->setText("Игра пройдена");
        if (gametable->rowCount() < 10) {
            Dialog r;
            r.setMoves(gametable->rowCount());
            r.setModal(true);
            r.exec();
        }
        edit->setReadOnly(true);
    }

}






