#ifndef TABLEWINDOW_HPP
#define TABLEWINDOW_HPP

#include <QWidget>

namespace Ui {
  class TableWindow;
}

class TableWindow : public QWidget
{
    Q_OBJECT

  public:
    explicit TableWindow(QWidget *parent = 0);
    ~TableWindow();

  private:
    Ui::TableWindow *ui;
};

#endif // TABLEWINDOW_HPP
