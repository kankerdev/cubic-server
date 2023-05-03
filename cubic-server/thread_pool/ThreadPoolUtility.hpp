#ifndef ZENITH_THREADPOOLUTILITY_HPP
#define ZENITH_THREADPOOLUTILITY_HPP

//=============
// STD includes
//=============
#include <semaphore>
#include <queue>
#include <mutex>
#include <atomic>
#include <functional>
#include <list>

//===============
// cubic includes
//===============
#include "exceptions.hpp"

//=====================
// thread_pool includes
//=====================
#include "Semaphore.hpp"

namespace thread_pool {
   DEFINE_EXCEPTION(ThreadPoolInternalError);
   DEFINE_EXCEPTION(JobException);
   class ThreadWorker;

// due to restriction on std semaphore, zenith semaphore are here used. (renamed thread_pool)
   struct ThreadPoolUtility {
      thread_pool::Semaphore jobSemaphore; // limitless semaphore. limit is overflow (which should not happen if the codebase is clean :) )
      std::atomic<int> inactiveThreads { };
      std::atomic<bool> stayAlive { true };
      std::atomic<int> lastId {0};

      std::list<ThreadWorker> workers; // each worker knows who it is, allowing for safe removal of the workers.
      mutable std::mutex workerProtection;

      int actualSize {};
      int targetSize {};
      mutable std::mutex sizeProtection;

      std::queue<std::queue<std::function<void(void)>>> jobQueue;
      mutable std::mutex queueProtection;

      std::atomic<int> totalJobsPushed { };
      std::atomic<int> totalJobsDone { };

      mutable ReverseSemaphore library;
   };
}

#endif /* ZENITH_THREADPOOLUTILITY_HPP */