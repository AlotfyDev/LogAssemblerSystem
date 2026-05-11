#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TRoundId.hpp

        Delivery:
            CME-INGRESS-PROD-W01 — Production Placement Execution Contract

        Current responsibility:
            Round identity for ingress reference scoping.

        Explicit non-ownership:
            - Does not own payload semantics.
            - Does not calculate references.
            - Does not own bridge/read-side lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TRoundId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TRoundId() noexcept = default;
        constexpr explicit TRoundId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TRoundId invalid() noexcept { return TRoundId{k_invalid_value}; }
        [[nodiscard]] static constexpr TRoundId from_raw(value_type v) noexcept { return TRoundId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TRoundId a, TRoundId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TRoundId a, TRoundId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TRoundId> {
        std::size_t operator()(const assembler::circulation_mechanism::TRoundId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TRoundId::value_type>{}(x.raw());
        }
    };
    }
