#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 	const float USER_HZ_ = 0.01; // The unit of time for a jiffy 


};

#endif