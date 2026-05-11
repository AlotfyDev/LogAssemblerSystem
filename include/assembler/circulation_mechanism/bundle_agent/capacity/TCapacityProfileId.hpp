#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCapacityProfileId.hpp

        Delivery:
            CME-BUNDLE-AGENT-PROD-W01 — Production Topology And Scaling Contract

        Current responsibility:
            Identifies capacity profile used by BundleAgent.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not own container storage.
            - Does not execute registry rebuild.
            - Does not reset concrete containers.
            - Does not calculate access refs.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TCapacityProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCapacityProfileId() noexcept = default;
        constexpr explicit TCapacityProfileId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCapacityProfileId invalid() noexcept { return TCapacityProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCapacityProfileId from_raw(value_type input) noexcept { return TCapacityProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCapacityProfileId lhs, TCapacityProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCapacityProfileId lhs, TCapacityProfileId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TCapacityProfileId> {
        std::size_t operator()(const assembler::circulation_mechanism::TCapacityProfileId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TCapacityProfileId::value_type>{}(input.raw());
        }
    };
    }
