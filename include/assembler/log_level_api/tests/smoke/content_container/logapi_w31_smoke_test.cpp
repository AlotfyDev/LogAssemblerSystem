#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "assembler/log_level_api/content_container/TLogApiContentContainerCoreSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content_container;

    std::vector<unsigned char> data(8 * 4, 0);

    TLogApiContentContainerShape shape{};
    shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlTick;
    shape.element_count = 4;
    shape.element_size_bytes = 8;
    shape.contiguous = true;

    TLogApiContentContainerRef container{};
    container.id = TLogApiContentContainerId{1};
    container.data = data.data();
    container.size_bytes = data.size();
    container.shape = shape;

    assert(container.IsPresent());
    assert(container.IsFixedContiguousArrayReady());

    auto view = TLogApiContentContainerView::From(container);
    assert(view.present);
    assert(view.fixed_contiguous_ready);
    assert(view.element_count == 4);

    TLogApiContainerParserProfile parser{};
    parser.id = TLogApiContainerParserId{1};
    parser.status = TLogApiContainerParserStatus::Resolved;
    parser.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    parser.element_kind = TLogApiContentContainerElementKind::Mt5MqlTick;
    parser.parser_name = "mt5.tick.container.parser";
    parser.element_parser_name = "mt5.tick.parser";
    parser.supported_schema_name = "mt5.mql_tick";

    assert(parser.IsResolved());
    assert(parser.Matches(shape));

    TLogApiContainerParseRequest request{};
    request.container = container;
    request.parser_profile = parser;
    assert(request.IsReady());

    TLogApiParsedContentBatchRef batch{};
    batch.id = TLogApiParsedContentBatchId{1};
    batch.source_container = container;
    batch.parsed_count = 4;
    batch.parsed = true;
    assert(batch.IsPresent());

    auto batch_view = TLogApiParsedContentBatchView::From(batch);
    assert(batch_view.present);
    assert(batch_view.parsed_count == 4);

    TLogApiContainerParseResult result{};
    result.batch = batch;
    assert(result.IsAccepted());

    auto strategy = TLogApiBatchEnvelopeStrategyDescriptor::BatchAsSingle();
    assert(strategy.IsDeclared());

    TLogApiContentContainerReadiness readiness{};
    readiness.parse_request = request;
    readiness.envelope_strategy = strategy;
    assert(readiness.IsReady());

    std::cout << "LOGAPI-W31 smoke test passed\\n";
    return 0;
}
