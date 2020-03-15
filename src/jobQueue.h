#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H
#include<vector>
#include "job.h"


class JobQueue{
    public:
    JobQueue(std::size_t max_jobs);
    bool push(Job* job);
    Job* pop();
    Job* steal();
    std::size_t size() const ;
    bool  empty() const ; 

    private : 
    std::vector< Job*> jobs ; 
    std::atomic<std::size_t> top, bottom ; 
};

#endif