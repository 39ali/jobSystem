#include <iostream>
#include <thread>
#include <vector>

#if 0
int counter =0 ;
#else
std::atomic<int> counter = {0};
#endif

void thread_function()
{

    counter=counter+1;
     using namespace std::chrono_literals;
      std::this_thread::sleep_for(2ns);
   // counter++;
     counter=counter+1;
}
 
//

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
