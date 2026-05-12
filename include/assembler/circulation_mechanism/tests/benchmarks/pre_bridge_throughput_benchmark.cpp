#include "cme_benchmark_common.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_ingress.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_dispatcher.hpp"

using namespace assembler::circulation_mechanism;

struct ThroughputTarget {
    std::uint64_t placed{0};
    std::uint64_t exposed{0};
    bool place_from_ingress_ref(TIngressAccessRef ref, TIngressPayloadEnvelopeRef payload) noexcept {
        if (!ref.can_be_consumed_by_ingress() || !payload.is_valid()) return false;
        ++placed;
        return true;
    }
    bool expose_from_dispatch_ref(TDispatchAccessRef ref) noexcept {
        if (!ref.can_be_consumed_by_dispatcher()) return false;
        ++exposed;
        return true;
    }
};

static constexpr TAccessRefScope scope() {
    return TAccessRefScope{TContainerRegistryIndex::from_raw(1), TSlotIndex::from_raw(1), TRoundId::from_raw(1), 1, 1};
}
static constexpr TIngressAccessRef ingress_ref() {
    return TIngressAccessRef{TSlotAccessRef{TAccessRefId::from_raw(1), TAccessRefKind::ingress_access, TAccessRefDirection::ingress, scope(), TReferenceValidityState::issued}};
}
static constexpr TDispatchAccessRef dispatch_ref() {
    return TDispatchAccessRef{TSlotAccessRef{TAccessRefId::from_raw(2), TAccessRefKind::dispatch_access, TAccessRefDirection::dispatch, scope(), TReferenceValidityState::issued}};
}

int main() {
    TIngress ingress{TIngressId::from_raw(1), TIngressBoundaryDescriptor{TIngressBoundaryId::from_raw(2), TIngressBoundaryStatus::ready, true, false}};
    TDispatcher dispatcher{
        TDispatcherId::from_raw(3),
        TPassivePullDispatchProfile{TDispatchProfileKind::passive_pull, false, false},
        TPushDispatchProfile{TDispatchProfileKind::push, false},
        TDispatchBoundaryDescriptor{TDispatchBoundaryId::from_raw(4), TDispatchBoundaryStatus::ready, true, false}
    };
    ThroughputTarget target{};
    auto result = cme_bench::run("pre_bridge_ingress_dispatch_pair", 50000, [&](std::uint64_t i) {
        ingress.place(TIngressReportId::from_raw(i + 10), TIngressPayloadEnvelopeRef::from_raw(i + 100), ingress_ref(), target);
        dispatcher.expose_passive(TDispatchReportId::from_raw(i + 20), dispatch_ref(), target);
    });
    result.print();
    return target.placed == 50000 && target.exposed == 50000 ? 0 : 1;
}
