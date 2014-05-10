#ifndef ISCHEDULER_H
#define ISCHEDULER_H

#include <istream>
#include <ostream>

class IScheduler
{
public:

	IScheduler(std::istream& resourceStream, std::istream& jobStream) {}
	virtual ~IScheduler() {}

	virtual std::string scheduleJobs() = 0; //returns output of schedule
	virtual int getIdlingJobCount() const = 0;
	virtual int getIdlingResourceCount() const = 0;

};

#endif
