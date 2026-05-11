#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {

    enum class TReferenceCandidateRejectionKind : std::uint8_t {
        none, invalid_registry_index, container_missing, container_state_mismatch, slot_not_found, slot_state_mismatch, round_scope_invalid, pool_full, direction_mismatch, profile_generation_mismatch
    };
    } // namespace circulation_mechanism
} // namespace assembler
