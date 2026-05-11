#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

enum class TPreBridgeDefaultProfileStatus : std::uint8_t {
    undefined,
    draft,
    ready,
    active,
    rejected,
    invalid
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
