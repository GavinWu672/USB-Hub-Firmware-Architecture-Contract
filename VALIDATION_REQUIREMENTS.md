# USB Hub Firmware Validation Requirements

## Purpose

This document defines change-type-driven validation requirements for USB hub firmware work.

It turns generic validation expectations into concrete evidence rules so firmware changes can be reviewed against the correct validation depth.

## Validation Principle

Validation requirements should scale with firmware risk.

- Low-risk changes may require only build-time evidence.
- Architecture-sensitive changes require stronger runtime or host-visible evidence.
- High-risk firmware changes must not be treated as complete without the required validation artifacts.

## Evidence Categories

| Category | Typical Evidence |
| --- | --- |
| Build-time evidence | build result, `.map` file, overlay report, code size / memory footprint |
| Host-visible evidence | USB enumeration log, host command verification, descriptor dump |
| Runtime behavior evidence | bus trace, update flow result, power sequencing observation |
| Synchronization evidence | host tool regression, schema or profile review |

## Change-Type To Evidence Matrix

| Change Type | Required Evidence | Notes |
| --- | --- | --- |
| Descriptor content or layout | USB enumeration log, descriptor review | Required for host-visible descriptor changes |
| Hub class behavior | USB enumeration log, host request verification | Required when standard hub responses may change |
| Port status or change handling | Host `GET_STATUS` verification, bus trace if needed | Required when port-state semantics or change handling is modified |
| Vendor command protocol | Host interaction verification, protocol review | Required when payload layout, semantics, or error behavior changes |
| Shared struct layout | Host tool regression, profile/schema review | Required when firmware-host shared layout changes |
| `hub_profile.json` or profile schema | Host interaction verification, schema review | Required when host-side profile behavior changes |
| Flash update flow | Update validation evidence, safe-region review | Required when erase/write execution behavior or update routing changes |
| CFU handler behavior or region | Update validation evidence, linker or memory-map review | Required when CFU execution ownership or placement changes |
| Clock or timing constants | USB enumeration log, timing validation | Required when timing-visible behavior may change |
| Memory placement or buffer allocation | `.map` file, overlay report, footprint impact review | Required when memory-space usage changes |
| ISR, reentrancy, or DPTR-sensitive logic | `.map` file, overlay report, runtime validation | Required when interrupt behavior or pointer safety may change |
| Cross-chip access path or topology | Bus transaction review, enumeration log | Required when master/slave coordination behavior changes |
| Power switching or over-current model | Descriptor review, host-visible behavior verification | Required when port power semantics or OC reporting changes |

## Hard Requirements

The following mappings should be treated as hard requirements:

- Descriptor or hub class changes -> enumeration evidence required
- Vendor command or profile changes -> host interaction verification required
- Flash or update-flow changes -> update validation evidence required
- Memory-placement or ISR-sensitive changes -> `.map` and overlay evidence required

If required evidence is missing, the change is not ready to merge.

## Memory Update Rule

If validation is performed, the evidence summary should be recorded in:

- `memory/04_validation_log.md`

If validation reveals architecture impact or unresolved risk, also update:

- `memory/03_decisions.md`

## Related Documents

- `WORKFLOW.md`
- `TRACEABILITY_MATRIX.md`
- `USB_HUB_ARCHITECTURE.md`
- `USB_HUB_FW_CHECKLIST.md`
- `memory/04_validation_log.md`
