#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {

    enum class TAccessRefDirection : std::uint8_t {
        ingress, dispatch, internal_slot
    };
    } // namespace circulation_mechanism
} // namespace assembler
