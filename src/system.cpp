#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

// For debugging
#include <iostream>

#include <algorithm>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
	return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {

	// Find all of the current pid directories in /proc
	// These are unique so you don't have to worry about duplicates
	auto v_pids = LinuxParser::Pids();

	// Clear the set so that we get rid of any old pids
	set_proc_ordered_.clear();

	// for all the current pids, insert a process object into the set
	for (auto v_curr : v_pids) {

		set_proc_ordered_.insert(Process(v_curr));

	}

	// Assign the 
	processes_.assign(set_proc_ordered_.begin(),set_proc_ordered_.end());

	std::reverse(processes_.begin(),processes_.end());

	return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 	
	return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 	
	return LinuxParser::MemoryUtilization(); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
	return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
	return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
	return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
	return LinuxParser::UpTime(); 
}