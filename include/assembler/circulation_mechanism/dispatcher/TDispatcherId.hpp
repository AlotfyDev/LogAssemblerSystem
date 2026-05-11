#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TDispatcherId.hpp

        Delivery:
            CME-DISPATCHER-PROD-W01 — Production Exposure Execution Contract

        Current responsibility:
            Identifies one dispatcher instance.

        Explicit non-ownership:
            - Does not own bridge protocol.
            - Does not own receiver lifecycle.
            - Does not execute persistence.
            - Does not parse payload content.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TDispatcherId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TDispatcherId() noexcept = default;
        constexpr explicit TDispatcherId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TDispatcherId invalid() noexcept { return TDispatcherId{k_invalid_value}; }
        [[nodiscard]] static constexpr TDispatcherId from_raw(value_type v) noexcept { return TDispatcherId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TDispatcherId a, TDispatcherId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TDispatcherId a, TDispatcherId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TDispatcherId> {
        std::size_t operator()(const assembler::circulation_mechanism::TDispatcherId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TDispatcherId::value_type>{}(x.raw());
        }
    };
    }
