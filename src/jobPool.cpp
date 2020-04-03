#include "jobPool.h"

static int job_count =0 ;
JobPool::JobPool(std::size_t max_jobs):
allocated_jobs(0),
jobs{max_jobs}{

}

Job* JobPool::allocate_job(){
    if(!is_full()){
        
        return &jobs[allocated_jobs++];
    }else
    {
        return nullptr;
    }
    
}


void JobPool::clear(){
    allocated_jobs=0;
}

bool JobPool::is_full() const{
    return allocated_jobs == jobs.size();
}

Job* JobPool::create_job(JobFunc job_func){

    Job* job = allocate_job();
    
    if(job != nullptr)
    {
        job->assign_func(job_func);
        job->set_num(job_count++);
    }
    return job;
}

Job* JobPool::create_job_as_child(JobFunc job_func , Job* parent){
    Job* job = allocate_job();
      
      if(job != nullptr)
      {
          job->assign_func(job_func);
          job->assign_parent(parent);
          parent->inc_unfinshed_jobs();
          job->set_num(job_count++);
      }
      return job;
}

