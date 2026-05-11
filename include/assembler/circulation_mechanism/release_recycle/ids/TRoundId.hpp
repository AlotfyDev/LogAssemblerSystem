#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TRoundId.hpp

        Delivery:
            CME-RELEASE-RECYCLE-PROD-W01 — Production Lifecycle Contract

        Current responsibility:
            Identifies the round involved in release/recycle.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute bridge or receiver lifecycle.
            - Does not mutate registry by itself.
            - Does not prove final delivery.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TRoundId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TRoundId() noexcept = default;
        constexpr explicit TRoundId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TRoundId invalid() noexcept { return TRoundId{k_invalid_value}; }
        [[nodiscard]] static constexpr TRoundId from_raw(value_type input) noexcept { return TRoundId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TRoundId lhs, TRoundId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TRoundId lhs, TRoundId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TRoundId> {
        std::size_t operator()(const assembler::circulation_mechanism::TRoundId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TRoundId::value_type>{}(input.raw());
        }
    };
    }
