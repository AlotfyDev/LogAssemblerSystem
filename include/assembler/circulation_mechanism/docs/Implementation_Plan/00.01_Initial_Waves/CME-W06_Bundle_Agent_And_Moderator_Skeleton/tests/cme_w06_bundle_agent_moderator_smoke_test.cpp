#include <type_traits>

#include "assembler/circulation_mechanism/circulation_mechanism_w03.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_w06.hpp"

int main()
{
    using namespace assembler::circulation_mechanism;

    constexpr TUniformContainerCapacityProfile uniform{
        TCapacityProfileId{1},
        TCapacityGenerationId{1},
        TCapacityProfileStatus::active,
        16U,
        1U
    };

    constexpr TIngressCapacityProfile ingress{
        TCapacityProfileId{2},
        TCapacityProfileStatus::active,
        16U,
        4U,
        8U
    };

    constexpr TDispatchCapacityProfile dispatch{
        TCapacityProfileId{3},
        TCapacityProfileStatus::active,
        16U,
        4U,
        8U,
        2U
    };

    constexpr TCirculationCapacityProfile capacity{
        TCapacityProfileId{4},
        TCapacityGenerationId{2},
        TCapacityProfileStatus::active,
        uniform,
        ingress,
        dispatch,
        4U,
        true,
        false
    };

    constexpr TSlotsContainerBundleAgentConfig bundle_config{capacity};
    static_assert(bundle_config.is_valid(), "bundle config valid");

    constexpr TSlotsContainerBundleAgent bundle{
        TBundleAgentId{10},
        TContainerFamilyId{11},
        bundle_config,
        TBundleAgentState::stable
    };

    static_assert(bundle.is_valid(), "bundle valid");
    constexpr auto topology = bundle.topology_view();
    static_assert(topology.is_valid(), "topology valid");
    static_assert(topology.active_container_count == 4U, "active container count");
    constexpr auto default_report = bundle.default_empty_profile_report();
    static_assert(default_report.is_valid(), "default empty profile report valid");
    static_assert(default_report.profile_available, "profile available");

    constexpr auto scaling_report = bundle.scaling_report(TScalingDirectionKind::horizontal, true);
    static_assert(scaling_report.is_valid(), "scaling report valid");
    static_assert(scaling_report.accepted, "scaling accepted");

    constexpr TSlotsContainerModeratorConfig mod_config{TCapacityProfileId{4}};
    static_assert(mod_config.is_valid(), "moderator config valid");

    constexpr TSlotsContainerModerator moderator{
        TModeratorId{20},
        TContainerId{21},
        TContainerRegistryIndex{1},
        mod_config,
        TModeratorState::safe_point_confirmed
    };

    static_assert(moderator.is_valid(), "moderator valid");
    constexpr auto readiness = moderator.readiness_view(TContainerState::default_empty, true);
    static_assert(readiness.is_valid(), "readiness valid");
    static_assert(readiness.can_expose_ingress_ready(), "can expose ingress readiness");

    constexpr auto moderated_view = moderator.moderated_container_view(TContainerState::default_empty, true);
    static_assert(moderated_view.is_valid(), "moderated view valid");

    constexpr auto reset_report = moderator.reset_report(
        TContainerState::reset_pending,
        TContainerState::default_empty,
        true
    );
    static_assert(reset_report.is_valid(), "reset report valid");
    static_assert(reset_report.reset_applied(), "reset applied");

    static_assert(std::is_trivially_copyable<TSlotsContainerBundleAgent>::value, "bundle skeleton trivially copyable");
    static_assert(std::is_trivially_copyable<TSlotsContainerModerator>::value, "moderator skeleton trivially copyable");

    return 0;
}
