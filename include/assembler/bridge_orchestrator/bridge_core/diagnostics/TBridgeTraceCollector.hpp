#pragma once
#include <array>
#include <cstddef>
#include "assembler/communication_context/bridge_core/traces/TBridgeCoreTrace.hpp"

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TBridgeTraceCollector final
    {
        std::array<TBridgeCoreTrace, Capacity> traces{};
        std::size_t count{0u};
        std::uint64_t rejected_traces{0u};

        constexpr bool add(TBridgeCoreTrace trace) noexcept
        {
            if (count >= Capacity || !trace.is_valid())
            {
                ++rejected_traces;
                return false;
            }

            traces[count++] = trace;
            return true;
        }
    };
}
