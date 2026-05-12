#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"
#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"
#include "assembler/log_level_api/api_facade/TLogApiFacadeSurface.hpp"

int main() {
    using namespace assembler::log_level_api::api_configurator;
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::validator;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::timestamp_stabilizer;
    using namespace assembler::log_level_api::api_facade;

    auto config_result = TLogApiConfigurator::Resolve(TLogApiDefaultConfiguration{});
    assert(config_result.IsAccepted());

    auto content_registry = TLogApiContentProfileResolver::MakeDefaultRegistryView();
    const auto* content_profile = content_registry.FindByName(config_result.profile.content_profile_name);
    assert(content_profile != nullptr);

    auto validator_registry = TLogApiValidatorBindingResolver::MakeDefaultRegistryView();
    const auto* validator_binding = validator_registry.FindByName(config_result.profile.validator_binding_name);
    assert(validator_binding != nullptr);

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    assert(metadata_config.IsReady());

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    assert(timestamp_config.IsResolved());

    TLogApiFacadeConfigRef facade_config{};
    facade_config.active_profile = &config_result.profile;
    facade_config.content_profile = content_profile;
    facade_config.validator_binding = validator_binding;
    facade_config.metadata_config = &metadata_config;
    facade_config.timestamp_config = &timestamp_config;
    assert(facade_config.IsReady());

    const char payload[] = "{\"message\":\"hello facade\"}";
    TLogApiContentOnlyInput input{};
    input.content = TLogApiContentInputRef{payload, sizeof(payload)};

    auto result = TLogApiFacade::AcceptContent(input, facade_config);
    assert(result.IsAccepted());
    assert(result.accepted_content.IsValid());

    auto view = TLogApiFacadeView::From(TLogApiFacadeId{1}, facade_config);
    assert(view.ready);
    assert(view.receives_content_only);
    assert(view.active_content_profile == "default.json.minimal");

    TLogApiContentOnlyInput empty{};
    auto rejected = TLogApiFacade::AcceptContent(empty, facade_config);
    assert(!rejected.IsAccepted());
    assert(rejected.HasBlockingIssue());

    std::cout << "LOGAPI-W06 smoke test passed\\n";
    return 0;
}
