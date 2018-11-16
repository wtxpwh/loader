#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>
#include <boost/process.hpp>
#include "miner_config.h"

#include "miner_stat.h"

#include "common.h"

using namespace std;

namespace bp = ::boost::process;

string decodealgo(int _algo)
{
    vector<string> algolist = { "cc", "cc", "cc", "cc", "cc",
                         "c11", "cc", "cc", "cc", "cc", "cc", "cc",
                         "cc", "cc", "cc", "cc", "hmq1725", "cc", "cc", "cc",
                         "hsr", "cc", "cc", "cc", "lyra2z", "cc", "cc", "cc",
                         "cc", "cc", "cc", "cc", "cc", "cc", "cc", "cc",
                         "cc", "cc", "cc", "cc", "skunk", "cc", "cc", "tribus", "bitcore", "cc",
                         "cc", "cc", "cc", "cc", "x17", "cc", "cc", "cc", "cc",
                         "cc", "cc", "cc", "cc", "cc", "phi", "cc", "cc", "cc",
                         "cc", "polytimos", "sonoa", "x16r", "x16s", "cc", "cc", "cc", "balloon","bcd","renesis" };
    //HSR 20, LBRY 21, LYRA2Z 24, phi2 25, SKUNK, 40,phi 60. x16r 67,  bcd 73
    if (_algo > 74)
        return algolist[0];
    else
        return algolist[_algo];
}


int main() {

    Json::Reader reader;
    Json::Value root;
    ifstream cfg("./config.json", ifstream::binary);
    if(!reader.parse(cfg, root, false)) {
        cout << "parse config file error!\n" << endl;
        return 0;
    }
    cfg.close();

    int uid = root["uid"].asInt();
    string worker = root["worker"].asString();

    miner_config minercfg(uid, worker);
    miner_stat ms;

    do{

        if(!minercfg.getminercfg()) {
            cout << "minercfg getminercfg error!\n" << endl;
            return 0;
        }

        string pool = "stratum+tcp://" + minercfg.cfggproxy + ".yunpools.com:" + to_string(minercfg.getrandomport());
        string user = minercfg.cfgusernameid +"."+ minercfg.workid;

        string exec{"./t-rex"};
        vector<string> args;
        //args.push_back("t-rex");
        args.push_back("-a");
        args.push_back(decodealgo(stoi(minercfg.cfgalgo)));
        args.push_back("-o");
        args.push_back(pool);
        args.push_back("-u");
        args.push_back(user);
        args.push_back("-p");
        args.push_back("x");
        args.push_back("--exit-on-cuda-error");

        bp::child cp(
                bp::args(args),
                bp::exe(exec)
        );


        int a=0, b=0;
        while(!cp.wait_for(std::chrono::milliseconds(1000))) {
            a++,b++;

            if(a==60) {
                a=0;
                if(ms.reboottrex()) {
                    cp.terminate();
                    break;
                }
            }

            if(b==600) {
               b=0;
                if(minercfg.isnewconfig()) {
                    cp.terminate();
                    break;
                }
            }
        }

    }while (true);

    return 0;
}