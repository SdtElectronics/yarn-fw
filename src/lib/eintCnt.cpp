
#include <limits>
#include "eintCnt.h"

eintc::eintc(seint& pin): _pin(pin),
                         enable(false),
                         cntTask(nullptr),
                         cnt(0),
                         overflowThresh(std::numeric_limits<size_t>::max()){                             
}

eintc::~eintc(){
    if(cntTask != nullptr){
        enable = false;
        cntTask->join();
        delete(cntTask);
    }
}

void eintc::start(){
    enable = true;
    cntTask = new std::thread([&]{
        while(enable){
            _pin.waitEv();
            if(++cnt > overflowThresh){
                overflowCb();
                overflowThresh = std::numeric_limits<size_t>::max();
            }
        }
    });
}

void eintc::stop(){
    enable = false;
}

size_t eintc::getCnt(){
    return cnt;
}

size_t eintc::reset (){
    size_t ret = cnt;
    cnt = 0;
    return ret;
}

void eintc::attachOvCb(size_t thresh, const std::function<void(void)>& cb){
    overflowThresh = thresh;
    overflowCb = cb;
}