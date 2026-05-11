#pragma once
#include <cstdint>
/*
    TIngressPayloadEnvelopeRef.hpp
    Opaque prepared envelope reference for ingress. It is content-blind.
*/
namespace assembler {
namespace circulation_mechanism {

struct TIngressPayloadEnvelopeRef final {
    using value_type = std::uint64_t;
    static constexpr value_type k_invalid_value = 0U;
    value_type value{k_invalid_value};
    constexpr TIngressPayloadEnvelopeRef() noexcept = default;
    constexpr explicit TIngressPayloadEnvelopeRef(value_type v) noexcept : value(v) {}
    [[nodiscard]] static constexpr TIngressPayloadEnvelopeRef invalid() noexcept { return TIngressPayloadEnvelopeRef{k_invalid_value}; }
    [[nodiscard]] static constexpr TIngressPayloadEnvelopeRef from_raw(value_type v) noexcept { return TIngressPayloadEnvelopeRef{v}; }
    [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
};
} // namespace circulation_mechanism
} // namespace assembler
