#ifndef JOB_H
#define JOB_H

#include <functional>
#include <atomic>

struct Job ;
using JobFunc = std::function<void(Job*,const void*)>;

class  Job{
   public:
    Job(){unfinishedJobs.store(1);};  
   Job(JobFunc job , Job* parent=nullptr);
   void run();
   bool is_finished() const ;
   void assign_func(JobFunc func){ function=func;}
  private:
    JobFunc function ;
    Job* parent ;
    std::atomic_size_t unfinishedJobs ;
    char padding[4] ;
    void finish();
};

#endif
