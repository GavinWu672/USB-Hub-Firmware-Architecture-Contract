# Memory Layer

## Purpose

This directory stores durable project context for AI-assisted USB hub firmware work.

Only confirmed facts, accepted decisions, and validation evidence should be written here.

## Rules

- Do not store guessed values.
- Do not replace formal specs with memory notes.
- If memory conflicts with `AGENTS.md`, `USB_HUB_ARCHITECTURE.md`, or `USB_HUB_FW_CHECKLIST.md`, the formal spec documents win.
- Use `FACT_INTAKE.md` before promoting new project facts into memory.

## Files

- `00_master_plan.md`
- `01_active_task.md`
- `02_project_facts.md`
- `03_decisions.md`
- `04_validation_log.md`

## Intake Flow

When connecting a real firmware repository:

1. collect source artifacts using `FACT_INTAKE.md`
2. update `USB_HUB_FW_CHECKLIST.md`
3. promote confirmed facts into `memory/02_project_facts.md`
4. record architecture-impacting changes in `memory/03_decisions.md`
5. record produced evidence in `memory/04_validation_log.md`
