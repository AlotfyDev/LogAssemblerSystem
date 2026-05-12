#pragma once

#include <string_view>

#include "assembler/communication_context/obligations/plugin_adapters/ids/TPluginAdapterId.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"

/**
 * @file TPluginAdapterDescriptor.hpp
 * @brief Bridge-visible descriptor for a content-provider plugin-adapter surface.
 *
 * @section ascc_comp_w01_reg05 REG-05 Descriptor Normalization
 * The descriptor is the registry subject.  `TPluginAdapterView` remains a
 * read-only projection, but the registry should not treat a projection as the
 * only original surface record.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This descriptor identifies and describes a bridge-visible adapter surface. It
 * does not own concrete endpoint adapter objects, payload internals, endpoint
 * lifecycle, or pipeline composition.
 */

namespace assembler::communication_context
{
    struct TPluginAdapterDescriptor final
    {
        TPluginAdapterId adapter_id{TPluginAdapterId::invalid()};
        TPluginAdapterView view{TPluginAdapterView::invalid()};
        std::string_view descriptor_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return adapter_id.is_valid()
                && view.is_valid()
                && adapter_id.value == view.adapter_id;
        }

        [[nodiscard]] constexpr TPluginAdapterView as_view() const noexcept
        {
            return view;
        }

        [[nodiscard]] static constexpr TPluginAdapterDescriptor make(
            TPluginAdapterId id,
            TPluginAdapterView adapter_view,
            std::string_view name = {}) noexcept
        {
            return TPluginAdapterDescriptor{
                id,
                adapter_view,
                name
            };
        }

        [[nodiscard]] static constexpr TPluginAdapterDescriptor from_view(
            TPluginAdapterView adapter_view,
            std::string_view name = {}) noexcept
        {
            return TPluginAdapterDescriptor{
                TPluginAdapterId::from_value(adapter_view.adapter_id),
                adapter_view,
                name
            };
        }
    };
}
