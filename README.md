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

## 治理架構圖（Governance Architecture Diagram）

```mermaid
flowchart TD
    classDef trigger fill:#F5F5F5,stroke:#888,stroke-width:1.2px,color:#333;
    classDef fact fill:#EAF4FF,stroke:#4A90E2,stroke-width:1.5px,color:#1F2D3D;
    classDef arch fill:#EDF8ED,stroke:#4F8A4F,stroke-width:1.5px,color:#1F2D3D;
    classDef ref fill:#FFF5E8,stroke:#D98C1F,stroke-width:1.5px,color:#1F2D3D;
    classDef exec fill:#F5EEFF,stroke:#7E57C2,stroke-width:1.5px,color:#1F2D3D;
    classDef mem fill:#FDECEF,stroke:#D45A7A,stroke-width:1.5px,color:#1F2D3D;

    subgraph Z0["變更觸發區 / Change Trigger Zone"]
        U1["韌體變更活動<br/>Firmware Change Activity"]
    end

    subgraph Z1["L1 — 專案事實區 / Project Truth Zone"]
        subgraph Z1A["事實與對應關係 / Facts and Mapping"]
            F1["USB_HUB_FW_CHECKLIST.md<br/>專案事實 / Project Facts"]
            F2["TOPOLOGY.md<br/>拓樸 / Port Mapping / Access Path"]
            F3["HUB_PROFILE_SCHEMA.md<br/>Profile / Schema 契約"]
            F4["TRACEABILITY_MATRIX.md<br/>Fact -> Rule -> Validation"]
        end
    end

    subgraph Z2["L2 — 架構邊界區 / Architecture Boundary Zone"]
        subgraph Z2A["設計限制 / Design Constraints"]
            A1["USB_HUB_ARCHITECTURE.md<br/>系統邊界 / System Boundaries"]
            A2["AGENTS.md<br/>AI Guardrails / No-Assumption"]
        end
    end

    subgraph Z3["L3 — 受控標準參考區 / Controlled Standards Reference Zone"]
        subgraph Z3A["USB-IF 參考層 / USB-IF Reference Layer"]
            S1["USB_IF_INTEGRATION_PLAN.md<br/>導入策略 / Precedence / Conflict Rules"]
            S2["USB_HUB_CLASS_REQUESTS_REF.md<br/>Hub Class Requests 受控參考"]
            S3["USB_HUB_PORT_STATUS_BITS_REF.md<br/>Port Status / Change Bits 受控參考"]
        end
    end

    subgraph Z4["L4 — 執行與審查區 / Execution and Review Zone"]
        subgraph Z4A["流程與 Gate / Process and Gate"]
            P1["WORKFLOW.md<br/>流程 / Review Path"]
            P2["VALIDATION_REQUIREMENTS.md<br/>Change Type -> Evidence Type"]
            P3["PR / MR Templates<br/>Hard Stops / Review Gate"]
        end
    end

    subgraph Z5["L5 — 證據與記憶區 / Evidence and Memory Zone"]
        subgraph Z5A["持久化結果 / Persistent Outcomes"]
            M1["Validation Evidence<br/>Map / Overlay / Enumeration / Host Trace"]
            M2["memory/02_project_facts.md<br/>已確認事實 / Confirmed Facts"]
            M3["memory/03_decisions.md<br/>架構決策 / Escalation Results"]
            M4["memory/04_validation_log.md<br/>驗證紀錄 / Validation Record"]
        end
    end

    U1 --> F1
    U1 --> P1

    F1 --> A1
    F2 --> A1
    F3 --> F4
    F1 --> F4
    A1 --> A2
    F4 --> A2

    S1 --> S2
    S1 --> S3
    S1 --> P1
    S2 --> F4
    S3 --> F4
    A1 --> P1
    A2 --> P1

    P1 --> P2
    F4 --> P2
    P2 --> P3
    P3 --> M1

    F1 --> M2
    A1 --> M3
    S1 --> M3
    M1 --> M4

    class U1 trigger;
    class F1,F2,F3,F4 fact;
    class A1,A2 arch;
    class S1,S2,S3 ref;
    class P1,P2,P3 exec;
    class M1,M2,M3,M4 mem;
```

這張圖描述的不是 firmware module，而是整個 repository 的治理架構：

- facts / project truth 先定義不可猜測的事實
- architecture / system boundaries 定義不可跨越的邊界
- agents / AI constraints 約束 AI 行為
- traceability 串起 facts、rules、validation
- standard reference 只作為受控語意層
- escalation 與 fact preservation 用來處理衝突與避免 context loss
- workflow 與 review gate 把這些規則落到實際變更流程

## 核心文件

- [USB_HUB_FW_CHECKLIST.md](./USB_HUB_FW_CHECKLIST.md)：不可猜測的 project facts
- [USB_HUB_ARCHITECTURE.md](./USB_HUB_ARCHITECTURE.md)：architecture boundaries 與 safety rules
- [TOPOLOGY.md](./TOPOLOGY.md)：多晶片 hub 的實體拓樸、logical port mapping、access path、shadow ownership
- [AGENTS.md](./AGENTS.md)：AI behavior constraints
- [WORKFLOW.md](./WORKFLOW.md)：GitHub / GitLab review workflow 與 hard stop conditions
- [TRACEABILITY_MATRIX.md](./TRACEABILITY_MATRIX.md)：facts、architecture、agent rules、validation 的追溯矩陣
- [VALIDATION_REQUIREMENTS.md](./VALIDATION_REQUIREMENTS.md)：依變更類型定義 validation evidence 的要求
- [USB_IF_INTEGRATION_PLAN.md](./USB_IF_INTEGRATION_PLAN.md)：USB-IF spec 僅作為 USB hub firmware 的受控 reference layer 導入方案
- [USB_HUB_CLASS_REQUESTS_REF.md](./USB_HUB_CLASS_REQUESTS_REF.md)：USB Hub class requests 的受控標準參考摘要
- [USB_HUB_PORT_STATUS_BITS_REF.md](./USB_HUB_PORT_STATUS_BITS_REF.md)：USB Hub port status / change semantics 的受控標準參考摘要
- [memory/README.md](./memory/README.md)：持久化 project context 的記憶層說明

## 治理流程圖（Governance Flow）

```mermaid
flowchart TD
    classDef step fill:#E8F4FD,stroke:#4A90E2,stroke-width:1.5px,color:#1F2D3D;
    classDef review fill:#FFF4E5,stroke:#D98C1F,stroke-width:1.5px,color:#1F2D3D;
    classDef memory fill:#FDECEF,stroke:#D45A7A,stroke-width:1.5px,color:#1F2D3D;

    A["確認事實 / Confirm Facts<br/>USB_HUB_FW_CHECKLIST.md"]
    B["審查架構邊界 / Review Architecture Boundary<br/>USB_HUB_ARCHITECTURE.md"]
    C["套用 AI 限制 / Apply AI Constraints<br/>AGENTS.md"]
    D["實作或審查變更 / Implement or Review Change"]
    E["收集驗證證據 / Collect Validation Evidence"]
    F["審查關卡 / Review Gate<br/>GitHub PR / GitLab MR"]
    G["更新記憶層 / Update Memory<br/>facts / decisions / validation"]

    A --> B
    B --> C
    C --> D
    D --> E
    E --> F
    F --> G

    class A,B,C,D,E step;
    class F review;
    class G memory;
```

這張圖只描述實際變更流程，對應的是：

`Facts -> Architecture -> Agent Constraints -> Implementation -> Validation -> Memory`

## Hard Stops

以下條件是阻斷條件，不是建議事項：

- Missing required facts -> stop implementation
- Architecture-sensitive change -> architecture review required
- Missing validation evidence for firmware-impacting changes -> stop merge

詳細規則請看：

- [WORKFLOW.md](./WORKFLOW.md)
- [VALIDATION_REQUIREMENTS.md](./VALIDATION_REQUIREMENTS.md)

## Technical Execution Constraints

以下是針對 `Keil C51` / `8051` / `USB Hub firmware` 的高風險執行限制：

- Interrupt Safety: `main` 與 `ISR` 共用的函式或狀態，必須明確處理 reentrancy 或共享保護。
- DPTR Guard: 若目標僅有單組 `DPTR`，則 ISR 內的 `xdata` 存取不得破壞主流程指標狀態。
- Atomic Event Handling: Port change / status change 類事件必須避免不安全的 clear-then-handle 寫法。
- Non-blocking Cross-Chip Access: Master/Slave 間的遠端通訊不得阻塞 USB 關鍵路徑，尤其不得塞進 ISR。
- Shadow RAM Priority: 標準 USB class request 應優先使用本地 shadow state，不得在 request 處理期間做阻塞式遠端掃描。

相關技術邊界請看：

- [USB_HUB_ARCHITECTURE.md](./USB_HUB_ARCHITECTURE.md)

## Quick Start

1. 先填 [USB_HUB_FW_CHECKLIST.md](./USB_HUB_FW_CHECKLIST.md) 中與本次變更直接相關的必要欄位。
2. 再看 [USB_HUB_ARCHITECTURE.md](./USB_HUB_ARCHITECTURE.md) 是否碰到 architecture boundary。
3. 用 [AGENTS.md](./AGENTS.md) 約束 AI 不得在缺乏事實時亂推論。
4. 用 [WORKFLOW.md](./WORKFLOW.md) 走 review gate。
5. 用 [TRACEABILITY_MATRIX.md](./TRACEABILITY_MATRIX.md) 確認 fact 與 rule 的對應關係。
6. 把已確認的 facts、decisions、validation evidence 更新到 [memory](./memory/README.md)。

補充規則：

- 若 `USB_HUB_FW_CHECKLIST.md` 缺少關鍵硬體事實，AI 必須停止作業並詢問，嚴禁假設預設值。
- 任何 firmware 修改建議都應附帶對 `Code` 與 `Data/Xdata` 使用量的預估影響分析。

## Review Gate

GitHub 與 GitLab 都有對應入口：

- [.github/PULL_REQUEST_TEMPLATE.md](./.github/PULL_REQUEST_TEMPLATE.md)
- [.gitlab/merge_request_templates/Default.md](./.gitlab/merge_request_templates/Default.md)

## 參考來源

本專案的 documentation-first 治理思路，有參考：

- <https://github.com/GavinWu672/ai-governance-framework>
