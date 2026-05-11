#pragma once
#include "../common/TReadSideAdapterContractId.hpp"
#include "../common/TReadSideAdapterInvocationStatus.hpp"
#include "../common/TReadSideAdapterKind.hpp"
#include "TReadSideAdapterIssueKind.hpp"

/*
    TReadSideAdapterReport.hpp

    Evidence report for adapter contract evaluation.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideAdapterReport final {
    TReadSideAdapterContractId contract_id{};
    TReadSideAdapterKind kind{TReadSideAdapterKind::unknown};
    TReadSideAdapterInvocationStatus invocation_status{TReadSideAdapterInvocationStatus::not_attempted};
    TReadSideAdapterIssueKind issue{TReadSideAdapterIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return contract_id.is_valid(); }
    [[nodiscard]] constexpr bool accepted() const noexcept {
        return is_valid() && invocation_status == TReadSideAdapterInvocationStatus::accepted && issue == TReadSideAdapterIssueKind::none;
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
