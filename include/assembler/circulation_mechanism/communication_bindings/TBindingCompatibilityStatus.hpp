#pragma once
    #include <cstdint>
    /*
        TBindingCompatibilityStatus.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: Binding compatibility outcome.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TBindingCompatibilityStatus : std::uint8_t {
        unknown, compatible, incompatible, requires_profile_review, blocked_by_boundary_rule
    };
    } // namespace circulation_mechanism
} // namespace assembler
