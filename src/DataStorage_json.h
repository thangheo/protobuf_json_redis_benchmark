#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "RedisDatabase.h"
struct DataStorage_t 
{
    // Define the structure to hold analytical data
    std::string fruit;
    double weight;
    double size;
    double price;
    // Include additional fields as per your specific analytical data requirements
};

class DataStorage
{
public:
    // Constructor and destructor
    DataStorage();
    ~DataStorage();

    // Function to add analytical data
    bool addData(const DataStorage_t& data);

    // Function to retrieve analytical data for a specific fruit
    std::vector<DataStorage_t> getData(const std::string& fruit) const;
  

private:
    std::shared_ptr<RedisDatabase> redisDB;
    // RedisPlusPlus key prefix
    std::string keyPrefix;

    // Function to serialize analytical data to a string
    std::string serializeData(const DataStorage_t& data) const;

    // Function to deserialize analytical data from a string
    DataStorage_t deserializeData(const std::string& dataStr) const;
};
