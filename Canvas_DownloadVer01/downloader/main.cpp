#include <QCoreApplication>
#include "downloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QUrl b("https://cluster31-files.instructure.com/files/1030~1634706/download?download_frd=1&verifier=mqAPXweuk9mvraPasMY8UYFEn3WDQmfEGL8MGs21");
    const QUrl c("https://cluster31-files.instructure.com/users/1030~22347/files/1030~1300290/my%20files/unfiled/01print.cc?download=1&inline=1&sf_verifier=b88b4f149c0c03fba5bb55bb4a7ff400&ts=1460676490&user_id=10300000000011895&verifier=ibOOdBKMM6JAHY7WMOPDFVX6fuZNO5o3MT1goxPI");
    const QUrl f("https://sit.instructure.com/files/2241844/download?download_frd=1&verifier=MbpaZFujQG8sN075oD4ZYk1nzNnlBY1SywykvRlu");

    QByteArray data;
    //data.append("username=mhe6&password=Stevens586341");
    Downloader d;
  //  d.sendpostrequest(b,data);
    d.doDownload(f);


    return a.exec();
}
