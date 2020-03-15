#include "jobQueue.h"



 JobQueue::JobQueue(std::size_t max_jobs){
     jobs.resize(max_jobs);
     top.store(0);
     bottom.store(0);
 }

bool JobQueue::push(Job* job){
    size_t _bottom = bottom.load(std::memory_order_acquire);

    if(_bottom<jobs.size()){
        jobs[bottom]=job;
        bottom.store(bottom+1,std::memory_order_release);
        return true;
    }
    else
    return false ;
}

Job* JobQueue::pop(){
    std::size_t _bottom = bottom.load(std::memory_order_acquire);
    _bottom= std::max<size_t>(_bottom-1 ,0);
    bottom.store(_bottom,std::memory_order_release);
    std::size_t _top = top.load(std::memory_order_acquire);

    if(_top<= bottom){
        Job* job = jobs[_bottom];
        if(top!=bottom){
            return job;
        }
    else{
        size_t expectedTop = top;
        size_t desiredTop = top+1;
        if (!top.compare_exchange_weak(expectedTop, desiredTop,
        std::memory_order_acq_rel)){
            job=nullptr;
        }
        bottom.store(desiredTop,std::memory_order_release);
        return job;
    }
}
    else {
        return nullptr;
    } 
}

Job* JobQueue::steal(){
    std::size_t _top = top.load(std::memory_order_acquire);
    _top=std::max<size_t>(_top+1,jobs.size()-1);
    top.store(_top,std::memory_order_release);
   std::size_t _bottom = bottom.load(std::memory_order_acquire);

    if(_top<=_bottom){
        return jobs[_top];
    }
    return nullptr;
}

std::size_t JobQueue::size() const{ return jobs.size();}
