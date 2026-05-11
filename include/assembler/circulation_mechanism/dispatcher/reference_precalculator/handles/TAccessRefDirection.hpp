#pragma once
    #include <cstdint>
    /*
        TAccessRefDirection.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Access reference direction.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TAccessRefDirection : std::uint8_t {
        ingress, dispatch, internal_slot
    };
    } // namespace circulation_mechanism
} // namespace assembler
