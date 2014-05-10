#ifndef ISCHEDULER_H
#define ISCHEDULER_H

#include <istream>
#include <ostream>

//interface for resource schedulers that create a schedules for distributing resources to jobs
class IScheduler
{
public:

	IScheduler(std::istream& , std::istream& ) {}
	virtual ~IScheduler() {}

	virtual std::string scheduleJobs() = 0; //returns schedule in format Job #: ResourceUID0 ResourceUID1...
	virtual int getIdlingJobCount() const = 0;
	virtual int getIdlingResourceCount() const = 0;

};

#endif
