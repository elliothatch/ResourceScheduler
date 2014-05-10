#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <algorithm>
#include "ResourceNode.h"
#include "ResourceManager.h"
#include "SimpleScheduler.h"
#include "ImprovedScheduler.h"

void testScheduler(IScheduler& scheduler, std::stringstream& resourceStream, std::stringstream& jobStream,
	std::vector<int>& idlingJobs, std::vector<int>& idlingResources,
	int numJobs, int resourceCount, unsigned long randomSeed);

//tests both the simple scheduler and the improved scheduler in a famine of resources
int main(int argc, const char* argv[])
{
	std::cout << "Resource Scheduling Simulation\n";

	ResourceManager& resourceManager = ResourceManager::getInstance();
	//create test resources
	int resourceCount = 100;
	for (int i = 0; i < resourceCount; i++)
	{
		resourceManager.addResource(ResourceNode(i));
	}


	unsigned long testSeed = std::random_device()();
	int numJobs = 1000;

	std::cout << "Test Simple Scheduler\n";
	//create input streams
	std::stringstream resourceStream;
	std::stringstream jobStream;
	SimpleScheduler simpleScheduler(resourceStream, jobStream);
	std::vector<int> simpleIdlingJobs;
	std::vector<int> simpleIdlingResources;

	testScheduler(simpleScheduler, resourceStream, jobStream, simpleIdlingJobs, simpleIdlingResources, numJobs, resourceCount, testSeed);

	std::cout << "Test Improved Scheduler\n";

	std::stringstream resourceStream2;
	std::stringstream jobStream2;
	ImprovedScheduler improvedScheduler(resourceStream2, jobStream2);
	std::vector<int> improvedIdlingJobs;
	std::vector<int> improvedIdlingResources;

	testScheduler(improvedScheduler, resourceStream2, jobStream2, improvedIdlingJobs, improvedIdlingResources, numJobs, resourceCount, testSeed);

	int simpleIdlingJobsCount = 0;
	for (int jobCount : simpleIdlingJobs)
	{
		simpleIdlingJobsCount += jobCount;
	}

	int simpleIdlingResourcesCount = 0;
	for (int resourceCount : simpleIdlingResources)
	{
		simpleIdlingResourcesCount += resourceCount;
	}

	std::cout << "\nSimple Scheduler:\n";
	std::cout << "Idling Jobs: " << simpleIdlingJobsCount << "\n";
	std::cout << "Idling Resources: " << simpleIdlingResourcesCount << "\n";

	int improvedIdlingJobsCount = 0;
	for (int jobCount : improvedIdlingJobs)
	{
		improvedIdlingJobsCount += jobCount;
	}

	int improvedIdlingResourcesCount = 0;
	for (int resourceCount : improvedIdlingResources)
	{
		improvedIdlingResourcesCount += resourceCount;
	}

	std::cout << "\nImproved Scheduler:\n";
	std::cout << "Idling Jobs: " << improvedIdlingJobsCount << "\n";
	std::cout << "Idling Resources: " << improvedIdlingResourcesCount << "\n";

	system("PAUSE");
	return 0;
}

//mutates vectors and inserts number of idling jobs and idling resources after each job batch
void testScheduler(IScheduler& scheduler, std::stringstream& resourceStream, std::stringstream& jobStream, 
						std::vector<int>& idlingJobs, std::vector<int>& idlingResources,
						int numJobs, int resourceCount, unsigned long randomSeed)
{
	//initialize random numbers
	std::mt19937 rng;
	rng.seed(randomSeed);
	std::uniform_int_distribution<std::mt19937::result_type> resourceDist(0, resourceCount - 1);
	//tests jobs that require [1,15] resources
	std::uniform_int_distribution<std::mt19937::result_type> jobDist(1, 15);
	resourceDist(rng);

	int jobsRemaining = numJobs;
	while (jobsRemaining > 0)
	{
		//assuming that the scheduler stores all stream values in a buffer, clear the error bits
		resourceStream.clear();
		jobStream.clear();

		//generate some jobs
		std::uniform_int_distribution<std::mt19937::result_type> jobAddDist(1, std::min(jobsRemaining, 8));
		int jobsToAdd = jobAddDist(rng);
		for (int i = 0; i < jobsToAdd; i++)
		{
			jobStream << std::to_string(jobDist(rng)) << " ";
			jobsRemaining--;
		}

		//open up resources
		std::uniform_int_distribution<std::mt19937::result_type> resourceAddDist(0, 20);
		int resourcesToAdd = resourceAddDist(rng);
		for (int i = 0; i < resourcesToAdd; i++)
		{
			resourceStream << std::to_string(resourceDist(rng)) << " ";
		}

		//run the scheduler
		std::cout<<scheduler.scheduleJobs();
		idlingJobs.push_back(scheduler.getIdlingJobCount());
		idlingResources.push_back(scheduler.getIdlingResourceCount());
	}
}