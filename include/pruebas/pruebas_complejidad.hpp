#pragma once

#include <chrono>
#include <string>

#include "catch_amalgamated.hpp"
#include "nanobench.h"

namespace pruebas {

template <typename Operation>
inline std::string measuredGrowth(const std::string& label, Operation operation)
    {
        ankerl::nanobench::Bench bench;
        bench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
        for (unsigned int count = 128; count <= 2048; count *= 2)
            bench.complexityN(count).run(label, [&] { operation(count); });

        const auto fits = bench.complexityBigO();
        REQUIRE_FALSE(fits.empty());
        return fits.front().name();
    }


} // namespace pruebas
