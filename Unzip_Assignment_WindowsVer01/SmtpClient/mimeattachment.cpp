#include "mimeattachment.h"
#include <QFileInfo>

/* [1] Constructors and Destructors */

MimeAttachment::MimeAttachment(QFile *file)
    : MimeFile(file)
{
}
MimeAttachment::MimeAttachment(const QByteArray& stream, const QString& fileName): MimeFile(stream, fileName)
{

}

MimeAttachment::~MimeAttachment()
{
}

/* [1] --- */


/* [2] Protected methods */

void MimeAttachment::prepare()
{
    this->header += "Content-disposition: attachment\r\n";

    /* !!! IMPORTANT !!! */
    MimeFile::prepare();
}

/* [2] --- */
