#include "stuinfo.h"

#include <QString>
stuinfo::stuinfo() {

}
stuinfo::stuinfo(QString name,long long number,QString age,QString gender,double score) {
    stu_name = name;
    stu_number = number;
    stu_age = age;
    stu_gender = gender;
    stu_score = score;
}
QString stuinfo::getname() {
    return stu_name;
}
long long stuinfo::getnumber() {
    return stu_number;
}
QString stuinfo::getage() {
    return stu_age;
}
QString stuinfo::getgender() {
    return stu_gender;
}

double stuinfo::getscore() {
    return stu_score;
}
void stuinfo::setname(QString name) {
    stu_name = name;
}
void stuinfo::setnumber(long long number) {
    stu_number = number;
}
void stuinfo::setage(QString age) {
    stu_age = age;
}
void stuinfo::setgender(QString gender) {
    stu_gender = gender;
}

void stuinfo::setscore(double score) {
    stu_score = score;
}
