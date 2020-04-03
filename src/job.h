#ifndef JOB_H
#define JOB_H

#include <functional>
#include <atomic>

struct Job ;
using JobFunc = std::function<void(Job*,const void*)>;

class  Job{
   public:
    Job():unfinishedJobs{1},parent{nullptr}{};  
   Job(JobFunc job , Job* parent=nullptr);
   void run();
   bool is_finished() const ;
   void assign_func(JobFunc func){ function=func;}
    void assign_parent(Job* _parent){parent=_parent; };
    void set_num(int id1) {job_id = id1;}
    inline int  get_job_id (){return job_id;}
    void inc_unfinshed_jobs();
    void dec_unfinshed_jobs();
  private:
    JobFunc function ;
    Job* parent ;
    int job_id;
    std::atomic_size_t unfinishedJobs ;
    char padding[4] ;
    void finish();
};

#endif
