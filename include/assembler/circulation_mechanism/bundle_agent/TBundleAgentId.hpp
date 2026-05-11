#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TBundleAgentId.hpp

        Delivery:
            CME-BUNDLE-AGENT-PROD-W01 — Production Topology And Scaling Contract

        Current responsibility:
            Identifies a BundleAgent instance.

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

    struct TBundleAgentId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TBundleAgentId() noexcept = default;
        constexpr explicit TBundleAgentId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TBundleAgentId invalid() noexcept { return TBundleAgentId{k_invalid_value}; }
        [[nodiscard]] static constexpr TBundleAgentId from_raw(value_type input) noexcept { return TBundleAgentId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TBundleAgentId lhs, TBundleAgentId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TBundleAgentId lhs, TBundleAgentId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TBundleAgentId> {
        std::size_t operator()(const assembler::circulation_mechanism::TBundleAgentId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TBundleAgentId::value_type>{}(input.raw());
        }
    };
    }
