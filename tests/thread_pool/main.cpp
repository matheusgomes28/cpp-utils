#include <thread_pool/thread_pool.h>

#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(thread_pool_tests, test_no_workers)
{
    // This should just create a thread_pool
    // with one thread
    thread_pool::Pool thread_pool{0};

    bool ret_val = false;
    thread_pool.queue([&]{
        ret_val = true;
    });

    // Somehow we need a future here!
    SUCCEED();
}

int main(int argc, char** argv)
{   
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
