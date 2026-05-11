#pragma once
#include <cstdint>

/*
    TContainerStorageKind.hpp

    Delivery:
        CME-CONTAINER-REGISTRY-PROD-W01 — Production Indexed Storage Contract

    Responsibility:
        Classifies registry storage kind.
*/

namespace assembler {
namespace circulation_mechanism {

enum class TContainerStorageKind : std::uint8_t {
    fixed_array,
    static_vector_like,
    external_span,
    custom_policy
};
} // namespace circulation_mechanism
} // namespace assembler
