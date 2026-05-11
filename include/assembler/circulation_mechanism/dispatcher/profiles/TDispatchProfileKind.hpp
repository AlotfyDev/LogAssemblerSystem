#pragma once
    #include <cstdint>
    /*
        TDispatchProfileKind.hpp
        Delivery: CME-DISPATCHER-PROD-W01
        Responsibility: Dispatch profile kind.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TDispatchProfileKind : std::uint8_t {
        passive_pull, push, hybrid, notification_only
    };
    } // namespace circulation_mechanism
} // namespace assembler
