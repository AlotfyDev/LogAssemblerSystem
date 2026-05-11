#pragma once
    #include <cstdint>

    /*
        TReadSideProfileIssueKind.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines read-side profile readiness issue kinds.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideProfileIssueKind : std::uint8_t {
        none,
        missing_admission_boundary,
        missing_receiver_context,
        missing_bridge_contract,
        unsupported_transfer_semantic,
        receiver_lifecycle_unknown,
        ack_required_but_not_visible,
        capacity_profile_missing,
        boundary_mismatch
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
