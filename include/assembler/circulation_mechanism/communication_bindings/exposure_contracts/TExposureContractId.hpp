#pragma once
    #include <cstdint>
    #include <functional>
    /*
        TExposureContractId.hpp

        Delivery:
            CME-COMMBIND-PROD-W01 — Production Boundary And Exposure Contracts

        Current responsibility:
            Identifies an exposure contract.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute adapter runtime.
            - Does not move/copy payload.
            - Does not own bridge protocol.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TExposureContractId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TExposureContractId() noexcept = default;
        constexpr explicit TExposureContractId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TExposureContractId invalid() noexcept { return TExposureContractId{k_invalid_value}; }
        [[nodiscard]] static constexpr TExposureContractId from_raw(value_type input) noexcept { return TExposureContractId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TExposureContractId lhs, TExposureContractId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TExposureContractId lhs, TExposureContractId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TExposureContractId> {
        std::size_t operator()(const assembler::circulation_mechanism::TExposureContractId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TExposureContractId::value_type>{}(input.raw());
        }
    };
    }
