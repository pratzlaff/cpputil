#include <iostream>
#include <cstdlib>
#include <cpputil/cpputil.hh>

using namespace std;

class my_thread : public util::thread {

  static util::rwlock _count_lock;
  static int _count;
  int _this_count;

public:

  my_thread() {
    _count_lock.wr_lock();
    _this_count = ++_count;
    _count_lock.unlock();
  }

  void run() {
    _count_lock.rd_lock();
    cout << "thread " << _this_count << " checking in" << endl;
    _count_lock.unlock();
  }

  void cleanup() {
    _count_lock.rd_lock();
    cout << "thread " << _this_count << " cancelled" << endl;
    _count_lock.unlock();
  }

  ~my_thread() {
    _count_lock.wr_lock();
    --_count;
    _count_lock.unlock();
  }
    
};

int my_thread::_count = 0;
util::rwlock my_thread::_count_lock;

int main(int argc, char** argv) {

  int nthreads = argc > 1 ? atoi(argv[1]) : 5;

  my_thread* t = new my_thread[nthreads];

  for (int i=0; i<nthreads; ++i)
    t[i].start();

  // There's a race condition here whereby the derived object
  // can be deleted before it's run method() is called, thus causing
  // the thread pure virtual run() to be called. The only reasonable
  // solution seems to be requiring a wait on the derived class.

  for (int i=0; i<nthreads; ++i)
    t[i].stop();

  delete [] t;
    
}
