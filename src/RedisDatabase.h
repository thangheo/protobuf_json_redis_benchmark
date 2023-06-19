#pragma once

#include <string>
#include <vector>
#include <sw/redis++/redis++.h>
#include <optional>

class RedisDatabase {
private:
    sw::redis::Redis redisClient;

    // RedisDatabase(const std::string& ip, int port);
    RedisDatabase(const RedisDatabase&) = delete;
    RedisDatabase& operator=(const RedisDatabase&) = delete;

public:
    RedisDatabase(const std::string& ip, int port);
    ~RedisDatabase();

    static RedisDatabase& getInstance(const std::string& ip, int port);
    // string
    bool set(const std::string& key, std::string& value);
    std::optional<std::string> get(const std::string& key);

    long long hashSet(const std::string& key, const std::string& field, double value);
    std::optional<double> hashGet(const std::string& key, const std::string& field);
    std::unordered_map<std::string, double> hashGetAll(const std::string& key);
    long long hashDelete(const std::string& key, const std::string& field);
};
