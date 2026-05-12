#pragma once

#include <string_view>

#include "assembler/communication_context/obligations/ports/ids/TPortId.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"

/**
 * @file TPortDescriptor.hpp
 * @brief Bridge-visible descriptor for a receiver/container-provider port surface.
 *
 * @section ascc_comp_w01_reg05 REG-05 Descriptor Normalization
 * The descriptor is the registry subject.  `TPortView` remains a read-only
 * projection, but the registry should not treat a projection as the only
 * original surface record.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This descriptor identifies and describes a bridge-visible port surface. It
 * does not own concrete endpoint port objects, receiver internals, endpoint
 * lifecycle, or pipeline composition.
 */

namespace assembler::communication_context
{
    struct TPortDescriptor final
    {
        TPortId port_id{TPortId::invalid()};
        TPortView view{TPortView::invalid()};
        std::string_view descriptor_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return port_id.is_valid()
                && view.is_valid()
                && port_id.value == view.port_id;
        }

        [[nodiscard]] constexpr TPortView as_view() const noexcept
        {
            return view;
        }

        [[nodiscard]] static constexpr TPortDescriptor make(
            TPortId id,
            TPortView port_view,
            std::string_view name = {}) noexcept
        {
            return TPortDescriptor{
                id,
                port_view,
                name
            };
        }

        [[nodiscard]] static constexpr TPortDescriptor from_view(
            TPortView port_view,
            std::string_view name = {}) noexcept
        {
            return TPortDescriptor{
                TPortId::from_value(port_view.port_id),
                port_view,
                name
            };
        }
    };
}
