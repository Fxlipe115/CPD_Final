#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QItemSelection>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButton_gerar_clicked();

    void on_actionAbrir_triggered();

    void on_actionSair_triggered();

    void on_actionSobre_triggered();

    void selection_changed_handler(const QItemSelection& selection);

  private:
    Ui::MainWindow *ui;
    QStringListModel* listModel;
    QStringListModel* comboModel;
};

#endif // MAINWINDOW_H
