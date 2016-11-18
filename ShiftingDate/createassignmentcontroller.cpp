/*Author:Yang Bai

 If we get createEntry signal, we will set original name "New Entry..."

*/


#include "createassignmentcontroller.h"

createassignmentcontroller::createassignmentcontroller(
        createassignment *createAssignment, QObject *parent):
    QObject(parent),
    m_createassignment(createAssignment)
{
    Q_ASSERT(createAssignment!=nullptr);
 }
createassignmententry *createassignmentcontroller::createEntry(){
        auto result = m_createassignment->createEntry();
        if(result!=nullptr){
            result->setName(tr("New Entry..."));
        }
        return result;
}

bool createassignmentcontroller::deleteEntry(createassignmententry *entry){
    return m_createassignment->deleteEntry(entry);
}
