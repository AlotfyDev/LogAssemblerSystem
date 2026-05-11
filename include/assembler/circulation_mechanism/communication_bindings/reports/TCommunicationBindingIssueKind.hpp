#pragma once
    #include <cstdint>
    /*
        TCommunicationBindingIssueKind.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: Binding issue classification.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCommunicationBindingIssueKind : std::uint8_t {
        none, provider_not_ready, port_not_ready, adapter_not_ready, boundary_mismatch, mutable_internal_exposure_attempt, wrong_direction, profile_incompatible, closed_binding, bridge_runtime_leak, copy_move_ownership_leak
    };
    } // namespace circulation_mechanism
} // namespace assembler
