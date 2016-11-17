/*Author:Jing Li,Yang Bai

  defined name,theme,expirationdate
and assignment in it. These are things we need when create an assignment.




*/
#ifndef CREATEASSIGNMENTENTRY_H
#define CREATEASSIGNMENTENTRY_H

#include <QObject>
#include<QString>
#include<QDate>
#include<QStringList>
#include <QMessageBox>


class createassignmententry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QDate expirationdate READ expirationdate WRITE setExpirationdate NOTIFY expirationdateChanged)
    Q_PROPERTY(QString assignment READ assignment WRITE setAssignment NOTIFY assignmentChanged)

public:
    explicit createassignmententry(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString theme() const;
    void setTheme(const QString &theme);

    QDate expirationdate() ;
    void setExpirationdate( const QDate &expirationdate);

    QString assignment() const;
    void setAssignment(const QString &assignment);

signals:
    void nameChanged();
    void themeChanged();
    void expirationdateChanged();
    void assignmentChanged();

public slots:

private:
    QString m_name;
    QString m_theme;
    QDate m_expirationdate;
    QString m_assignment;

};

#endif // CREATEASSIGNMENTENTRY_H
