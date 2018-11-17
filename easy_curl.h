//
// Created by wtxpwh on 2018/11/14.
//

#ifndef LOADER_EASY_CURL_H
#define LOADER_EASY_CURL_H


#include <string>

class easy_curl {


public:
    easy_curl(void);
    ~easy_curl(void);
    int http_post(const std::string & strUrl, const std::string & strParam, std::string & strResponse);
    int http_get(const std::string & strUrl, std::string & strResponse);

};


#endif //LOADER_EASY_CURL_H
