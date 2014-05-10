#include "ImprovedScheduler.h"
#include <sstream>

ImprovedScheduler::ImprovedScheduler(std::istream& resourceStream, std::istream& jobStream)
:IScheduler(resourceStream, jobStream),
m_resourceStream(&resourceStream), m_jobStream(&jobStream), m_resourceBuffer(), m_jobBuffer(), m_jobCount(0)
{
}

std::string ImprovedScheduler::scheduleJobs()
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
		{
			m_jobBuffer.push_back(std::make_pair(jobSize, 0));
		}
	}

	std::stringstream schedule;

	while (m_jobBuffer.size() > 0)
	{
		int currentJob = 0;
		while (currentJob + 1 < m_jobBuffer.size())
		{
			int jobSize = m_jobBuffer.at(currentJob).first;
			if (jobSize <= m_resourceBuffer.size())
				break;
			else
			{
				//do this job if it's been skipped 3 times already
				if (m_jobBuffer.at(currentJob).second >= 3)
				{
					break;
				}
				else
				{
					m_jobBuffer.at(currentJob).second++;
					currentJob++;
				}
			}
		}
		int jobSize = m_jobBuffer.at(currentJob).first;
		//check size again in case all the jobs are too big
		if (jobSize > m_resourceBuffer.size())
			break;
		schedule << "Job " << m_jobCount << ": ";
		for (int i = 0; i < jobSize; i++)
		{
			schedule << m_resourceBuffer.front() << " ";
			m_resourceBuffer.pop();
		}
		m_jobBuffer.erase(m_jobBuffer.begin() + currentJob);
		schedule << "\n";
		m_jobCount++;
	}

	return schedule.str();
}

int ImprovedScheduler::getIdlingJobCount() const
{
	return m_jobBuffer.size();
}

int ImprovedScheduler::getIdlingResourceCount() const
{
	return m_resourceBuffer.size();
}