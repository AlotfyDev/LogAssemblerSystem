#pragma once
#include <cstdint>
#include <functional>
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverAdmissionReportId final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};
    constexpr TReceiverAdmissionReportId() noexcept = default;
    constexpr explicit TReceiverAdmissionReportId(value_type input) noexcept : value(input) {}
    [[nodiscard]] static constexpr TReceiverAdmissionReportId invalid() noexcept { return TReceiverAdmissionReportId{k_invalid_value}; }
    [[nodiscard]] static constexpr TReceiverAdmissionReportId from_raw(value_type input) noexcept { return TReceiverAdmissionReportId{input}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
