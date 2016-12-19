/*Author:Jing Li
  Header file of class "HOLIDAY"
  read file with the date of festivals,
  then judge if the date is weekend or a festival.

*/
#ifndef HOLIDAY_H
#define HOLIDAY_H
#include<QDate>
#include<QString>
#include<QMessageBox>
#include <QTextStream>
#include <QFile>
class Holiday
{
private:
    QDate m_date;
public:
    Holiday(QDate date);
    QString festival();
};
#endif // HOLIDAY_H
