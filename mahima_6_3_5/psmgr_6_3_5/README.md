# stase eval4 — net/psmgr

## Pipeline summary

| Stage | What it does | Count |
|---|---|---|
| **SA (CodeQL + RbSA)** | WMI rules flag candidate sites; two SA engines, distinct union. | **143** distinct (118 CodeQL + 25 RbSA-only) |
| **Symex (KLEE)** | Replay symbolic execution over each candidate. | **118** confirmed / 0 discarded / 118 total |
| **Agent filter** | LLM review of SE replay + chain co-occurrence. | **67** kept / 51 dropped |
| **Concrete boot** | KASAN replay on real kernel. | pending |

_SA total is the distinct union of both static-analysis engines. RbSA-only = 25 module-scoped findings CodeQL missed (generic kernel-header sinks excluded, per the `drivers/` convention). These RbSA-only sites are **not** carried into the KLEE/agent/concrete stages below, which ran on the 118 CodeQL candidates. Source: `../rbsa_vs_codeql.csv`._

---

## WMI-1 — Signal Divergence (Ungoverned Signal)

**WMI-1: Shared State Divergence @ psmgr_connect**
Site: `psmgr_sock.c:psmgr_connect` — 14 sites, 14 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/00fcf91a…/`](1_wmi_findings/findings/wmi-1/00fcf91a-6a42-4e18-ac3b-780fe699adeb/)

**WMI-1: Shared State Divergence @ psmgr_create**
Site: `psmgr_sock.c:psmgr_create` — 7 sites, 7 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/04980adb…/`](1_wmi_findings/findings/wmi-1/04980adb-33e1-4044-aa17-991c40af359b/)

**WMI-1: Shared State Divergence @ psmgr_setsockopt**
Site: `psmgr_sock.c:psmgr_setsockopt` — 14 sites, 14 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/05210394…/`](1_wmi_findings/findings/wmi-1/05210394-37f0-4fbc-aeb6-2d2fe19b5e47/)

**WMI-1: Shared State Divergence @ psmgr_process_ctrl**
Site: `psmgr_pipeline.c:psmgr_process_ctrl` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/0c73cd03…/`](1_wmi_findings/findings/wmi-1/0c73cd03-98d1-4414-816a-e2c6dcb44b75/)

**WMI-1: Shared State Divergence @ psmgr_process_commit_req**
Site: `psmgr_pipeline.c:psmgr_process_commit_req` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/1b386f7e…/`](1_wmi_findings/findings/wmi-1/1b386f7e-6d84-4423-9b12-a1a969688177/)

**WMI-1: Shared State Divergence @ psmgr_release**
Site: `psmgr_sock.c:psmgr_release` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/4055539e…/`](1_wmi_findings/findings/wmi-1/4055539e-9675-461b-adb2-b39e989d7951/)

**WMI-1: Shared State Divergence @ psmgr_sendmsg**
Site: `psmgr_pipeline.c:psmgr_sendmsg` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/714f8e79…/`](1_wmi_findings/findings/wmi-1/714f8e79-ecf0-490d-a390-d535aea4a8b0/)

**WMI-1: Shared State Divergence @ psmgr_bind**
Site: `psmgr_sock.c:psmgr_bind` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/7b960a68…/`](1_wmi_findings/findings/wmi-1/7b960a68-a845-46c8-b9ad-9791a07bb201/)

**WMI-1: Shared State Divergence @ psmgr_compute_token**
Site: `psmgr_pipeline.c:psmgr_compute_token` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/f04d5a06…/`](1_wmi_findings/findings/wmi-1/f04d5a06-23e3-43dd-9cce-13cbb8564265/)

---

## WMI-2 — Live Resource Inconsistency

**WMI-2: Live Resource Inconsistency @ psmgr_connect**
Site: `psmgr_sock.c:psmgr_connect` — 12 sites, 12 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/00f83cae…/`](1_wmi_findings/findings/wmi-2/00f83cae-ddd2-45a8-b808-994a5322162c/)

**WMI-2: Live Resource Inconsistency @ psmgr_recvmsg**
Site: `psmgr_pipeline.c:psmgr_recvmsg` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/219f7dd2…/`](1_wmi_findings/findings/wmi-2/219f7dd2-89d8-4c7a-aafd-65c25a5ba6f2/)

**WMI-2: Live Resource Inconsistency @ psmgr_poll**
Site: `psmgr_pipeline.c:psmgr_poll` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/23dca4b9…/`](1_wmi_findings/findings/wmi-2/23dca4b9-15f1-4fa7-a17e-b00da5d51738/)

**WMI-2: Live Resource Inconsistency @ psmgr_setsockopt**
Site: `psmgr_sock.c:psmgr_setsockopt` — 13 sites, 13 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/240925ec…/`](1_wmi_findings/findings/wmi-2/240925ec-e6af-443e-9e80-b6699c16e75a/)

**WMI-2: Live Resource Inconsistency @ psmgr_check_seq**
Site: `psmgr_pipeline.c:psmgr_check_seq` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/2dab37ce…/`](1_wmi_findings/findings/wmi-2/2dab37ce-b372-4ea1-9f83-8e1da9791547/)

**WMI-2: Live Resource Inconsistency @ psmgr_bind**
Site: `psmgr_sock.c:psmgr_bind` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/3b7fca40…/`](1_wmi_findings/findings/wmi-2/3b7fca40-ac22-4efb-893d-1cdb57eae5b8/)

**WMI-2: Live Resource Inconsistency @ psmgr_process_commit_req**
Site: `psmgr_pipeline.c:psmgr_process_commit_req` — 4 sites, 4 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/409212ff…/`](1_wmi_findings/findings/wmi-2/409212ff-bfeb-4c17-8296-6fcf8e91a134/)

**WMI-2: Live Resource Inconsistency @ psmgr_create**
Site: `psmgr_sock.c:psmgr_create` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/41cfa8ce…/`](1_wmi_findings/findings/wmi-2/41cfa8ce-edec-402f-804b-b170c8c6536a/)

**WMI-2: Live Resource Inconsistency @ psmgr_write_count_update**
Site: `psmgr_pipeline.c:psmgr_write_count_update` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/4420163c…/`](1_wmi_findings/findings/wmi-2/4420163c-d837-495d-8bd8-b73216953f58/)

**WMI-2: Live Resource Inconsistency @ psmgr_process_data**
Site: `psmgr_pipeline.c:psmgr_process_data` — 6 sites, 6 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/50397a77…/`](1_wmi_findings/findings/wmi-2/50397a77-0714-42f8-99bd-cc0d8ef11428/)

**WMI-2: Live Resource Inconsistency @ psmgr_session_lookup**
Site: `psmgr_sock.c:psmgr_session_lookup` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/721610f2…/`](1_wmi_findings/findings/wmi-2/721610f2-7827-4a53-a6fa-7ebf57fbea92/)

**WMI-2: Live Resource Inconsistency @ psmgr_sendmsg**
Site: `psmgr_pipeline.c:psmgr_sendmsg` — 5 sites, 5 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/7b60470d…/`](1_wmi_findings/findings/wmi-2/7b60470d-566a-4d6c-a4ca-8a90b562a643/)

**WMI-2: Live Resource Inconsistency @ psmgr_init**
Site: `af_psmgr.c:psmgr_init` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/99ea0f9d…/`](1_wmi_findings/findings/wmi-2/99ea0f9d-477f-4a52-add3-5bb43dab0408/)

**WMI-2: Live Resource Inconsistency @ psmgr_process_ctrl**
Site: `psmgr_pipeline.c:psmgr_process_ctrl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/9f1ff54f…/`](1_wmi_findings/findings/wmi-2/9f1ff54f-d541-4694-b10b-e190b59ec0db/)

---

## WMI-3 — Attacker Content in Authoritative Position

**WMI-3: Attacker-Determined Content in an Authoritative Position @ psmgr_create**
Site: `psmgr_sock.c:psmgr_create` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/0a4c5889…/`](1_wmi_findings/findings/wmi-3/0a4c5889-8b0c-4084-ad5a-2a058bb71c63/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ psmgr_process_commit_req**
Site: `psmgr_pipeline.c:psmgr_process_commit_req` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/6aa74e76…/`](1_wmi_findings/findings/wmi-3/6aa74e76-64ab-4816-b1d2-74363887e2ba/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ psmgr_process_data**
Site: `psmgr_pipeline.c:psmgr_process_data` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/c06ec284…/`](1_wmi_findings/findings/wmi-3/c06ec284-2765-43f2-886f-ba95572c0c1a/)

---

## WMI-4 — Arbitrary Access (Target or Extent from Field)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_setsockopt**
Site: `psmgr_sock.c:psmgr_setsockopt` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/5661827f…/`](1_wmi_findings/findings/wmi-4/5661827f-8c3e-421c-bd82-ea60baaec7e6/)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_exec**
Site: `psmgr_pipeline.c:psmgr_exec` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/5eb0299a…/`](1_wmi_findings/findings/wmi-4/5eb0299a-fbbb-47cf-a7ee-a2a1d27f70d6/)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_process_ctrl**
Site: `psmgr_pipeline.c:psmgr_process_ctrl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/6b446e03…/`](1_wmi_findings/findings/wmi-4/6b446e03-933d-4214-b3ed-c7273f0d21e5/)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_recvmsg**
Site: `psmgr_pipeline.c:psmgr_recvmsg` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/6f169bab…/`](1_wmi_findings/findings/wmi-4/6f169bab-2ded-4fc1-bdc2-b25da5f062f9/)

---

## Reference for `1_wmi_findings/findings/<uuid>/wmi.json`

| Field | Meaning |
|---|---|
| `operation.name` | identifier of the abstract operation |
| `operation.effects[]` | what the operation does — `type`, `arguments.destinations[]` (struct.field segments) |
| `trigger.function` | function where the bug fires |
| `trigger.file` | source file |
| `name` | human-readable WMI check identifier |
| `metadata.wmi_index` | WMI check number (1–4) |
| `metadata.verdict_kind` | `concrete_confirmed` \| `symex_explored` \| `static_candidate` |
| `metadata.detected_by[]` | SA detections — `{engine, rule, mechanism, file, line}` (SE-confirmed only) |
| `metadata.symex_oracle` | KLEE run record |
| `metadata.concrete_oracle` | Boot corroboration (when kernel_image provided) |

Internal pipeline stages: `2_sa_codeql/` (CodeQL output), `3_se_confirm/` (KLEE harnesses + SE confirm),
`4_concrete/` (replay filter + agent verdict). `detection_summary.csv` is a per-mechanism roll-up.
