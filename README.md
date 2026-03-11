# USB Hub Firmware AI-Safe Architecture Contract

## Overview

This repository is a governance and specification baseline for `Keil C` / `Keil C51` based `USB hub firmware` projects.

It is intended to help engineers and AI coding agents work from the same contract:

- What the firmware architecture allows
- What facts must not be guessed
- What safety boundaries must be preserved
- What project facts must be confirmed before implementation

This project is not a firmware codebase by itself. It is a documentation-first control layer for firmware design, implementation review, and AI-assisted change governance.

## Primary Use Case

This project is primarily for:

- Keil C based USB hub firmware projects
- 8051 or enhanced 8051 style embedded firmware environments
- Teams using AI assistance for firmware specification, review, or controlled implementation

## Repository Structure

- [AGENTS.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/AGENTS.md): AI governance rules and non-negotiable safety constraints
- [USB_HUB_ARCHITECTURE.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_ARCHITECTURE.md): architecture boundaries, protocol rules, flash safety, and topology guidance
- [USB_HUB_FW_CHECKLIST.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_FW_CHECKLIST.md): project fact checklist that must be filled before risky implementation decisions
- [memory/README.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/README.md): lightweight project memory guidance for AI-assisted work

## How To Use This Repository

### 1. Start From Facts

Before changing firmware logic, fill the required fields in [USB_HUB_FW_CHECKLIST.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_FW_CHECKLIST.md).

Typical examples:

- oscillator frequency
- descriptor storage location
- hub topology
- flash execution region
- vendor command layout

If a required fact is still unknown, stop and confirm it first.

### 2. Use Architecture As The Safety Boundary

Use [USB_HUB_ARCHITECTURE.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_ARCHITECTURE.md) to define what must not be violated, especially for:

- cross-chip register access
- flash erase and write execution
- protocol struct layout
- vendor command governance
- power and reset sequencing

### 3. Use Governance Rules For AI Collaboration

Use [AGENTS.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/AGENTS.md) as the operating contract for AI-assisted work.

Core principle:

- unknown facts must be requested, not inferred

## Reference To `ai-governance-framework`

This repository is influenced by the documentation-first governance style of [`GavinWu672/ai-governance-framework`](https://github.com/GavinWu672/ai-governance-framework).

From that framework, the most suitable concept to adopt here is the `memory/` layer. In the upstream repository, the memory mechanism is used to preserve project context across sessions and reduce repeated re-explanation. The README also describes a dedicated `memory/` directory and a `memory_janitor.py` workflow for maintaining that state. Source used:

- GitHub repository page: <https://github.com/GavinWu672/ai-governance-framework>

### Why `memory/` Fits This Project

For USB hub firmware work, memory is useful because AI sessions often lose project-critical context such as:

- confirmed clock and descriptor facts
- flash-safe execution constraints
- approved vendor command definitions
- cross-chip access limitations
- known validation evidence and open risks

That makes `memory/` a good fit for this project even if other upstream features are not adopted yet.

### What Is Adopted Here

This repository adopts the `memory/` concept in a simplified form:

- keep durable project facts in dedicated memory files
- separate active work from stable architecture rules
- record validation evidence and unresolved risks

This project does not currently import the upstream scripts or CI hooks. It only adopts the memory pattern at the documentation level.

## Memory Layout

The local [memory](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/README.md) directory is intended to preserve durable context for AI and engineers.

- [00_master_plan.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/00_master_plan.md): project objective, scope, and current documentation status
- [01_active_task.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/01_active_task.md): current working task and next action
- [02_project_facts.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/02_project_facts.md): confirmed facts that must not be re-guessed
- [03_decisions.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/03_decisions.md): architectural decisions and rationale
- [04_validation_log.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/04_validation_log.md): validation evidence, checks performed, and remaining gaps

## Recommended Workflow

1. Fill required facts in the checklist.
2. Update `memory/02_project_facts.md` with confirmed values only.
3. Record design decisions in `memory/03_decisions.md`.
4. Use the architecture document as the implementation boundary.
5. Log evidence in `memory/04_validation_log.md` after review, build, or enumeration checks.

## Current Status

Current repository status as of March 11, 2026:

- governance rules are defined
- architecture spec is defined
- project fact checklist is defined
- memory structure is initialized
- project-specific firmware facts are still incomplete

## Next Recommended Step

The next practical step is to fill these high-impact unknowns first:

- exact `.uvprojx` file name
- build target name
- oscillator frequency
- descriptor storage location
- flash safe execution region
- actual hub topology
- vendor command protocol document location

## License / Usage Note

This repository currently contains project documentation only. If you later import tooling or text from external governance frameworks, verify the upstream license and attribution requirements first.
