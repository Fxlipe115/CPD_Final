#include "tablewindow.hpp"
#include "ui_tablewindow.h"

TableWindow::TableWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TableWindow)
{
  ui->setupUi(this);
}

TableWindow::~TableWindow()
{
  delete ui;
}

void TableWindow::on_pushButton_sair_clicked()
{
    this->close();
}
