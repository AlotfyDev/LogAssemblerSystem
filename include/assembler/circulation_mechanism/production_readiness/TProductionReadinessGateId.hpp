#pragma once
#include <cstdint>
#include <functional>

/*
    TProductionReadinessGateId.hpp

    Delivery:
        CME-INTEGRATION-PROD-W04 — Production Readiness Gate

    Responsibility:
        Identifies one production readiness gate evaluation.

    Non-ownership:
        Identity only. Does not evaluate readiness by itself.
*/

namespace assembler {
namespace circulation_mechanism {

struct TProductionReadinessGateId final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};

    constexpr TProductionReadinessGateId() noexcept = default;
    constexpr explicit TProductionReadinessGateId(value_type input) noexcept : value(input) {}

    [[nodiscard]] static constexpr TProductionReadinessGateId invalid() noexcept { return TProductionReadinessGateId{k_invalid_value}; }
    [[nodiscard]] static constexpr TProductionReadinessGateId from_raw(value_type input) noexcept { return TProductionReadinessGateId{input}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

    [[nodiscard]] friend constexpr bool operator==(TProductionReadinessGateId lhs, TProductionReadinessGateId rhs) noexcept { return lhs.value == rhs.value; }
    [[nodiscard]] friend constexpr bool operator!=(TProductionReadinessGateId lhs, TProductionReadinessGateId rhs) noexcept { return !(lhs == rhs); }
};
} // namespace circulation_mechanism
} // namespace assembler
