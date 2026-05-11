#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideAdapterContractId.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Current responsibility:
            Identifies one read-side adapter contract.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not implement the adapter runtime.
            - Does not persist payload.
            - Does not export telemetry.
            - Does not call external systems by itself.
            - Does not mutate PreBridge runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TReadSideAdapterContractId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideAdapterContractId() noexcept = default;
        constexpr explicit TReadSideAdapterContractId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideAdapterContractId invalid() noexcept { return TReadSideAdapterContractId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideAdapterContractId from_raw(value_type input) noexcept { return TReadSideAdapterContractId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideAdapterContractId lhs, TReadSideAdapterContractId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideAdapterContractId lhs, TReadSideAdapterContractId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side::TReadSideAdapterContractId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side::TReadSideAdapterContractId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side::TReadSideAdapterContractId::value_type>{}(input.raw());
        }
    };
    }
