#include "DataStorage_json.h"
#include "RedisDatabase.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

using namespace rapidjson;

using namespace std;
#define DS_RD_PORT 6380
DataStorage::DataStorage()
    // : redisDB("tcp://localhost")
{
    // Initialize the RedisPlusPlus connection
    // Replace "tcp://localhost" with the appropriate Redis server address if necessary
    redisDB = std::make_shared<RedisDatabase>("127.0.0.1",DS_RD_PORT);
    // Set the key prefix
    keyPrefix = "analytical_data:";
}
DataStorage::~DataStorage()
{
   
}

bool DataStorage::addData(const DataStorage_t& data)
{
    // Serialize the data to a string
    std::string dataStr = serializeData(data);
    // Generate the Redis key
    std::string key = keyPrefix + data.fruit;
    // Set the value in Redis
    return redisDB->set(key, dataStr);
}
std::vector<DataStorage_t> DataStorage::getData(const std::string& fruit) const
{   
    
    // Generate the Redis key
    std::string key = keyPrefix + fruit;

    // Retrieve the value from Redis
    std::optional<std::string> dataStr = redisDB->get(key);
    if (!dataStr)
    {
        // Key not found, return empty vector
        return std::vector<DataStorage_t>();
    }
    // Deserialize the data from the string
    DataStorage_t data = deserializeData(*dataStr);

    // Return a vector containing the retrieved data
    return std::vector<DataStorage_t>{data};
}

std::string DataStorage::serializeData(const DataStorage_t& data) const
{
    Document document;
    document.SetObject();

    Document::AllocatorType& allocator = document.GetAllocator();

    // Add data fields to the JSON object
    document.AddMember("fruit", Value(data.fruit.c_str(), allocator).Move(), allocator);
    document.AddMember("weight", data.weight, allocator);
    document.AddMember("size", data.size, allocator);
    document.AddMember("price", data.price, allocator);

    // Serialize the JSON document to a string
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

DataStorage_t DataStorage::deserializeData(const std::string& dataStr) const
{
    Document document;
    if (document.Parse(dataStr.c_str()).HasParseError() || !document.IsObject())
    {
        // Invalid JSON data format, return a default-initialized DataStorage
        return DataStorage_t();
    }

    DataStorage_t data;

    // Extract data fields from the JSON object
    if (document.HasMember("fruit") && document["fruit"].IsString())
    {
        data.fruit = document["fruit"].GetString();
    }

    if (document.HasMember("weight") && document["weight"].IsDouble())
    {
        data.weight = document["weight"].GetDouble();
    }

    if (document.HasMember("size") && document["size"].IsDouble())
    {
        data.size = document["size"].GetDouble();
    }

    if (document.HasMember("price") && document["price"].IsDouble())
    {
        data.price = document["price"].GetDouble();
    }

    return data;
}
