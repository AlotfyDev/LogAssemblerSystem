#include "assembler/circulation_mechanism/circulation_mechanism_concurrency.hpp"

using namespace assembler::circulation_mechanism::concurrency;

int main()
{
    constexpr auto single = TSingleWriterProfile::make(TCirculationConcurrencyProfileId::from_raw(1));
    static_assert(single.is_valid(), "single writer profile valid");
    static_assert(single.accepted(), "single writer profile accepted");
    static_assert(single.validation_issue() == TCirculationConcurrencyIssueKind::none, "no issue");

    constexpr auto independent = TIndependentInstanceProfile::make(TCirculationConcurrencyProfileId::from_raw(2));
    static_assert(independent.accepted(), "independent instance profile accepted");

    constexpr auto guarantee = TNoInternalThreadingGuarantee::make();
    static_assert(guarantee.production_safe_default(), "no internal threading guarantee safe");

    constexpr TCirculationConcurrencyProfileView view{independent};
    static_assert(view.is_valid(), "view valid");
    static_assert(view.accepted(), "view accepted");

    constexpr TCirculationConcurrencyReport report{
        TCirculationConcurrencyReportId::from_raw(3),
        independent.mode,
        independent.validation_issue(),
        independent.accepted()
    };
    static_assert(report.passed(), "report passed");

    return 0;
}
