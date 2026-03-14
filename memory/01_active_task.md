# Active Task

## Current Task

Maintain and refine the USB Hub Firmware Architecture Contract as a reusable firmware governance baseline.

The repository now also needs to act as a real external contract repo for `ai-governance-framework`, not only as a standalone documentation baseline.

## Next Action

Fill project-specific facts from the actual Keil project and firmware sources, and add minimal reference-layer artifacts only where they are backed by traceable sources.

- Validate `contract.yaml` loading through `ai-governance-framework`
- Validate external `hub-firmware` rule activation
- Validate advisory interrupt-safety execution through `post_task_check`

## Blockers

- Exact `.uvprojx` file name is unknown
- Actual clock values are unknown
- Actual descriptor location is unknown
- Flash safe execution region is unknown
- DPTR configuration is unknown
- Power switching mode is unknown
- Over-current model is unknown
