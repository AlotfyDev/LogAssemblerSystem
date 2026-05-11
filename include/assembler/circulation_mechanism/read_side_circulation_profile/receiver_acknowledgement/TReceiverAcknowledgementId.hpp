#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    struct TReceiverAcknowledgementId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TReceiverAcknowledgementId() noexcept = default;
        constexpr explicit TReceiverAcknowledgementId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TReceiverAcknowledgementId invalid() noexcept { return TReceiverAcknowledgementId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReceiverAcknowledgementId from_raw(value_type input) noexcept { return TReceiverAcknowledgementId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TReceiverAcknowledgementId a, TReceiverAcknowledgementId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReceiverAcknowledgementId a, TReceiverAcknowledgementId b) noexcept { return !(a==b); }
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
