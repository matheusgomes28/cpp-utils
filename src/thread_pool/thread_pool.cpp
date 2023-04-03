#include <thread_pool/thread_pool.h>
#include <thread_pool/thread_pool.h>

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>

namespace
{
    enum class RequestType
    {
        Execute,
        Stop
    };
    
    using RequestFunction = std::function<void()>;

    struct Request
    {
        RequestType type;
        RequestFunction function;
    };
} // namespace

class thread_pool::Pool::ThreadPoolImpl
{
public:

    explicit ThreadPoolImpl(std::size_t n_threads)
    {
        for (std::size_t i = 0; i < std::max(n_threads, 1lu); ++i)
        {
            _threads.push_back(std::thread{[&]{

                bool should_stop = false;
                while (!should_stop)
                {
                    std::unique_lock<std::mutex> cv_lock{_queue_mutex};
                    _queue_condition.wait(cv_lock, [&]{
                        return !_queue.empty();
                    });

                    // need to pop from the queue
                    auto const request = _queue.front();
                    _queue.pop();

                    switch (request.type)
                    {
                    case RequestType::Execute:
                        request.function();
                        break;
                    case RequestType::Stop:
                        should_stop = true;
                    }
                }
            }});
        }
    }

    ~ThreadPoolImpl()
    {
        stop();

        for (auto& thread : _threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    void stop()
    {
        std::lock_guard<std::mutex> queue_guard{_queue_mutex};
        for (std::size_t i = 0; i < _threads.size(); ++i)
        {
            _queue.push({RequestType::Stop, []{}});
        }
    }

    void queue(std::function<void()> task)
    {
        std::lock_guard<std::mutex> queue_guard{_queue_mutex};
        _queue.push({RequestType::Execute, task});
    }

private:
    std::mutex _queue_mutex;
    std::condition_variable _queue_condition;
    std::queue<Request> _queue;
    std::vector<std::thread> _threads;
};


// Public API thing

thread_pool::Pool::Pool(std::size_t n)
    : _impl{std::make_unique<ThreadPoolImpl>(n)}
{
}

thread_pool::Pool::~Pool() = default;

void thread_pool::Pool::queue(std::function<void()> task)
{
    if (_impl)
    {
        _impl->queue(task);
    }
}

void thread_pool::Pool::stop()
{
    if (_impl)
    {
        _impl->stop();
    }
}
