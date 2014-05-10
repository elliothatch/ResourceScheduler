#ifndef IMPROVEDSCHEDULER_H
#define IMPROVEDSCHEDULER_H

#include "IScheduler.h"
#include <deque>
#include <queue>

//if ImprovedScheduler encounters a job that is too large for the available resources it will skip it and find a smaller task so resources are not left idling
//a job will only be skipped 3 times at most
class ImprovedScheduler : public IScheduler
{
public:
	ImprovedScheduler(std::istream& resourceStream, std::istream& jobStream);

	virtual std::string scheduleJobs();
	virtual int getIdlingJobCount() const;
	virtual int getIdlingResourceCount() const;

private:
	std::istream* m_resourceStream;
	std::istream* m_jobStream;
	std::queue<int> m_resourceBuffer;
	std::deque<std::pair<int, int>> m_jobBuffer; //pair(job size, skip count
	int m_jobCount;
};

#endif