#include "tablewindow.hpp"
#include "ui_tablewindow.h"

TableWindow::TableWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TableWindow)
{
  ui->setupUi(this);
}

TableWindow::~TableWindow()
{
  delete ui;
}
