//
// Created by wtxpwh on 2018/11/16.
//

#ifndef LOADER_MINER_STAT_H
#define LOADER_MINER_STAT_H

#include "easy_curl.h"


class miner_stat {

    easy_curl curl;

public:
    miner_stat();
    ~miner_stat();

    bool reboottrex();
    float gethashrate();

    float hashrate;

};


#endif //LOADER_MINER_STAT_H
