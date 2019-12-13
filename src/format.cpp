#include <string>
#include <cstdio>

#include "format.h"

// For debugging 
#include <iostream>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 

	int hours = seconds/3600;
	int minutes = (seconds/60) - (hours*60);
	int s = seconds % 60;

	char timeString[9];
	
	sprintf(timeString, "%02d:%02d:%02d",hours,minutes,s);

	return string(timeString); 
}