#include "mimeinlinefile.h"

/* [1] Constructors and Destructors */

MimeInlineFile::MimeInlineFile(QFile *f)
    : MimeFile(f)
{
}

MimeInlineFile::~MimeInlineFile()
{}

/* [1] --- */


/* [2] Getters and Setters */

/* [2] --- */


/* [3] Protected methods */

void MimeInlineFile::prepare()
{
    this->header += "Content-Disposition: inline\r\n";

    /* !!! IMPORTANT !!! */
    MimeFile::prepare();
}

/* [3] --- */
