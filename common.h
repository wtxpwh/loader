//
// Created by wtxpwh on 2018/11/15.
//

#ifndef LOADER_COMMON_H
#define LOADER_COMMON_H

#include<chrono>
#include<thread>

#define sleep(X) std::this_thread::sleep_for(std::chrono::milliseconds(X))


#endif //LOADER_COMMON_H
