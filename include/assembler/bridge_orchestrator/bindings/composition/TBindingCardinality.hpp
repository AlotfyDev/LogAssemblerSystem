#pragma once

#include <string_view>

/**
 * @file TBindingCardinality.hpp
 * @brief Cardinality vocabulary for ASCC binding composition metadata.
 *
 * @section ascc_comp_w04 Purpose
 * Cardinality describes the participant-count shape of a binding as metadata.
 * It does not execute binding, materialize sessions, invoke endpoints, or
 * replace channel topology rules.
 */

namespace assembler::communication_context
{
    enum class TBindingCardinality
    {
        unknown,
        one_to_one,
        one_to_many,
        many_to_one,
        many_to_many,
        observer_only
    };

    [[nodiscard]] constexpr bool is_single_pair_cardinality(
        TBindingCardinality cardinality) noexcept
    {
        return cardinality == TBindingCardinality::one_to_one;
    }

    [[nodiscard]] constexpr bool allows_multiple_sources(
        TBindingCardinality cardinality) noexcept
    {
        return cardinality == TBindingCardinality::many_to_one
            || cardinality == TBindingCardinality::many_to_many;
    }

    [[nodiscard]] constexpr bool allows_multiple_targets(
        TBindingCardinality cardinality) noexcept
    {
        return cardinality == TBindingCardinality::one_to_many
            || cardinality == TBindingCardinality::many_to_many;
    }

    [[nodiscard]] constexpr bool is_observer_only_cardinality(
        TBindingCardinality cardinality) noexcept
    {
        return cardinality == TBindingCardinality::observer_only;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBindingCardinality cardinality) noexcept
    {
        switch (cardinality)
        {
            case TBindingCardinality::unknown: return "unknown";
            case TBindingCardinality::one_to_one: return "one_to_one";
            case TBindingCardinality::one_to_many: return "one_to_many";
            case TBindingCardinality::many_to_one: return "many_to_one";
            case TBindingCardinality::many_to_many: return "many_to_many";
            case TBindingCardinality::observer_only: return "observer_only";
        }

        return "unknown";
    }
}
