#pragma once
    #include <cstdint>
    /*
        TCommunicationBindingStatus.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: Binding lifecycle/readiness status.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TCommunicationBindingStatus : std::uint8_t {
        unbound, bound, ready, blocked, mismatch, closed
    };
    } // namespace circulation_mechanism
} // namespace assembler
