/*Author:Jing Li
  Source file of class"createassignmententry",create currentDatetime automaticly,
  when set the datetime,judge that if it is holiday by using the holiday class.
 *Author:Yang Bai
 if name,theme, date or assignment changed,
return the signal that they has changed.



*/
#include "createassignmententry.h"
#include"mainwindow.h"
#include"holiday.h"
createassignmententry::createassignmententry(QObject *parent) : QObject(parent),m_expirationdate( QDate::currentDate ())
{

}

QString createassignmententry::name() const
{
    return m_name;
}

void createassignmententry::setName(const QString &name)
{
    if( m_name!=name){
        m_name=name;
        emit nameChanged();
    }
    m_name = name;
}

QString createassignmententry::theme() const
{
    return m_theme;
}

void createassignmententry::setTheme(const QString &theme)
{
    if(m_theme!=theme){
        m_theme=theme;
        emit themeChanged();
    }
}

QDate createassignmententry::expirationdate()
{
   /* int x =m_expirationdate.dayOfWeek();
    if(x==6||x==7)
    {

   QMessageBox a;
    a.setText("it is weekend,no class!");
    a.exec();
  return m_expirationdate;
    }
   else
    return m_expirationdate;
    */
    Holiday x(m_expirationdate);
    QString y=x.festival();
    if(y=="")
        return m_expirationdate;
    else
    {
        QMessageBox a;
        a.setText(y);
        a.exec();
        return m_expirationdate;
    }

}

void createassignmententry::setExpirationdate(const QDate &expirationdate)
{
    if(m_expirationdate!=expirationdate)
    {

     m_expirationdate = expirationdate;
    emit expirationdateChanged();
    }
}

QString createassignmententry::assignment() const
{
    return m_assignment;
}

void createassignmententry::setAssignment(const QString &assignment)
{
    if(m_assignment!=assignment){
        m_assignment=assignment;
        emit assignmentChanged();
    }
}
