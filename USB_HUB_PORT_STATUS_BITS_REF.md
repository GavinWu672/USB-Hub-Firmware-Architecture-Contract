# USB Hub Port Status Bits Reference

## Purpose

This document is a controlled USB-IF reference artifact for USB hub port status and port change semantics.

It is part of the repository's standard reference layer and is intended only to clarify standard-visible hub behavior. It does not override project-specific port-state handling or internal cascade signaling.

## Reference Metadata

| Field | Value |
| --- | --- |
| Source document | Universal Serial Bus Specification, Revision 2.0 |
| Revision | 2.0 |
| Topic scope | USB hub port status bits and port change bits |
| Extraction date | 2026-03-11 |
| Notes | This is a hub-focused semantic summary for governance and review. Always confirm against the authoritative USB-IF source before compliance decisions. |

## Usage Rules

- Use this file to interpret standard-visible port status and port change semantics.
- Do not use this file to infer internal firmware shadow register layout or private cascade signaling.
- If a standard-visible bit meaning appears to conflict with confirmed project behavior, trigger the conflict process defined in `AGENTS.md`.

## Port Status Semantic Categories

| Category | Meaning |
| --- | --- |
| Connection state | Whether a device is currently attached to the downstream port |
| Enable state | Whether the port is enabled for traffic |
| Suspend state | Whether the port is in suspend |
| Over-current state | Whether over-current is indicated |
| Reset state | Whether the port is currently in reset |
| Power state | Whether port power is applied |
| Speed indication | Standard speed-related interpretation if exposed by the hub implementation |
| Change indicators | Edge or event indicators corresponding to status transitions |

## Review Notes

### 1. Status vs Change Semantics

Status bits describe current state. Change bits typically represent an observed transition that must be handled carefully.

Firmware review should confirm:

- how status is captured
- how change bits are cleared
- whether event handling can lose transitions

### 2. Internal vs Standard-Visible Meaning

A project may maintain internal shadow state or private cascade metadata that is not identical to the USB-visible port status view.

Internal firmware-only state must not be silently described as if it were USB-IF-defined port status.

### 3. Multi-Chip Hub Review

For cascade or multi-chip designs, review must distinguish between:

- local hardware status
- cached remote state
- freshly queried remote state

Standard-visible responses should not assume remote state is immediate or atomic.

## Validation Guidance

When firmware changes affect port status or port change handling, collect evidence such as:

- host-side `GET_STATUS` verification
- USB enumeration logs
- bus traces when timing or state ordering is in question

## Related Documents

- `USB_IF_INTEGRATION_PLAN.md`
- `USB_HUB_ARCHITECTURE.md`
- `AGENTS.md`
- `TRACEABILITY_MATRIX.md`
