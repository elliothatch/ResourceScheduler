#ifndef SIMPLESCHEDULER_H
#define SIMPLECHEDULER_H
#include "IScheduler.h"
#include <queue>

class SimpleScheduler : public IScheduler
{
public:
	SimpleScheduler(std::istream& resourceStream, std::istream& jobStream);

	virtual std::string scheduleJobs();
	virtual int getIdlingJobCount() const;
	virtual int getIdlingResourceCount() const;

private:
	std::istream* m_resourceStream;
	std::istream* m_jobStream;
	std::queue<int> m_resourceBuffer;
	std::queue<int> m_jobBuffer;
	int m_jobCount;
};

#endif
