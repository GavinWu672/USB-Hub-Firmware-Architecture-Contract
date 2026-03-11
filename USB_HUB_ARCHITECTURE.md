# USB Hub Firmware AI-Safe Architecture Spec

## Purpose

This document defines the firmware architecture boundaries, safety rules, and implementation model for the USB hub project.

This file describes architectural intent and non-negotiable design constraints. Project-specific facts that are still unknown must remain unresolved until they are filled in within `USB_HUB_FW_CHECKLIST.md`.

## Scope

This architecture spec is primarily intended to be used as a design reference for:

- Keil C based firmware projects
- USB hub firmware implementations
- Architecture review before code generation or firmware modification

## 1. Hub Topology

### Reference Topology Example

```text
Host
  |
Hub A
  |- Port1 -> Device
  `- Port2 -> Hub B
```

### Cross-Chip Access Model

Slave hub register access may occur through one of the following paths:

- I2C
- SMBus
- Vendor command tunnel

### Cross-Chip Access Rules

- Cross-chip register access is not atomic.
- Cross-chip register access is not immediate.
- Firmware must not treat remote state as if it were local register state.
- Firmware must not implement tight polling loops against a slave hub.
- Firmware must not assume local register access timing for cross-chip operations.
- Remote hub state may be stale due to transport latency.
- Firmware must tolerate delayed or reordered state visibility.

## 2. Firmware Memory Layout

### Reference Layout

```text
+------------+-------------+-------------+-------------+
| Bootloader | Common Bank | CFU Handler | Application |
+------------+-------------+-------------+-------------+
```

### Flash Region Rules

| Region | Executable | Erasable |
| --- | --- | --- |
| Bootloader | Yes | No |
| Common Bank | Yes | No |
| Application | Yes | Yes |

Notes:

- The exact memory addresses are project-specific facts and must be defined separately.
- If `CFU Handler` resides in a dedicated region, its execution and erase policy must be explicitly documented in the checklist or linker outputs.

### Resource Allocation Guidance

For C51-style memory spaces, allocation policy should be explicit rather than implied.

Typical guidance:

- `data`: only the most frequently accessed counters and flags
- `idata`: stack and ordinary local variables
- `xdata`: USB descriptors, large buffers, and cross-chip state tables

Additional rules:

- Buffers should be pre-allocated in `xdata` unless a smaller and explicitly justified placement is required.
- Large local arrays should not be declared inside functions on constrained 8051 targets.
- Stack growth risk must be considered together with local variable usage in `idata`.

Actual placement remains a project fact and must be confirmed from source or build outputs.

## 3. Flash Update Execution Rules

During flash erase or write:

- Program execution must remain in a non-erasable safe region.
- Interrupts must be disabled if required by the flash programming model.
- USB transfers must be paused or explicitly controlled.
- Only approved flash APIs may be used.

Allowed flash abstraction examples:

- `flash_write()`
- `flash_erase()`

Forbidden behavior:

- Direct register-level flash programming without a defined API contract
- Executing erase or write routines from an erasable application area
- Modifying the bootloader region without an explicit update design

## 4. Vendor Command Protocol

### USB Vendor Request Direction

- `0x40`: Host to device
- `0xC0`: Device to host

### Dispatcher Model

Reference dispatch pattern:

```c
switch (bRequest)
{
    /* command handlers */
}
```

### Governance Rules

- New vendor commands require protocol definition first.
- Each new command must define payload layout and error behavior.
- Command behavior must not rely on compiler-dependent structure layout.
- Vendor command payloads should include reserved fields for forward compatibility.
- Protocol versioning must be defined if payload layouts change.

## 5. Protocol Struct Rules

All protocol structs must:

- Define a fixed byte layout.
- Include explicit reserved bytes where alignment or future extension is needed.
- Avoid compiler-dependent padding assumptions.

Reference example:

```c
struct HUB_INFO
{
    u16 vid;
    u16 pid;
    u8 portCount;
    u8 reserved[3];
};
```

## 6. Descriptor Architecture

Descriptor storage location must be explicitly defined.

Descriptors may reside in:

- Code memory
- External memory
- Another explicitly documented storage region

Descriptor rules:

- Descriptor layout must remain consistent with host enumeration expectations.
- Descriptor modification must not occur without validating enumeration behavior.
- Descriptor ownership must be traceable to a defined source file or generated artifact.

## 7. Interrupt Concurrency Model

Hub firmware commonly spans ISR and main-loop execution contexts.

Concurrency rules:

- Shared flags between ISR and main context must be declared `volatile`.
- Multi-byte counters or state accessed from both ISR and main context must be protected by a critical section.
- ISR execution must remain minimal.
- ISR code must not contain blocking loops.
- Functions shared between `main` and ISR context must be reviewed for reentrancy.
- If a function is callable from both `main` and ISR context, the design must explicitly choose one of:
  - reentrant handling
  - single-context ownership
  - protected shared access

### DPTR Safety

On baseline 8051 targets with a single DPTR, ISR-side `xdata` access may corrupt main-context pointer state if not protected.

Rules:

- ISR code must preserve pointer state when accessing `xdata` on single-DPTR targets.
- AI must not assume multiple DPTR support unless confirmed by project facts.
- High-frequency ISR logic should avoid unnecessary `xdata` traffic.

### Bus Ownership

Long-latency physical bus access such as I2C or SMBus must have explicit ownership rules.

Rules:

- Cross-chip bus transactions should run at task level or background level.
- ISR context must not initiate blocking physical bus transfers.
- Firmware must not allow concurrent ownership of the same cross-chip transport path without an explicit arbitration design.

## 8. Transaction Translator Model

The hub implementation must define whether the device operates in:

- `single-TT` mode
- `multi-TT` mode

Changes affecting port transaction scheduling must be validated against hub class behavior and descriptor expectations.

## 9. Power and Reset Sequencing

### Reference Power-On Sequence

1. Clock initialization
2. USB PHY initialization
3. Hub core initialization
4. Port power enable

### Timing Constants

The following values are required project facts and must not be guessed:

- Port power delay: `__ ms`
- Reset delay: `__ ms`

## 10. Hub Class Behavior

Reference ownership model:

- Hub class request handling: `hub_class.c`
- Port status bitmap source: `hub_port.c`

### Behavioral Dimensions

- Power switching mode: `ganged` or `individual`
- Over-current model: `global` or `per-port`

These selections must be confirmed by project facts before implementation changes are made.

### Access Hierarchy

For multi-chip hub designs, access paths should be treated with explicit latency classes:

- `L1 Direct`: direct access to local master-hub registers
- `L2 Proxy`: local shadow or cached state representing remote hub state
- `L3 Remote`: actual bus transactions to a slave hub

Rules:

- `L3 Remote` access is high-latency and must not be assumed safe inside ISR context.
- USB request paths should prefer `L1 Direct` or validated `L2 Proxy` state whenever timing-sensitive.
- Remote state synchronization should be designed as an asynchronous coordination path, not as an immediate register read model.

### Shadow RAM Priority

Timing-sensitive standard USB request handling should prefer local shadow state over blocking remote state fetches.

Rules:

- Standard USB class requests should read from local shadow or cached state whenever architecture permits.
- Request handling must not stall on remote multi-chip polling in timing-sensitive paths.
- If remote refresh is required, it should be handled asynchronously outside the critical request-response path.

### Port Status Change Handling

Port status and change bits may be hardware-driven and asynchronous.

Rules:

- Firmware must avoid unsafe clear-then-handle patterns that can lose events.
- Change-bit handling should use a read-capture-handle-clear model or an equivalent safe event-preservation design.
- AI must not assume hardware state remains unchanged between status read and bit clear.

## 11. Validation Requirements

Any architecture-sensitive firmware change should be validated against:

- Map file memory usage
- Overlay report
- Descriptor layout
- USB enumeration logs

USB enumeration should be validated with a host tool, protocol trace, or analyzer whenever available.

## 12. Related Documents

- `AGENTS.md`: AI governance and safety rules
- `USB_HUB_FW_CHECKLIST.md`: Required project facts and unresolved inputs
- `TRACEABILITY_MATRIX.md`: Fact-to-rule dependency mapping
- `WORKFLOW.md`: Operational review and validation process
