#include "mimehtml.h"

/* [1] Constructors and Destructors */

MimeHtml::MimeHtml(const QString &html) : MimeText(html)
{
    this->cType = "text/html";
}

MimeHtml::~MimeHtml() {}

/* [1] --- */


/* [2] Getters and Setters */

void MimeHtml::setHtml(const QString & html)
{
    this->text = html;
}

const QString & MimeHtml::getHtml() const
{
    return text;
}


/* [2] --- */


/* [3] Protected methods */

void MimeHtml::prepare()
{
    /* !!! IMPORTANT !!! */
    MimeText::prepare();
}

/* [3] --- */
