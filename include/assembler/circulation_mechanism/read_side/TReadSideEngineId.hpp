#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideEngineId.hpp

        Delivery:
            CME-READSIDE-PROD-W01 — ReadSide Engine Facade And Injection Surface

        Current responsibility:
            Identifies one injectable ReadSide circulation engine instance.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not own PreBridge runtime.
            - Does not own Bridge Orchestrator internals.
            - Does not implement receiver/addon behavior.
            - Does not perform persistence or telemetry export.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TReadSideEngineId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideEngineId() noexcept = default;
        constexpr explicit TReadSideEngineId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideEngineId invalid() noexcept { return TReadSideEngineId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideEngineId from_raw(value_type input) noexcept { return TReadSideEngineId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideEngineId lhs, TReadSideEngineId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideEngineId lhs, TReadSideEngineId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side::TReadSideEngineId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side::TReadSideEngineId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side::TReadSideEngineId::value_type>{}(input.raw());
        }
    };
    }
