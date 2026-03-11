# USB Hub Class Requests Reference

## Purpose

This document is a controlled USB-IF reference artifact for USB hub class request semantics.

It is part of the repository's standard reference layer and is intended only to clarify hub-class standard behavior. It does not override project-specific firmware facts.

## Reference Metadata

| Field | Value |
| --- | --- |
| Source document | Universal Serial Bus Specification, Revision 2.0 |
| Revision | 2.0 |
| Section | 11.24.2 |
| Topic scope | USB hub class requests |
| Extraction date | 2026-03-11 |
| Notes | This is a hub-focused semantic summary for governance and review. Always confirm against the authoritative USB-IF source before compliance decisions. |

## Usage Rules

- Use this file to clarify standard hub request intent.
- Do not use this file to infer project-specific descriptor storage, vendor protocol behavior, or flash execution behavior.
- If standard semantics appear to conflict with confirmed project behavior, follow `AGENTS.md` Standard Conflict Resolution Mode and Standard Escalation Mode.

## Standard Request Summary

| Request | Direction | Typical Target | Semantic Meaning |
| --- | --- | --- | --- |
| `GET_STATUS` | Device-to-host | Hub or port | Read current status fields from the addressed hub or port |
| `CLEAR_FEATURE` | Host-to-device | Hub or port | Clear a hub feature or port feature |
| `SET_FEATURE` | Host-to-device | Hub or port | Set a hub feature or port feature |
| `GET_DESCRIPTOR` | Device-to-host | Hub | Read a descriptor, including hub-related descriptors |
| `SET_DESCRIPTOR` | Host-to-device | Hub | Descriptor write path if supported by implementation or class semantics |
| `CLEAR_TT_BUFFER` | Host-to-device | Hub | Clear a Transaction Translator buffer condition |
| `RESET_TT` | Host-to-device | Hub | Reset the Transaction Translator state |
| `GET_TT_STATE` | Device-to-host | Hub | Read Transaction Translator state if supported |
| `STOP_TT` | Host-to-device | Hub | Stop Transaction Translator activity if supported |

## Review Notes

### 1. Port-Oriented Semantics

Requests such as `GET_STATUS`, `SET_FEATURE`, and `CLEAR_FEATURE` may apply to individual ports. Review must confirm whether the project maps these semantics directly to local hub hardware, shadow state, or remote cascade state.

### 2. TT-Oriented Semantics

TT-related requests are relevant only when TT behavior is part of the hub implementation. Do not assume TT support without project confirmation.

### 3. Descriptor Handling

`GET_DESCRIPTOR` standard meaning does not define where descriptors are stored in firmware. Descriptor ownership and storage location remain project facts.

## Validation Guidance

When firmware changes affect hub class request behavior, collect evidence such as:

- USB enumeration logs
- Host request verification results
- Bus traces if request timing or response semantics are in question

## Related Documents

- `USB_IF_INTEGRATION_PLAN.md`
- `USB_HUB_ARCHITECTURE.md`
- `USB_HUB_FW_CHECKLIST.md`
- `TRACEABILITY_MATRIX.md`
