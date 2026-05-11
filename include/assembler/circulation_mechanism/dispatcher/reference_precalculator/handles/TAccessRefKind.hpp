#pragma once
    #include <cstdint>
    /*
        TAccessRefKind.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Access reference kind.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TAccessRefKind : std::uint8_t {
        slot_access, ingress_access, dispatch_access, round_scoped, next_ref_token
    };
    } // namespace circulation_mechanism
} // namespace assembler
