#ifndef HTTPDOWNLOADER_HPP
#define HTTPDOWNLOADER_HPP
#include <string>



class HTTPDownloader {
private:
    void* curl;
public:
    // download a file using HTTP GET and store in in a std::string
    HTTPDownloader();
    ~HTTPDownloader();   
    std::string download(const std::string& url);

};
#endif
