# Firmware Fact Intake Guide

## Purpose

This guide defines the minimum evidence collection path for connecting a real Keil C / C51 firmware repository to this contract repository.

Use it before filling `USB_HUB_FW_CHECKLIST.md` or `memory/02_project_facts.md`.

## Intake Principle

- Record only confirmed facts.
- Every fact should point to a concrete source artifact.
- If the source artifact is missing, keep the field unresolved.
- Do not replace missing firmware evidence with architectural guesses.

## Recommended Intake Order

### 1. Toolchain And Build Identity

Collect:

- `.uvprojx`
- build target name
- Keil version if present

Used to fill:

- Toolchain
- project file
- build target

### 2. Memory And Flash Ownership

Collect:

- linker outputs
- `.map` file
- overlay report
- flash API source file

Used to fill:

- flash layout
- safe execution region
- CFU handler region
- descriptor storage location
- code / data / xdata usage clues

### 3. Interrupt And Concurrency Facts

Collect:

- ISR source file
- critical section macros
- SoC documentation for DPTR mode

Used to fill:

- ISR declaration
- register bank usage
- DPTR configuration
- critical section entry / exit macros

### 4. USB Role And Hub Behavior

Collect:

- hub class handler source
- descriptor source
- hub descriptor dump or source definition

Used to fill:

- hub mode
- power switching mode
- over-current model
- hub class handler ownership

### 5. Vendor Command And Host Synchronization

Collect:

- vendor command dispatcher source
- protocol document
- shared host model definitions

Used to fill:

- vendor command encoding / protocol source
- shared protocol structs
- host tool synchronization impact

### 6. Topology And Cross-Chip Access

Collect:

- topology document
- board schematic notes
- cross-chip access source or design note

Used to fill:

- port mapping
- access path
- cascade presence
- remote ownership assumptions

## Minimum Artifact Checklist

Before claiming the contract repo is connected to a real firmware repo, try to gather:

- actual `.uvprojx`
- actual `.map`
- actual overlay report
- actual ISR source file
- actual descriptor source file
- actual flash / update source file

If fewer than these exist, keep the affected checklist fields unresolved.

## Update Targets

When a fact is confirmed, update:

- `USB_HUB_FW_CHECKLIST.md`
- `memory/02_project_facts.md`

When a fact changes architecture or safety assumptions, also update:

- `memory/03_decisions.md`

When validation artifacts are produced, also update:

- `memory/04_validation_log.md`
