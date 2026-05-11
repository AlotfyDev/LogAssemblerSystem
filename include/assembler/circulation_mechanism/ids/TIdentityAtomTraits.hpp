#pragma once

#include "TBoundaryId.hpp"
#include "TContainerId.hpp"
#include "TContainerRegistryIndex.hpp"
#include "TReferenceId.hpp"
#include "TRoundId.hpp"
#include "TSlotIndex.hpp"

#include <type_traits>

/*
    TIdentityAtomTraits.hpp

    Delivery:
        CME-IDS-PROD-W01 — Production Identity Contract

    Responsibility:
        Provides small compile-time helpers for distinguishing CME identity
        atoms and locator atoms.

    Non-ownership:
        Does not create or mutate IDs. Does not define runtime behavior.
*/

namespace assembler {
namespace circulation_mechanism {


template <typename T>
struct TIsCmeIdentityAtom : std::false_type
{
};

template <> struct TIsCmeIdentityAtom<TBoundaryId> : std::true_type {};
template <> struct TIsCmeIdentityAtom<TContainerId> : std::true_type {};
template <> struct TIsCmeIdentityAtom<TContainerRegistryIndex> : std::true_type {};
template <> struct TIsCmeIdentityAtom<TReferenceId> : std::true_type {};
template <> struct TIsCmeIdentityAtom<TRoundId> : std::true_type {};
template <> struct TIsCmeIdentityAtom<TSlotIndex> : std::true_type {};

template <typename T>
struct TIsCmeLocatorAtom : std::false_type
{
};

template <> struct TIsCmeLocatorAtom<TContainerRegistryIndex> : std::true_type {};
template <> struct TIsCmeLocatorAtom<TSlotIndex> : std::true_type {};

template <typename T>
constexpr bool is_cme_identity_atom_v = TIsCmeIdentityAtom<T>::value;

template <typename T>
constexpr bool is_cme_locator_atom_v = TIsCmeLocatorAtom<T>::value;

} // namespace circulation_mechanism
} // namespace assembler
