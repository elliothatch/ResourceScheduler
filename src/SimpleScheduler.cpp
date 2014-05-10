#include "SimpleScheduler.h"
#include <sstream>


SimpleScheduler::SimpleScheduler(std::istream& resourceStream, std::istream& jobStream)
:IScheduler(resourceStream, jobStream),
m_resourceStream(&resourceStream), m_jobStream(&jobStream), m_resourceBuffer(), m_jobBuffer(), m_jobCount(0)
{
}

std::string SimpleScheduler::scheduleJobs()
{
	//read in resources
	while (m_resourceStream->good())
	{
		int resourceUID = 0;
		*m_resourceStream >> resourceUID;
		if (m_resourceStream->good())
			m_resourceBuffer.push(resourceUID);
	}

	//read in jobs
	while (m_jobStream->good())
	{
		int jobSize = 0;
		*m_jobStream >> jobSize;
		if (m_jobStream->good())
			m_jobBuffer.push(jobSize);
	}

	std::stringstream schedule;

	while (m_jobBuffer.size() > 0 && m_jobBuffer.front() <= m_resourceBuffer.size())
	{
		int jobSize = m_jobBuffer.front();
		schedule << "Job " << m_jobCount << ": ";
		for (int i = 0; i < jobSize; i++)
		{
			schedule << m_resourceBuffer.front() << " ";
			m_resourceBuffer.pop();
		}
		m_jobBuffer.pop();
		schedule << "\n";
		m_jobCount++;
	}

	return schedule.str();
}

int SimpleScheduler::getIdlingJobCount() const
{
	return m_jobBuffer.size();
}

int SimpleScheduler::getIdlingResourceCount() const
{
	return m_resourceBuffer.size();
}