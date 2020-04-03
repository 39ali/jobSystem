#include "job.h"

void Job::run(){
    function(this,nullptr);
    finish();
}

void Job::finish (){
    unfinishedJobs.fetch_sub(1,std::memory_order_relaxed);
    if(is_finished()){
        if(parent!= nullptr){
            parent->dec_unfinshed_jobs();
            parent->is_finished();
        }
    }
}

bool Job::is_finished() const{
    return unfinishedJobs==0;
}

void Job::inc_unfinshed_jobs(){
    unfinishedJobs.fetch_add(1,std::memory_order_relaxed);
}
void Job::dec_unfinshed_jobs(){
    unfinishedJobs.fetch_sub(1,std::memory_order_relaxed);
}
Job::Job(JobFunc func , Job* parent):
function{func},
parent{parent},
unfinishedJobs(1){
    if(parent!=nullptr){
        parent->unfinishedJobs++;
    }
}
