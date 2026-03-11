# USB Hub Firmware Traceability Matrix

## Purpose

This document maps project facts to architecture boundaries, AI governance rules, and expected validation evidence.

Its purpose is to make the dependency chain explicit:

`fact -> architecture rule -> agent constraint -> validation evidence`

This matrix is intended to reduce assumption-driven firmware changes and improve review consistency.

## How To Use

When a firmware change is proposed:

1. Find the affected fact area.
2. Confirm the fact in `USB_HUB_FW_CHECKLIST.md`.
3. Review the linked rule in `USB_HUB_ARCHITECTURE.md`.
4. Apply the linked constraint in `AGENTS.md`.
5. Collect the listed validation evidence when applicable.

## Traceability Matrix

| Fact Area | Checklist Source | Architecture Impact | Agent Constraint | Validation Evidence |
| --- | --- | --- | --- | --- |
| Toolchain | `1. Toolchain` | Memory model, build assumptions, compiler behavior | No assumption of compiler-dependent behavior | Build output, map file, overlay report |
| Hub SoC | `2. Hub SoC` | Hub behavior, port count, speed capability | Do not infer SoC capability from similar parts | Enumeration logs, descriptor review |
| Clock | `3. Clock` | Timing assumptions, power/reset sequencing | Do not assume oscillator or clock source | Enumeration logs, timing validation, build config review |
| USB role | `4. USB Role` | Hub class behavior, protocol expectations | Do not assume device role or hub mode | Enumeration logs, descriptor review |
| Memory model | `5. Memory Model` | Buffer placement, descriptor access, code/data separation | Do not guess storage model or memory region behavior | Map file, overlay report |
| Interrupt style | `6. Interrupt Style` | ISR concurrency model | Do not introduce unsafe ISR/main shared-state access | Code review, build result, runtime validation |
| Critical section | `7. Critical Section` | Concurrency protection for shared state | Do not modify shared access without confirmed protection model | Code review, runtime validation |
| Descriptor management | `8. Descriptor Management` | Descriptor architecture, enumeration contract | Do not guess descriptor location, owner, or layout | Enumeration logs, host tool verification, descriptor review |
| Vendor command | `9. Vendor Command` | Vendor command protocol, payload layout, host compatibility | No new command without protocol definition, payload layout, and error codes | Host interaction verification, protocol review |
| Firmware update | `10. Firmware Update` | Flash update execution rules, safe region constraints | Do not alter flash behavior without confirmed safe execution region | Map file, flash flow review, update validation evidence |
| Power timing | `11. Power Timing` | Power/reset sequencing | Do not assume reset or port power delay values | Enumeration logs, board config review |
| Hub topology | `12. Hub Topology` | Cross-chip access rules, state visibility behavior | Do not treat remote hub state as local or immediate | Enumeration logs, topology review, bus transaction review |
| Transaction translator | `13. Transaction Translator` | TT model, port transaction scheduling | Do not assume single-TT or multi-TT behavior | Descriptor review, hub behavior verification |
| Tool synchronization | `14. Tool Synchronization` | Protocol and struct compatibility across firmware and host tools | Warn on host-side model impact when struct layout changes | Host tool regression, profile review |
| Build outputs | `15. Build Outputs` | Memory usage, overlays, binary footprint validation | Firmware-impacting changes should include evidence | Map file, overlay report, build log |

## Review Rules

- If a fact is unresolved, the related architecture rule must not be treated as fully satisfied.
- If an architecture-sensitive area changes, the linked memory records should be updated.
- If protocol, descriptor, or flash behavior changes, validation evidence should be attached to the review.

## Related Documents

- `USB_HUB_FW_CHECKLIST.md`
- `USB_HUB_ARCHITECTURE.md`
- `AGENTS.md`
- `WORKFLOW.md`
- `memory/03_decisions.md`
- `memory/04_validation_log.md`
