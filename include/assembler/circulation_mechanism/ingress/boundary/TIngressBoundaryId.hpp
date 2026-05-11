#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TIngressBoundaryId.hpp

        Delivery:
            CME-INGRESS-PROD-W01 — Production Placement Execution Contract

        Current responsibility:
            Identifies one ingress boundary descriptor.

        Explicit non-ownership:
            - Does not own payload semantics.
            - Does not calculate references.
            - Does not own bridge/read-side lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TIngressBoundaryId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TIngressBoundaryId() noexcept = default;
        constexpr explicit TIngressBoundaryId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TIngressBoundaryId invalid() noexcept { return TIngressBoundaryId{k_invalid_value}; }
        [[nodiscard]] static constexpr TIngressBoundaryId from_raw(value_type v) noexcept { return TIngressBoundaryId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TIngressBoundaryId a, TIngressBoundaryId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TIngressBoundaryId a, TIngressBoundaryId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TIngressBoundaryId> {
        std::size_t operator()(const assembler::circulation_mechanism::TIngressBoundaryId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TIngressBoundaryId::value_type>{}(x.raw());
        }
    };
    }
