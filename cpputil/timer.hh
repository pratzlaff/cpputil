#ifndef UTIL_TIMER_HH
#define UTIL_TIMER_HH

#include <sys/time.h>
#include <unistd.h>

namespace util {

  struct timeval operator+(const struct timeval& t1, const struct timeval& t2);
  struct timeval operator-(const struct timeval& t1, const struct timeval& t2);

  class timer {

    struct timeval base_time;
    struct timeval idle_time; // total time we've been stopped
    struct timeval stop_time; // time when stop() was called
    bool stopped;

  public:

    explicit timer(bool start=true);
    void stop();
    void start();
    void reset();
    double elapsed() const;

  };

  inline struct timeval operator+(const struct timeval& t1, const struct timeval& t2)
  {
    struct timeval ret_time;
    ret_time.tv_usec = t1.tv_usec + t2.tv_usec;
    ret_time.tv_sec = t1.tv_sec + t2.tv_sec;

    if (ret_time.tv_usec >= 1000000 || ret_time.tv_usec <= -1000000) {
      ret_time.tv_sec += ret_time.tv_usec / 1000000;
      ret_time.tv_usec %= 1000000;
    }

    return ret_time;
  }

  inline struct timeval operator-(const struct timeval& t1, const struct timeval& t2)
  {
    struct timeval tmp = t2;
    tmp.tv_sec *= -1;
    tmp.tv_usec *= -1;
    return t1+tmp;
  }

  inline timer::timer(bool start)
    : stopped(!start)
  {
    reset();
  }

  inline void timer::stop()
  {
    if (stopped)
      return;

    gettimeofday(&stop_time, 0);
    stopped = true;
  }

  inline void timer::start()
  {
    if (!stopped)
      return;

    struct timeval start;
    gettimeofday(&start, 0);
    idle_time = idle_time + start - stop_time;
    stopped = false;
  }

  inline void timer::reset()
  {
    gettimeofday(&base_time, 0);
    timerclear(&idle_time);
    stop_time = base_time;
  }

  inline double timer::elapsed() const
  {
    struct timeval current;

    if (stopped)
      current = stop_time;
    else
      gettimeofday(&current, 0);

    struct timeval elapsed = current - base_time - idle_time;
    return elapsed.tv_sec + elapsed.tv_usec/1e6;
  }

} // namespace util

#endif // UTIL_TIMER_HH
