#include <thread_pool/thread_pool.h>
#include <thread_pool/thread_pool.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class thread_pool::Pool::ThreadPoolImpl
{
public:
    void start()
    {

    }

    void stop()
    {

    }

    void queue(std::function<void()> task)
    {

    }

private:
    std::mutex _queue_mutex;
    std::condition_variable _queue_condition;
    std::queue<std::function<void()>> _queue;
    std::vector<std::thread> _threads;
};