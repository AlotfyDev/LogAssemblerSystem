#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TDispatchBoundaryId.hpp

        Delivery:
            CME-DISPATCHER-PROD-W01 — Production Exposure Execution Contract

        Current responsibility:
            Identifies dispatch output boundary.

        Explicit non-ownership:
            - Does not own bridge protocol.
            - Does not own receiver lifecycle.
            - Does not execute persistence.
            - Does not parse payload content.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TDispatchBoundaryId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TDispatchBoundaryId() noexcept = default;
        constexpr explicit TDispatchBoundaryId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TDispatchBoundaryId invalid() noexcept { return TDispatchBoundaryId{k_invalid_value}; }
        [[nodiscard]] static constexpr TDispatchBoundaryId from_raw(value_type v) noexcept { return TDispatchBoundaryId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TDispatchBoundaryId a, TDispatchBoundaryId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TDispatchBoundaryId a, TDispatchBoundaryId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TDispatchBoundaryId> {
        std::size_t operator()(const assembler::circulation_mechanism::TDispatchBoundaryId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TDispatchBoundaryId::value_type>{}(x.raw());
        }
    };
    }
