# USB Hub Firmware AI-Safe Architecture Contract

## 專案說明

本 repository 是一套提供給 `Keil C` / `Keil C51` 類型 `USB Hub firmware` 專案使用的治理與規格基線。

它不是 firmware SDK、USB stack implementation、build system，也不是可直接燒錄的 firmware codebase。  
它的定位是 documentation-first 的控制層，用來約束：

- firmware 設計
- architecture review
- AI 協作行為
- validation 要求
- project memory 維護

## 適用對象

本專案主要適用於：

- `Keil C` / `Keil C51` 韌體專案
- `8051` 或 enhanced `8051` 類型的 USB Hub firmware 環境
- 需要 AI 協助撰寫規格、做設計審查、或進行受控修改的團隊

## 核心文件

- [USB_HUB_FW_CHECKLIST.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_FW_CHECKLIST.md)：不可猜測的 project facts
- [USB_HUB_ARCHITECTURE.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_ARCHITECTURE.md)：architecture boundaries 與 safety rules
- [AGENTS.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/AGENTS.md)：AI behavior constraints
- [WORKFLOW.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/WORKFLOW.md)：GitHub / GitLab review workflow 與 hard stop conditions
- [TRACEABILITY_MATRIX.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/TRACEABILITY_MATRIX.md)：facts、architecture、agent rules、validation 的追溯矩陣
- [USB_IF_INTEGRATION_PLAN.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_IF_INTEGRATION_PLAN.md)：USB-IF spec 僅作為 USB hub firmware 的受控 reference layer 導入方案
- [memory/README.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/README.md)：持久化 project context 的記憶層說明

## Governance Flow

```mermaid
flowchart TD
    A[USB_HUB_FW_CHECKLIST.md<br/>Facts / Non-Assumable Inputs]
    B[USB_HUB_ARCHITECTURE.md<br/>Architecture Boundaries]
    C[AGENTS.md<br/>AI Behavior Constraints]
    D[Implementation<br/>Keil C51 / USB Hub Firmware Changes]
    E[Validation<br/>Map / Overlay / Descriptor / Enumeration]
    F[memory/<br/>Facts / Decisions / Validation Log]
    G[Review Gate<br/>GitHub PR or GitLab MR Template]

    A --> B
    B --> C
    C --> D
    D --> E
    E --> F
    A --> G
    B --> G
    C --> G
    E --> G
    G --> D
```

核心主線：

`Facts -> Architecture -> Agent Constraints -> Implementation -> Validation -> Memory`

## Hard Stops

以下條件是阻斷條件，不是建議事項：

- Missing required facts -> stop implementation
- Architecture-sensitive change -> architecture review required
- Missing validation evidence for firmware-impacting changes -> stop merge

詳細規則請看：

- [WORKFLOW.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/WORKFLOW.md)

## Quick Start

1. 先填 [USB_HUB_FW_CHECKLIST.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_FW_CHECKLIST.md) 中與本次變更直接相關的必要欄位。
2. 再看 [USB_HUB_ARCHITECTURE.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/USB_HUB_ARCHITECTURE.md) 是否碰到 architecture boundary。
3. 用 [AGENTS.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/AGENTS.md) 約束 AI 不得在缺乏事實時亂推論。
4. 用 [WORKFLOW.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/WORKFLOW.md) 走 review gate。
5. 用 [TRACEABILITY_MATRIX.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/TRACEABILITY_MATRIX.md) 確認 fact 與 rule 的對應關係。
6. 把已確認的 facts、decisions、validation evidence 更新到 [memory](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/memory/README.md)。

## Review Gate

GitHub 與 GitLab 都有對應入口：

- [.github/PULL_REQUEST_TEMPLATE.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/.github/PULL_REQUEST_TEMPLATE.md)
- [.gitlab/merge_request_templates/Default.md](/e:/BackUp/Git_EE/USB-Hub-Firmware-Architecture-Contract/.gitlab/merge_request_templates/Default.md)

## 參考來源

本專案的 documentation-first 治理思路，有參考：

- <https://github.com/GavinWu672/ai-governance-framework>
