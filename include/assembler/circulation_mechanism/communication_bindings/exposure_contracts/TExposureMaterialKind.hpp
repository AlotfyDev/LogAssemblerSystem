#pragma once
    #include <cstdint>
    /*
        TExposureMaterialKind.hpp
        Delivery: CME-COMMBIND-PROD-W01
        Responsibility: What material the exposure contract permits.
    */
    namespace assembler {
namespace circulation_mechanism {

    enum class TExposureMaterialKind : std::uint8_t {
        none, view_only, dispatch_ref, borrowed_payload_view, copied_payload, moved_payload, implementation_defined
    };
    } // namespace circulation_mechanism
} // namespace assembler
