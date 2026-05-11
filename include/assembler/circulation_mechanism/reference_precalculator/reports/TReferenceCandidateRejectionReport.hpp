#pragma once
#include "TReferenceReportId.hpp"
#include "TReferenceCandidateRejectionKind.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/TReferencePrecalculatorId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceCandidateRejectionReport final {
    TReferenceReportId report_id{};
    TReferencePrecalculatorId precalculator_id{};
    TContainerRegistryIndex candidate_index{};
    TReferenceCandidateRejectionKind rejection_kind{TReferenceCandidateRejectionKind::none};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && precalculator_id.is_valid(); }
    [[nodiscard]] constexpr bool rejected() const noexcept { return rejection_kind != TReferenceCandidateRejectionKind::none; }
};
} // namespace circulation_mechanism
} // namespace assembler
