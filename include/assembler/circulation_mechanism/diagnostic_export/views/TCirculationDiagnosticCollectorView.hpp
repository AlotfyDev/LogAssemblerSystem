#pragma once
#include "../collector/TCirculationDiagnosticSnapshot.hpp"

/*
    TCirculationDiagnosticCollectorView.hpp

    Read-only projection of collector snapshot.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

template <std::size_t Capacity>
struct TCirculationDiagnosticCollectorView final {
    TCirculationDiagnosticSnapshot<Capacity> snapshot{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return snapshot.is_valid();
    }

    [[nodiscard]] constexpr bool has_blocking_issue() const noexcept {
        return snapshot.has_blocking_issue;
    }
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
