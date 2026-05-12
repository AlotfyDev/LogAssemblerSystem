#pragma once

/*
    LOGAPI-W11 — Default C-Style Struct Primitive Schemas

    This header belongs to the default C-style struct primitive content schema
    add-on pack.

    Responsibility:
        Define ABI/layout-sensitive primitive struct schema descriptors,
        fixed-width primitive field descriptors, explicit offsets, sizes,
        alignment, padding, endianness, presence/default flags, and level-specific
        primitive struct schema profiles.

    Boundary:
        This wave defines C-style struct primitive schema descriptors only.
        It must not implement binary parsing, concrete validators, metadata structs,
        timestamp stabilization, envelope assembly, API facade hot-path behavior,
        circulation bindings, or policy assignment.

    Doctrine:
        C-style struct schemas must be layout-specified, not compiler-implied.
        Defaults are bundled conveniences, not a closed content universe.
*/

#include <algorithm>
#include <cstdint>
#include <vector>

#include "TLogApiCStructEndianKind.hpp"
#include "TLogApiCStructFieldDescriptor.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiCStructLayoutDescriptor final {
    std::uint32_t total_size_bytes{0};
    std::uint32_t alignment_bytes{1};
    TLogApiCStructEndianKind endian{TLogApiCStructEndianKind::LittleEndian};
    std::vector<TLogApiCStructFieldDescriptor> fields{};

    [[nodiscard]] bool HasOverlappingFields() const noexcept {
        for (std::size_t i = 0; i < fields.size(); ++i) {
            const auto a0 = fields[i].layout.offset_bytes;
            const auto a1 = fields[i].layout.EndOffset();
            for (std::size_t j = i + 1; j < fields.size(); ++j) {
                const auto b0 = fields[j].layout.offset_bytes;
                const auto b1 = fields[j].layout.EndOffset();
                if (a0 < b1 && b0 < a1) return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (total_size_bytes == 0 || alignment_bytes == 0) return false;
        if (endian == TLogApiCStructEndianKind::Unknown) return false;
        if (fields.empty()) return false;
        for (const auto& field : fields) {
            if (!field.IsDeclared()) return false;
            if (field.layout.EndOffset() > total_size_bytes) return false;
        }
        return !HasOverlappingFields();
    }

    [[nodiscard]] std::size_t RequiredCount() const noexcept {
        std::size_t count = 0;
        for (const auto& field : fields) {
            if (field.presence == TLogApiCStructFieldPresenceKind::Required) ++count;
        }
        return count;
    }

    [[nodiscard]] std::size_t DefaultedCount() const noexcept {
        std::size_t count = 0;
        for (const auto& field : fields) {
            if (field.presence == TLogApiCStructFieldPresenceKind::Defaulted) ++count;
        }
        return count;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
