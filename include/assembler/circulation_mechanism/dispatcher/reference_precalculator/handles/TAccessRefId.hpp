#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TAccessRefId.hpp

        Delivery:
            CME-DISPATCHER-PROD-W01 — Production Exposure Execution Contract

        Current responsibility:
            Identifies dispatch access reference.

        Explicit non-ownership:
            - Does not own bridge protocol.
            - Does not own receiver lifecycle.
            - Does not execute persistence.
            - Does not parse payload content.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TAccessRefId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TAccessRefId() noexcept = default;
        constexpr explicit TAccessRefId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TAccessRefId invalid() noexcept { return TAccessRefId{k_invalid_value}; }
        [[nodiscard]] static constexpr TAccessRefId from_raw(value_type v) noexcept { return TAccessRefId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TAccessRefId a, TAccessRefId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TAccessRefId a, TAccessRefId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TAccessRefId> {
        std::size_t operator()(const assembler::circulation_mechanism::TAccessRefId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TAccessRefId::value_type>{}(x.raw());
        }
    };
    }
