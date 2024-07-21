#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <valarray>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

struct timeval
timeval_diff(const struct timeval& t1, const struct timeval& t2)
{
  struct timeval d;
  d.tv_sec = t2.tv_sec - t1.tv_sec;
  d.tv_usec = t2.tv_usec - t1.tv_usec;
  return d;
}

struct timeval
timeval_add(const struct timeval& t1, const struct timeval& t2)
{
  struct timeval newt;
  newt.tv_sec = t1.tv_sec + t2.tv_sec;
  newt.tv_usec = t1.tv_usec + t2.tv_usec;

  if (newt.tv_usec >= 1000000 || newt.tv_usec <= -1000000) {
    newt.tv_sec += newt.tv_usec / 1000000;
    newt.tv_usec %= 1000000;
  }

  return newt;
}

class timer {
  struct timeval tv_started;
  struct timeval tv;
  bool running;

public:

  timer() :
    running(false)
  {
    timerclear(&tv);
  }

  void start() {
    gettimeofday(&tv_started, 0);
    running = true;
  }

  void stop() {
    struct tv_ended;
    timerclear(&tv_ended);

    running = false;
    gettimeofday(&tv_ended, 0);
  }
    

      
      

class compute_time {

  struct timeval utime_, stime_, wtime_;

public:

  compute_time() {
    timerclear(&utime_);
    timerclear(&stime_);
    timerclear(&wtime_);
  }

  void timeit(int n=1) {

    struct rusage ru_start, ru_end;
    struct timeval wtime_start, wtime_end;

    getrusage(RUSAGE_SELF, &ru_start);
    gettimeofday(&wtime_start, 0);

    for (int i=0; i<n; ++i)
      (*this)();

    gettimeofday(&wtime_end, 0);
    getrusage(RUSAGE_SELF, &ru_end);

    utime_ = timeval_diff(ru_start.ru_utime, ru_end.ru_utime);
    stime_ = timeval_diff(ru_start.ru_stime, ru_end.ru_stime);
    wtime_ = timeval_diff(wtime_start, wtime_end);
  }

  struct timeval wtime() const { return wtime_; }
  struct timeval utime() const { return utime_; }
  struct timeval stime() const { return stime_; }

  virtual void operator()() = 0;

  virtual ~compute_time() { }

};

class valarray_time : public compute_time {

  std::valarray<int> v;
  int n;

public:
  valarray_time(int n_) : v(0, 1000), n(n_)
  { }

  void operator()() {
    for (int i=0; i<n; ++i) {
      //      v += 10;
      //      v *= 10;
      v = v*10+10;
    }
  }

};

class carray_time : public compute_time {

  int v[1000];
  int n;

public:
  carray_time(int n_) : n(n_)
  { memset(v, 0, sizeof(v)); }

  void operator()() {
    for (int j=0; j<n; ++j) {
    for (std::size_t i=0; i<sizeof(v)/sizeof(int); ++i)
      v[i] += 10;
        for (std::size_t i=0; i<sizeof(v)/sizeof(int); ++i)
          v[i] *= 10;
    }
  }

};

std::ostream& operator<<(std::ostream& s, const struct timeval& t) {
  return s << "sec=" << t.tv_sec << ", usec=" << t.tv_usec;
}


int main(int argc, char** argv) {

  valarray_time t1(std::atoi(argv[1]));
  t1.timeit();

  carray_time t2(std::atoi(argv[1]));
  t2.timeit();

  std::cout << "wtime: " << t1.wtime() << std::endl;
  std::cout << "utime: " << t1.utime() << std::endl;
  std::cout << "stime: " << t1.stime() << std::endl;

  std::cout << "wtime: " << t2.wtime() << std::endl;
  std::cout << "utime: " << t2.utime() << std::endl;
  std::cout << "stime: " << t2.stime() << std::endl;

}
