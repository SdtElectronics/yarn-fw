
#pragma once

#include <atomic>
#include <thread>
#include <functional>

#include "../drivers/softEINT.h"

class eintc{
  public:
    eintc(seint& pin);
    ~eintc();

    void   start ();
    void   stop  ();
    size_t getCnt();
    size_t reset ();
    void   attachOvCb(size_t thresh, const std::function<void(void)>& cb);

  private:
    seint& _pin;
    std::atomic_bool enable;
    std::thread* cntTask;
    std::atomic_uint_fast64_t cnt;
    size_t overflowThresh;
    std::function<void(void)> overflowCb;
};