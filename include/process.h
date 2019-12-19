#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  Process(int pid) : pid_(pid) {proc_path_ = LinuxParser::kProcDirectory + std::to_string(Process::Pid());Ram();CpuUtilization();};

  void validateProcess() {};

  float		  getRamUsg()		 const {return ram_usg_;};
  std::string getUser() 	 const {return user_;};
  std::string getCommand() 	 const {return command_;};
  float		  getCpuUsg() 	 const {return cpu_usg_;};
  long int 	  getUptime() 	 const {return uptime_;};
  std::string getProcPath()  const {return proc_path_;};

  void setRamUsg(float a) 		  {ram_usg_ = a;};
  void setUser(std::string a)     {user_ = a;};
  void setCommand(std::string a)  {command_ = a;};
  void setCpuUsg(float a) 		  {cpu_usg_ = a;};
  void setUptime(long int a) 	  {uptime_ = a;};
  void setProcPath(std::string a) {proc_path_ = a;};  

  // TODO: Declare any necessary private members
 private: 	
 	float ram_usg_{0};
 	int pid_;
 	std::string user_;
 	std::string command_;
 	float cpu_usg_{0};
 	long int uptime_;
 	std::string proc_path_;
 	char buffer_ [9];
};

#endif