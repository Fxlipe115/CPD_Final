#include "tablewindow.hpp"
#include "ui_tablewindow.h"
#include <QFileDialog>

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

void TableWindow::on_pushButton_export_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Salvar"),
                             "./",
                             tr("Arquivos CSV (*.csv)"));
}
