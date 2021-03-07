#include "editdialog.h"
#include "ui_editdialog.h"
#include "node.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>

extern long long editNumber;

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    NODE pHead;
    QString name;//姓名
    long long number = editNumber;//考号
    //qDebug()<<number<<endl;
    QString age;//年龄
    QString gender;//性别
    double score;//学生成绩（0-100）
    pHead.InputStudent();
    bool pd = pHead.SearchStudent(name,number,age,gender,score);
    if(pd==false) {
        QMessageBox::about(NULL,"反馈","查无此人!");
        return;
    }
    ui->idlineEdit->setText(QString::number(number));
    ui->idlineEdit->setReadOnly(true);
    ui->namelineEdit->setText(name);
    ui->agelineEdit->setText(age);
    if(gender=="男") {
        ui->comboBox->setCurrentIndex(0);
    } else if(gender=="女") {
        ui->comboBox->setCurrentIndex(1);
    } else {
        ui->comboBox->setCurrentIndex(-1);
    }
    ui->gradelineEdit->setText(QString::number(score));

}

editDialog::~editDialog()
{
    delete ui;
}


void editDialog::on_editButton_clicked()
{
    if(ui->namelineEdit->text() == "" || ui->idlineEdit->text() == "" || ui->agelineEdit->text() == "" || ui->gradelineEdit->text() == "") {
        QMessageBox::about(NULL, "反馈", "存在空项");
        return;
    }
    NODE pHead;
    pHead.InputStudent();
    QString name = ui->namelineEdit->text().trimmed();
    long long number = ui->idlineEdit->text().toLongLong();
    QString age = ui->agelineEdit->text().trimmed();
    QString gender = ui->comboBox->currentIndex()==0 ? "男" : "女";
    double grade = ui->gradelineEdit->text().toDouble();
    pHead.ChangeStudent(name,number,age,gender,grade);
    pHead.OutputStudent();

    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->updateTableWidget();

    ui->idlineEdit->clear();
    ui->agelineEdit->clear();
    ui->namelineEdit->clear();
    ui->gradelineEdit->clear();
}
