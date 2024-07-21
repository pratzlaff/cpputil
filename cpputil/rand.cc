#include <cpputil/rand.hh>
#include <cpputil/thread.hh>
#include <ctime>

namespace {
  util::mutex srand_mutex;
}

volatile bool util::call_srand = true;

void util::srand_init()
{
  srand_mutex.lock();
  if (call_srand) {
    std::srand(std::time(0));
    call_srand = false;
  }
  srand_mutex.unlock();
}
