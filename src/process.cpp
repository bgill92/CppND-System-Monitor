#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

#include <stdexcept>
#include <cstdio>

// for debugging
#include <iostream>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

	// Open stat file
	std::ifstream filestream(getProcPath() + LinuxParser::kStatFilename);

	string temp, line;

	long int utime, stime, cutime, cstime, starttime;

	// long int starttime = 0;

	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {		
			std::replace(line.begin(), line.end(), '=', ' ');
			std::replace(line.begin(), line.end(), '"', ' ');
			std::istringstream linestream(line);
			bool rightParenthesesFlag = false;

			while(!rightParenthesesFlag) { // Try to find the right parentheses because that denotes the second token in stat
				linestream >> temp;
				if(temp.find(")") != string::npos) { // Found the right parenthesis
					rightParenthesesFlag = true;
				}
			}

			for(int i = 0; i < 11; i++) { // Now burn through the next 11 tokens
				linestream >> temp;
			}

			linestream >> utime >> stime >> cutime >> cstime; // tokens 14-17

			for(int i = 0; i < 11; i++) { // Now burn through the next 4 tokens
				linestream >> temp;
			}

			linestream >> starttime; // 22nd token is the uptime

		}
	}

	auto total_time = utime + stime + cutime + cstime;
	auto Hertz = sysconf(_SC_CLK_TCK);
	auto seconds = LinuxParser::UpTime() - (int)((float)starttime / Hertz);
	setCpuUsg((((float)total_time / (float)Hertz) / (float)seconds));

	return getCpuUsg();
}

// TODO: Return the command that generated this process
string Process::Command() { 
	string line;
	std::ifstream filestream(getProcPath() + LinuxParser::kCmdlineFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			setCommand(line);
			return getCommand(); 
		}
	}
	// std::cout << "Failure in Process::Command()" << std::endl;
	// throw std::runtime_error("No command for Pid: " + std::to_string(Process::Pid()));
	setCommand("");
	return getCommand();
}

// TODO: Return this process's memory utilization
string Process::Ram() { 

	string line, key;

	long int mem_usage_kB = 0;

	string temp;

	std::ifstream filestream(getProcPath() + LinuxParser::kStatusFilename);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::replace(line.begin(), line.end(), '=', ' ');
			std::replace(line.begin(), line.end(), '"', ' ');
			std::istringstream linestream(line);
			while (linestream >> key >> temp) {
				if (key == "VmSize:") {
					mem_usage_kB = std::stoi(temp);
				}
			}
		}
	}
	

	setRamUsg((float)mem_usage_kB*0.001);	

	sprintf(buffer_,"%5d",(int)getRamUsg());

	return string(buffer_,0,6);

}

// TODO: Return the user (name) that generated this process
string Process::User() { 

	string lineOfInt;

	try{
		lineOfInt = LinuxParser::findAndReturnLine(getProcPath() + LinuxParser::kStatusFilename, "Uid:");
	} catch(const std::exception& e) {
		std::cout << "Failure in Process::User, PID: " << this->Pid() << std::endl;
	}

	if (lineOfInt != "") {

		std::replace(lineOfInt.begin(), lineOfInt.end(), ':', ' ');
	    std::istringstream linestream(lineOfInt);

	    string temp;
	    int uid;

	    linestream >> temp >> uid;    

		string line, user_name;

		int uid_read;	

		std::ifstream filestream(LinuxParser::kPasswordPath);
		if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
		  std::replace(line.begin(), line.end(), ':', ' ');
		  std::replace(line.begin(), line.end(), '=', ' ');
		  std::replace(line.begin(), line.end(), '"', ' ');
		  std::istringstream linestream(line);
	      while (linestream >> user_name >> temp >> uid_read) {
	        if (uid_read == uid) {  
	        	setUser(user_name);
	          	return getUser();
	        }
	      }
		}
		}

		throw std::runtime_error("Specific Uid was not found");
	} else {

		setRamUsg(0);
		setUser("");
		setCommand("");
		setCpuUsg(0);
		setUptime(0);
		return "";
	}
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 

	// Open stat file
	std::ifstream filestream(getProcPath() + LinuxParser::kStatFilename);

	string temp, line;

	long int uptime = 0;


	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {		
			std::replace(line.begin(), line.end(), '=', ' ');
			std::replace(line.begin(), line.end(), '"', ' ');
			std::istringstream linestream(line);
			bool rightParenthesesFlag = false;

			while(!rightParenthesesFlag) { // Try to find the right parentheses because that denotes the second token in stat
				linestream >> temp;
				if(temp.find(")") != string::npos) { // Found the right parenthesis
					rightParenthesesFlag = true;
				}
			}

			for(int i = 0; i < 19; i++) { // Now burn through the next 19 tokens
				linestream >> temp;
			}

			linestream >> uptime; // 22nd token is the uptime

			setUptime(uptime);
		}
	}

	return getUptime()/sysconf(_SC_CLK_TCK);

}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
	return this->getRamUsg() < a.getRamUsg();
	// return this->getCpuUsg() < a.getCpuUsg();
}