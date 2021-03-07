#include "mainwindow.h"
#include "ui_mainwindow.h"

long long editNumber; //传递考号

bool getStuInfo(QVector<stuinfo> &allStuInfo) {
    QFile file("stuinfo.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream inp(&file);
    if(!file.isOpen()) {
        QMessageBox::about(NULL,"反馈","数据文件打开失败");
        return false;
    }
    while(!inp.atEnd()) {
        QString name;//姓名
        long long number;//考号
        QString age;//年龄
        QString gender;//性别
        double score;//学生成绩（0-100）
        inp>>name>>number>>age>>gender>>score;
        allStuInfo.push_back(stuinfo(name,number,age,gender,score));
    }
    allStuInfo.pop_back();
    file.close();
    return true;
}

void MainWindow::updateTableWidget() {
    ui->tableWidget->clearContents();
    QVector<stuinfo> allStuInfo;
    if(!getStuInfo(allStuInfo))
        return;
    if(allStuInfo.empty()) {
        QMessageBox::about(NULL,"反馈","没有考生信息");
        return;
    }

    ui->tableWidget->setRowCount(allStuInfo.size());

    for(int i = 0 ; i < allStuInfo.size() ; i++ ) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(allStuInfo[i].getnumber())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(allStuInfo[i].getname()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(allStuInfo[i].getgender()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(allStuInfo[i].getage()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(allStuInfo[i].getscore())));
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    auto temp = QMessageBox::information(this, "提示", "你是否要关闭此程序?", QMessageBox::Yes | QMessageBox::No);
    if (temp == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    QStringList headerText;
    QTableWidgetItem *headerItem;
    headerText<<"准考证号"<<"姓名"<<"性别"<<"年龄"<<"成绩";
    ui->tableWidget->setColumnCount(headerText.count());
    for(int i=0;i<ui->tableWidget->columnCount();i++) {
        headerItem=new QTableWidgetItem(headerText.at(i));
        QFont font=headerItem->font();
        font.setBold(true);
        font.setPointSize(12);
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Interactive);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    MainWindow::updateTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_Button_clicked()
{
    add_Dialog *new_add_dialog = new add_Dialog(this);
    new_add_dialog->setWindowTitle("添加考生信息");
    new_add_dialog->setModal(true);
    new_add_dialog->show();
}

void MainWindow::on_del_Button_clicked()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count >= 2 || count == 0) {
        QMessageBox::information(this, "提示", "请仅选择一个单元格！");
    } else {
        QTableWidgetItem *item = items.at(0);
        int row = item->row();
        QTableWidgetItem *numberItem = ui->tableWidget->item(row,0);
        QString text = numberItem->text();
        long long number=text.toLongLong();
        qDebug()<<number<<endl;
        auto temp = QMessageBox::information(this, "提示", "你是否要删除考号为"+QString::number(number)+"的数据?", QMessageBox::Yes | QMessageBox::No);
        if (temp == QMessageBox::Yes) {
            Node pHead;
            pHead.InputStudent();
            pHead.DeleteStudent(number);
            pHead.OutputStudent();
            this->updateTableWidget();
        }
        else {
        }
    }
}


void MainWindow::on_edit_Button_clicked()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count >= 2 || count == 0) {
        QMessageBox::information(this, "提示", "请仅选择一个单元格！");
    } else {
        QTableWidgetItem *item = items.at(0);
        int row = item->row();
        QTableWidgetItem *numberItem = ui->tableWidget->item(row,0);
        QString text = numberItem->text();
        long long number=text.toLongLong();
        qDebug()<<number<<endl;
        auto temp = QMessageBox::information(this, "提示", "你是否要修改考号为"+QString::number(number)+"的数据?", QMessageBox::Yes | QMessageBox::No);
        if (temp == QMessageBox::Yes) {
            editNumber = number;
            editDialog *new_editDialog = new editDialog(this);
            new_editDialog->setWindowTitle("修改考生信息");
            new_editDialog->setModal(true);
            new_editDialog->show();
        }
        else {
        }
        this->updateTableWidget();
    }
}

void MainWindow::on_find1_Button_clicked()
{
    QVector<stuinfo> allStuInfo;
    QString find = ui->name_lineEdit->text().trimmed();
    if(!getStuInfo(allStuInfo))
        return;
    if(allStuInfo.empty()) {
        QMessageBox::about(NULL,"反馈","没有考生信息");
        return;
    }
    QVector<stuinfo> stuInfo;

    QVector<stuinfo>::iterator iter;
    for (iter=allStuInfo.begin();iter!=allStuInfo.end();iter++) {
        if(iter->getname().contains(find, Qt::CaseSensitive)) {
            stuInfo.push_back(*iter);
        }
    }

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(stuInfo.size());

    for(int i = 0 ; i < stuInfo.size() ; i++ ) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(stuInfo[i].getnumber())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(stuInfo[i].getname()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(stuInfo[i].getgender()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(stuInfo[i].getage()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(stuInfo[i].getscore())));
    }
}

void MainWindow::on_find2_Button_clicked()
{
    QVector<stuinfo> allStuInfo;
    QString find = ui->name_lineEdit->text().trimmed();
    if(!getStuInfo(allStuInfo))
        return;
    if(allStuInfo.empty()) {
        QMessageBox::about(NULL,"反馈","没有考生信息");
        return;
    }
    QVector<stuinfo> stuInfo;

    QVector<stuinfo>::iterator iter;
    for (iter=allStuInfo.begin();iter!=allStuInfo.end();iter++) {
        if(iter->getname()==find) {
            stuInfo.push_back(*iter);
        }
    }

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(stuInfo.size());

    for(int i = 0 ; i < stuInfo.size() ; i++ ) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(stuInfo[i].getnumber())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(stuInfo[i].getname()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(stuInfo[i].getgender()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(stuInfo[i].getage()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(stuInfo[i].getscore())));
    }
}

void MainWindow::on_all_Button_clicked()
{
    MainWindow::updateTableWidget();
}


 void MainWindow::Table2Excel(QTableWidget *table,QString title)
 {
     QString fileName = QFileDialog::getSaveFileName(table, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xlsx)");
     if (fileName!="")
     {
         QAxObject *excel = new QAxObject;
         if (excel->setControl("Excel.Application")) //连接Excel控件
         {
             excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
             excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
             QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
             workbooks->dynamicCall("Add");//新建一个工作簿
             QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
             QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

             int i,j;
             //QTablewidget 获取数据的列数
             int colcount=table->columnCount();
              //QTablewidget 获取数据的行数
             int rowscount=table->rowCount();
             QAxObject *cell,*col;
             //标题行
             cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
             cell->dynamicCall("SetValue(const QString&)", title);
             cell->querySubObject("Font")->setProperty("Size", 18);
             //调整行高
             worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
             //合并标题行
             QString cellTitle;
             cellTitle.append("A1:");
             cellTitle.append(QChar(colcount - 1 + 'A'));
             cellTitle.append(QString::number(1));
             QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
             range->setProperty("WrapText", true);
             range->setProperty("MergeCells", true);
             range->setProperty("HorizontalAlignment", -4108);//xlCenter
             range->setProperty("VerticalAlignment", -4108);//xlCenter
             //列标题
             for(i=0;i<colcount;i++)
             {
                 QString columnName;
                 columnName.append(QChar(i  + 'A'));
                 columnName.append(":");
                 columnName.append(QChar(i + 'A'));
                 col = worksheet->querySubObject("Columns(const QString&)", columnName);
                 col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                 cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                 //QTableWidget 获取表格头部文字信息
                 columnName=table->horizontalHeaderItem(i)->text();
                 //QTableView 获取表格头部文字信息
                 cell->dynamicCall("SetValue(const QString&)", columnName);
                 cell->querySubObject("Font")->setProperty("Bold", true);
                 cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                 cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                 cell->setProperty("VerticalAlignment", -4108);//xlCenter
             }

            //数据区

            //QTableWidget 获取表格数据部分
             for(i=0;i<rowscount;i++){
                 for (j=0;j<colcount;j++)
                 {
                     worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
                 }
             }
             //画框线
             QString lrange;
             lrange.append("A2:");
             lrange.append(colcount - 1 + 'A');
             lrange.append(QString::number(table->rowCount() + 2));
             range = worksheet->querySubObject("Range(const QString&)", lrange);
             range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
             range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
             //调整数据区行高
             QString rowsName;
             rowsName.append("2:");
             rowsName.append(QString::number(table->rowCount() + 2));
             range = worksheet->querySubObject("Range(const QString&)", rowsName);
             range->setProperty("RowHeight", 20);
             workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
             workbook->dynamicCall("Close()");//关闭工作簿
             excel->dynamicCall("Quit()");//关闭excel
             delete excel;
             excel=NULL;
             if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
             {
                 QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
             }
         }
         else
         {
             QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
         }
     }
 }

void MainWindow::on_output_Button_clicked()
{
    Table2Excel(ui->tableWidget,"考试报名管理系统");
}
