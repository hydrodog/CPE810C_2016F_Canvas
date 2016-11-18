/*Author:Yang Bai

 Header file of class "createassignmentcontroller",
 handle the signal of createEntry and deleteEntry.

*/

#ifndef CREATEASSIGNMENTCONTROLLER_H
#define CREATEASSIGNMENTCONTROLLER_H

#include"createassignment.h"
#include <QObject>

class createassignmentcontroller : public QObject
{
    Q_OBJECT
public:
    explicit  createassignmentcontroller(createassignment *createAssignment, QObject *parent = 0);

    createassignmententry *createEntry();
    bool deleteEntry(createassignmententry *entry);

signals:

public slots:

private:
    createassignment *m_createassignment;

};

#endif // CREATEASSIGNMENTCONTROLLER_H
