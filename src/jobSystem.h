 
#ifndef Job_System_H
#define Job_System_H
#include <thread>
#include "jobWorker.h"

class JobSystem{
    public:
    JobSystem(std::size_t threads_count, std::size_t jobs_per_thread);
    ~JobSystem();
    JobWorker* get_random_worker();
    JobWorker* master_worker ;
    private:
    std::vector<JobWorker> workers;
     std::thread::id master_thread_id;
    JobWorker* find_thread_worker(const std::thread::id thread_id);
};

#endif