#include <iostream>
#include<vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sys/time.h>

long getMicrotime();
std::vector<long> time_start;

int main(){
  time_start.push_back(getMicrotime());
  int j = 0;
  std::vector<int> v_;
  std::vector<long> time_;

  auto start1 = std::chrono::high_resolution_clock::now();
  auto end1 = std::chrono::high_resolution_clock::now();
  auto start = std::chrono::high_resolution_clock::now();
  auto end = start + std::chrono::nanoseconds(1000000);



  for(int i = 0;i<20000000;i++)
  {
    start1 = std::chrono::high_resolution_clock::now();
    j=j+1;

    if(std::chrono::high_resolution_clock::now() > end)
    {
      v_.push_back(j);
      time_.push_back(getMicrotime());
      end = std::chrono::high_resolution_clock::now()+std::chrono::nanoseconds(1000000);
    }
    end1 = std::chrono::high_resolution_clock::now();

  }

  std::ofstream outfile_TS1;
  std::remove("simple_execs.txt");
  std::remove("simple_execs_time.txt");
  std::remove("P2_start.txt");

  outfile_TS1.open("simple_execs.txt", std::ios_base::app);
  for(unsigned int i = 0;i<v_.size();i++)
  {
    outfile_TS1<<std::setprecision(20)<<v_[i]<< std::endl;
  }
  outfile_TS1.close();

  outfile_TS1.open("simple_execs_time.txt", std::ios_base::app);
  for(unsigned int i = 0;i<time_.size();i++)
  {
    outfile_TS1<<std::setprecision(20)<<time_[i]<< std::endl;
  }
  outfile_TS1.close();

  outfile_TS1.open("P2_start.txt", std::ios_base::app);
  for(unsigned int i = 0;i<time_start.size();i++)
  {
    outfile_TS1<<std::setprecision(20)<<time_start[i]<< std::endl;
  }
  outfile_TS1.close();

  return 0;
}


long getMicrotime(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
