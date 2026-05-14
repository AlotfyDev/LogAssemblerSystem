#pragma once
#include <string_view>
#include "assembler/communication_context/bindings/obligations/TBindingObligationSurfaceMap.hpp"
#include "assembler/communication_context/bindings/roles/TBindingParticipantRoleMap.hpp"
/**
 * @file TConcreteBindingInvocationDescriptor.hpp
 * @brief Descriptor for a concrete binding's possible invocation path.
 *
 * Describes whether a concrete binding can support an invocation path through
 * mapped participant roles and obligation surfaces. It does not execute that
 * invocation.
 */
namespace assembler::communication_context {
struct TConcreteBindingInvocationDescriptor final {
    TBindingParticipantRoleMap role_map{};
    TBindingObligationSurfaceMap obligation_map{};
    bool invocation_supported{false};
    std::string_view descriptor_name{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return role_map.is_valid() && obligation_map.is_valid() && !descriptor_name.empty(); }
    [[nodiscard]] constexpr bool can_invoke() const noexcept { return is_valid() && invocation_supported; }
    [[nodiscard]] static constexpr TConcreteBindingInvocationDescriptor envelope_placement_descriptor(std::string_view name="envelope_placement_binding_invocation_descriptor") noexcept { return {TBindingParticipantRoleMap::content_to_receiver(), TBindingObligationSurfaceMap::envelope_placement(), true, name}; }
};
}
