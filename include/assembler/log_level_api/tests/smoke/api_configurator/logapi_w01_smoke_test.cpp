#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"

int main() {
    using namespace assembler::log_level_api::api_configurator;

    TLogApiDefaultConfiguration defaults{};
    auto result = TLogApiConfigurator::Resolve(defaults);
    assert(result.IsAccepted());
    assert(result.profile.IsReadyForConsumingPath());

    auto view = TLogApiConfigurationView::From(result.profile);
    assert(view.ready_for_consuming_path);
    assert(view.schema_path == "json");
    assert(view.assembler_family == "validator_composed_envelope_assembler");

    TLogApiConfigurationPatch patch{};
    patch.schema_path = TLogApiSchemaPathKind::CStyleStructPrimitives;
    patch.assembler_family = TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler;
    patch.validation_required = false;
    patch.validator_binding_name = std::string{};

    auto patched = TLogApiConfigurator::Resolve(defaults, patch);
    assert(patched.IsAccepted());
    assert(patched.profile.schema_path == TLogApiSchemaPathKind::CStyleStructPrimitives);
    assert(patched.profile.assembler_family == TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler);
    assert(!patched.profile.validation_required);

    std::cout << "LOGAPI-W01 smoke test passed\\n";
    return 0;
}
