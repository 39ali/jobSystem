
#include <iostream>
#include <chrono>
#include <cmath>
#include "jobSystem.h"
#define JOB_COUNT 65000

std::atomic_int counter;
void empty_job(Job* job, const void*)
{
  int j =0;
    for (int i=0 ;i< 2000; i++){
        j+=1+std::sin(i)*std::cos(i*j);
    }
   
    printf("job %d ,%d executed!\n" , job->get_job_id(),j);

}
 
int main (){
JobSystem job_system {8,JOB_COUNT
};

JobWorker* worker = job_system.master_worker;

    
#if 0
auto start = std::chrono::steady_clock::now();
for(std::size_t i = 0; i <JOB_COUNT; ++i)
{

Job* job = worker->get_job_pool()->create_job(&empty_job);
   worker->submit_job(job);
   worker->wait(job);
}
    
    

  auto end = std::chrono::steady_clock::now();
   std::cout << "Elapsed time in microseconds : "
    << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
    << " µs" << std::endl;
   std:: cout << "Elapsed time in milliseconds : "
        <<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms" << std::endl;
#else
    
    auto start1 = std::chrono::steady_clock::now();
    
     Job* parent = worker->get_job_pool()->create_job(&empty_job);
    for(std::size_t i = 0; i <JOB_COUNT-1; ++i)
    {
       Job* job = worker->get_job_pool()->create_job_as_child(&empty_job,parent);
    
       worker->submit_job(job);
    }
    worker->submit_job(parent);
    worker->wait(parent);
        

    auto   end1 = std::chrono::steady_clock::now();
        std::cout << "Elapsed time in microseconds : "
        << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count()
        << " µs" << std::endl;
       std:: cout << "Elapsed time in milliseconds : "
            <<std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count()
            << " ms" << std::endl;
    
#endif
return 0;
}

/*#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int> mySharedWork;
std::atomic<bool> dataProduced(false);

void dataProducer(){
    mySharedWork={1,0,3};
    dataProduced.store(true, std::memory_order_relaxed);
}

void dataConsumer(){
  while(!dataProduced.load(std::memory_order_relaxed));
    mySharedWork[1]= 2;
}

int main(){
    
  std::cout << std::endl;

  std::thread t1(dataConsumer);
  std::thread t2(dataProducer);

  t1.join();
  t2.join();
  
  for (auto v: mySharedWork){
      std::cout << v << " ";
  }
      
  std::cout << "\n\n";
  
}*/
