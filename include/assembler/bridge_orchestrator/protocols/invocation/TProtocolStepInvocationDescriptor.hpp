#pragma once
#include <string_view>
#include "assembler/communication_context/protocols/bindings/TProtocolStepObligationBinding.hpp"
#include "assembler/communication_context/protocols/bindings/TProtocolStepRequirementBinding.hpp"

/**
 * @file TProtocolStepInvocationDescriptor.hpp
 * @brief Describes a possible invocation associated with a protocol step.
 *
 * This descriptor does not execute the invocation. It lets bridge execution
 * layers reason about whether a protocol step has an invocation path.
 */
namespace assembler::communication_context {
    struct TProtocolStepInvocationDescriptor final {
        TProtocolStepRequirementBinding requirement_binding{};
        TProtocolStepObligationBinding obligation_binding{};
        bool invocation_required{false};
        bool evidence_required{true};
        std::string_view descriptor_name{};
        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return requirement_binding.is_valid()
                && obligation_binding.is_valid()
                && !descriptor_name.empty();
        }
        [[nodiscard]] constexpr bool can_attempt_invocation() const noexcept {
            return is_valid();
        }
    };
}
