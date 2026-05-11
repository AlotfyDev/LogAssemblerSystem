#pragma once
#include "../common/TReadSideAdapterContract.hpp"

/*
    TReadSideAdapterContractView.hpp

    Read-only projection of adapter contract.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideAdapterContractView final {
    TReadSideAdapterContract contract{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return contract.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return contract.ready(); }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
