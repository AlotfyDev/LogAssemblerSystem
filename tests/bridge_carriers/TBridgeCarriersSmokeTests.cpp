#include <cassert>

#include "assembler/communication_context/bridge_carriers/TBridgeCarriers.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccCarrierReadinessView.hpp"

using namespace assembler::communication_context;

namespace
{
    void test_validation_runtime()
    {
        TCarrierView carrier{};
        carrier.kind = TAsccCarrierKind::message;
        carrier.name = "primary-message-carrier";

        TCarrierValidationEngine validation_engine{};

        const auto validation_report =
            validation_engine.validate(carrier);

        assert(validation_report.valid());
        assert(validation_report.accepted);
    }

    void test_requirement_satisfaction_runtime()
    {
        TCarrierView carrier{};
        carrier.kind = TAsccCarrierKind::message;
        carrier.name = "requirement-runtime-carrier";

        TCarrierRequirementSatisfactionEngine<8> engine{};

        engine.register_requirement(
            {
                "message-flow",
                true,
                "carrier supports message runtime"
            });

        const auto report =
            engine.evaluate(carrier);

        assert(report.valid());
        assert(report.satisfied);
        assert(report.total_requirements == 1);
    }

    void test_flow_runtime()
    {
        TCarrierFlowRuntime<8> runtime{};

        runtime.record(
            {
                TCarrierFlowDirection::inbound,
                true,
                "accepted inbound flow"
            });

        runtime.record(
            {
                TCarrierFlowDirection::outbound,
                true,
                "accepted outbound flow"
            });

        const auto report = runtime.report();

        assert(report.valid());
        assert(report.total_records == 2);
        assert(report.rejected_records == 0);
    }

    void test_readiness_pipeline()
    {
        TCarrierReadinessReport readiness{};

        readiness.validation_ready = true;
        readiness.requirement_ready = true;
        readiness.flow_ready = true;

        readiness.total_records = 4;
        readiness.rejected_records = 0;

        const auto runtime_view =
            TCarrierRuntimeReadinessView::from_report(
                readiness,
                "runtime-ready");

        assert(runtime_view.operational());
        assert(runtime_view.ready);
        assert(!runtime_view.failed);

        const auto facade_view =
            TAsccCarrierReadinessView::from_runtime_view(
                runtime_view,
                "managerial-projection");

        assert(facade_view.is_valid());
        assert(facade_view.ready());
    }

    void test_protocol_binding_runtime()
    {
        TCarrierProtocolBindingMap<8> bindings{};

        const bool registered =
            bindings.register_binding(
                {
                    TAsccCarrierKind::message,
                    "session-runtime",
                    TCarrierProtocolCompatibility::compatible,
                    "message carrier supports session runtime"
                });

        assert(registered);

        const auto compatibility =
            bindings.compatibility_of(
                TAsccCarrierKind::message,
                "session-runtime");

        assert(
            compatibility
            == TCarrierProtocolCompatibility::compatible);

        assert(
            bindings.compatible(
                TAsccCarrierKind::message,
                "session-runtime"));
    }

    void test_obligation_resolution_runtime()
    {
        TCarrierObligationResolver<8> resolver{};

        const bool registered =
            resolver.register_binding(
                {
                    TAsccCarrierKind::message,
                    TCarrierObligationFamily::validation,
                    true,
                    "message carrier requires validation"
                });

        assert(registered);

        assert(
            resolver.supports(
                TAsccCarrierKind::message,
                TCarrierObligationFamily::validation));

        assert(
            resolver.requires(
                TAsccCarrierKind::message,
                TCarrierObligationFamily::validation));
    }
}

int main()
{
    test_validation_runtime();
    test_requirement_satisfaction_runtime();
    test_flow_runtime();
    test_readiness_pipeline();
    test_protocol_binding_runtime();
    test_obligation_resolution_runtime();

    return 0;
}
