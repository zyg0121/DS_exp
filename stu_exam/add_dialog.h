#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class add_Dialog;
}

class add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_Dialog(QWidget *parent = nullptr);
    ~add_Dialog();
    void setTableWidget();

protected:
    void closeEvent(QCloseEvent*event);

private slots:
    void on_addButton_clicked();

private:
    Ui::add_Dialog *ui;


};

#endif // ADD_DIALOG_H
