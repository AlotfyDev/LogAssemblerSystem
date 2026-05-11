#pragma once

#include <cstdint>
#include <functional>

/*
    TSlotIndex.hpp

    Local dependency copy for CME-SLOT-PROD-W01.

    Responsibility:
        One-based local slot index inside a TContainer layout.

    Non-ownership:
        Does not identify a payload globally. Does not own storage.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSlotIndex final
{
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;

    value_type value{k_invalid_value};

    constexpr TSlotIndex() noexcept = default;
    constexpr explicit TSlotIndex(value_type input_value) noexcept : value(input_value) {}

    [[nodiscard]] static constexpr TSlotIndex invalid() noexcept { return TSlotIndex{k_invalid_value}; }
    [[nodiscard]] static constexpr TSlotIndex from_raw(value_type input_value) noexcept { return TSlotIndex{input_value}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
    [[nodiscard]] constexpr value_type one_based() const noexcept { return value; }
    [[nodiscard]] constexpr value_type zero_based_or(value_type fallback) const noexcept { return is_valid() ? value - 1U : fallback; }

    [[nodiscard]] friend constexpr bool operator==(TSlotIndex lhs, TSlotIndex rhs) noexcept { return lhs.value == rhs.value; }
    [[nodiscard]] friend constexpr bool operator!=(TSlotIndex lhs, TSlotIndex rhs) noexcept { return !(lhs == rhs); }
};

} // namespace circulation_mechanism
} // namespace assembler


namespace std {
template <>
struct hash<assembler::circulation_mechanism::TSlotIndex>
{
    [[nodiscard]] std::size_t operator()(const assembler::circulation_mechanism::TSlotIndex& input) const noexcept
    {
        return std::hash<assembler::circulation_mechanism::TSlotIndex::value_type>{}(input.raw());
    }
};
}
