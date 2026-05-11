#pragma once
    #include <cstdint>
    #include <functional>
    /*
        TCommunicationBindingId.hpp

        Delivery:
            CME-COMMBIND-PROD-W01 — Production Boundary And Exposure Contracts

        Current responsibility:
            Identifies one circulation communication binding.

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

    struct TCommunicationBindingId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TCommunicationBindingId() noexcept = default;
        constexpr explicit TCommunicationBindingId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TCommunicationBindingId invalid() noexcept { return TCommunicationBindingId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCommunicationBindingId from_raw(value_type input) noexcept { return TCommunicationBindingId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TCommunicationBindingId lhs, TCommunicationBindingId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCommunicationBindingId lhs, TCommunicationBindingId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TCommunicationBindingId> {
        std::size_t operator()(const assembler::circulation_mechanism::TCommunicationBindingId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TCommunicationBindingId::value_type>{}(input.raw());
        }
    };
    }
