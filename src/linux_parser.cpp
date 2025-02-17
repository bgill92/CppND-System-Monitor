#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include <stdexcept>

#include "linux_parser.h"

// For debugging
#include <iostream>
//

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::findAndReturnLine(string filePath, std::string keyToFind) {

  string line, key;

  std::ifstream filestream(filePath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      // std::replace(line.begin(), line.end(), ':', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == keyToFind) {
          // std::replace(value.begin(), value.end(), '_', ' ');
          return line;
        }
      }
    }
  } 
  // throw std::runtime_error("keyToFind was not found");
  return "";
}


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  // Use /proc/meminfo to get memory utilization information
  string key, value, line;
  int MemTotal, MemFree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'k', ' ');
      std::replace(line.begin(), line.end(), 'B', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> value) {
        if (key == "MemTotal") {
          MemTotal = stoi(value);
        }
        if (key == "MemFree") {
          MemFree = stoi(value);
        }        
      }
    }
  }

  // LinuxParser::findAndReturnLine(kProcDirectory + kMeminfoFilename, "MemTotal")

  return (((float)MemTotal - (float) MemFree)/( (float) MemTotal)); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
 string uptime, line;
 std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
 return (long int) std::stof(uptime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string lineOfInt;
  try {
   lineOfInt = LinuxParser::findAndReturnLine(kProcDirectory + kStatFilename, "processes");
  } catch (const std::exception& e) {
    std::cout << "Failure in LinuxParser::TotalProcesses()" << std::endl;
  }
  std::istringstream linestream(lineOfInt);

  string key, value;

  linestream >> key >> value;

  return std::stoi(value); 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string lineOfInt;
  try {
    lineOfInt = LinuxParser::findAndReturnLine(kProcDirectory + kStatFilename, "procs_running");
  } catch(const std::exception& e) {
    std::cout << "Failure in LinuxParser::RunningProcesses()" << std::endl;
  }
  std::istringstream linestream(lineOfInt);

  string key, value;

  linestream >> key >> value;

  return std::stoi(value); 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }