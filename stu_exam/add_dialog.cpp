#include "add_dialog.h"
#include "ui_add_dialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "stuinfo.h"
#include "mainwindow.h"
add_Dialog::add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_Dialog)
{
    ui->setupUi(this);
}

add_Dialog::~add_Dialog()
{
    delete ui;
}

void add_Dialog::on_addButton_clicked()
{
    ui->namelineEdit->setFocus();
    QString name = ui->namelineEdit->text().trimmed();
    long long number = ui->idlineEdit->text().toLongLong();
    QString age = ui->agelineEdit->text().trimmed();
    QString gender = ui->comboBox->currentIndex()==0 ? "男" : "女";
    double grade = ui->gradelineEdit->text().toDouble();

    if(ui->namelineEdit->text()=="" || ui->idlineEdit->text()=="" || ui->agelineEdit->text()=="" ||  ui->gradelineEdit->text()=="") {
        QMessageBox::about(NULL, "反馈", "存在空项");
        return;
    }
    if(grade < 0 || grade >100) { //判断分数合理性
        QMessageBox::about(NULL, "反馈", "分数需在0~100区间");
        return;
    }
    QFile file("stuinfo.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
    if(!file.isOpen()) {
        QMessageBox::about(NULL, "反馈", "数据文件打开失败");
        return;
    }
    QTextStream out(&file);
    out<<name<<" "<<number<<" "<<age<<" "<<gender<<" "<<grade<<"\n";
    file.close();
    QMessageBox::about(NULL,"反馈","成功保存");

    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->updateTableWidget();

    ui->namelineEdit->clear();
    ui->idlineEdit->clear();
    ui->agelineEdit->clear();
    ui->gradelineEdit->clear();
}

void add_Dialog::closeEvent(QCloseEvent *event) {
    auto temp = QMessageBox::information(this, "提示", "你是否要关闭?", QMessageBox::Yes | QMessageBox::No);
    if (temp == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}
