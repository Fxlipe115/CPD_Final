#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablewindow.hpp"
#include <QFileDialog>
#include <QItemSelection>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  listModel = new QStringListModel(this);
  comboModel = new QStringListModel(this);

  ui->listView_columns->setModel(listModel);
  ui->comboBox->setModel(comboModel);

  connect(ui->listView_columns->selectionModel(),
        SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(selection_changed_handler(QItemSelection)));

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

  if(fileName != nullptr)
  {
    QFile f(fileName);
    if(f.open(QIODevice::ReadOnly))
    {
      QByteArray line = f.readLine().trimmed();
      QList<QByteArray> array = line.split(';');
      QStringList list;
      for(auto& elem : array)
      {
        list << elem;
      }
      listModel->setStringList(list);
    }
  }
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

void MainWindow::selection_changed_handler(const QItemSelection& selection)
{
  QModelIndexList indexes = ui->listView_columns->selectionModel()->selectedIndexes();
  QStringList list;
  for(auto& i : indexes)
  {
    list << i.data(Qt::DisplayRole).toString();
  }
  comboModel->setStringList(list);
  ui->comboBox->setCurrentIndex(0);
}
