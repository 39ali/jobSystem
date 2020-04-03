#include <iostream>
#include <thread>
#include <vector>


int counter =0 ;

std::mutex counter_mutex;

void thread_function()
{
    counter_mutex.lock();
    counter++;
     using namespace std::chrono_literals;
      std::this_thread::sleep_for(2ns);
    counter++;
    counter_mutex.unlock();
}
 
int main()
{
    std::vector<std::thread> threads ;
    for(int i = 0; i < 1000; i++){
        threads.emplace_back(thread_function);
    }
      
    for(int i = 0; i < 1000; i++){
        threads[i].join();
       }

    std::cout<<"counter:"<< counter << "\n";
    return 0;
}
