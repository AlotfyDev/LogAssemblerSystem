#pragma once
    #include <cstdint>

    /*
        TContainerFamilyId.hpp

        Wave:
            CME-W06_Bundle_Agent_And_Moderator_Skeleton

        Responsibility:
            Defines a typed identity atom for the owning component.

        Does not own:
            - Runtime behavior.
            - Storage.
            - Bridge or read-side lifecycle.
    */

    namespace assembler {
namespace circulation_mechanism {

    struct TContainerFamilyId final
    {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;

        value_type value{k_invalid_value};

        constexpr TContainerFamilyId() noexcept = default;
        constexpr explicit TContainerFamilyId(value_type input_value) noexcept : value(input_value) {}

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != k_invalid_value;
        }

        [[nodiscard]] friend constexpr bool operator==(TContainerFamilyId lhs, TContainerFamilyId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(TContainerFamilyId lhs, TContainerFamilyId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
    } // namespace circulation_mechanism
} // namespace assembler
