#include <gtest/gtest.h>
#include "../src/RedisDatabase.h"

// Fixture for the RedisDatabase tests
class RedisDatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any necessary resources before each test
        // For example, initialize a Redis server for testing
    }

    void TearDown() override {
        // Clean up any resources after each test
        // For example, stop the Redis server used for testing
    }

    // Helper function to initialize the RedisDatabase object
    RedisDatabase createRedisDatabase() {
        // Provide the IP and port of the Redis server used for testing
        std::string ip = "127.0.0.1";
        int port = 6379;
        return RedisDatabase(ip, port);
    }
};

// Test case for hashSet() and hashGet()
TEST_F(RedisDatabaseTest, TestSetAndGet) {
    RedisDatabase db = createRedisDatabase();
    std::string val ="asdfasd24234%#$@ doi";
    // Perform hashSet()
    db.set("indicators", val );

    // Perform hashGet()
    std::optional<std::string> result = db.get("indicators");

    EXPECT_EQ(result, val);
}


// Test case for hashSet() and hashGet()
TEST_F(RedisDatabaseTest, TestHashSetAndGet) {
    RedisDatabase db = createRedisDatabase();
    double val =123.423424;
    // Perform hashSet()
    db.hashSet("hash", "field", val );

    // Perform hashGet()
    std::optional<double> result = db.hashGet("hash", "field");

    EXPECT_EQ(result, val);
}

// Test case for hashGetAll()
TEST_F(RedisDatabaseTest, TestHashGetAll) {
    RedisDatabase db = createRedisDatabase();
    double val1=-120123.213,val2=12312.23424;
    // Perform hashSet()
    db.hashSet("hash", "field1", val1);
    db.hashSet("hash", "field2", val2);

    // Perform hashGetAll()
    std::unordered_map<std::string, double> result = db.hashGetAll("hash");

    // Verify the result
    // ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result["field1"], val1);
    EXPECT_EQ(result["field2"], val2);
}

// Test case for hashDelete()
TEST_F(RedisDatabaseTest, TestHashDelete) {
    RedisDatabase db = createRedisDatabase();
    // Perform hashSet()
    double val1= 56765.123123;
    db.hashSet("hash", "field", val1);
    // Perform hashDelete()
    db.hashDelete("hash", "field");
    // Perform hashGet()
    std::optional<double> result = db.hashGet("hash", "field");

    // Verify the result (should be an empty string)
    EXPECT_EQ(result, std::nullopt);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
