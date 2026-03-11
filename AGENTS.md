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

The agent must not:

- Assume local-register timing behavior.
- Implement tight polling loops against a slave hub.
- Depend on immediate visibility of remote register state.

## 3. Flash Update Safety

Flash erase and write operations must execute only from a non-erasable safe region, such as:

- Bootloader
- Common bank
- Fixed safe execution region

The agent must not:

- Modify the bootloader region unless explicitly authorized by the project spec.
- Execute flash erase or write code from an erasable application region.
- Add direct flash programming behavior without a defined flash API.

## 4. Protocol Safety

All protocol structures must:

- Use a fixed byte layout.
- Include explicit reserved or padding bytes where needed.
- Avoid compiler-dependent alignment behavior.

The agent must not rely on:

- Implicit structure packing
- Compiler-specific default alignment
- Host-side reinterpretation without an explicit layout contract

## 5. Vendor Command Governance

A new vendor command requires all of the following before implementation:

1. Protocol definition
2. Payload layout
3. Error code specification

Implementation without a protocol spec is forbidden.

## 6. Tool Synchronization

If firmware struct layout changes, the agent must warn that the following artifacts may also require updates:

- C# models
- Swift structs
- JSON profiles
- Host tools

## 7. Validation Expectations

Any firmware-impacting change should be checked against the following evidence when available:

- Map file memory usage
- Overlay report
- Descriptor layout
- USB enumeration logs

## 8. Document Relationship

This governance file works with the following project documents:

- `USB_HUB_ARCHITECTURE.md`: Architecture rules and implementation boundaries
- `USB_HUB_FW_CHECKLIST.md`: Fact checklist and project-specific required inputs
