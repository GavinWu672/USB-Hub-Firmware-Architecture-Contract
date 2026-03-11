# USB Hub Firmware Topology Map

## Purpose

This document defines the concrete topology and routing model for multi-chip USB hub firmware designs.

It exists to turn high-level cross-chip safety rules into an executable review map for:

- logical port ownership
- chip-to-port mapping
- access path selection
- shadow RAM ownership
- bus ownership and timing rules

This file must not invent topology facts. Unknown entries must remain explicitly unresolved until confirmed from schematic, firmware source, or hardware documentation.

## Scope

Use this document when the firmware design includes:

- master and slave hub relationships
- cascade hub routing
- cross-chip port status aggregation
- shadow-state based host-visible reporting
- remote register access over I2C, SMBus, or vendor forwarding

## 1. Physical Topology

### Reference Diagram

```text
Host
  |
Master Hub
  |- Local Port Group
  `- Slave Hub Link(s)
       |- Slave Hub A
       `- Slave Hub B
```

### Project Topology Facts

| Field | Value | Source |
| --- | --- | --- |
| Master hub device | `____` | Schematic, SoC documentation |
| Slave hub count | `____` | Schematic |
| Master-to-slave transport | `____` | Firmware design, hardware design |
| Cascade present | `____` | Architecture decision |

## 2. Logical Port Mapping

This section maps host-visible logical ports to the actual chip and access target.

| Logical Port | Owning Chip | Physical Port | Register Base or Address | Access Path | Notes |
| --- | --- | --- | --- | --- | --- |
| Port 1 | `____` | `____` | `____` | `local / i2c / smbus / vendor` | `____` |
| Port 2 | `____` | `____` | `____` | `local / i2c / smbus / vendor` | `____` |
| Port 3 | `____` | `____` | `____` | `local / i2c / smbus / vendor` | `____` |
| Port 4 | `____` | `____` | `____` | `local / i2c / smbus / vendor` | `____` |

Add rows as required for the real hub configuration.

## 3. Access Path Hierarchy

Access paths must be classified explicitly.

| Level | Name | Meaning | Allowed Use |
| --- | --- | --- | --- |
| L1 | Direct | Local master-hub register access | Timing-sensitive paths, ISR-safe only if local hardware allows |
| L2 | Proxy | Local shadow or cached copy of remote state | Preferred for host-visible status reporting |
| L3 | Remote | Physical cross-chip transaction | Background or task-level coordination only |

### Project Access Rules

| Operation | Preferred Path | Forbidden Path | Notes |
| --- | --- | --- | --- |
| Host-visible `GET_STATUS` | `____` | `____` | `____` |
| Port power control | `____` | `____` | `____` |
| Port reset control | `____` | `____` | `____` |
| Slave status refresh | `____` | `____` | `____` |
| Aggregated bitmap generation | `____` | `____` | `____` |

## 4. Shadow RAM Ownership

This section defines which states are host-visible from shadow RAM and how shadow state is refreshed.

| State Category | Source Chip | Host Reads From | Shadow Owner | Refresh Method | Notes |
| --- | --- | --- | --- | --- | --- |
| Port connection status | `____` | `____` | `____` | `ISR / polling / event-driven / task` | `____` |
| Port change bits | `____` | `____` | `____` | `ISR / polling / event-driven / task` | `____` |
| Power state | `____` | `____` | `____` | `ISR / polling / event-driven / task` | `____` |
| Over-current state | `____` | `____` | `____` | `ISR / polling / event-driven / task` | `____` |

### Shadow-State Rules

- Host-visible timing-sensitive status should prefer validated shadow RAM instead of direct remote reads.
- Shadow update ownership must be explicit.
- If shadow RAM can become stale, the acceptable staleness window must be defined by project behavior or validation evidence.

## 5. Bus Ownership

Physical cross-chip communication must have explicit ownership rules.

| Context | Bus Access Allowed | Conditions | Timeout / Retry Rule | Notes |
| --- | --- | --- | --- | --- |
| ISR | `yes / no` | `____` | `____` | `____` |
| Main loop | `yes / no` | `____` | `____` | `____` |
| Background task | `yes / no` | `____` | `____` | `____` |
| USB request path | `yes / no` | `____` | `____` | `____` |

### Bus Rules

- If ISR bus access is forbidden, firmware review must ensure no blocking physical transaction is reachable from ISR code.
- Retry and timeout behavior must be bounded and must not create tight polling loops.
- Concurrent bus ownership must not be assumed safe without explicit arbitration design.

## 6. Read / Write Ownership

This section defines who is allowed to read or modify each class of state.

| State or Register Group | Read Owner | Write Owner | Direct Remote Access Allowed | Notes |
| --- | --- | --- | --- | --- |
| Local master status registers | `____` | `____` | `____` | `____` |
| Slave status registers | `____` | `____` | `____` | `____` |
| Shadow port bitmap | `____` | `____` | `____` | `____` |
| Port power control registers | `____` | `____` | `____` | `____` |
| Port reset control registers | `____` | `____` | `____` | `____` |

## 7. Validation Expectations

Topology-sensitive changes should be validated with evidence such as:

- logical port mapping review
- host-visible port status verification
- bus transaction trace
- enumeration logs
- shadow RAM synchronization review

## 8. Related Documents

- `USB_HUB_ARCHITECTURE.md`
- `USB_HUB_FW_CHECKLIST.md`
- `TRACEABILITY_MATRIX.md`
- `AGENTS.md`
- `WORKFLOW.md`
