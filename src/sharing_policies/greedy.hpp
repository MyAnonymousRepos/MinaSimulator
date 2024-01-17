#pragma once

#include "job.hpp"
#include "sharing_group.hpp"

class GreedySharingPolicy {
public:
    CommOpScheduleResult operator()(const SharingGroup &sharingGroup, const Job &job, double now) const;
};
