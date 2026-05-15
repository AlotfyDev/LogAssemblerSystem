# ASCC-COMP-W03 — Participant To Protocol, Binding, And Carrier Relationship

## Participant To Protocol

Protocol requirements require roles, capabilities, carrier kinds, directions, and protocol families. Participant runtime must match `TParticipantCapabilityRequirement` against `TParticipantCarrierCapability`.

## Participant To Binding

Bindings map participant roles to binding sides. `TParticipantRoleBindingMap` is the participant-side view of that relation.

## Participant To Carrier Runtime

Carrier participation means producing, consuming, observing, or relaying carriers. This is runtime behavior and is represented by `TParticipantCarrierParticipationRuntime`.

## Participant To Obligation Surface

Participants must be bound to surfaces they can provide or consume without exposing endpoint internals. This is represented by `TParticipantObligationSurfaceBinding`.

## Participant To Facade

Facade should expose participant catalog/readiness/evidence, not mutable participant internals.
