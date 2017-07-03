#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablewindow.hpp"
#include <QFileDialog>

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

void MainWindow::on_actionAbrir_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Arquivo"),
                                                  "./",
                                                  tr("Arquivos CSV (*.csv)"));
}

void MainWindow::on_actionSair_triggered()
{
  this->close();
}

void MainWindow::on_actionSobre_triggered()
{
  //TODO
  //criar janela 'Sobre'
}
