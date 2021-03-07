#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include "add_dialog.h"
#include "stuinfo.h"
#include "node.h"
#include "editdialog.h"
#include <QStringList>
#include <QFont>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <QDebug>

#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void updateTableWidget();
    ~MainWindow();
    void Table2Excel(QTableWidget *table,QString title);

protected:
    void closeEvent(QCloseEvent*event);

private slots:
    void on_add_Button_clicked();

    void on_del_Button_clicked();

    void on_edit_Button_clicked();

    void on_find1_Button_clicked();

    void on_find2_Button_clicked();

    void on_all_Button_clicked();

    void on_output_Button_clicked();

private:
    Ui::MainWindow *ui;
    add_Dialog *add_dialog;
};
#endif // MAINWINDOW_H
