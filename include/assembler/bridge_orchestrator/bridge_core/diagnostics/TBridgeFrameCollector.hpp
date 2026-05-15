#pragma once
#include <array>
#include <cstddef>
#include "assembler/communication_context/bridge_core/frames/TBridgeCoreFrame.hpp"

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TBridgeFrameCollector final
    {
        std::array<TBridgeCoreFrame, Capacity> frames{};
        std::size_t count{0u};
        std::uint64_t rejected_frames{0u};

        constexpr bool add(TBridgeCoreFrame frame) noexcept
        {
            if (count >= Capacity || !frame.is_valid())
            {
                ++rejected_frames;
                return false;
            }

            frames[count++] = frame;
            return true;
        }
    };
}
