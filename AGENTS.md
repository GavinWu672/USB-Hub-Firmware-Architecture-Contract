# USB Hub Firmware AI Governance Rules

## Purpose

This document defines the mandatory AI governance rules for USB hub firmware work.

This project is intended to serve as a reference baseline for Keil C based USB hub firmware development.

The rules in this file are constraints, not suggestions. If required facts are missing, the agent must stop making implementation assumptions and request clarification.

## Scope

This document set is primarily intended for:

- Keil C51 or closely related Keil C firmware projects
- USB hub firmware architecture and implementation work
- Firmware-facing host protocol and update design review

## 1. No-Assumption Policy

The agent must not assume any of the following without an explicit project source:

- Oscillator frequency
- Descriptor location
- Hub topology
- USB role
- Hub port power switching model
- USB stack model
- Vendor command encoding
- Flash execution region

If any required fact is missing:

- Do not infer a value.
- Do not modify firmware logic based on a guess.
- Request clarification first.

## 2. Cross-Chip Safety

Cross-chip register access is governed by the following constraints:

- It is not atomic.
- It is not immediate.
- It must not be treated as local register access.
- It may occur through I2C, SMBus, or vendor command forwarding.
- It may require completion polling with bounded, non-tight polling behavior.

The agent must not:

- Assume local-register timing behavior.
- Implement tight polling loops against a slave hub.
- Depend on immediate visibility of remote register state.

## 3. Architecture Boundary

The architecture rules defined in `USB_HUB_ARCHITECTURE.md` are implementation boundaries.

The agent must not introduce changes that violate those boundaries without explicit architectural review.

Examples include:

- Changing hub topology assumptions
- Altering flash execution safety regions
- Introducing new vendor command protocols without a defined architecture update
- Modifying descriptor layout contracts

## 4. Flash Update Safety

Flash erase and write operations must execute only from a non-erasable safe region, such as:

- Bootloader
- Common bank
- Fixed safe execution region

The agent must not:

- Modify the bootloader region unless explicitly authorized by the project spec.
- Execute flash erase or write code from an erasable application region.
- Add direct flash programming behavior without a defined flash API.

## 5. Protocol Safety

All protocol structures must:

- Use a fixed byte layout.
- Include explicit reserved or padding bytes where needed.
- Avoid compiler-dependent alignment behavior.

The agent must not rely on:

- Implicit structure packing
- Compiler-specific default alignment
- Host-side reinterpretation without an explicit layout contract

Direct casting between protocol structs and raw byte buffers is discouraged unless explicitly defined by the protocol specification.

## 6. Vendor Command Governance

A new vendor command requires all of the following before implementation:

1. Protocol definition
2. Payload layout
3. Error code specification

Implementation without a protocol spec is forbidden.

## 7. Tool Synchronization

If firmware struct layout changes, the agent must warn that the following artifacts may also require updates:

- C# models
- Swift structs
- JSON profiles
- Host tools

## 8. Validation Expectations

Any firmware-impacting change should be checked against the following evidence when available:

- Map file memory usage
- Overlay report
- Descriptor layout
- USB enumeration logs

Changes affecting protocol, descriptors, or flash behavior should include enumeration or host-interaction verification evidence whenever available.

## 9. Standard Conflict Resolution Mode

If the agent detects a conflict between:

- a controlled standards reference such as USB-IF semantics
- and a confirmed project fact or architecture rule

the agent must not silently replace the project behavior with the generic standard interpretation.

The agent must report the conflict using the following structure:

```text
[Standard Conflict Detected]

Standard says: <standard-based interpretation>

Project fact says: <confirmed project-specific behavior>

Decision required: Should I preserve the project fact or flag a compliance risk?
```

Example:

```text
[Standard Conflict Detected]

Standard says: Port Status Bit 3 is reserved.

Project fact says: Used for internal cascade hub status.

Decision required: Should I preserve the project fact or flag a compliance risk?
```

When this mode is triggered, the agent should:

- preserve the current project fact unless explicitly directed otherwise
- flag the issue for architecture review
- record the decision in `memory/03_decisions.md` if resolved

## 10. Document Relationship

This governance file works with the following project documents:

- `USB_HUB_ARCHITECTURE.md`: Architecture rules and implementation boundaries
- `USB_HUB_FW_CHECKLIST.md`: Fact checklist and project-specific required inputs
