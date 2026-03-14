# Fact Intake Worksheet

## Purpose

Use this worksheet during the first pass against a real firmware repository.

This is the working sheet that bridges:

- `SOURCE_INVENTORY.md`
- `USB_HUB_FW_CHECKLIST.md`
- `memory/02_project_facts.md`

## Stage 1 - Locate Core Artifacts

- [ ] `.uvprojx` found
- [ ] `.map` file found
- [ ] overlay report found
- [ ] ISR source file found
- [ ] descriptor source file found
- [ ] flash / update source file found

## Stage 2 - Promote High-Risk Facts First

Fill only when confirmed.

| Fact | Value | Source |
| --- | --- | --- |
| Project file | pending | pending |
| Build target | pending | pending |
| Oscillator frequency | pending | pending |
| Descriptor storage location | pending | pending |
| Flash safe execution region | pending | pending |
| DPTR configuration | pending | pending |
| Hub mode | pending | pending |
| Power switching mode | pending | pending |
| Over-current model | pending | pending |

## Stage 3 - Promote Ownership Facts

| Fact | Value | Source |
| --- | --- | --- |
| Hub class handler | pending | pending |
| Descriptor owner module | pending | pending |
| Flash API location | pending | pending |
| CFU handler definition | pending | pending |
| CFU handler region | pending | pending |
| Vendor command dispatcher | pending | pending |

## Stage 4 - Promote Validation-Relevant Facts

| Fact | Value | Source |
| --- | --- | --- |
| `.map` evidence artifact | pending | pending |
| overlay evidence artifact | pending | pending |
| descriptor verification artifact | pending | pending |
| host interaction verification artifact | pending | pending |

## Completion Check

Before updating the contract repo as "connected to a real firmware repo", confirm:

- [ ] `SOURCE_INVENTORY.md` has concrete paths
- [ ] `USB_HUB_FW_CHECKLIST.md` has updated confirmed fields
- [ ] `memory/02_project_facts.md` has promoted confirmed facts
- [ ] `memory/03_decisions.md` has been updated if any architecture assumptions changed
- [ ] `memory/04_validation_log.md` has evidence references if artifacts were collected
