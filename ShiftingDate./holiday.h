#ifndef HOLIDAY_H
#define HOLIDAY_H
#include<QDate>
#include<QString>
#include<QMessageBox>
class Holiday
{
private:
    QDate m_date;
public:
    Holiday(QDate date);
    QString festival();
};
#endif // HOLIDAY_H
