#include "DataStorage_protobuf.h"
#include "RedisDatabase.h"
#include "protobuf/DataStorage.pb.h"

using namespace std;
#define DS_RD_PORT 6379
DataStorage::DataStorage()
{
    // Replace "tcp://localhost" with the appropriate Redis server address if necessary
    redisDB = std::make_shared<RedisDatabase>("127.0.0.1",DS_RD_PORT);
    keyPrefix = "fruit_protobuf_data:";
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
    
    std::string key = keyPrefix + fruit;

    std::optional<std::string> dataStr = redisDB->get(key);
    if (!dataStr)
    {
        return std::vector<DataStorage_t>();
    }
    DataStorage_t data = deserializeData(*dataStr);

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
        return DataStorage_t();
    }

    return data;
}
