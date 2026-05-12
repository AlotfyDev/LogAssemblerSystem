#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::validator;

    auto contract = TLogApiValidatorBindingResolver::MakeDefaultJsonContract();
    assert(contract.IsReadyForBinding());
    assert(contract.capabilities.Supports(TLogApiValidatorCapabilityKind::ValidateContentShape));
    assert(contract.safe_points.Supports(TLogApiValidatorSafePointKind::BeforeValidation));

    auto registry = TLogApiValidatorBindingResolver::MakeDefaultRegistryView();
    assert(registry.HasResolvedBinding("default.json.validator.binding"));

    auto content_registry = TLogApiContentProfileResolver::MakeDefaultRegistryView();
    const auto* json_profile = content_registry.FindByName("default.json.minimal");
    assert(json_profile != nullptr);
    assert(json_profile->validation_required);

    const auto* binding = registry.FindByName("default.json.validator.binding");
    assert(binding != nullptr);

    const char payload[] = "{\"message\":\"hello\"}";
    TLogApiContentInputRef content{payload, sizeof(payload)};

    TLogApiValidationRequest request{content, json_profile, binding};
    assert(request.IsReady());

    auto accepted = TLogApiValidationResult::Accepted();
    assert(accepted.IsAccepted());

    auto binding_view = TLogApiValidatorBindingView::From(*binding);
    assert(binding_view.resolved);
    assert(binding_view.binding_name == "default.json.validator.binding");

    std::cout << "LOGAPI-W03 smoke test passed\\n";
    return 0;
}
