add_executable(thread_pool_tests main.cpp)
target_link_libraries(thread_pool_tests PRIVATE
  thread_pool
  GTest::GTest)

add_test(NAME "ThreadPool unit tests" COMMAND thread_pool_tests)
