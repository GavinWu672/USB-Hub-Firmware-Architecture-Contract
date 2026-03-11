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
3. Review the linked section in `USB_HUB_ARCHITECTURE.md`.
4. Apply the linked constraint in `AGENTS.md`.
5. Collect the listed build-time and runtime evidence when applicable.

## Traceability Matrix

| Fact Area | Checklist Source | Architecture Section | Risk Level | Typical Failure Mode | Agent Constraint | Build-Time Evidence | Runtime Evidence |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Toolchain | `1. Toolchain` | `USB_HUB_ARCHITECTURE.md §5` | Medium | Compiler-dependent layout mismatch | No assumption of compiler-dependent behavior | Build output, map file, overlay report | Host-side protocol compatibility check if applicable |
| Hub SoC | `2. Hub SoC` | `USB_HUB_ARCHITECTURE.md §10` | High | Unsupported speed or hub behavior mismatch | Do not infer SoC capability from similar parts | Build config review, descriptor review | Enumeration logs |
| Clock | `3. Clock` | `USB_HUB_ARCHITECTURE.md §9` | High | Incorrect USB timing or reset timing | Do not assume oscillator or clock source | Build config review | Enumeration logs, timing validation |
| USB role | `4. USB Role` | `USB_HUB_ARCHITECTURE.md §10` | High | Wrong class behavior or invalid descriptors | Do not assume device role or hub mode | Descriptor review | Enumeration logs |
| Memory model | `5. Memory Model` | `USB_HUB_ARCHITECTURE.md §2`, `§6` | High | Wrong buffer placement or descriptor access failure | Do not guess storage model or memory region behavior | Map file, overlay report | Runtime test if memory placement affects behavior |
| Interrupt style | `6. Interrupt Style` | `USB_HUB_ARCHITECTURE.md §7` | High | ISR/main concurrency bug | Do not introduce unsafe ISR/main shared-state access | Code review, build result | Runtime validation |
| Critical section | `7. Critical Section` | `USB_HUB_ARCHITECTURE.md §7` | High | Shared-state corruption | Do not modify shared access without confirmed protection model | Code review | Runtime validation |
| Descriptor management | `8. Descriptor Management` | `USB_HUB_ARCHITECTURE.md §6` | High | Enumeration failure | Do not guess descriptor location, owner, or layout | Descriptor review, binary dump if available | Enumeration logs, host tool verification |
| Vendor command | `9. Vendor Command` | `USB_HUB_ARCHITECTURE.md §4`, `§5` | High | Host-tool protocol breakage | No new command without protocol definition, payload layout, and error codes | Protocol review, shared model review | Host interaction trace, command verification |
| Firmware update | `10. Firmware Update` | `USB_HUB_ARCHITECTURE.md §2`, `§3` | Critical | Firmware brick | Do not alter flash behavior without confirmed safe execution region | Map file, flash flow review | Update validation evidence, device behavior check |
| Power timing | `11. Power Timing` | `USB_HUB_ARCHITECTURE.md §9` | High | Reset or port-power timing failure | Do not assume reset or port power delay values | Board config review | Enumeration logs, timing observation |
| Hub topology | `12. Hub Topology` | `USB_HUB_ARCHITECTURE.md §1` | High | Cross-chip deadlock or stale-state behavior | Do not treat remote hub state as local or immediate | Topology review, bus path review | Enumeration logs, bus transaction review |
| Transaction translator | `13. Transaction Translator` | `USB_HUB_ARCHITECTURE.md §8`, `§10` | High | Split-transaction scheduling failure | Do not assume single-TT or multi-TT behavior | Descriptor review | Hub behavior verification |
| Power switching model | `4. USB Role` | `USB_HUB_ARCHITECTURE.md §10` | High | Wrong port power behavior | Do not assume ganged or individual power switching | Descriptor review, config review | Port power behavior verification |
| Tool synchronization | `14. Tool Synchronization` | `USB_HUB_ARCHITECTURE.md §5` | Medium | Host-side struct mismatch | Warn on host-side model impact when struct layout changes | Shared model review, profile review | Host tool regression |
| Build outputs | `15. Build Outputs` | `USB_HUB_ARCHITECTURE.md §11` | Medium | Undetected memory or overlay regression | Firmware-impacting changes should include evidence | Map file, overlay report, build log | Runtime verification if build changes affect behavior |

## Review Rules

- If a fact is unresolved, the related architecture rule must not be treated as fully satisfied.
- If an architecture-sensitive area changes, the linked memory records should be updated.
- If protocol, descriptor, or flash behavior changes, validation evidence should be attached to the review.
- Critical and high-risk fact areas should be reviewed before medium-risk areas.

## Related Documents

- `USB_HUB_FW_CHECKLIST.md`
- `USB_HUB_ARCHITECTURE.md`
- `AGENTS.md`
- `WORKFLOW.md`
- `.github/PULL_REQUEST_TEMPLATE.md`
- `.gitlab/merge_request_templates/Default.md`
- `memory/03_decisions.md`
- `memory/04_validation_log.md`
