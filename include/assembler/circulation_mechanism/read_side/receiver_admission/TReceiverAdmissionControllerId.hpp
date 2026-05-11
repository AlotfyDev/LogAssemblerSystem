#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReceiverAdmissionControllerId.hpp

        Delivery:
            CME-READSIDE-PROD-W03 — ReadSide Backpressure And Receiver Admission Runtime

        Current responsibility:
            Identifies one read-side receiver admission controller.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not invoke receiver.
            - Does not execute bridge runtime.
            - Does not persist payload.
            - Does not mutate PreBridge runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TReceiverAdmissionControllerId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TReceiverAdmissionControllerId() noexcept = default;
        constexpr explicit TReceiverAdmissionControllerId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TReceiverAdmissionControllerId invalid() noexcept { return TReceiverAdmissionControllerId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReceiverAdmissionControllerId from_raw(value_type input) noexcept { return TReceiverAdmissionControllerId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TReceiverAdmissionControllerId lhs, TReceiverAdmissionControllerId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReceiverAdmissionControllerId lhs, TReceiverAdmissionControllerId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side::TReceiverAdmissionControllerId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side::TReceiverAdmissionControllerId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side::TReceiverAdmissionControllerId::value_type>{}(input.raw());
        }
    };
    }
