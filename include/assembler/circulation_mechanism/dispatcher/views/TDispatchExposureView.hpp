#pragma once
#include "assembler/circulation_mechanism/dispatcher/TDispatcherId.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatchExposureStatus.hpp"
#include "assembler/circulation_mechanism/reference_precalculator/handles/TDispatchAccessRef.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchExposureView final {
    TDispatcherId dispatcher_id{};
    TDispatchAccessRef dispatch_ref{};
    TDispatchExposureStatus status{TDispatchExposureStatus::not_exposed};
    bool mutable_internals_exposed{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return dispatcher_id.is_valid() && dispatch_ref.is_valid(); }
    [[nodiscard]] constexpr bool exposed() const noexcept {
        return status == TDispatchExposureStatus::exposed || status == TDispatchExposureStatus::observed || status == TDispatchExposureStatus::consumed;
    }
    [[nodiscard]] constexpr bool boundary_safe() const noexcept { return !mutable_internals_exposed; }
};
} // namespace circulation_mechanism
} // namespace assembler
