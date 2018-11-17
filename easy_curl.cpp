//
// Created by wtxpwh on 2018/11/14.
//

#include "easy_curl.h"
#include <iostream>

#include <boost/network/protocol/http.hpp>

using namespace boost::network;



easy_curl::easy_curl(void)
{

}

easy_curl::~easy_curl(void)
{

}

int easy_curl::http_post(const std::string & strUrl, const std::string & strParam, std::string & strResponse)
{
    int res = 0;

    try {
        http::client client;
        http::client::request request(strUrl);
        http::client::response response = client.post(request, strParam);

        strResponse = body(response);

    } catch (std::exception& e) {
        std::cout << "http_post error! error info: " << e.what() << std::endl;
        res = 1;
    }

    return res;
}

int easy_curl::http_get(const std::string & strUrl, std::string & strResponse)
{
    int res = 0;

    try {
        http::client client;
        http::client::request request(strUrl);
        http::client::response response = client.get(request);
        strResponse = body(response);
    } catch (std::exception& e) {
        std::cout << "http_get error! error info: " << e.what() << std::endl;
        res = 1;
    }

    return res;
}

/*
static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    string* str = dynamic_cast<string*>((string *)lpVoid);
    if (NULL == str || NULL == buffer)
    {
        return -1;
    }

    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}


int easy_curl::http_post(const string & strUrl, const string & strParam, string & strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if (NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strParam.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

int easy_curl::http_get(const string & strUrl, string & strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if (NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

*/