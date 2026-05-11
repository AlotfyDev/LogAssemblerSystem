#pragma once

#include "../diagnostics/TReadSideDiagnosticRecord.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideDiagnosticView final {
    TReadSideDiagnosticRecord record{};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return record.is_valid(); }
    [[nodiscard]] constexpr bool has_issue() const noexcept { return record.has_issue(); }
    [[nodiscard]] constexpr bool blocks_integration() const noexcept { return record.blocks_integration(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
