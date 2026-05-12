#include "assembler/circulation_mechanism/circulation_mechanism_read_side_engine.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

constexpr rscp::TReadSideAdmissionBoundaryDescriptor make_admission()
{
    return rscp::TReadSideAdmissionBoundaryDescriptor{
        rscp::TReadSideAdmissionBoundaryId::from_raw(1),
        rscp::TReadSideAdmissionMode::passive_pull_from_bridge,
        rscp::TReadSideAdmissionStatus::ready,
        true,
        false
    };
}

constexpr rscp::TReceiverContextDescriptor make_receiver()
{
    return rscp::TReceiverContextDescriptor{
        rscp::TReceiverContextId::from_raw(2),
        rscp::TReceiverContextKind::in_process_receiver,
        rscp::TReceiverLifecycleExpectation::ack_required,
        true,
        true
    };
}

constexpr rscp::TPostBridgeBoundaryContractDescriptor make_contract()
{
    return rscp::TPostBridgeBoundaryContractDescriptor{
        rscp::TPostBridgeBoundaryContractId::from_raw(3),
        rscp::TPostBridgeTransferSemantic::move,
        rscp::TPostBridgeBoundaryContractStatus::compatible,
        true,
        true
    };
}

constexpr rscp::TReadSideCirculationProfile make_read_profile()
{
    return rscp::TReadSideCirculationProfile{
        rscp::TReadSideProfileId::from_raw(4),
        rscp::TReadSideProfileStatus::ready,
        make_admission(),
        make_receiver(),
        make_contract()
    };
}

constexpr rscp::TPostBridgeCapacityProfile make_capacity()
{
    return rscp::TPostBridgeCapacityProfile{
        rscp::TPostBridgeCapacityProfileId::from_raw(5),
        rscp::TPostBridgeCapacityStatus::ready,
        1U,
        4U,
        2U,
        2U,
        0U
    };
}

int main()
{
    constexpr TCirculationConfigurationDescriptor runtime_config{
        TCirculationConfigurationId::from_raw(10),
        TCirculationConfigurationStatus::validated,
        TCirculationProfileKind::read_side,
        TCirculationApiVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(1)
    };

    constexpr TReadSideCirculationConfig config{
        runtime_config,
        make_read_profile(),
        make_capacity(),
        rscp::TReadSideBackpressureProfile{
            rscp::TReadSideBackpressureProfileId::from_raw(6),
            rscp::TReadSideBackpressureMode::observe_only,
            rscp::TReadSideBackpressureState::normal,
            false
        },
        rscp::TDelayedReleaseProfile{
            rscp::TDelayedReleaseProfileId::from_raw(7),
            rscp::TDelayedReleaseTriggerKind::receiver_acknowledgement,
            true,
            10U
        },
        rscp::TAddonBoundaryDescriptor{
            rscp::TAddonBoundaryId::from_raw(8),
            rscp::TAddonBoundaryKind::in_process_receiver,
            rscp::TAddonBoundaryStatus::ready,
            true,
            true,
            true,
            false
        }
    };

    static_assert(config.is_valid(), "read-side config must be valid");

    constexpr TReadSideEngineProfile profile{config, true, false};
    static_assert(profile.is_valid(), "read-side engine profile valid");

    TReadSideCirculationEngine engine{TReadSideEngineId::from_raw(20), profile};
    if (!engine.is_valid()) return 1;

    auto init = engine.initialize(TReadSideEngineReportId::from_raw(21));
    if (!init.passed()) return 2;
    if (!engine.view().ready()) return 3;

    auto start = engine.start(TReadSideEngineReportId::from_raw(22));
    if (!start.passed()) return 4;
    if (!engine.view().ready()) return 5;

    auto stop = engine.stop(TReadSideEngineReportId::from_raw(23));
    if (!stop.passed()) return 6;

    return 0;
}
