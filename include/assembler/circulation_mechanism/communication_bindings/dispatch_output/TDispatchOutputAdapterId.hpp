#pragma once
    #include <cstdint>
    #include <functional>
    /*
        TDispatchOutputAdapterId.hpp

        Delivery:
            CME-COMMBIND-PROD-W01 — Production Boundary And Exposure Contracts

        Current responsibility:
            Identifies a dispatch output adapter descriptor.

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

    struct TDispatchOutputAdapterId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TDispatchOutputAdapterId() noexcept = default;
        constexpr explicit TDispatchOutputAdapterId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TDispatchOutputAdapterId invalid() noexcept { return TDispatchOutputAdapterId{k_invalid_value}; }
        [[nodiscard]] static constexpr TDispatchOutputAdapterId from_raw(value_type input) noexcept { return TDispatchOutputAdapterId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TDispatchOutputAdapterId lhs, TDispatchOutputAdapterId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TDispatchOutputAdapterId lhs, TDispatchOutputAdapterId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TDispatchOutputAdapterId> {
        std::size_t operator()(const assembler::circulation_mechanism::TDispatchOutputAdapterId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TDispatchOutputAdapterId::value_type>{}(input.raw());
        }
    };
    }
