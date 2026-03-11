# USB Hub Firmware Governance Workflow

## Purpose

This document defines the operational workflow for using this repository in a GitHub or GitLab based firmware development environment.

It connects the project documents into a repeatable review path:

`facts -> architecture -> change -> validation -> memory`

## Scope

This workflow is intended for:

- Keil C / Keil C51 based USB hub firmware work
- AI-assisted firmware design or review
- GitHub pull request or GitLab merge request based change control

## Workflow Stages

## Hard Stop Conditions

The following conditions are blocking conditions, not suggestions:

- Missing required facts -> stop implementation
- Architecture-sensitive change -> architecture review required
- Missing validation evidence for firmware-impacting changes -> stop merge

These stop conditions apply before firmware logic changes are treated as ready for review or integration.

## 1. Confirm Facts Before Firmware Change

Before any firmware logic change:

- Review `USB_HUB_FW_CHECKLIST.md`
- Fill all required fields directly related to the change
- Stop if required facts are still unknown

Examples of blocking unknowns:

- Oscillator frequency
- Descriptor storage location
- Hub topology
- Flash safe execution region
- Vendor command encoding

If any required fact is missing, implementation must stop until the fact is confirmed.

## 2. Review Architecture Boundaries

Before implementation:

- Review `USB_HUB_ARCHITECTURE.md`
- Identify whether the change affects architecture-sensitive areas

High-risk areas include:

- Cross-chip register access
- Flash erase and write execution
- Vendor command protocol
- Protocol struct layout
- Power and reset sequencing

If architecture assumptions change, update:

- `USB_HUB_ARCHITECTURE.md`
- `memory/03_decisions.md`

If the change affects an architecture boundary, architecture review is required before merge.

## 3. Apply AI Governance Rules

During AI-assisted work:

- Follow `AGENTS.md`
- Do not infer missing facts
- Do not invent protocol layout
- Do not modify flash behavior without confirmed execution rules

If a required fact is missing, request clarification instead of proceeding.

## 4. Implement Or Review Change

Only after facts and architecture boundaries are confirmed should firmware implementation or review proceed.

Typical change types:

- Firmware logic updates
- Vendor command extension
- Descriptor updates
- Flash update flow changes
- Topology-aware hub behavior changes

## 5. Validate The Change

After implementation or review, collect validation evidence where applicable:

- Build result
- `.map` file memory usage
- Overlay report
- Descriptor layout review
- USB enumeration logs
- Host-side regression results

Validation findings should be recorded in:

- `memory/04_validation_log.md`

If validation evidence is expected for the change but missing, the change is not ready to merge.

## 6. Update Project Memory

Memory must be updated when durable project knowledge changes.

### Required Triggers

- Confirmed hardware or firmware fact -> `memory/02_project_facts.md`
- Architecture or protocol decision -> `memory/03_decisions.md`
- Validation result or test evidence -> `memory/04_validation_log.md`
- Current task or scope change -> `memory/01_active_task.md`

## 7. Review Gate

All firmware-related changes should go through pull request or merge request review.

Use:

- `.github/PULL_REQUEST_TEMPLATE.md`
- `.gitlab/merge_request_templates/Default.md`

The merge request template enforces checks across:

- Required facts
- Architecture impact
- Protocol and tool impact
- Validation evidence
- Memory updates

## Review Rule

If the merge request cannot show:

- confirmed required facts
- reviewed architecture impact
- appropriate validation evidence

then the change is not ready to merge.

## Document Map

- `AGENTS.md`: AI governance rules
- `USB_HUB_ARCHITECTURE.md`: architecture boundaries
- `USB_HUB_FW_CHECKLIST.md`: required project facts
- `README.md`: repository overview
- `memory/`: durable project context
- `.github/PULL_REQUEST_TEMPLATE.md`: GitHub review gate
- `.gitlab/merge_request_templates/Default.md`: GitLab review gate
