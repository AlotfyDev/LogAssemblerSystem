#include <cassert>
#include <iostream>
#include <string>

#include "assembler/log_level_api/metadata_injector/profile_registry/TLogApiMetadataProfileRegistrySurface.hpp"

int main() {
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::metadata_injector::profile_registry;

    auto registry = TLogApiDefaultMetadataProfileRegistry::Make();

    TLogApiMetadataProfileLookupKey key{"default.metadata.struct"};
    auto lookup = registry.Lookup(key);
    assert(lookup.FoundUsable());

    auto view = TLogApiMetadataProfileRegistryView::From(registry);
    assert(view.profile_count == 1);
    assert(view.active_profile_names.size() == 1);

    TLogApiMetadataProfileUpdateSet updates{};
    updates.updates.push_back({
        TLogApiMetadataProfileUpdateKind::ReplaceFieldValue,
        "default.metadata.struct",
        TLogApiMetadataFieldValue{
            TLogApiMetadataFieldId{3},
            TLogApiMetadataFieldValueKind::String,
            std::string{"v2"}
        }
    });

    auto update_result = TLogApiMetadataProfileUpdater::Apply(registry, updates);
    assert(update_result.IsAccepted());

    auto updated = update_result.registry.Lookup(key);
    assert(updated.FoundUsable());

    const auto* value = updated.profile->config.default_values.Find(TLogApiMetadataFieldId{3});
    assert(value != nullptr);
    assert(std::get<std::string>(value->value) == "v2");

    TLogApiMetadataProfileUpdateSet suspend{};
    suspend.updates.push_back({
        TLogApiMetadataProfileUpdateKind::SuspendProfile,
        "default.metadata.struct",
        {}
    });

    auto suspended = TLogApiMetadataProfileUpdater::Apply(update_result.registry, suspend);
    assert(suspended.IsAccepted());
    auto suspended_view = TLogApiMetadataProfileRegistryView::From(suspended.registry);
    assert(suspended_view.active_profile_names.empty());

    std::cout << "LOGAPI-W19 smoke test passed\\n";
    return 0;
}
