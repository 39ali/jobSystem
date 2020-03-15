
#include <iostream>
#include "jobSystem.h"


void empty_job(Job*, const void*)
{
    std::cout<< "job executed\n" <<std::endl;
}
 
int main (){
JobSystem job_system {4,100};

JobWorker* worker = job_system.master_worker;

Job* root = worker->get_job_pool()->create_job(&empty_job);

for(std::size_t i = 0; i <10; ++i)
{
//Job* child = worker->get_job_pool()->create_job_as_child(&empty_job,root);
Job* root = worker->get_job_pool()->create_job(&empty_job);
   worker->submit_job(root);
   worker->wait(root);
}

//  worker->submit_job(root);;


std::cout<< "yooo" <<std::endl;
return 0;
}
