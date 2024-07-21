#ifndef UTIL_THREAD_HH
#define UTIL_THREAD_HH

#include <pthread.h>

#include <string>
#include <stdexcept>

namespace util {

  class mutex {
  private:
    pthread_mutex_t _mutex;

  public:

    mutex() throw() {
      pthread_mutex_init(&_mutex, 0);
    }

    void lock() throw() {
      pthread_mutex_lock(&_mutex);
    }

    void unlock() throw() {
      pthread_mutex_unlock(&_mutex);
    }

    ~mutex() {
      pthread_mutex_destroy(&_mutex);
    }
  };

  class rwlock {
  private:
    pthread_rwlock_t _lock;

  public:

    rwlock() throw() {
      pthread_rwlock_init(&_lock, 0);
    }

    void rd_lock() throw() {
      pthread_rwlock_rdlock(&_lock);
    }

    void wr_lock() throw() {
      pthread_rwlock_wrlock(&_lock);
    }

    void unlock() throw() {
      pthread_rwlock_unlock(&_lock);
    }

    ~rwlock() {
      pthread_rwlock_destroy(&_lock);
    }
  };

  class thread_started_error : public std::logic_error {
  public:
    thread_started_error(const std::string& msg =
			 "thread already started") throw()
      : std::logic_error(msg) { }
  };

  class thread {
  private:
    pthread_t _pthread;
    volatile bool _done, _started;
    mutex _start_mutex;

    static void _cleanup_thread(void *arg) {
      thread* obj = static_cast<thread*>(arg);
      obj->cleanup();
    }

    static void* _run_thread(void *arg) {
      thread* obj = static_cast<thread*>(arg);
      pthread_cleanup_push(_cleanup_thread, arg);
      obj->run();
      obj->_done = true;
      pthread_cleanup_pop(1);
      return 0;
    }

  public:

    thread() : _done(false), _started(false) { }

    virtual void run() = 0;

    void start() throw(thread_started_error) {

      _start_mutex.lock();

      if (_started)
	throw thread_started_error();
      else
	_started = true;

      _start_mutex.unlock();

      pthread_create(&_pthread, 0, _run_thread, this);
    }

    void wait() {
      pthread_join(_pthread, 0);
    }

    virtual void cleanup() { }

    void stop() {
      if (!_done)
	pthread_cancel(_pthread);
      _done = true;
    }

    virtual ~thread() {
      if (!_done) {
	wait();
	_done = true;
      }
    }
  };

} // namespace util

#endif
