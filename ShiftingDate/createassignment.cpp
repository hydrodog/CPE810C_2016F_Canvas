/*Author:Yang Bai
 Source file of class "createassignment",
 if an entry is created, send back the "createassignmententry" object,
 which includes name,theme,expirationdate and assignemnt.
 And send back entryAdded signal.

 If an entry is deleted, delete the entry and send back entryRemoved signal.



*/
#include "createassignment.h"

createassignment::createassignment(QObject *parent) : QObject(parent)
{

}

createassignment::Entries createassignment::entries() const
{
    return m_entries;
}

createassignmententry *createassignment::createEntry()
{
    auto result=new createassignmententry(this);
    if(result!=nullptr)
    {
        m_entries.append(result);
        emit entryAdded(result);
    }
    return result;
}

bool createassignment::deleteEntry(createassignmententry *entry)
{
    if(m_entries.contains(entry)){
        emit entryRemoved(entry);
        m_entries.removeOne(entry);
        delete entry;
        return true;
    }
    return false;
}
