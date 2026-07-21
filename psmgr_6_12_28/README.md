# stase eval4 — net/psmgr

## Pipeline summary

| Stage | What it does | Count |
|---|---|---|
| **SA (CodeQL)** | WMI rules flag candidate sites in source. | **113** detections |
| **Symex (KLEE)** | Replay symbolic execution over each candidate. | **113** confirmed / 0 discarded / 113 total |
| **Agent filter** | LLM review of SE replay + chain co-occurrence. | **0** kept / 0 dropped |
| **Concrete boot** | KASAN replay on real kernel. | pending (no kernel_image provided) |

---

## WMI-1 — Signal Divergence (Ungoverned Signal)

**WMI-1: Shared State Divergence @ psmgr_setsockopt**
Site: `psmgr_sock.c:psmgr_setsockopt` — 14 sites, 14 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/0423482c…/`](1_wmi_findings/findings/wmi-1/0423482c-8842-4a7f-90ac-a57fe0f75dc1/)

**WMI-1: Shared State Divergence @ psmgr_connect**
Site: `psmgr_sock.c:psmgr_connect` — 14 sites, 14 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/076c4fe1…/`](1_wmi_findings/findings/wmi-1/076c4fe1-37cd-4a30-b874-c5528c50a2a3/)

**WMI-1: Shared State Divergence @ psmgr_process_commit_req**
Site: `psmgr_core.c:psmgr_process_commit_req` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/0910274d…/`](1_wmi_findings/findings/wmi-1/0910274d-194c-4419-ae9d-f4a6f58dafcc/)

**WMI-1: Shared State Divergence @ psmgr_bind**
Site: `psmgr_sock.c:psmgr_bind` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/0e0d8ca1…/`](1_wmi_findings/findings/wmi-1/0e0d8ca1-0259-4360-941d-f7711e0a3790/)

**WMI-1: Shared State Divergence @ psmgr_compute_token**
Site: `psmgr_core.c:psmgr_compute_token` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/16049a8a…/`](1_wmi_findings/findings/wmi-1/16049a8a-3922-46a9-8d4d-020c9a5cff8b/)

**WMI-1: Shared State Divergence @ psmgr_release**
Site: `psmgr_sock.c:psmgr_release` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/1ebf90bf…/`](1_wmi_findings/findings/wmi-1/1ebf90bf-e942-4f60-b51a-9cc7d109b04b/)

**WMI-1: Shared State Divergence @ psmgr_sendmsg**
Site: `psmgr_core.c:psmgr_sendmsg` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/4c854d21…/`](1_wmi_findings/findings/wmi-1/4c854d21-8036-4719-9f71-bc5d8754ed95/)

**WMI-1: Shared State Divergence @ psmgr_process_ctrl**
Site: `psmgr_core.c:psmgr_process_ctrl` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/64098b9e…/`](1_wmi_findings/findings/wmi-1/64098b9e-953e-4987-8d2b-461020486898/)

---

## WMI-2 — Live Resource Inconsistency

**WMI-2: Live Resource Inconsistency @ psmgr_process_commit_req**
Site: `psmgr_core.c:psmgr_process_commit_req` — 4 sites, 4 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/06b0ac32…/`](1_wmi_findings/findings/wmi-2/06b0ac32-3d18-4aac-9e46-68b3bf30f1ff/)

**WMI-2: Live Resource Inconsistency @ psmgr_setsockopt**
Site: `psmgr_sock.c:psmgr_setsockopt` — 13 sites, 13 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/13049b3f…/`](1_wmi_findings/findings/wmi-2/13049b3f-cd96-4cbe-83cc-d09a668f792e/)

**WMI-2: Live Resource Inconsistency @ psmgr_sendmsg**
Site: `psmgr_core.c:psmgr_sendmsg` — 5 sites, 5 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/241497bf…/`](1_wmi_findings/findings/wmi-2/241497bf-fee6-428c-83ce-af068ebca724/)

**WMI-2: Live Resource Inconsistency @ psmgr_bind**
Site: `psmgr_sock.c:psmgr_bind` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/252ab5bc…/`](1_wmi_findings/findings/wmi-2/252ab5bc-e17f-49ce-931d-f5d9f7c1f1e4/)

**WMI-2: Live Resource Inconsistency @ psmgr_connect**
Site: `psmgr_sock.c:psmgr_connect` — 12 sites, 12 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/2dff4de0…/`](1_wmi_findings/findings/wmi-2/2dff4de0-c100-4b8e-903a-8b36fb30df11/)

**WMI-2: Live Resource Inconsistency @ psmgr_session_lookup**
Site: `psmgr_sock.c:psmgr_session_lookup` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/3b875f7b…/`](1_wmi_findings/findings/wmi-2/3b875f7b-f870-4859-9a1c-4f454407f537/)

**WMI-2: Live Resource Inconsistency @ psmgr_process_data**
Site: `psmgr_core.c:psmgr_process_data` — 6 sites, 6 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/4992f8c8…/`](1_wmi_findings/findings/wmi-2/4992f8c8-95ae-4cf4-aed8-1c9255c49536/)

**WMI-2: Live Resource Inconsistency @ psmgr_check_seq**
Site: `psmgr_core.c:psmgr_check_seq` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/5096a514…/`](1_wmi_findings/findings/wmi-2/5096a514-1597-4b92-8aab-5f6b0b1b43b8/)

**WMI-2: Live Resource Inconsistency @ psmgr_poll**
Site: `psmgr_core.c:psmgr_poll` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/53637ec1…/`](1_wmi_findings/findings/wmi-2/53637ec1-3be2-462a-9e45-d46935f9e6cd/)

**WMI-2: Live Resource Inconsistency @ psmgr_write_count_update**
Site: `psmgr_core.c:psmgr_write_count_update` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/7893a7e7…/`](1_wmi_findings/findings/wmi-2/7893a7e7-321b-4738-877a-0d17035308ab/)

**WMI-2: Live Resource Inconsistency @ psmgr_process_ctrl**
Site: `psmgr_core.c:psmgr_process_ctrl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/9753e3ee…/`](1_wmi_findings/findings/wmi-2/9753e3ee-f29d-4133-9043-378a97ebe420/)

**WMI-2: Live Resource Inconsistency @ psmgr_recvmsg**
Site: `psmgr_core.c:psmgr_recvmsg` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/980e4f37…/`](1_wmi_findings/findings/wmi-2/980e4f37-9ade-4fd8-a751-6d96034c0d4e/)

---

## WMI-3 — Attacker Content in Authoritative Position

**WMI-3: Attacker-Determined Content in an Authoritative Position @ psmgr_process_data**
Site: `psmgr_core.c:psmgr_process_data` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/4b1decbf…/`](1_wmi_findings/findings/wmi-3/4b1decbf-d2d2-4b77-a3ea-086ef8f0ab93/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ psmgr_process_commit_req**
Site: `psmgr_core.c:psmgr_process_commit_req` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/f21206f6…/`](1_wmi_findings/findings/wmi-3/f21206f6-d4c2-41d2-94d8-9c05f75eee73/)

---

## WMI-4 — Arbitrary Access (Target or Extent from Field)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_setsockopt**
Site: `psmgr_sock.c:psmgr_setsockopt` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/0b600e12…/`](1_wmi_findings/findings/wmi-4/0b600e12-8957-496f-ac23-773bc11a41dc/)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_recvmsg**
Site: `psmgr_core.c:psmgr_recvmsg` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/112c54f0…/`](1_wmi_findings/findings/wmi-4/112c54f0-b94a-43bf-8a15-e37cc73997fd/)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_exec**
Site: `psmgr_core.c:psmgr_exec` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/2b324216…/`](1_wmi_findings/findings/wmi-4/2b324216-a9b6-468e-b001-4256b8840f6a/)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ psmgr_process_ctrl**
Site: `psmgr_core.c:psmgr_process_ctrl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/de081aaa…/`](1_wmi_findings/findings/wmi-4/de081aaa-12dc-451f-ad0a-3a7e029c0a03/)

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
