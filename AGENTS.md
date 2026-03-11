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

## 10. Standard Escalation Mode

### Purpose

Standard Escalation Mode defines how the project should respond when a USB-IF specification appears to conflict with confirmed project behavior.

This mode prevents automatic replacement of project implementation with generic standard interpretations.

### Trigger Conditions

Standard Escalation Mode must be triggered when any of the following occurs:

- A USB-IF reference contradicts a confirmed project fact.
- A firmware change relies on a standard rule that is not reflected in current firmware behavior.
- A reviewer suspects that the implementation deviates from the USB specification.

Example triggers:

- Hub descriptor field behavior differs from USB-IF interpretation.
- Port status or change bits behave differently from the standard expectation.
- Transaction Translator behavior appears inconsistent with hub class rules.

### Escalation Procedure

When a conflict is detected:

1. Stop automatic implementation changes.
2. Identify the affected areas:
   - Project fact: `USB_HUB_FW_CHECKLIST.md`
   - Architecture rule: `USB_HUB_ARCHITECTURE.md`
   - Standard reference: USB-IF source
3. Perform architecture review.
4. Classify the result using one of the following categories:

| Category | Meaning |
| --- | --- |
| Project Implementation Constraint | The project intentionally diverges due to hardware design or SoC limitation |
| Standards Compliance Risk | Implementation may violate the USB specification |
| Documentation Error | Misinterpretation of the specification |

5. Record the resolution in `memory/03_decisions.md`.

### Escalation Output

A completed escalation review should document:

- the relevant USB-IF reference
- the affected firmware behavior
- the classification decision
- the chosen resolution path

No silent behavior changes should occur after a standards conflict.

### When Escalation Is Not Required

Escalation is not required when the USB-IF reference is used only to clarify semantics, such as:

- descriptor field definitions
- port status bit meanings
- hub class request semantics

These cases fall under the reference layer usage defined in `USB_IF_INTEGRATION_PLAN.md`.

## 11. Project Fact Preservation Mode

### Purpose

Project Fact Preservation Mode protects confirmed project facts from being overwritten, reinterpreted, or forgotten across development sessions.

Firmware development often spans multiple tools, sessions, and AI contexts. Without explicit preservation, critical facts may be lost or replaced by assumptions.

### Preservation Principle

Confirmed project facts must be treated as persistent engineering truth until explicitly updated.

Facts must not be silently replaced by:

- standard assumptions
- similar hardware behavior
- inferred defaults
- AI-generated guesses

### Source of Project Facts

Confirmed project facts originate from:

- hardware schematics
- SoC documentation
- linker outputs
- firmware source code
- verified build artifacts

The authoritative location for these facts is:

- `USB_HUB_FW_CHECKLIST.md`

### Fact Preservation Rules

The following rules apply to confirmed facts.

#### Rule 1 - No Silent Replacement

A confirmed fact must not be replaced unless the source evidence changes.

Examples:

- oscillator frequency
- descriptor storage location
- safe flash execution region
- vendor command payload layout
- cascade hub transport path

#### Rule 2 - Fact Updates Require Evidence

Updating a project fact requires:

- updated source reference
- architecture review if the change affects system behavior

#### Rule 3 - Fact Updates Must Be Logged

Any confirmed change must update:

- `memory/02_project_facts.md`

If the change affects system design decisions, also update:

- `memory/03_decisions.md`

#### Rule 4 - AI Must Respect Confirmed Facts

When working with firmware changes, the AI agent must:

- read confirmed facts first
- avoid generating alternative interpretations
- request clarification if a fact appears inconsistent

### Typical Failure Modes Prevented

Project Fact Preservation Mode prevents common firmware errors:

| Failure Mode | Example |
| --- | --- |
| Context loss | Oscillator frequency assumed incorrectly |
| Hardware abstraction error | Treating cross-chip access as local register access |
| Descriptor misplacement | Assuming descriptor location in code memory |
| Flash execution error | Executing erase routine from application region |

### Relationship With Other Governance Layers

Project Fact Preservation Mode works together with:

| Document | Role |
| --- | --- |
| `USB_HUB_FW_CHECKLIST.md` | Authoritative project facts |
| `USB_HUB_ARCHITECTURE.md` | System architecture boundaries |
| `AGENTS.md` | AI behavior constraints |
| `TRACEABILITY_MATRIX.md` | Dependency mapping |
| `memory/` | Persistent project knowledge |

## 12. Document Relationship

This governance file works with the following project documents:

- `USB_HUB_ARCHITECTURE.md`: Architecture rules and implementation boundaries
- `USB_HUB_FW_CHECKLIST.md`: Fact checklist and project-specific required inputs
