> **最後更新**: 2026-03-14
> **Owner**: USB Hub Firmware Contract
> **Freshness**: Sprint (7d)

# PLAN

[>] Phase 1 : Enable ai-governance-framework contract integration
- Add `contract.yaml`
- Add external `hub-firmware` rule pack
- Add advisory interrupt safety validator
- Verify `session_start`, `pre_task_check`, and `post_task_check` integration paths

[ ] Phase 2 : Fill project-specific facts from the real firmware repository
- Confirm toolchain and `.uvprojx` target facts
- Confirm flash layout, descriptor location, and DPTR configuration
- Confirm topology, power switching mode, and over-current model

[ ] Phase 3 : Replace example assumptions with repo-native validation evidence
- Define expected `.map` / overlay artifacts
- Define host-visible validation evidence expectations
- Refine interrupt-safety checks from real firmware code patterns
