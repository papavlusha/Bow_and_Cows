#include "records.h"
#include "ui_records.h"

Records::Records(QDialog *parent) :
    QDialog(parent)
{
    QFile file("champions");
    if(!file.open(QIODevice::ReadOnly))
        qDebug()<< "Error";
    list =  new QHBoxLayout(this);
    recTable = new QTableWidget;
    recTable->setColumnCount(2);
    recTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Имя Пользователя"));
    recTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Ходов"));
    recTable->setColumnWidth(0,250);
    recTable->setColumnWidth(1,53);
    list->addWidget(recTable);
    while (!file.atEnd()) {
            QString line = file.readLine();
            QString numpart;
            if(!line.isEmpty()) {
                recTable->insertRow(recTable->rowCount());
                for(int i = 0; i < line.size() ;i++) {
                     if (line[i] =='$') {
                     line.remove(0,i+1);
                     break;
                     }
                      numpart+=line[i];
                 }
                  recTable->setItem(recTable->rowCount()-1, 1, new QTableWidgetItem(numpart));
                  numpart.clear();
                  for(int i = 0; i < line.size() ;i++) {
                       if (line[i+1] ==' ') {
                       break;
                       }
                      numpart+=line[i];
                   }
                  numpart.remove(numpart.size()-1,1);
                 recTable->setItem(recTable->rowCount()-1, 0, new QTableWidgetItem(numpart));
                QString bib = line;
            }
            setMinimumSize(350,400);
            setMaximumSize(500,700);
    }
    recTable->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    recTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recTable->sortByColumn(1,Qt::SortOrder::AscendingOrder);
    file.close();
    setLayout(list);
    setWindowTitle("Таблица Рекордов");
}

Dialog::Dialog(QDialog *parent)
    : QDialog (parent)
{

inf = new QLabel;
inf->setText("Введите свой никнейм");
HBox = new QHBoxLayout;
OkButton = new QPushButton;
cancelButton = new QPushButton;
enter = new QLineEdit;
OkButton->setText("ОК");
cancelButton->setText("Отмена");
enter = new QLineEdit;
HBox->addWidget(inf);
HBox->addWidget(enter);
HBox->addWidget(OkButton);
HBox->addWidget(cancelButton);
setLayout(HBox);
connect(OkButton,SIGNAL(clicked()),this,SLOT(ok()));
connect(cancelButton,SIGNAL(clicked()),this,SLOT(NO()));
setFixedSize(450,60);
setWindowTitle("Рекорды");
}

void  Dialog::ok() {
    if(enter->text() == "") {
        close();
    }
    QFile file("champions");
    if(!file.open(QIODevice::Append))
        qDebug() << "error";
    QTextStream writeStream(&file);
    writeStream << QString::number(movs_)  << "$" << enter->text() << endl;
    file.close();
    close();
}
