#pragma once
#include <cstdint>
/*
    TContainerTimeRange.hpp
    Delivery: CME-CONTAINER-PROD-W01
    Responsibility: Container-owned time range metadata for ordering/diagnostics/eviction.
*/
namespace assembler {
namespace circulation_mechanism {

struct TContainerTimeRange final {
    std::int64_t first_timestamp{0};
    std::int64_t last_timestamp{0};
    bool has_value{false};
    bool complete{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return !has_value || first_timestamp <= last_timestamp; }
    [[nodiscard]] constexpr bool empty() const noexcept { return !has_value; }
    [[nodiscard]] constexpr bool is_orderable() const noexcept { return has_value && is_valid(); }
    [[nodiscard]] constexpr std::int64_t span() const noexcept { return has_value ? (last_timestamp - first_timestamp) : 0; }
    [[nodiscard]] constexpr bool older_than(TContainerTimeRange other) const noexcept { return is_orderable() && other.is_orderable() && first_timestamp < other.first_timestamp; }
    constexpr void clear() noexcept { first_timestamp = 0; last_timestamp = 0; has_value = false; complete = false; }
    constexpr bool include(std::int64_t ts) noexcept {
        if (!has_value) { first_timestamp = ts; last_timestamp = ts; has_value = true; complete = true; return true; }
        if (ts < first_timestamp) first_timestamp = ts;
        if (ts > last_timestamp) last_timestamp = ts;
        return true;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
