// #include "InMemoryDatabase.h"
#include <sw/redis++/redis++.h>
#include <iostream>
#include <string> 
#include <optional>
#include "RedisDatabase.h"


using namespace std;
using namespace sw::redis;

// RedisDatabase& RedisDatabase::getInstance(const std::string& ip, int port) {
//     static RedisDatabase instance(ip, port);
//     return instance;
// }

RedisDatabase::RedisDatabase(const std::string& ip, int port)
    : redisClient("tcp://" + ip + ":" + std::to_string(port)) {
    // Initialize the Redis client
}

RedisDatabase::~RedisDatabase()
{
}

// RedisDatabase& RedisDatabase::getInstance(const std::string& ip, int port) {
//     static RedisDatabase instance(ip, port);
//     return instance;
// }
bool RedisDatabase::set(const std::string& key, string& value)
{
    return redisClient.set(key, value);
}

std::optional<std::string> RedisDatabase::get(const std::string& key)
{
    sw::redis::OptionalString result = redisClient.get(key);
    if (result)
        return (*result);
    else
        return std::nullopt;
}

std::optional<double> RedisDatabase::hashGet(const std::string& key, const std::string& field)
{
    auto result = redisClient.hget(key, field);
    if (result)
        return std::stod(*result);
    else
        return std::nullopt;
}

long long RedisDatabase::hashSet(const std::string& key, const std::string& field, double value)
{
    return redisClient.hset(key, field, std::to_string(value));
}

long long RedisDatabase::hashDelete(const std::string& key, const std::string& field)
{
    return redisClient.hdel(key, field);
}

std::unordered_map<std::string, double> RedisDatabase::hashGetAll(const std::string& key)
{
    // std::vector<std::optional<double>> values;
    std::unordered_map<std::string, double> rmap ;
    std::unordered_map<std::string, std::string> result ;
    // redisClient.hgetall(key, std::back_inserter(result));
    redisClient.hgetall("hash", std::inserter(result, result.begin()));
    for (const auto& r : result)
    {        
        rmap[r.first] = std::stod(r.second);
    }

    return rmap;
}
