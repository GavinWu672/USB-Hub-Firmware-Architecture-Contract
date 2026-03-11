# Hub Profile Schema

## Purpose

This document defines the expected schema for `hub_profile.json` so that firmware-side struct changes can be traced to host-side JSON profile updates.

This schema description is documentation-first. It does not imply that `hub_profile.json` already exists for every project.

## Scope

Use this schema only for project profiles that mirror firmware-visible hub capabilities, protocol fields, or topology data.

It must not be used as a replacement for:

- `USB_HUB_FW_CHECKLIST.md`
- `USB_HUB_ARCHITECTURE.md`
- formal protocol layout documents

## Required Top-Level Fields

| Field | Type | Description |
| --- | --- | --- |
| `profileVersion` | string | Version of the host-side profile format |
| `deviceRole` | string | Expected to be `usb-hub` for this repository scope |
| `vid` | integer or string | USB vendor ID |
| `pid` | integer or string | USB product ID |
| `portCount` | integer | Number of downstream ports |
| `hubMode` | string | `single-tt` or `multi-tt` if applicable |
| `powerSwitchingMode` | string | `ganged` or `individual` |
| `overCurrentModel` | string | `global` or `per-port` |

## Optional Structured Fields

### `descriptor`

Descriptor metadata mirrored for host-side tooling.

| Field | Type | Description |
| --- | --- | --- |
| `storageLocation` | string | Firmware descriptor storage location if exposed to tools |
| `ownerModule` | string | Source module owning descriptor content |
| `representation` | string | `byte-array`, `struct`, or another documented representation |

### `topology`

Topology information if the project models cascade behavior.

| Field | Type | Description |
| --- | --- | --- |
| `cascadePresent` | boolean | Whether a downstream slave hub exists |
| `accessPath` | string | `i2c`, `smbus`, `vendor`, or another documented path |
| `portMapping` | string or object | Project-defined mapping of logical to physical ports |

### `protocol`

Shared protocol metadata for host tools.

| Field | Type | Description |
| --- | --- | --- |
| `vendorCommandVersion` | string | Version of vendor command contract |
| `structLayoutVersion` | string | Version of firmware/host shared struct layout |

## Synchronization Rule

If firmware-visible struct layout, descriptor-visible behavior, topology exposure, or power model changes, the following should be reviewed together:

- `hub_profile.json`
- `HUB_PROFILE_SCHEMA.md`
- host-side models or parsers

## Validation Expectations

When `hub_profile.json` changes, review should confirm:

- field names still map to documented firmware concepts
- enum-like values still match architecture terminology
- dependent host tools remain compatible
