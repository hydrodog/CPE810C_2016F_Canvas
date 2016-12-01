#include <QtWidgets/QApplication>
#include "smtpclient.h"
#include "mimepart.h"
#include "mimehtml.h"
#include "mimeattachment.h"
#include "mimemessage.h"
#include "mimetext.h"
#include "mimeinlinefile.h"
#include "mimefile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // This is a first demo application of the SmtpClient for Qt project

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and the password
    // for smtp authentification.

    smtp.setUser("your_email_address@gmail.com");
    smtp.setPassword("your_password");

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;

    message.setSender(new EmailAddress("zma4@stevens.edu.com", "Zheao Ma"));
    message.addRecipient(new EmailAddress("zma4@stevens.edu.com", "Zheao Ma"));
    message.setSubject("SmtpClient for Qt - Demo");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText("Hi,\nThis is a simple email message.\n");

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();

}
