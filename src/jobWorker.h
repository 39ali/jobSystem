class JobSystem ;
#ifndef JOB_WORKER_H
#define JOB_WORKER_H
#include <thread>
#include "jobPool.h"
#include "jobQueue.h"


class JobWorker{
    public:
    enum Mode{
        Background,
        Master
    };
    enum class State{
        Running,
        Stopping,
    };

    JobWorker(JobSystem* jsystem, std::size_t maxJobs,Mode mode= Mode::Background);
    JobWorker(const JobWorker& worker);
    ~JobWorker(){};
    inline Job* create_job(JobFunc job_func){return pool.create_job(job_func);}
    inline Job* create_job_as_child(JobFunc job_func , Job* parent){ return pool.create_job_as_child(job_func,parent);}
    void wait(Job* job);
    void loop();
    void run();
    void submit_job(Job* job);
    bool is_running(){return state==State::Running?true:false;}
    void set_state(State state);
    inline void join(){worker_thread.join();}
   
    private:
    JobPool pool;
    std::thread::id thread_id;
    std::thread worker_thread;
    State state;
    std::atomic<Mode> mode;
    JobSystem* job_system;
    JobQueue queue;

    private:       
    Job* get_job();
    JobPool* get_job_pool(){return &pool;}

};

#endif
