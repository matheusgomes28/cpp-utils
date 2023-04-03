#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <memory>

namespace thread_pool
{
    class Pool
    {
    public:
        void start();
        void stop();
        void queue(std::function<void()> task);

    private:
        class ThreadPoolImpl;
        std::unique_ptr<ThreadPoolImpl> _impl;
    };
} // namespace thread_pool
#endif // THREAD_POOL_H
