#pragma once
#include "TCirculationApiVersion.hpp"
#include "TCirculationProfileVersion.hpp"
#include "TCirculationSchemaVersion.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationVersionSet final {
    TCirculationApiVersion api_version{};
    TCirculationProfileVersion profile_version{};
    TCirculationSchemaVersion schema_version{};
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return api_version.is_valid() && profile_version.is_valid() && schema_version.is_valid();
    }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
