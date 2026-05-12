#include "cme_benchmark_common.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_reference_precalculator.hpp"
#include <array>

using namespace assembler::circulation_mechanism;

struct RefBenchContainer {
    TContainerState state_value{TContainerState::ingress_ready};
    TSlotIndex ingress_slot{TSlotIndex::from_raw(1)};
    TSlotIndex dispatch_slot{TSlotIndex::from_raw(1)};
    constexpr TContainerState state() const noexcept { return state_value; }
    constexpr TSlotIndex find_first_ingress_writable_slot() const noexcept { return ingress_slot; }
    constexpr TSlotIndex find_first_dispatch_ready_slot() const noexcept { return dispatch_slot; }
};

struct RefBenchRegistry {
    std::array<RefBenchContainer, 1> containers{RefBenchContainer{}};
    constexpr const RefBenchContainer* try_get(TContainerRegistryIndex index) const noexcept {
        return index.is_valid() && index.one_based() == 1 ? &containers[0] : nullptr;
    }
    constexpr std::uint64_t generation() const noexcept { return 1; }
};

int main() {
    RefBenchRegistry registry{};
    std::array<TReferenceCandidate, 1> candidates{
        TReferenceCandidate{TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready, 1}
    };
    volatile std::uint64_t sink = 0;
    auto result = cme_bench::run("reference_supply", 50000, [&](std::uint64_t i) {
        TReferencePrecalculator<1, 1> precalc{TReferencePrecalculatorId::from_raw(i + 1), TReferenceSupplyPolicy{1, 1, true}, 1};
        auto report = precalc.replenish_ingress(registry, candidates, TRoundId::from_raw(1), TReferenceReportId::from_raw(1));
        sink += report.ingress_refs_prepared;
    });
    result.print();
    return sink == 0 ? 1 : 0;
}
