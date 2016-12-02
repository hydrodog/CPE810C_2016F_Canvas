#include "mimetext.h"

/* [1] Constructors and Destructors */

MimeText::MimeText(const QString &txt)
{
    this->text = txt;
    this->cType = "text/plain";
    this->cCharset = "utf-8";
    this->cEncoding = _8Bit;
}

MimeText::~MimeText() { }

/* [1] --- */


/* [2] Getters and Setters */

void MimeText::setText(const QString & text)
{
    this->text = text;
}

const QString & MimeText::getText() const
{
    return text;
}

/* [2] --- */


/* [3] Protected Methods */

void MimeText::prepare()
{
    this->content.clear();
    this->content.append(text);

    /* !!! IMPORTANT !!! */
    MimePart::prepare();
}

/* [3] --- */
