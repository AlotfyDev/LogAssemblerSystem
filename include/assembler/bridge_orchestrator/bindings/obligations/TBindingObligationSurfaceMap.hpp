#pragma once
#include <string_view>
/**
 * @file TBindingObligationSurfaceMap.hpp
 * @brief Descriptor mapping a binding to plugin-adapter and port obligation surfaces.
 *
 * Bridges binding descriptors to future endpoint invocation descriptors without
 * executing any endpoint call.
 */
namespace assembler::communication_context {
struct TBindingObligationSurfaceMap final {
    std::string_view plugin_adapter_surface{}, port_surface{}, operation_family{};
    bool plugin_adapter_required{true}, port_required{true};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return !plugin_adapter_surface.empty() && !port_surface.empty() && !operation_family.empty(); }
    [[nodiscard]] static constexpr TBindingObligationSurfaceMap envelope_placement(std::string_view adapter="envelope_plugin_adapter", std::string_view port="envelope_placement_port") noexcept { return {adapter,port,"envelope_placement",true,true}; }
};
}
