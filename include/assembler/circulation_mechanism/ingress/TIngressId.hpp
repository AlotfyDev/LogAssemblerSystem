#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TIngressId.hpp

        Delivery:
            CME-INGRESS-PROD-W01 — Production Placement Execution Contract

        Current responsibility:
            Identifies one Ingress actor/surface.

        Explicit non-ownership:
            - Does not own payload semantics.
            - Does not calculate references.
            - Does not own bridge/read-side lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TIngressId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TIngressId() noexcept = default;
        constexpr explicit TIngressId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TIngressId invalid() noexcept { return TIngressId{k_invalid_value}; }
        [[nodiscard]] static constexpr TIngressId from_raw(value_type v) noexcept { return TIngressId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TIngressId a, TIngressId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TIngressId a, TIngressId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TIngressId> {
        std::size_t operator()(const assembler::circulation_mechanism::TIngressId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TIngressId::value_type>{}(x.raw());
        }
    };
    }
