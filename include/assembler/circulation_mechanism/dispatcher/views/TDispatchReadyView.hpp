#pragma once
#include "assembler/circulation_mechanism/dispatcher/TDispatcherId.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatcherStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchReadyView final {
    TDispatcherId dispatcher_id{};
    TDispatcherStatus status{TDispatcherStatus::uninitialized};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return dispatcher_id.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return status == TDispatcherStatus::ready || status == TDispatcherStatus::awaiting_dispatch_ref; }
};
} // namespace circulation_mechanism
} // namespace assembler
