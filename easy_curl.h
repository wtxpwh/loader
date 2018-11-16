//
// Created by wtxpwh on 2018/11/14.
//

#ifndef LOADER_EASY_CURL_H
#define LOADER_EASY_CURL_H


#include <string>


using namespace std;


class easy_curl {


public:
    easy_curl(void);
    ~easy_curl(void);
    int http_post(const string & strUrl, const string & strParam, string & strResponse);
    int http_get(const string & strUrl, string & strResponse);


    //int download_file(const string & strUrl, const string & strFile);

};


#endif //LOADER_EASY_CURL_H
