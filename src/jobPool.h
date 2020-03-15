#pragma once
#include "job.h"
#include <vector>

class JobPool{
    public:
    JobPool(std::size_t max_jobs_count);
     Job* allocate_job();
    bool is_full() const ;
    void clear();

    Job* create_job(JobFunc job_func);
    Job* create_job_as_child(JobFunc job_func , Job* parent);

    template<typename Data>
    Job* create_job(JobFunc job_func ,const Data& data);
    template<typename Data>
    Job* create_job_as_child(JobFunc job_func,const Data& data , Job* parent);
    template<typename Function> 
    Job* create_closure_Job(Function func);
    
    private:
    std::size_t allocated_jobs ;
    std::vector<Job> jobs;
};