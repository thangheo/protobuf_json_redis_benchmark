#include <gtest/gtest.h>
#include "../src/DataStorage_protobuf.h"
#include "../src/protobuf/DataStorage.pb.h" // Include the generated protobuf header

TEST(DataStorageDataStorageTest, AddAndRetrieveDataStorageData) {
    DataStorage storage;

    // Create DataStorage protobuf messages
    DataStorage_t data1;
    data1.set_fruit("APPLE");
    data1.set_weight(100.0);
    data1.set_size(110.0);
    data1.set_price(1.0);

    DataStorage_t data2;
    data2.set_fruit("BANANA");
    data2.set_weight(2000.0);
    data2.set_size(20.0);
    data2.set_price(180.0);

    // Add data to the storage
    storage.addData(data1);
    storage.addData(data2);

    // Retrieve data
    std::vector<DataStorage_t> retrievedData = storage.getData("APPLE");

    ASSERT_EQ(retrievedData.size(), 1);
    EXPECT_EQ(retrievedData[0].fruit(), data1.fruit());
    EXPECT_EQ(retrievedData[0].weight(), data1.weight());
    EXPECT_EQ(retrievedData[0].size(), data1.size());
    EXPECT_EQ(retrievedData[0].price(), data1.price());
}

TEST(DataStorageDataStorageTest, RetrieveNonExistentSymbol) {
    DataStorage storage;

    std::vector<DataStorage_t> retrievedData = storage.getData("COCONUT");

    EXPECT_TRUE(retrievedData.empty());
}

TEST(RedisDataStorageTest, WriteAndRead1000Times) {
    DataStorage storage;

    // Measure the time taken to write the data
    auto startWrite = std::chrono::steady_clock::now();
    std::vector<DataStorage_t> retrievedData;
    std::string fruit;
    double weight;
    // Write and read the data 1000 times
    for (int i = 0; i < 100000; ++i) {
        // Create a unique fruit and weight
        fruit = "CUCUMABA" + std::to_string(i);
        weight = 100.0 + i;

        // Create an DataStorage message
        DataStorage_t data;
        data.set_fruit(fruit);
        data.set_weight(123);
        data.set_size(110.0);
        data.set_price(90.0);

        // Write the data
        storage.addData(data);

        // Read the data
        retrievedData = storage.getData(fruit);
    }
    ASSERT_EQ(retrievedData.size(), 1);
    EXPECT_EQ(retrievedData[0].fruit(), fruit);
    EXPECT_EQ(retrievedData[0].weight(), 123);
    EXPECT_EQ(retrievedData[0].size(), 110.0);
    EXPECT_EQ(retrievedData[0].price(), 90.0);

    auto endWrite = std::chrono::steady_clock::now();
    std::chrono::duration<double> writeDuration = endWrite - startWrite;
    std::cout << "Write duration: " << writeDuration.count() << " seconds" << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
