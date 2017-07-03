#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablewindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_gerar_clicked()
{
  //TODO
  //gerar tabela com colunas selecionadas na lista
  //ordenada pela coluna selecionada no combobox
  TableWindow* tw = new TableWindow(this);
  tw->show();
}
