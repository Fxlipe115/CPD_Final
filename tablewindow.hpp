#ifndef TABLEWINDOW_HPP
#define TABLEWINDOW_HPP

#include <QDialog>

namespace Ui {
  class TableWindow;
}

class TableWindow : public QDialog
{
    Q_OBJECT

  public:
    explicit TableWindow(QWidget *parent = 0);
    ~TableWindow();

  private slots:
    void on_pushButton_sair_clicked();

  private:
    Ui::TableWindow *ui;
};

#endif // TABLEWINDOW_HPP
