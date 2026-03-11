# Firmware Change Review

This repository uses the USB Hub Firmware Architecture Contract.

Before merging firmware-related changes, confirm the following.

---

## 1. Affected Fact Area

Which fact areas are affected by this change?

- [ ] Clock
- [ ] Descriptor management
- [ ] Vendor command
- [ ] Firmware update
- [ ] Hub topology
- [ ] Power switching model
- [ ] Transaction translator
- [ ] Interrupt or critical section behavior
- [ ] Other fact area documented in `TRACEABILITY_MATRIX.md`

---

## 2. Required Facts Confirmed

Have the required fields in `USB_HUB_FW_CHECKLIST.md` been verified?

- [ ] Toolchain confirmed
- [ ] Hub SoC confirmed
- [ ] Oscillator frequency confirmed
- [ ] USB role confirmed
- [ ] Descriptor storage location confirmed
- [ ] Flash safe execution region confirmed

If any required field is missing, firmware modification should not proceed.

---

## 3. Architecture Impact

Does this change affect architecture rules?

- [ ] Hub topology
- [ ] Flash update region
- [ ] Vendor command protocol
- [ ] Descriptor layout
- [ ] Power / reset sequencing

If yes, update:

- `USB_HUB_ARCHITECTURE.md`
- `memory/03_decisions.md`

Architecture impact summary:

<!-- Describe what changed and why -->

---

## 4. Protocol / Tool Impact

Does this change affect host communication?

- [ ] Vendor command payload
- [ ] Protocol struct layout
- [ ] Descriptor fields

If yes, confirm:

- [ ] Host tools updated if required
- [ ] JSON profile updated if required
- [ ] Protocol version reviewed

Related tool / protocol notes:

<!-- Describe affected host-side models, tools, or payload changes -->

---

## 5. Validation Evidence

Provide validation evidence.

- [ ] Build success
- [ ] `.map` file reviewed
- [ ] Overlay report checked
- [ ] USB enumeration verified
- [ ] Host tool regression passed if applicable

Evidence:

```text
Paste logs, review notes, or test results here.
```

---

## 6. Memory Updates

If applicable, update memory records:

- [ ] `memory/02_project_facts.md`
- [ ] `memory/03_decisions.md`
- [ ] `memory/04_validation_log.md`

Memory update summary:

<!-- Describe what memory files were updated -->
