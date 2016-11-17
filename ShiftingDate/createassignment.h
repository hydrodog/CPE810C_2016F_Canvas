/*Author:Yang Bai
Header file of class "createassignment"
  This class represents our assignment itself. It has methods to create new entries, list all
  existing ones and delete entries again.
 defined createEntry() and deleteEntry() functions
 defined entryAdded and entryRemoved signals.


*/
#ifndef CREATEASSIGNMENT_H
#define CREATEASSIGNMENT_H
#include"createassignmententry.h"

#include <QObject>
#include<QList>

class createassignment : public QObject
{
    Q_OBJECT
public:

    typedef QList<createassignmententry*>Entries;

    explicit createassignment(QObject *parent = 0);

    Entries entries() const;

    createassignmententry* createEntry();
    bool deleteEntry(createassignmententry *entry);

signals:

    void entryAdded(createassignmententry *entry);
    void entryRemoved(createassignmententry *entry);

public slots:

private:
    Entries m_entries;

};

#endif // CREATEASSIGNMENT_H
