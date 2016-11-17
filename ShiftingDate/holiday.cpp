/*Author:Jing Li
  Header file of class "HOLIDAY"
  read a txt file with the date of festivals,
  then judge if the date is weekend or a festival.

*/
#include "holiday.h"

Holiday::Holiday(QDate date):m_date(date)
{

}
QString Holiday::festival()
{
    int month=m_date.month();
    int day=m_date.day();
    int x =m_date.dayOfWeek();
    QString s="";
    if(x==6||x==7)
        return s="It is weekend, No class!";

    QFile file("calendar.txt" );
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox b;
        b.setText("error,no files");
        b.exec();
    }
          QTextStream stream( &file );

          QString line;
          while (!stream.atEnd())
             {
              line = stream.read(2);
              QString str=line;
              int m=str.toInt();//read month from file
              line = stream.read(3);
              str=line;
              int d=str.toInt();//read day from file
              line = stream.readLine();//read festival from file
              if(month==m&&day==d)
              {

               s="It is "+line+",No class!";
              }
             }

              file.close();
              return s;

    /* now these messages below are in the "calendar.txt"files.
     *
    if(month==1&&day==1)
        return s="It is New Year's Day, No class!";
    if(month==1&&day==15)
        return s="Martin Luther King,Jr.Day No class!";
    if(month==2&&day==12)
        return s="It is Lincoln's Birthday, No class!";
    if(month==2&&day==14)
        return s="It is St. Valentine's Day, No class!";
    if(month==2&&day==18)
        return s="It is Washington's Birthday, No class!";
    if(month==3&&day==17)
        return s="It is St. Patrick's Day, No class!";
    if(month==5&&day==28)
        return s="It is Memorial Day, No class!";
    if(month==7&&day==4)
        return s="It is Independence Day, No class!";
    if(month==9&&day==3)
        return s="It is Labor Day, No class!";
    if(month==10&&day==12)
        return s="It is Columbus Day, No class!";
    if(month==11&&day==1)
        return s="It is Halloween, No class!";
    if(month==11&&day==23)
        return s="It is Thanksgiving Day, No class!";
    if(month==12&&day==25)
        return s="It is Christmas, No class!";
    else
        return s="";
        */


}
