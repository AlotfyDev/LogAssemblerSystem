#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    struct TRetryProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TRetryProfileId() noexcept = default;
        constexpr explicit TRetryProfileId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TRetryProfileId invalid() noexcept { return TRetryProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TRetryProfileId from_raw(value_type input) noexcept { return TRetryProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TRetryProfileId a, TRetryProfileId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TRetryProfileId a, TRetryProfileId b) noexcept { return !(a==b); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
