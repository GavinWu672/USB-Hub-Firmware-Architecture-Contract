# USB Hub Firmware Fact Checklist

## Purpose

This document records project facts that the agent and engineers must not guess.

Use this file as the single source of truth for unresolved firmware inputs. If a required field remains empty, implementation decisions that depend on it must stop until the fact is confirmed.

## Scope

This checklist is primarily intended for:

- Keil C51 based firmware projects
- USB hub firmware bring-up, maintenance, and change review
- Capturing project-specific facts required before implementation

## Global Rules

If a required field is missing:

- Do not infer a value.
- Do not modify firmware logic based on a guess.
- Request clarification.

Required fields must be confirmed when the current change scope depends on them.

## 1. Toolchain

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Compiler | Keil C51 | `.uvprojx` |
| Keil version | `____` | `.uvprojx` or build environment |
| Project file | `____.uvprojx` | Repository |
| Build target | `____` | `.uvprojx` |

## 2. Hub SoC

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Hub controller | `____` | `board.h`, `soc.h` |
| CPU architecture | `8051 / enhanced 8051` | `soc.h` |
| USB speed | `Full-Speed / High-Speed` | SoC spec, firmware config |
| Port count | `____` | SoC spec, descriptors |

## 3. Clock

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Oscillator | `____ MHz` | `clock.c`, `board.h` |
| USB clock source | `____` | `clock.c`, `board.h` |
| CPU clock | `____` | `clock.c`, `board.h` |

## 4. USB Role

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| USB role | `USB Hub` | Firmware architecture |
| Hub mode | `Single TT / Multi TT` | Descriptor set, hub config |
| Power switching mode | `____` | Hub descriptor, firmware config |
| Over-current model | `____` | Hub descriptor, firmware config |
| Hub class handler | `____` | Source tree |
| Source file | `hub_class.c` | Repository |

## 5. Memory Model

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Memory spaces used | `data / idata / xdata / code` | Toolchain, source |
| USB endpoint buffers | `____` | USB stack source |
| Descriptor storage | `____` | `descriptor.c` |
| Source file | `descriptor.c` | Repository |

## 6. Interrupt Style

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| ISR declaration | `void usb_isr(void) interrupt N` | `usb_isr.c` |
| Register bank usage | `using N` | `usb_isr.c` |
| DPTR configuration | `single / dual / extended` | SoC spec, compiler config |
| Source file | `usb_isr.c` | Repository |

## 7. Critical Section

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Enter macro | `ENTER_CRITICAL()` | `system.h` |
| Exit macro | `EXIT_CRITICAL()` | `system.h` |
| Source file | `system.h` | Repository |

## 8. Descriptor Management

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Descriptor storage location | `____` | `descriptor.c` |
| Representation | `____` | `descriptor.c` |
| Descriptor owner module | `____` | Source tree |
| Source file | `descriptor.c` | Repository |

## 9. Vendor Command

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Dispatcher file | `vendor_cmd.c` | Repository |
| Command table location | `vendor_cmd.c` | Repository |
| Protocol document | `____` | Spec set |
| Error code definition | `____` | Spec set |

## 10. Firmware Update

Status: Required

| Field | Value | Source |
| --- | --- | --- |
| Flash layout | `Bootloader / CFU Handler / Application` | Linker, memory map |
| CFU handler definition | `____` | Update design, architecture spec |
| CFU handler region | `____` | Linker, memory map |
| Flash API location | `____` | `flash.c` or equivalent |
| Safe execution region for erase/write | `____` | Linker, architecture spec |
| Source file | `flash.c` | Repository |

## 11. Power Timing

Status: Required if the change affects reset, power control, suspend/resume, or enumeration timing

| Field | Value | Source |
| --- | --- | --- |
| Port power delay | `____ ms` | Board config, hub spec |
| Reset delay | `____ ms` | Board config, hub spec |
| Suspend or resume delay | `____ ms` | Firmware config, hub spec |

## 12. Hub Topology

Status: Optional, but required if cascade topology is used

### Reference Example

```text
Host
  |
Hub A
  |- Port1
  `- Port2 -> Hub B
```

| Field | Value | Source |
| --- | --- | --- |
| Port mapping | `____` | Schematic, firmware config |
| Access path | `I2C / SMBus / Vendor` | Cross-chip design |
| Cascade present | `____` | Architecture decision |

## 13. Transaction Translator

Status: Required if USB 2.0 hub transaction behavior is relevant to the change

| Field | Value | Source |
| --- | --- | --- |
| TT mode | `Single TT / Multi TT` | Descriptor set, hub config |
| TT scheduling policy | `____` | Firmware source, architecture decision |

## 14. Tool Synchronization

Status: Optional

| Field | Value | Source |
| --- | --- | --- |
| Shared protocol structs | `____` | Firmware and host model definitions |
| Host tools | `C# / Swift / Electron` | Tool inventory |
| Profile file | `hub_profile.json` | Repository |
| Profile schema | `HUB_PROFILE_SCHEMA.md` | Repository |

## 15. Build Outputs

Status: Required if the change affects firmware size, memory layout, overlays, descriptors, or flash behavior

| Field | Value | Source |
| --- | --- | --- |
| Map file | `project.map` or `____` | Build output |
| Overlay report | `overlay.txt` or `____` | Build output |
| Code size evidence | `____` | Map file, build log |

## Completion Criteria

This checklist is ready for implementation use only when:

- All required fields used by the target change are filled in.
- Sources are traceable to code, build files, linker outputs, or hardware documentation.
- Any struct layout changes have been propagated to dependent host-side artifacts.
