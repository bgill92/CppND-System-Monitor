#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 	// const float USER_HZ_ = 0.01; // The unit of time for a jiffy 

 	int user_{0};
 	int nice_{0};
 	int system_{0};
 	int idle_{0};
 	int iowait_{0};
 	int irq_{0};
 	int softirq_{0};
 	int steal_{0};
 	int guest_{0};
 	int guest_nice_{0};

 	int prev_user_{0};
 	int prev_nice_{0};
 	int prev_system_{0};
 	int prev_idle_{0};
 	int prev_iowait_{0};
 	int prev_irq_{0};
 	int prev_softirq_{0};
 	int prev_steal_{0};
 	int prev_guest_{0};
 	int prev_guest_nice_{0}; 	

};

#endif