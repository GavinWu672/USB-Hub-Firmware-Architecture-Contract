# Decisions

## Accepted Decisions

- The repository remains documentation-first.
- Governance, architecture, and checklist documents stay separated by function.
- Unknown firmware facts must not be guessed.
- A lightweight `memory/` layer is adopted from the general idea used by `ai-governance-framework`.
- The repository has reached a structurally complete firmware governance skeleton for Keil C / 8051 / USB hub firmware work.
- The next maturity step is enforcement strength and operational execution, not broader spec expansion.

## Governance Maturity Assessment - Repository Architecture Status

### Decision Summary

The repository has reached a structurally complete firmware governance skeleton.

Core governance layers now exist:

- Project facts (`USB_HUB_FW_CHECKLIST.md`)
- Architecture boundaries (`USB_HUB_ARCHITECTURE.md`)
- AI behavior constraints (`AGENTS.md`)
- Fact-rule traceability (`TRACEABILITY_MATRIX.md`)
- Operational workflow (`WORKFLOW.md`)
- Persistent context (`memory/`)
- Controlled USB-IF reference integration

The documentation model is internally coherent and domain-specific to Keil C / 8051 USB hub firmware development.

At this stage, the primary maturity gaps are no longer document coverage or architecture structure.

They are related to operational enforcement and execution reliability.

### Current State

The repository now provides a full governance chain:

`facts -> architecture -> AI constraints -> traceability -> workflow -> validation -> memory`

This structure addresses common AI-assisted firmware development risks:

- hidden assumptions
- architecture violations
- context loss across sessions
- incomplete validation evidence

The repository therefore functions as a firmware governance framework candidate, rather than a simple documentation collection.

### Primary Remaining Risks

#### 1. Governance bypass risk

Governance rules may still be bypassed if review gates are treated as guidance rather than blocking conditions in real firmware workflows.

Without stronger enforcement surfaces such as PR/MR templates, review gates, or CI signals, the framework risks remaining documentation-only.

#### 2. README boundary expansion

`README.md` is approaching the boundary where it may absorb too much institutional detail.

If this continues, the repository entry point may lose its primary role as a navigation layer and begin duplicating workflow or governance logic that should remain in dedicated documents.

#### 3. Validation generalization risk

Validation expectations currently exist but remain mostly generic.

They are not yet consistently mapped from change type to required validation evidence, especially in areas such as:

- USB enumeration behavior
- host interaction verification
- flash update execution safety
- build artifact inspection (`map`, `overlay`)

#### 4. Fact drift risk

Project facts recorded in `USB_HUB_FW_CHECKLIST.md` may drift from the actual firmware implementation over time.

Examples include:

- clock configuration changes
- descriptor relocation
- flash layout updates
- vendor command protocol evolution

Without periodic synchronization, the checklist risks losing its role as the authoritative fact layer.

### Priority Direction

The next maturity phase should focus on execution hardness rather than additional specification breadth.

Three directions are recommended.

#### 1. Strengthen enforcement

Ensure that missing required facts, architecture-sensitive changes, and missing validation evidence become practical stop conditions during review.

#### 2. Preserve document boundaries

Maintain clear separation of responsibilities:

- `README.md` -> repository entry and navigation
- `WORKFLOW.md` -> operational process
- `TRACEABILITY_MATRIX.md` -> fact-rule dependency mapping
- `USB_HUB_ARCHITECTURE.md` -> system design boundaries
- `USB_HUB_FW_CHECKLIST.md` -> project fact source of truth

#### 3. Introduce change-type-driven validation

Refine validation expectations so firmware changes map to specific required evidence types.

Typical mappings should include:

- enumeration behavior validation
- host interaction verification
- flash update safety validation
- build artifact inspection

### Architectural Conclusion

This repository should no longer be viewed primarily as a documentation collection.

It now represents a firmware governance framework candidate for AI-assisted firmware development.

The next maturity step is execution enforcement, not broader documentation coverage.

## Pending Decisions

- Whether to add a project-level `PLAN.md`
- Whether to introduce validation scripts
- Whether to add vendor command spec templates
