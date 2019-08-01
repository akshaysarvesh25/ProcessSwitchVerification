#include <iostream>
#include <chrono>
#include <thread>
#include <sched.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <thread>
#include <time.h>
#include <pthread.h>

std::vector<int> v_0;
std::vector<int> v_1;
std::vector<long> time_0;
std::vector<long> time_1;
std::vector<long> time_start;

long getMicrotime();

void sleep1(std::chrono::microseconds us)
{
    static int i =0;
    auto start = std::chrono::high_resolution_clock::now();
    static auto end = start + std::chrono::nanoseconds(1000000);
    auto end1 = start + us;
    do {
        i = i+1;
        if(std::chrono::high_resolution_clock::now() > end)
        {
          v_0.push_back(i);
          time_0.push_back(getMicrotime());
          end = std::chrono::high_resolution_clock::now()+std::chrono::nanoseconds(100000);
        }

    } while (std::chrono::high_resolution_clock::now() < end1);
}


void sleep2(std::chrono::microseconds us)
{
    static int i =0;
    auto start = std::chrono::high_resolution_clock::now();
    static auto end = start + std::chrono::nanoseconds(1000000);
    auto end1 = start + us;
    do {
        //std::this_thread::yield();
        sched_yield();
        //pthread_yield();
        i = i+1;
        if(std::chrono::high_resolution_clock::now() > end)
        {
          v_1.push_back(i);
          time_1.push_back(getMicrotime());
          end = std::chrono::high_resolution_clock::now()+std::chrono::nanoseconds(100000);
        }

    } while (std::chrono::high_resolution_clock::now() < end1);
}

int main()
{
    time_start.push_back(getMicrotime());

    auto start = std::chrono::high_resolution_clock::now();
    std::cout<<getpid()<<std::endl;




    for(int j = 0 ;j<10;j++)
    {
      sleep1(std::chrono::microseconds(100000));
      sleep2(std::chrono::microseconds(100000));
    }


              std::ofstream outfile_TS1;
              std::remove("P1_no_switch.txt");
              std::remove("P1_switch.txt");
              std::remove("P1_no_switch_time.txt");
              std::remove("P1_switch_time.txt");
              std::remove("P1_start.txt");


              outfile_TS1.open("P1_no_switch.txt", std::ios_base::app);
              for(unsigned int i = 0;i<v_0.size();i++)
              {
                outfile_TS1<<std::setprecision(20)<<v_0[i]<< std::endl;
              }
              outfile_TS1.close();

              outfile_TS1.open("P1_switch.txt", std::ios_base::app);
              for(unsigned int i = 0;i<v_1.size();i++)
              {
                outfile_TS1<<std::setprecision(20)<<v_1[i]<< std::endl;
              }
              outfile_TS1.close();

              outfile_TS1.open("P1_no_switch_time.txt", std::ios_base::app);
              for(unsigned int i = 0;i<time_0.size();i++)
              {
                outfile_TS1<<std::setprecision(20)<<time_0[i]<< std::endl;
                //std::cout<<"Writing file"<<std::endl;
              }
              outfile_TS1.close();

              outfile_TS1.open("P1_switch_time.txt", std::ios_base::app);
              for(unsigned int i = 0;i<time_1.size();i++)
              {
                outfile_TS1<<std::setprecision(20)<<time_1[i]<< std::endl;
              }
              outfile_TS1.close();

              outfile_TS1.open("P1_start.txt", std::ios_base::app);
              for(unsigned int i = 0;i<time_start.size();i++)
              {
                outfile_TS1<<std::setprecision(20)<<time_start[i]<< std::endl;
              }
              outfile_TS1.close();



}


long getMicrotime(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
