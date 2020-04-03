


#include "jobWorker.h"
#include "jobSystem.h"
#include <iostream>
JobWorker::JobWorker(JobSystem* jsystem, std::size_t maxJobs,Mode mode):
job_system{jsystem},
queue{maxJobs},
pool{maxJobs},
mode{mode},
state{State::Stopping}
{

}


  JobWorker::JobWorker(const JobWorker& worker):
  job_system{worker.job_system},
  pool{worker.queue.size()},
   queue{worker.queue.size()}    
{
        
    }



void JobWorker::run(){
state = State::Running;
worker_thread = std::thread(&JobWorker::loop,this);
}



void JobWorker::submit_job(Job* job){
    if(job)
        queue.push(job);
}

void JobWorker::loop(){
    thread_id = std::this_thread::get_id();
    state= State::Running;
  while(state==JobWorker::State::Running){
    Job* job = get_job();
    if(job){
       job->run();
    }
  }
}

void JobWorker::wait(Job* wait_job){
  
    while(!wait_job->is_finished()){
        Job* job = get_job();
        if(job)
        job->run();
    }
}


 void JobWorker::set_state(State _state){
state = _state ;
}


Job* JobWorker::get_job(){
    Job* job = queue.pop();
    if(job){

   return job;
    }
    else{
        JobWorker* worker =
                            job_system->get_random_worker();
        if(worker!=this && worker){
          //  std::cout<< "trying to steal a job"<< std::endl;
            Job* job =  worker->queue.steal();
            if(job)
            {
               //  std::cout<< "job steal"<< std::endl;
            return job;
            }
            else{ //no job to steal
              //   std::cout<< "no job to steal"<< std::endl;
                std::this_thread::yield();
                return nullptr;
            }
        }else
        {
           //   std::cout<< "no worker to steal from"<< std::endl;
            std::this_thread::yield();
            return nullptr;
        }

    }
}
