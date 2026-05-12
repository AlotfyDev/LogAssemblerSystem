#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content_container/TLogApiContentContainerCoreSurface.hpp"
#include "assembler/log_level_api/content_lifetime/TLogApiContentLifetimeSurface.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content_lifetime;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::content_container;

    const char payload[] = "lifetime-payload";
    TLogApiContentInputRef content{payload, sizeof(payload)};

    auto borrowed_desc = TLogApiContentLifetimeDefaultProfiles::BorrowedDuringCall();
    auto borrowed_lease = TLogApiContentLifetimeDefaultProfiles::ActiveLease(1, borrowed_desc);

    TLogApiBorrowedContentRef borrowed{content, borrowed_lease};
    assert(borrowed.IsUsableDuringCall());
    assert(!borrowed.lease.AllowsHandoff());

    auto stable_desc = TLogApiContentLifetimeDefaultProfiles::StableUntilHandoff();
    auto stable_lease = TLogApiContentLifetimeDefaultProfiles::ActiveLease(2, stable_desc);

    TLogApiStableContentRef stable{content, stable_lease};
    assert(stable.IsSafeForHandoff());

    auto report = TLogApiContentRefLifetimeGate::Evaluate(stable_lease);
    assert(report.IsAccepted());
    assert(TLogApiContentRefLifetimeGate::AllowsHandoff(stable_lease));

    TLogApiParsedContentRef parsed{};
    parsed.parsed_kind = TLogApiParsedContentKind::OpaqueContentRef;
    parsed.source_content = content;
    parsed.parsed = false;

    TLogApiParsedContentLifetimeRef parsed_lifetime{parsed, stable_lease};
    assert(parsed_lifetime.IsPresent());
    assert(parsed_lifetime.IsSafeForHandoff());

    TLogApiContentContainerShape shape{};
    shape.container_kind = TLogApiContentContainerKind::OpaqueArray;
    shape.element_kind = TLogApiContentContainerElementKind::OpaquePayload;
    shape.element_count = 1;
    shape.element_size_bytes = sizeof(payload);
    shape.contiguous = true;

    TLogApiContentContainerRef container{};
    container.id = TLogApiContentContainerId{1};
    container.data = payload;
    container.size_bytes = sizeof(payload);
    container.shape = shape;

    TLogApiParsedContentBatchRef batch{};
    batch.id = TLogApiParsedContentBatchId{1};
    batch.source_container = container;
    batch.parsed_count = 1;
    batch.parsed = true;

    TLogApiParsedBatchLifetimeRef batch_lifetime{batch, stable_lease};
    assert(batch_lifetime.IsPresent());
    assert(batch_lifetime.IsSafeForHandoff());

    auto view = TLogApiContentLifetimeView::From(stable_lease);
    assert(view.active);
    assert(view.safe_for_handoff);
    assert(view.label == "stable_until_handoff");

    TLogApiContentRefLease expired{};
    expired.id = TLogApiContentRefLeaseId{3};
    expired.status = TLogApiContentRefLeaseStatus::Expired;
    expired.lifetime = stable_desc;

    auto rejected = TLogApiContentRefLifetimeGate::Evaluate(expired);
    assert(!rejected.IsAccepted());
    assert(rejected.HasBlockingIssue());

    std::cout << "LOGAPI-EXT-W03 smoke test passed\\n";
    return 0;
}
