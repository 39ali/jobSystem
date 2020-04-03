#include "jobQueue.h"
#include <iostream>
#include <thread>

 JobQueue::JobQueue(std::size_t max_jobs):
top{0},
bottom{0}{
     jobs.resize(max_jobs);
 }

bool JobQueue::push(Job* job){
    int _bottom = bottom.load(std::memory_order_relaxed);


    if(_bottom<jobs.size()){
     
     //   std::cout<< "job-pushed at"<<_bottom<<std::endl;
        jobs[_bottom]=job;
        bottom.store(_bottom+1,std::memory_order_release);
      //    std::cout << "push "<<bottom <<std::endl;
        return true;
    }
    else
    return false ;
}

Job* JobQueue::pop(){
  
  
    int _bottom = bottom.load(std::memory_order_acquire);
   // std::cout << "bottom val : " << _bottom <<std::endl;
    _bottom= std::max<int>(_bottom-1 ,0);
    bottom.store(_bottom,std::memory_order_relaxed);
    
    int _top = top.load(std::memory_order_relaxed);
 
    if(_top<= _bottom){
       
        Job* job = jobs[_bottom];
        if (!job)
            return nullptr;
        if(_top!=_bottom){
              // std::cout << "returned2 Job index " << _bottom << std::endl;
         //    std::cout<< "job-popped at "<<_bottom<<std::endl;
            return job;
        }
    else{
        int expectedTop = _top;
        int desiredTop =std::min( _top+1,(int)jobs.size());
        if (!top.compare_exchange_strong(expectedTop, desiredTop,
        std::memory_order_relaxed)){
            job=nullptr;
        }
            bottom.store(_top+1,std::memory_order_relaxed);
          //  std::cout<< "pop bottom "<<_top+1<<"bottom val"<< _bottom<<std::endl;
       //   std::cout<< "job-popped main worker at "<<_bottom<<std::endl;
            //         std::cout << "returned3 Job index " << _bottom << std::endl;
        return job;
    }
}
    else {
        // std::cout<< "pop bottom store "<< _top <<" "<<_bottom <<" |  "<<std::endl;
        bottom.store(_top , std::memory_order_relaxed);
        return nullptr;
    } 
}

Job* JobQueue::steal(){
      
 

    int _top = top.load(std::memory_order_relaxed);


    int _bottom = bottom.load(std::memory_order_relaxed);
    
   
  //std::cout << "steal ("<<std::this_thread::get_id()<<") "<< _top << ","<<_bottom <<std::endl;
   
    //  std::cout << "steal" << _top <<"|"<< _bottom <<"|"<<std::endl;
    if (_top <_bottom)
    {
       //  std::cout<< std::this_thread::get_id()<<" tring to steal a job "<<std::endl;
    // There's technically a data race here if _jobs is not an atomic<jobs*> array.
        Job* job = jobs[_top];

    if (top.compare_exchange_weak(_top, _top + 1, std::memory_order_relaxed) == false)
    {
    return nullptr;
    }
      //  std::cout<< std::this_thread::get_id()<<"job-stolen at "<<_top<<std::endl;
     //   std::cout << "steal afer exchange ("<<std::this_thread::get_id()<<") "<< top << ","<<_bottom<<std::endl;;
     //   if(job)4
     //   printf("job was stolen %d \n",  job->get_job_id());
  // std::cout << "job was stolen" << <<"|"<<std::endl;
      //  std::cout << "returned1 Job index " << _top << std::endl;
    return job;
    }
    else
    {
    return nullptr;
    }
}

std::size_t JobQueue::size() const{ return jobs.size();}
