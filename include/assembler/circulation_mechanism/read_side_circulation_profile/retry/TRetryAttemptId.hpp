#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    struct TRetryAttemptId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TRetryAttemptId() noexcept = default;
        constexpr explicit TRetryAttemptId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TRetryAttemptId invalid() noexcept { return TRetryAttemptId{k_invalid_value}; }
        [[nodiscard]] static constexpr TRetryAttemptId from_raw(value_type input) noexcept { return TRetryAttemptId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TRetryAttemptId a, TRetryAttemptId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TRetryAttemptId a, TRetryAttemptId b) noexcept { return !(a==b); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
