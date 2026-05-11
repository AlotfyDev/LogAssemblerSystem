#pragma once
    #include <cstdint>
    /*
        TCommunicationBindingKind.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: Binding kind.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCommunicationBindingKind : std::uint8_t {
        ingress_placement, dispatch_output, bridge_facing_boundary, exposure_contract, diagnostic_only
    };
    } // namespace circulation_mechanism
} // namespace assembler
