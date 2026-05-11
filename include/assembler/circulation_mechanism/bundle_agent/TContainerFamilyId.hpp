#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TContainerFamilyId.hpp

        Delivery:
            CME-BUNDLE-AGENT-PROD-W01 — Production Topology And Scaling Contract

        Current responsibility:
            Identifies a uniform container family managed by BundleAgent.

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

    struct TContainerFamilyId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TContainerFamilyId() noexcept = default;
        constexpr explicit TContainerFamilyId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TContainerFamilyId invalid() noexcept { return TContainerFamilyId{k_invalid_value}; }
        [[nodiscard]] static constexpr TContainerFamilyId from_raw(value_type input) noexcept { return TContainerFamilyId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TContainerFamilyId lhs, TContainerFamilyId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TContainerFamilyId lhs, TContainerFamilyId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TContainerFamilyId> {
        std::size_t operator()(const assembler::circulation_mechanism::TContainerFamilyId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TContainerFamilyId::value_type>{}(input.raw());
        }
    };
    }
