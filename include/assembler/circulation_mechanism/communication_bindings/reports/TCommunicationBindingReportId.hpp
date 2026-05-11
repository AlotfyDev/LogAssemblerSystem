#pragma once
#include <cstdint>
#include <functional>
namespace assembler {
namespace circulation_mechanism {

struct TCommunicationBindingReportId final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};
    constexpr TCommunicationBindingReportId() noexcept = default;
    constexpr explicit TCommunicationBindingReportId(value_type v) noexcept : value(v) {}
    [[nodiscard]] static constexpr TCommunicationBindingReportId invalid() noexcept { return TCommunicationBindingReportId{k_invalid_value}; }
    [[nodiscard]] static constexpr TCommunicationBindingReportId from_raw(value_type v) noexcept { return TCommunicationBindingReportId{v}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] friend constexpr bool operator==(TCommunicationBindingReportId a,TCommunicationBindingReportId b) noexcept { return a.value==b.value; }
    [[nodiscard]] friend constexpr bool operator!=(TCommunicationBindingReportId a,TCommunicationBindingReportId b) noexcept { return !(a==b); }
};
} // namespace circulation_mechanism
} // namespace assembler
