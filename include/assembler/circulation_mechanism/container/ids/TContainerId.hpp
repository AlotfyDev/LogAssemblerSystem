#pragma once
    #include <cstdint>
    #include <functional>
    namespace assembler {
namespace circulation_mechanism {

    struct TContainerId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TContainerId() noexcept = default;
        constexpr explicit TContainerId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TContainerId invalid() noexcept { return TContainerId{k_invalid_value}; }
        [[nodiscard]] static constexpr TContainerId from_raw(value_type v) noexcept { return TContainerId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TContainerId a,TContainerId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TContainerId a,TContainerId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TContainerId> {
        std::size_t operator()(const assembler::circulation_mechanism::TContainerId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TContainerId::value_type>{}(x.raw());
        }
    };
    }
