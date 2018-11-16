//
// Created by wtxpwh on 2018/11/16.
//

#include "miner_stat.h"
#include <jsoncpp/json/json.h>

#include <string>
#include <iostream>

#include "common.h"

using namespace std;

miner_stat::miner_stat()
{
    hashrate = 0.0;
}
miner_stat::~miner_stat()
{

}

float miner_stat::gethashrate()
{
    string minerinfojson;
    int tsresp = 0;

    for (int j = 0; j < 10; ++j) {
        tsresp = curl.http_get("localhost:4067/summary", minerinfojson);
        if(tsresp != 0) {
            cout << "http get gup summary error!retry!" << endl;
            sleep(1000);
        }
        else
            break;
    }

    if (tsresp != 0)
        return 0;

    Json::Reader reader;
    Json::Value root;

    if(!reader.parse(minerinfojson, root, false)) {
        cout << "parse T-rex miner config error!\n" << endl;
        return 0;
    }

    cout << "get trex summary ok!" << endl;
    cout << minerinfojson << endl;

    return root["hashrate"].asFloat();
}

bool miner_stat::reboottrex()
{

    float hr = gethashrate();

    cout << "hashrate=" + to_string(hr) << endl;

    if(hr < (hashrate * 0.3)) {
        cout << "hashrate error! reboot!" << endl;
        return true;
    }

    if(hr > hashrate) {
        cout << "update hashrate!" + to_string(hashrate) + "to" + to_string(hr) << endl;
        hashrate = hr;
    }
    return false;
}