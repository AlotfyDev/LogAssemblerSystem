#pragma once
#include <cstdint>

/*
    TReadSidePayloadRef.hpp

    Current responsibility:
        Opaque read-side payload reference for adapter contract evaluation.

    Non-ownership:
        Does not expose payload bytes and does not own payload lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSidePayloadRef final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};

    constexpr TReadSidePayloadRef() noexcept = default;
    constexpr explicit TReadSidePayloadRef(value_type input) noexcept : value(input) {}

    [[nodiscard]] static constexpr TReadSidePayloadRef invalid() noexcept { return TReadSidePayloadRef{k_invalid_value}; }
    [[nodiscard]] static constexpr TReadSidePayloadRef from_raw(value_type input) noexcept { return TReadSidePayloadRef{input}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
