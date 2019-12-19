#include "processor.h"

#include "linux_parser.h"

// debugging
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
	
	// algorithm per https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

	auto lineOfInt = LinuxParser::findAndReturnLine(LinuxParser::kProcDirectory + LinuxParser::kStatFilename , "cpu");

	std::istringstream linestream(lineOfInt);

	std::string temp;

	linestream >> temp >> user_ >> nice_ >> system_ >> idle_ >> iowait_ >> irq_ >> softirq_ >> steal_ >> guest_ >> guest_nice_;

	auto PrevIdle = prev_idle_ + prev_iowait_;
	auto Idle = idle_ + iowait_;

	auto PrevNonIdle = prev_user_ + prev_nice_ + prev_system_ + prev_irq_ + prev_softirq_ + prev_steal_;
	auto NonIdle = user_ + nice_ + system_ + irq_ + softirq_ + steal_;

	auto PrevTotal = PrevIdle + PrevNonIdle;
	auto Total = Idle + NonIdle;

	// differentiate: actual value minus the previous one
	auto totald = Total - PrevTotal;
	auto idled = Idle - PrevIdle;

	prev_user_ 	  	 = user_;
 	prev_nice_ 	   	 = nice_;
 	prev_system_  	 = system_;
 	prev_idle_    	 = idle_;
 	prev_iowait_  	 = iowait_;
 	prev_irq_     	 = irq_;
 	prev_softirq_ 	 = softirq_;
 	prev_steal_   	 = steal_;
 	prev_guest_   	 = guest_;
 	prev_guest_nice_ = guest_nice_; 

	auto CPU_Percentage = ((float)totald - (float)idled)/((float)totald);

	return CPU_Percentage; 

}