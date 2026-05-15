#pragma once
#include <array>
#include <cstddef>
#include <string_view>
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"

/**
 * @file TAsccSessionPolicyCatalogView.hpp
 * @brief Administrative facade catalog of session policy profiles supported by ASCC.
 */
namespace assembler::communication_context {
    template <std::size_t Capacity>
    struct TAsccSessionPolicyCatalogView final {
        std::array<TSessionPolicy, Capacity> policies{};
        std::size_t count{0u};
        std::string_view catalog_name{"ascc_session_policy_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return count <= Capacity && !catalog_name.empty(); }
        constexpr bool add(TSessionPolicy policy) noexcept {
            if (count >= Capacity || !policy.is_valid()) return false;
            policies[count++] = policy;
            return true;
        }
        [[nodiscard]] constexpr bool has_policy() const noexcept { return count > 0u; }
        [[nodiscard]] static constexpr TAsccSessionPolicyCatalogView default_session_policies(std::string_view name = "ascc_default_session_policy_catalog") noexcept {
            TAsccSessionPolicyCatalogView<Capacity> view{{}, 0u, name};
            view.add(TSessionPolicy::strict_declaration_session());
            return view;
        }
    };
}
