# HUB Firmware Safety Rules

## HUB-001 - cfu-response-must-follow-request

- CFU or firmware-update response behavior must follow the active request contract.
- Do not emit success, completion, or state transition signals before the corresponding request path has validated preconditions and ownership.
- Evidence required:
  - update validation evidence
  - host request verification

## HUB-004 - dptr-guard

- Interrupt-sensitive code must not corrupt DPTR-dependent main-flow state.
- If the target uses a single DPTR configuration, ISR-side `xdata` access must preserve main-context pointer safety.
- Interrupt handlers must avoid blocking or host-visible slow paths.
- Evidence required:
  - interrupt safety review
  - `.map` / overlay evidence when memory placement is affected
