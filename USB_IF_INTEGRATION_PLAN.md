# USB-IF Integration Plan for USB Hub Firmware Governance

## Purpose

This document defines how USB-IF specifications should be integrated into this repository without overriding project-specific firmware facts.

The goal is not to import the entire USB-IF corpus into AI context.

The goal is to expose only the USB hub related standard knowledge that is useful for:

- hub class behavior review
- descriptor review
- enumeration review
- TT behavior review
- port power and over-current behavior review

## Integration Principle

USB-IF specifications must be treated as a controlled reference layer, not as the primary truth source for this repository.

This repository uses the following priority model:

1. `USB_HUB_FW_CHECKLIST.md`
2. `USB_HUB_ARCHITECTURE.md`
3. `AGENTS.md`
4. `TRACEABILITY_MATRIX.md`
5. USB-IF hub reference layer

Interpretation:

- Project facts override generic standards context.
- Architecture boundaries override generic implementation patterns.
- AI behavior constraints remain active even when standard references are available.
- USB-IF references may clarify standard semantics, but must not replace confirmed project facts.

## Scope

This integration plan is limited to `USB hub firmware`.

It does not currently target:

- USB Type-C
- USB Power Delivery
- USB4
- unrelated USB device class specifications
- full compliance or certification document sets

## What Should Be Included

Only hub-relevant standard topics should be included in the reference layer.

### Recommended Topic Set

- Hub class requests
- Hub descriptor fields
- Port status bits
- Port change bits
- Hub feature and port feature semantics
- Power switching behavior
- Over-current reporting behavior
- Single-TT versus multi-TT behavior
- Enumeration-related hub constraints

## What Must Not Be Directly Imported

The following should not be directly injected as general AI working context:

- Full USB-IF document corpus
- Full text of unrelated class specifications
- Type-C and PD specifications for a hub-only firmware workflow
- Large compliance and electrical test documents
- Any generic standards text that could override board-specific or SoC-specific facts

## Why Full-Corpus Injection Is Unsafe

Directly loading all USB-IF specifications into AI context creates three problems:

1. Scope dilution
   The corpus is much broader than this project and includes many unrelated domains.

2. Project fact loss
   Standard documents do not answer project-specific facts such as oscillator frequency, descriptor storage location, safe flash execution region, vendor payload layout, or cascade transport path.

3. False authority
   The model may incorrectly apply generic USB rules in places where the project has explicit architecture constraints or implementation-specific safety rules.

## Recommended Reference Model

The recommended design is a topic-indexed reference layer rather than free access to the entire specification set.

### Preferred Access Pattern

- `usb_hub_class_lookup(topic)`
- `usb_hub_descriptor_lookup(field)`
- `usb_hub_port_status_bits()`
- `usb_hub_tt_rules()`
- `usb_hub_power_switching_rules()`

This pattern keeps the reference layer narrow, reviewable, and relevant to hub firmware work.

## Architecture Alignment Rules

USB-IF references may be used to answer:

- What the USB hub class expects
- What descriptor fields mean
- What port status and change bits represent
- What the standard distinguishes between single-TT and multi-TT behavior
- What enumeration-visible hub behavior should look like

USB-IF references must not be used to answer:

- Where descriptors are stored in this project
- What flash region is safe for erase or write execution
- How cascade hub access is transported in this design
- How vendor command payloads are defined in this project
- Whether host tools require synchronization

## Review Rule

If a standard reference conflicts with a confirmed project fact:

- Do not silently replace the project fact.
- Escalate the conflict for architecture review.
- Record the decision in `memory/03_decisions.md` if the conflict is resolved.

## Validation Guidance

If USB-IF references are used to justify a firmware change, the change should still be validated with project evidence such as:

- USB enumeration logs
- Descriptor review
- Host interaction verification
- Map file and overlay outputs when applicable

Standard references do not replace validation.

## Recommended Next Step

If this repository later adds a structured USB-IF reference backend, start with:

1. Hub class requests
2. Hub descriptor field mapping
3. Port status and change bit lookup
4. TT mode behavior lookup
5. Power switching and over-current rule lookup
