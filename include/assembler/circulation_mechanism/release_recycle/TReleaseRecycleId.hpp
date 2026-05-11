#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReleaseRecycleId.hpp

        Delivery:
            CME-RELEASE-RECYCLE-PROD-W01 — Production Lifecycle Contract

        Current responsibility:
            Identifies one release/recycle lifecycle record.

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

    struct TReleaseRecycleId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TReleaseRecycleId() noexcept = default;
        constexpr explicit TReleaseRecycleId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TReleaseRecycleId invalid() noexcept { return TReleaseRecycleId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReleaseRecycleId from_raw(value_type input) noexcept { return TReleaseRecycleId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TReleaseRecycleId lhs, TReleaseRecycleId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReleaseRecycleId lhs, TReleaseRecycleId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TReleaseRecycleId> {
        std::size_t operator()(const assembler::circulation_mechanism::TReleaseRecycleId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TReleaseRecycleId::value_type>{}(input.raw());
        }
    };
    }
