#ifndef STUINFO_H
#define STUINFO_H
#include <QString>

class stuinfo {

    private:
        QString stu_name;//姓名
        long long stu_number;//考号
        QString stu_age;//年龄
        QString stu_gender;//性别
        double stu_score;//学生成绩（0-100）
    public:
        stuinfo();
        //inp>>name>>number>>age>>gender>>score;
        stuinfo(QString name,long long number,QString age,QString gender,double score);
        //获取
        QString getname() ;
        long long getnumber() ;
        QString getage() ;
        QString getgender();
        double getscore() ;
        //设置
        void setname(QString name);
        void setnumber(long long number);
        void setage(QString age);
        void setgender(QString gender);
        void setscore(double score) ;

};

#endif // STUINFO_H
