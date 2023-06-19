#include "DataStorage_protobuf.h"
#include "RedisDatabase.h"
#include "protobuf/DataStorage.pb.h"

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
    std::string key = keyPrefix + data.fruit();
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
    std::string serializedData;

    if (data.SerializeToString(&serializedData)) {
        return serializedData;
    } else {
        return "";
    }
}

DataStorage_t DataStorage::deserializeData(const std::string& dataStr) const
{
    DataStorage_t data;

    if (!data.ParseFromString(dataStr)) {
        // Invalid protobuf data, return a default-initialized DataStorage
        return DataStorage_t();
    }

    return data;
}
