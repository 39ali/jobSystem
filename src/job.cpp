#include "job.h"

void Job::run(){
    function(this,nullptr);
    finish();
}

void Job::finish (){
    unfinishedJobs.fetch_sub(1);
    if(is_finished()){
        if(parent!= nullptr){
            parent->finish();
        }
    }
}

bool Job::is_finished() const{
    return unfinishedJobs==0;
}

Job::Job(JobFunc func , Job* parent):
function{func},
parent{parent},
unfinishedJobs(1){
    if(parent!=nullptr){
        parent->unfinishedJobs++;
    }
}