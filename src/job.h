#pragma once 
#include <functional>
#include <atomic>

struct Job ;
using JobFunc = std::function<void(Job*,const void*)>;

struct Job{
    JobFunc function ;
    Job* parent ;
    std::atomic_size_t unfinishedJobs ;
    char padding[4] ;
};


Job* AllocateJob(){
return new Job();
}

Job* CreateJob(JobFunc func){
Job* job = AllocateJob();
job->function = func; 
job->parent= nullptr;
job->unfinishedJobs=1;
return job ;
} 


Job* CreateJobAsChild(Job* parent,JobFunc function){
parent->unfinishedJobs.fetch_add(1);
Job* job = AllocateJob();
job->function = function;
job->parent=parent ;
job->unfinishedJobs=1;
return job;
}
