#include "experiments.hpp"

void TestTreeConflicts() {
    Job::CalcTransmissionDuration = DurationCaculator(2'000'000'000, 1.0, 0.000'05);
    FatTree topology(16);
    FatTreeResource resources(topology, 1, 1); // TODO
    unsigned int jobCount = 0;
    auto getNextJob = [&jobCount]() -> std::unique_ptr<Job> {
        if (jobCount >= 20000)
            return nullptr;
        ++jobCount;
        auto model = "../data/opt-350m-16.json";
        thread_local std::default_random_engine engine(42);
        thread_local std::vector<unsigned int> hostCountList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        thread_local std::vector<unsigned int> stepCountList = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        std::uniform_int_distribution<std::size_t> randomHostCount(0, hostCountList.size() - 1);
        std::uniform_int_distribution<std::size_t> randomStepCount(0, stepCountList.size() - 1);
        auto hostCount = hostCountList[randomHostCount(engine)];
        auto stepCount = stepCountList[randomStepCount(engine)];
        return std::make_unique<Job>(hostCount, stepCount, ModelInfoProvider::GetModelInfo(model, 1.0));
    };
    FirstHostAllocationPolicy hostAllocationPolicy;
    FirstTreeBuildingPolicy treeBuildingPolicy;
    GreedySharingPolicy sharingPolicy;
    AllocationController controller(std::move(resources), std::move(getNextJob), std::move(hostAllocationPolicy),
                                    std::move(treeBuildingPolicy), std::move(sharingPolicy));
    controller.RecordTreeConflicts = true;
    controller.RunSimulation(std::nullopt, true);
}
