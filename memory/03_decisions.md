# Decisions

## Accepted Decisions

- The repository remains documentation-first.
- Governance, architecture, and checklist documents stay separated by function.
- Unknown firmware facts must not be guessed.
- A lightweight `memory/` layer is adopted from the general idea used by `ai-governance-framework`.
- The repository has reached a complete firmware governance skeleton for Keil C / 8051 / USB hub firmware work.
- The next maturity step is enforcement strength and operational execution, not broader spec expansion.

## Review Conclusion

The repository is no longer primarily a documentation collection.

It is now a firmware governance framework candidate.

Current state:

- Project facts, architecture boundaries, AI constraints, traceability, workflow, memory, and controlled USB-IF references are all present.
- The documentation model is internally coherent and domain-specific to Keil C / 8051 / USB hub firmware.

Primary remaining risks:

- Governance rules may still be bypassed in real firmware change workflows if review gates are treated as guidance instead of blocking conditions.
- `README.md` is approaching the boundary where it risks absorbing too much institutional detail instead of remaining the repository entry point.
- Validation rules exist, but are still mostly generic and are not yet fully mapped from change type to required evidence type.

Priority direction:

1. Strengthen enforcement so required facts, architecture-sensitive changes, and missing validation evidence become actual stop conditions.
2. Preserve document boundaries so `README.md` remains a navigation layer, while workflow, traceability, architecture, and checklist remain the authoritative detail layers.
3. Refine validation into change-type-driven requirements, especially for enumeration, host interaction, flash-update behavior, and build-output evidence.

## Pending Decisions

- Whether to add a project-level `PLAN.md`
- Whether to introduce validation scripts
- Whether to add vendor command spec templates
