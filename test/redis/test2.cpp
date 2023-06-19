#include <sw/redis++/redis++.h>
# include <iostream>
using namespace sw::redis;
int main(void) {
    // auto redis = Redis("tcp://default:password@127.0.0.1:6379/0");
    auto redis = Redis("tcp://127.0.0.1:6379");
    std::cout << redis.ping() << std::endl;
}