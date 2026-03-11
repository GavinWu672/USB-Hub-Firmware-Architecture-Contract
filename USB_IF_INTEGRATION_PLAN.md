# USB-IF Integration Plan for USB Hub Firmware Governance (v2)

## Purpose

This document defines how USB-IF specifications should be integrated into this repository without overriding project-specific firmware facts.

The goal is not to import the entire USB-IF document corpus into AI context.

The goal is to expose only the hub-relevant standard semantics required for:

- hub class behavior review
- descriptor interpretation
- enumeration review
- transaction translator (TT) behavior review
- port power and over-current behavior review

USB-IF specifications are treated as a controlled reference layer, not as the primary truth source for this repository.

## Integration Priority Model

This repository follows the following precedence model:

1. `USB_HUB_FW_CHECKLIST.md`
2. `USB_HUB_ARCHITECTURE.md`
3. `AGENTS.md`
4. `TRACEABILITY_MATRIX.md`
5. USB-IF hub reference layer

Interpretation:

- Project facts override generic standards context.
- Architecture boundaries override generic implementation patterns.
- AI governance constraints remain active even when standard references are available.
- USB-IF references clarify standard semantics but must not replace confirmed project facts.

## Scope

This integration plan is limited to USB Hub firmware governance.

The following domains are out of scope:

- USB Type-C specifications
- USB Power Delivery specifications
- USB4 specifications
- unrelated USB device class specifications
- electrical compliance and certification test suites

If future firmware work requires these domains, they must be introduced as separate controlled reference layers.

## Interpretation Boundary

USB-IF references are semantic references, not implementation authority.

They may explain:

- what a hub descriptor field means
- what a hub class request represents
- what a port status bit indicates
- what the standard distinguishes between single-TT and multi-TT behavior

They must not be used to determine:

- where descriptors are stored in this firmware
- what flash region is safe for erase/write execution
- how cascade hub communication is transported
- how vendor command payloads are structured
- whether host tools require synchronization

Those decisions are governed by:

- `USB_HUB_FW_CHECKLIST.md`
- `USB_HUB_ARCHITECTURE.md`

## Reference Source Governance

Each extracted USB-IF reference entry must include traceable metadata.

Required metadata fields:

- Source document name
- Specification version or revision
- Section number
- Extraction date
- Topic scope
- Notes or interpretation limits

Example:

| Field | Example |
| --- | --- |
| Source document | USB 2.0 Specification |
| Revision | 2.0 |
| Section | 11.24.2.7 |
| Topic | Hub Port Status Bits |
| Extraction date | YYYY-MM-DD |

No reference entry should exist without traceable source metadata.

## Recommended Topic Set

Only hub-relevant standard topics should be included.

### Core Topics

- Hub class requests
- Hub descriptor fields
- Port status bits
- Port change bits
- Hub feature and port feature semantics
- Power switching behavior
- Over-current reporting behavior
- Single-TT vs multi-TT behavior
- Enumeration-visible hub constraints

## Reference Topic Classification

USB-IF topics should be divided into two categories.

### Static Lookup Topics

These topics can be extracted into structured lookup tables.

Examples:

- Hub class requests
- Hub descriptor fields
- Port status bits
- Port change bits
- Hub feature definitions

These topics are stable and suitable for indexed lookup.

### Contextual Review Topics

These topics require contextual interpretation.

Examples:

- Enumeration behavior constraints
- Transaction translator scheduling implications
- Power switching interactions
- Over-current reporting timing

These topics should be used only during architecture or design review, not as automatic implementation rules.

## Preferred Access Model

A topic-indexed reference layer is preferred over free-form specification search.

Example query model:

```text
usb_hub_class_lookup(topic)
usb_hub_descriptor_lookup(field)
usb_hub_port_status_bits()
usb_hub_tt_rules()
usb_hub_power_switching_rules()
```

This model:

- keeps the reference layer narrow
- reduces unrelated context exposure
- improves traceability during review

## Why Full-Corpus Injection Is Unsafe

Directly loading the full USB-IF specification corpus into AI context introduces three risks.

### 1. Scope Dilution

USB-IF documentation includes many domains unrelated to hub firmware.

Examples:

- USB4
- Type-C alternate modes
- PD policy engines
- compliance and electrical tests

These topics increase context noise.

### 2. Project Fact Loss

Standard documents do not define project-specific implementation facts such as:

- oscillator frequency
- descriptor storage location
- safe flash execution region
- vendor command payload layout
- cascade transport path

These must always come from `USB_HUB_FW_CHECKLIST.md`.

### 3. False Authority

Large specification corpora can cause the model to incorrectly apply generic USB rules where the project has explicit architectural constraints.

This repository intentionally treats confirmed project facts as higher priority than generic specification context.

## Conflict Resolution Rule

If a USB-IF reference conflicts with a confirmed project fact:

- Do not silently replace the project fact.
- Trigger architecture review.
- Classify the result as one of the following:

| Category | Meaning |
| --- | --- |
| Project implementation constraint | Project intentionally diverges from standard pattern |
| Standards compliance risk | Implementation may violate the specification |
| Documentation inconsistency | The interpretation or documentation is incorrect |

Record the decision in:

- `memory/03_decisions.md`

## Validation Guidance

USB-IF references do not replace validation.

If a firmware change references USB-IF semantics, validation should include project-level evidence.

Recommended validation artifacts:

| Topic | Validation Evidence |
| --- | --- |
| Hub descriptor behavior | Descriptor review, enumeration log |
| Port status bits | Host request verification, bus trace |
| TT behavior | Hub behavior verification |
| Power switching | Port power sequencing observation |
| Protocol behavior | Host interaction verification |

Additional firmware evidence may include:

- map file
- overlay report
- build logs

## Recommended Implementation Strategy

If a structured USB-IF reference backend is added later, the recommended implementation order is:

1. Hub class request lookup
2. Hub descriptor field lookup
3. Port status and change bit lookup
4. TT mode rule lookup
5. Power switching and over-current rule lookup

These topics provide the highest practical value for hub firmware review.

## Current Reference Artifacts

The repository currently includes these concrete USB hub reference artifacts:

- `USB_HUB_CLASS_REQUESTS_REF.md`
- `USB_HUB_PORT_STATUS_BITS_REF.md`

## Related Documents

- `USB_HUB_FW_CHECKLIST.md`
- `USB_HUB_ARCHITECTURE.md`
- `TRACEABILITY_MATRIX.md`
- `AGENTS.md`
- `WORKFLOW.md`
- `memory/03_decisions.md`
