#include "jobPool.h"

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
    }
    return job;
}