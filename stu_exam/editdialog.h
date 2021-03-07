#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(QWidget *parent = nullptr);
    ~editDialog();

private slots:
    void on_editButton_clicked();

private:
    Ui::editDialog *ui;
};

#endif // EDITDIALOG_H
