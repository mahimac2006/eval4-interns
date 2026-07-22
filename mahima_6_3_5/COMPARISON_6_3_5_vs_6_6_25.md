# WMA cross-version existence — 6.3.5 vs 6.6.25

**Verdict: the full WMA instantiation exists in 6.3.5 for both modules**, on the same nucleus
objects as 6.6.25. Differences are parameter-level (field offsets, thresholds, constants,
file rename), not structural. psmgr = complete 4-WMI chain (confirmed); vgem = WMI-1/2/3
cluster, WMI-4 weak (chain not closed) — same shape as 6.6.25.

`#STASE detected` = **post concrete-replay + agent verdict** (the validated/kept set). `SE-confirmed` = intermediate KLEE stage (recall-biased, discards 0). POC pending PAGENT.

## net/psmgr
| WMI | #SA detected 6.3.5 / 6.6.25 | SE-confirmed 6.3.5 / 6.6.25 | #STASE detected 6.3.5 / 6.6.25 | findings 6.3.5 / 6.6.25 |
|---|---|---|---|---|
| 1 | 46 / 38 | 46 / 38 | 31 / — | 45 / 38 |
| 2 | 57 / 61 | 57 / 61 | 29 / — | 57 / 51 |
| 3 | 5 / 2 | 5 / 2 | 2 / — | 5 / 2 |
| 4 | 10 / 11 | 10 / 11 | 5 / — | 6 / 6 |
| **tot** | **118 / 112** | **118 / 112** | **67 / 109** | **113 / 97** |
- SE discarded: 0 / 0 (both). Chain: **confirmed both versions** (nucleus `psmgr_desc` / `psmgr_session`).
- Agent-verdict (6.3.5, real / false-pos / unclear): WMI-1 11/15/20, WMI-2 3/35/19, WMI-3 0/4/1, WMI-4 2/5/3.

## drivers/vgem
| WMI | #SA detected 6.3.5 / 6.6.25 | SE-confirmed 6.3.5 / 6.6.25 | #STASE detected 6.3.5 / 6.6.25 | findings 6.3.5 / 6.6.25 |
|---|---|---|---|---|
| 1 | 44 / — | 44 / — | 33 / — | 44 / 23 |
| 2 | 81 / — | 81 / — | 42 / — | 81 / 59 |
| 3 | 7 / — | 7 / — | 3 / — | 7 / 6 |
| 4 | 1 / — | 1 / — | 0 / — | 1 / 1 |
| **tot** | **133 / 124** | **133 / 124** | **78 / 115** | **133 / 89** |
- SE discarded: 0 / 0. Chain: **WMI-4 weak both versions** (1 candidate, 0 concrete). 6.3.5 final-filter kept 25; 6.6.25 kept 10.
- Agent-verdict (6.3.5, real / false-pos / unclear): WMI-1 9/13/22, WMI-2 11/43/27, WMI-3 0/3/4, WMI-4 0/1/0.

## Same vs different (source diffs, `_diffs/`)
**psmgr — same WMIs, shifted parameters:**
- `psmgr_core.c` (6.6.25) renamed `psmgr_pipeline.c` (6.3.5); functions unchanged (~-2 line shift).
- `struct psmgr_desc`: `token`/`write_count` field order **swapped** → WMI memory **offsets differ**.
- `PSMGR_BUF_WRITE_THRESH` **24 (6.3.5) → 32 (6.6.25)** — the WMI-2 threshold gate.
- Constants renamed/renumbered: `PSMGR_SOL` 284→280, `PSMGR_MSG_DATA` 0x03→0x01, roles PRIMARY/SECONDARY→RELAY/BRIDGE. No WMI added/removed.

**vgem — same WMIs, small logic delta in the WMI-1 surface:**
- `dmamove_mark_staged` state machine differs (INIT/STAGING/POSTPROC transitions).
- STAGING-reject guard (INTERMEDIATE-in-flight) present in 6.3.5, **removed in 6.6.25**.
- Version-shim churn: `dma_buf_vmap` (6.3.5) vs `dma_buf_vmap_unlocked` (6.6.25); `dma_fence_allocate_private_stub()` gains a `ktime_get()` arg. No WMI added/removed.

## Notes
- SE 0-discarded is by tool design (recall-biased; semantic WMI-1/2 disposed downstream) — matches all 6.6.25 reference modules. Real narrowing at concrete_filter (mine tighter: 67/78 vs ref 109/115) and agent_final_filter.
- 6.3.5 counts run without the reachability pre-filter (ref dropped ~18 there), so 6.3.5 SA/SE totals are slightly higher.
- POC column pending PAGENT.


## Site-level mapping — 6.3.5 → 6.6.25 (via `_diffs/`)

Every 6.3.5 SA site (core WMI rules, from each module's `detection_summary.provided.csv`) mapped to its
6.6.25 location through the source diff. `diff -ruN` records the psmgr rename as delete+add, so
`psmgr_pipeline.c`→`psmgr_core.c` line correspondence was recovered by re-diffing the two embedded file bodies.
Status: **unchanged** = identical code (line may shift); **modified** = same site, line text changed; **removed** = no 6.6.25 counterpart.

**Existence result: 0 sites removed — every mapped 6.3.5 site has a 6.6.25 counterpart.** This corroborates the
top-line verdict: the WMIs exist in both versions; differences are parameter-level, not structural. Direction is
6.3.5→6.6.25 only (the repo has no 6.6.25 per-site SA output for these modules, so "6.6.25-only" sites can't be listed here).

### net/psmgr — 118 sites mapped (`psmgr_pipeline.c`→`psmgr_core.c`, +2 line shift)
| WMI | unchanged | modified | removed |
|---|---|---|---|
| 1 | 36 | 10 | 0 |
| 2 | 45 | 12 | 0 |
| 3 | 5 | 0 | 0 |
| 4 | 10 | 0 | 0 |
| **tot** | **96** | **22** | **0** |

Modified sites (same finding, line text changed in 6.6.25):
- `af_psmgr.c`: 277→277, 278→277
- `psmgr_pipeline.c`: 268→269, 469→471
- `psmgr_sock.c`: 419→417, 427→427, 428→427, 429→427, 430→427, 447→445, 455→455, 456→455, 457→455, 458→455, 382→382, 385→385, 393→393, 407→407, 438→438, 561→561, 583→583, 644→644

### drivers/vgem — 112 sites mapped (from reference SA locations; `vgem_pipeline.c` identical, not in diff)
| WMI | unchanged | modified | removed |
|---|---|---|---|
| 1 | 43 | 1 | 0 |
| 2 | 55 | 5 | 0 |
| 3 | 7 | 0 | 0 |
| 4 | 1 | 0 | 0 |
| **tot** | **106** | **6** | **0** |

_Note: 112 of the 133 vgem sites are line-mappable — the reference `detection_summary.provided.csv` lists 60 of WMI-2's 81 counted locations, so 21 WMI-2 entries have no site to map. The 0-removed result is unaffected._

Modified sites (same finding, line text changed in 6.6.25):
- `vgem_dmamove.c`: 334→334, 324→324, 325→324, 805→804, 812→804, 813→804

<details>
<summary><b>Full per-site mapping (all sites, click to expand)</b></summary>

All core-WMI 6.3.5 SA sites with their 6.6.25 line and status. `unchanged` = identical code (line may shift); `modified` = same site, line text changed.

#### net/psmgr — 118 sites

| WMI | 6.3.5 site | 6.6.25 site | status |
|---|---|---|---|
| 1 | `psmgr_pipeline.c:146` | `psmgr_core.c:146` | unchanged |
| 1 | `psmgr_pipeline.c:317` | `psmgr_core.c:319` | unchanged |
| 1 | `psmgr_pipeline.c:322` | `psmgr_core.c:324` | unchanged |
| 1 | `psmgr_pipeline.c:326` | `psmgr_core.c:328` | unchanged |
| 1 | `psmgr_pipeline.c:372` | `psmgr_core.c:374` | unchanged |
| 1 | `psmgr_pipeline.c:377` | `psmgr_core.c:379` | unchanged |
| 1 | `psmgr_pipeline.c:485` | `psmgr_core.c:487` | unchanged |
| 1 | `psmgr_sock.c:172` | `psmgr_sock.c:172` | unchanged |
| 1 | `psmgr_sock.c:175` | `psmgr_sock.c:175` | unchanged |
| 1 | `psmgr_sock.c:187` | `psmgr_sock.c:187` | unchanged |
| 1 | `psmgr_sock.c:188` | `psmgr_sock.c:188` | unchanged |
| 1 | `psmgr_sock.c:189` | `psmgr_sock.c:189` | unchanged |
| 1 | `psmgr_sock.c:190` | `psmgr_sock.c:190` | unchanged |
| 1 | `psmgr_sock.c:191` | `psmgr_sock.c:191` | unchanged |
| 1 | `psmgr_sock.c:192` | `psmgr_sock.c:192` | unchanged |
| 1 | `psmgr_sock.c:257` | `psmgr_sock.c:257` | unchanged |
| 1 | `psmgr_sock.c:258` | `psmgr_sock.c:258` | unchanged |
| 1 | `psmgr_sock.c:316` | `psmgr_sock.c:316` | unchanged |
| 1 | `psmgr_sock.c:419` | `psmgr_sock.c:417` | modified |
| 1 | `psmgr_sock.c:427` | `psmgr_sock.c:427` | modified |
| 1 | `psmgr_sock.c:428` | `psmgr_sock.c:427` | modified |
| 1 | `psmgr_sock.c:429` | `psmgr_sock.c:427` | modified |
| 1 | `psmgr_sock.c:430` | `psmgr_sock.c:427` | modified |
| 1 | `psmgr_sock.c:447` | `psmgr_sock.c:445` | modified |
| 1 | `psmgr_sock.c:455` | `psmgr_sock.c:455` | modified |
| 1 | `psmgr_sock.c:456` | `psmgr_sock.c:455` | modified |
| 1 | `psmgr_sock.c:457` | `psmgr_sock.c:455` | modified |
| 1 | `psmgr_sock.c:458` | `psmgr_sock.c:455` | modified |
| 1 | `psmgr_sock.c:474` | `psmgr_sock.c:474` | unchanged |
| 1 | `psmgr_sock.c:475` | `psmgr_sock.c:475` | unchanged |
| 1 | `psmgr_sock.c:476` | `psmgr_sock.c:476` | unchanged |
| 1 | `psmgr_sock.c:477` | `psmgr_sock.c:477` | unchanged |
| 1 | `psmgr_sock.c:533` | `psmgr_sock.c:533` | unchanged |
| 1 | `psmgr_sock.c:535` | `psmgr_sock.c:535` | unchanged |
| 1 | `psmgr_sock.c:542` | `psmgr_sock.c:542` | unchanged |
| 1 | `psmgr_sock.c:545` | `psmgr_sock.c:545` | unchanged |
| 1 | `psmgr_sock.c:568` | `psmgr_sock.c:568` | unchanged |
| 1 | `psmgr_sock.c:569` | `psmgr_sock.c:569` | unchanged |
| 1 | `psmgr_sock.c:591` | `psmgr_sock.c:591` | unchanged |
| 1 | `psmgr_sock.c:627` | `psmgr_sock.c:627` | unchanged |
| 1 | `psmgr_sock.c:629` | `psmgr_sock.c:629` | unchanged |
| 1 | `psmgr_sock.c:631` | `psmgr_sock.c:631` | unchanged |
| 1 | `psmgr_sock.c:632` | `psmgr_sock.c:632` | unchanged |
| 1 | `psmgr_sock.c:650` | `psmgr_sock.c:650` | unchanged |
| 1 | `psmgr_sock.c:654` | `psmgr_sock.c:654` | unchanged |
| 1 | `psmgr_sock.c:684` | `psmgr_sock.c:684` | unchanged |
| 2 | `af_psmgr.c:277` | `af_psmgr.c:277` | modified |
| 2 | `af_psmgr.c:278` | `af_psmgr.c:277` | modified |
| 2 | `af_psmgr.c:279` | `af_psmgr.c:279` | unchanged |
| 2 | `psmgr_pipeline.c:78` | `psmgr_core.c:78` | unchanged |
| 2 | `psmgr_pipeline.c:91` | `psmgr_core.c:91` | unchanged |
| 2 | `psmgr_pipeline.c:167` | `psmgr_core.c:167` | unchanged |
| 2 | `psmgr_pipeline.c:171` | `psmgr_core.c:171` | unchanged |
| 2 | `psmgr_pipeline.c:190` | `psmgr_core.c:190` | unchanged |
| 2 | `psmgr_pipeline.c:196` | `psmgr_core.c:196` | unchanged |
| 2 | `psmgr_pipeline.c:220` | `psmgr_core.c:220` | unchanged |
| 2 | `psmgr_pipeline.c:252` | `psmgr_core.c:254` | unchanged |
| 2 | `psmgr_pipeline.c:259` | `psmgr_core.c:261` | unchanged |
| 2 | `psmgr_pipeline.c:268` | `psmgr_core.c:269` | modified |
| 2 | `psmgr_pipeline.c:311` | `psmgr_core.c:313` | unchanged |
| 2 | `psmgr_pipeline.c:350` | `psmgr_core.c:352` | unchanged |
| 2 | `psmgr_pipeline.c:351` | `psmgr_core.c:353` | unchanged |
| 2 | `psmgr_pipeline.c:352` | `psmgr_core.c:354` | unchanged |
| 2 | `psmgr_pipeline.c:359` | `psmgr_core.c:361` | unchanged |
| 2 | `psmgr_pipeline.c:403` | `psmgr_core.c:405` | unchanged |
| 2 | `psmgr_pipeline.c:407` | `psmgr_core.c:409` | unchanged |
| 2 | `psmgr_pipeline.c:428` | `psmgr_core.c:430` | unchanged |
| 2 | `psmgr_pipeline.c:435` | `psmgr_core.c:437` | unchanged |
| 2 | `psmgr_pipeline.c:441` | `psmgr_core.c:443` | unchanged |
| 2 | `psmgr_pipeline.c:456` | `psmgr_core.c:458` | unchanged |
| 2 | `psmgr_pipeline.c:469` | `psmgr_core.c:471` | modified |
| 2 | `psmgr_pipeline.c:586` | `psmgr_core.c:588` | unchanged |
| 2 | `psmgr_sock.c:61` | `psmgr_sock.c:61` | unchanged |
| 2 | `psmgr_sock.c:183` | `psmgr_sock.c:183` | unchanged |
| 2 | `psmgr_sock.c:195` | `psmgr_sock.c:195` | unchanged |
| 2 | `psmgr_sock.c:205` | `psmgr_sock.c:205` | unchanged |
| 2 | `psmgr_sock.c:310` | `psmgr_sock.c:310` | unchanged |
| 2 | `psmgr_sock.c:313` | `psmgr_sock.c:313` | unchanged |
| 2 | `psmgr_sock.c:354` | `psmgr_sock.c:354` | unchanged |
| 2 | `psmgr_sock.c:356` | `psmgr_sock.c:356` | unchanged |
| 2 | `psmgr_sock.c:373` | `psmgr_sock.c:373` | unchanged |
| 2 | `psmgr_sock.c:382` | `psmgr_sock.c:382` | modified |
| 2 | `psmgr_sock.c:385` | `psmgr_sock.c:385` | modified |
| 2 | `psmgr_sock.c:388` | `psmgr_sock.c:388` | unchanged |
| 2 | `psmgr_sock.c:393` | `psmgr_sock.c:393` | modified |
| 2 | `psmgr_sock.c:394` | `psmgr_sock.c:394` | unchanged |
| 2 | `psmgr_sock.c:397` | `psmgr_sock.c:397` | unchanged |
| 2 | `psmgr_sock.c:407` | `psmgr_sock.c:407` | modified |
| 2 | `psmgr_sock.c:438` | `psmgr_sock.c:438` | modified |
| 2 | `psmgr_sock.c:488` | `psmgr_sock.c:488` | unchanged |
| 2 | `psmgr_sock.c:530` | `psmgr_sock.c:530` | unchanged |
| 2 | `psmgr_sock.c:561` | `psmgr_sock.c:561` | modified |
| 2 | `psmgr_sock.c:562` | `psmgr_sock.c:562` | unchanged |
| 2 | `psmgr_sock.c:583` | `psmgr_sock.c:583` | modified |
| 2 | `psmgr_sock.c:584` | `psmgr_sock.c:584` | unchanged |
| 2 | `psmgr_sock.c:602` | `psmgr_sock.c:602` | unchanged |
| 2 | `psmgr_sock.c:603` | `psmgr_sock.c:603` | unchanged |
| 2 | `psmgr_sock.c:644` | `psmgr_sock.c:644` | modified |
| 2 | `psmgr_sock.c:645` | `psmgr_sock.c:645` | unchanged |
| 2 | `psmgr_sock.c:646` | `psmgr_sock.c:646` | unchanged |
| 2 | `psmgr_sock.c:662` | `psmgr_sock.c:662` | unchanged |
| 2 | `psmgr_sock.c:676` | `psmgr_sock.c:676` | unchanged |
| 2 | `psmgr_sock.c:678` | `psmgr_sock.c:678` | unchanged |
| 3 | `psmgr_pipeline.c:281` | `psmgr_core.c:283` | unchanged |
| 3 | `psmgr_pipeline.c:359` | `psmgr_core.c:361` | unchanged |
| 3 | `psmgr_sock.c:183` | `psmgr_sock.c:183` | unchanged |
| 3 | `psmgr_sock.c:195` | `psmgr_sock.c:195` | unchanged |
| 3 | `psmgr_sock.c:205` | `psmgr_sock.c:205` | unchanged |
| 4 | `psmgr_pipeline.c:316` | `psmgr_core.c:318` | unchanged |
| 4 | `psmgr_pipeline.c:453` | `psmgr_core.c:455` | unchanged |
| 4 | `psmgr_pipeline.c:475` | `psmgr_core.c:477` | unchanged |
| 4 | `psmgr_pipeline.c:516` | `psmgr_core.c:518` | unchanged |
| 4 | `psmgr_pipeline.c:594` | `psmgr_core.c:596` | unchanged |
| 4 | `psmgr_pipeline.c:600` | `psmgr_core.c:602` | unchanged |
| 4 | `psmgr_pipeline.c:622` | `psmgr_core.c:624` | unchanged |
| 4 | `psmgr_pipeline.c:644` | `psmgr_core.c:646` | unchanged |
| 4 | `psmgr_pipeline.c:647` | `psmgr_core.c:649` | unchanged |
| 4 | `psmgr_sock.c:683` | `psmgr_sock.c:683` | unchanged |

#### drivers/vgem — 112 sites

| WMI | 6.3.5 site | 6.6.25 site | status |
|---|---|---|---|
| 1 | `vgem_dmamove.c:124` | `vgem_dmamove.c:124` | unchanged |
| 1 | `vgem_dmamove.c:125` | `vgem_dmamove.c:125` | unchanged |
| 1 | `vgem_dmamove.c:148` | `vgem_dmamove.c:148` | unchanged |
| 1 | `vgem_dmamove.c:150` | `vgem_dmamove.c:150` | unchanged |
| 1 | `vgem_dmamove.c:245` | `vgem_dmamove.c:245` | unchanged |
| 1 | `vgem_dmamove.c:246` | `vgem_dmamove.c:246` | unchanged |
| 1 | `vgem_dmamove.c:252` | `vgem_dmamove.c:252` | unchanged |
| 1 | `vgem_dmamove.c:253` | `vgem_dmamove.c:253` | unchanged |
| 1 | `vgem_dmamove.c:269` | `vgem_dmamove.c:269` | unchanged |
| 1 | `vgem_dmamove.c:270` | `vgem_dmamove.c:270` | unchanged |
| 1 | `vgem_dmamove.c:276` | `vgem_dmamove.c:276` | unchanged |
| 1 | `vgem_dmamove.c:277` | `vgem_dmamove.c:277` | unchanged |
| 1 | `vgem_dmamove.c:334` | `vgem_dmamove.c:334` | modified |
| 1 | `vgem_dmamove.c:394` | `vgem_dmamove.c:398` | unchanged |
| 1 | `vgem_dmamove.c:398` | `vgem_dmamove.c:402` | unchanged |
| 1 | `vgem_dmamove.c:411` | `vgem_dmamove.c:415` | unchanged |
| 1 | `vgem_dmamove.c:517` | `vgem_dmamove.c:521` | unchanged |
| 1 | `vgem_dmamove.c:522` | `vgem_dmamove.c:526` | unchanged |
| 1 | `vgem_dmamove.c:621` | `vgem_dmamove.c:625` | unchanged |
| 1 | `vgem_dmamove.c:664` | `vgem_dmamove.c:668` | unchanged |
| 1 | `vgem_dmamove.c:681` | `vgem_dmamove.c:685` | unchanged |
| 1 | `vgem_dmamove.c:794` | `vgem_dmamove.c:798` | unchanged |
| 1 | `vgem_dmamove.c:795` | `vgem_dmamove.c:799` | unchanged |
| 1 | `vgem_dmamove.c:796` | `vgem_dmamove.c:800` | unchanged |
| 1 | `vgem_dmamove.c:797` | `vgem_dmamove.c:801` | unchanged |
| 1 | `vgem_dmamove.c:948` | `vgem_dmamove.c:929` | unchanged |
| 1 | `vgem_dmamove.c:976` | `vgem_dmamove.c:957` | unchanged |
| 1 | `vgem_pipeline.c:82` | `vgem_pipeline.c:82` | unchanged |
| 1 | `vgem_pipeline.c:170` | `vgem_pipeline.c:170` | unchanged |
| 1 | `vgem_pipeline.c:228` | `vgem_pipeline.c:228` | unchanged |
| 1 | `vgem_postproc.c:156` | `vgem_postproc.c:156` | unchanged |
| 1 | `vgem_postproc.c:158` | `vgem_postproc.c:158` | unchanged |
| 1 | `vgem_postproc.c:159` | `vgem_postproc.c:159` | unchanged |
| 1 | `vgem_postproc.c:160` | `vgem_postproc.c:160` | unchanged |
| 1 | `vgem_postproc.c:161` | `vgem_postproc.c:161` | unchanged |
| 1 | `vgem_postproc.c:163` | `vgem_postproc.c:163` | unchanged |
| 1 | `vgem_postproc.c:165` | `vgem_postproc.c:165` | unchanged |
| 1 | `vgem_postproc.c:181` | `vgem_postproc.c:181` | unchanged |
| 1 | `vgem_postproc.c:225` | `vgem_postproc.c:225` | unchanged |
| 1 | `vgem_postproc.c:227` | `vgem_postproc.c:227` | unchanged |
| 1 | `vgem_postproc.c:333` | `vgem_postproc.c:333` | unchanged |
| 1 | `vgem_postproc.c:350` | `vgem_postproc.c:350` | unchanged |
| 1 | `vgem_postproc.c:475` | `vgem_postproc.c:475` | unchanged |
| 1 | `vgem_postproc.c:482` | `vgem_postproc.c:482` | unchanged |
| 2 | `vgem_dmamove.c:96` | `vgem_dmamove.c:96` | unchanged |
| 2 | `vgem_dmamove.c:147` | `vgem_dmamove.c:147` | unchanged |
| 2 | `vgem_dmamove.c:174` | `vgem_dmamove.c:174` | unchanged |
| 2 | `vgem_dmamove.c:175` | `vgem_dmamove.c:175` | unchanged |
| 2 | `vgem_dmamove.c:201` | `vgem_dmamove.c:201` | unchanged |
| 2 | `vgem_dmamove.c:202` | `vgem_dmamove.c:202` | unchanged |
| 2 | `vgem_dmamove.c:243` | `vgem_dmamove.c:243` | unchanged |
| 2 | `vgem_dmamove.c:266` | `vgem_dmamove.c:266` | unchanged |
| 2 | `vgem_dmamove.c:267` | `vgem_dmamove.c:267` | unchanged |
| 2 | `vgem_dmamove.c:296` | `vgem_dmamove.c:296` | unchanged |
| 2 | `vgem_dmamove.c:324` | `vgem_dmamove.c:324` | modified |
| 2 | `vgem_dmamove.c:325` | `vgem_dmamove.c:324` | modified |
| 2 | `vgem_dmamove.c:385` | `vgem_dmamove.c:389` | unchanged |
| 2 | `vgem_dmamove.c:389` | `vgem_dmamove.c:393` | unchanged |
| 2 | `vgem_dmamove.c:393` | `vgem_dmamove.c:397` | unchanged |
| 2 | `vgem_dmamove.c:400` | `vgem_dmamove.c:404` | unchanged |
| 2 | `vgem_dmamove.c:402` | `vgem_dmamove.c:406` | unchanged |
| 2 | `vgem_dmamove.c:491` | `vgem_dmamove.c:495` | unchanged |
| 2 | `vgem_dmamove.c:556` | `vgem_dmamove.c:560` | unchanged |
| 2 | `vgem_dmamove.c:559` | `vgem_dmamove.c:563` | unchanged |
| 2 | `vgem_dmamove.c:566` | `vgem_dmamove.c:570` | unchanged |
| 2 | `vgem_dmamove.c:574` | `vgem_dmamove.c:578` | unchanged |
| 2 | `vgem_dmamove.c:575` | `vgem_dmamove.c:579` | unchanged |
| 2 | `vgem_dmamove.c:582` | `vgem_dmamove.c:586` | unchanged |
| 2 | `vgem_dmamove.c:583` | `vgem_dmamove.c:587` | unchanged |
| 2 | `vgem_dmamove.c:595` | `vgem_dmamove.c:599` | unchanged |
| 2 | `vgem_dmamove.c:596` | `vgem_dmamove.c:600` | unchanged |
| 2 | `vgem_dmamove.c:619` | `vgem_dmamove.c:623` | unchanged |
| 2 | `vgem_dmamove.c:649` | `vgem_dmamove.c:653` | unchanged |
| 2 | `vgem_dmamove.c:706` | `vgem_dmamove.c:710` | unchanged |
| 2 | `vgem_dmamove.c:714` | `vgem_dmamove.c:718` | unchanged |
| 2 | `vgem_dmamove.c:754` | `vgem_dmamove.c:758` | unchanged |
| 2 | `vgem_dmamove.c:798` | `vgem_dmamove.c:802` | unchanged |
| 2 | `vgem_dmamove.c:805` | `vgem_dmamove.c:804` | modified |
| 2 | `vgem_dmamove.c:812` | `vgem_dmamove.c:804` | modified |
| 2 | `vgem_dmamove.c:813` | `vgem_dmamove.c:804` | modified |
| 2 | `vgem_dmamove.c:865` | `vgem_dmamove.c:846` | unchanged |
| 2 | `vgem_dmamove.c:866` | `vgem_dmamove.c:847` | unchanged |
| 2 | `vgem_dmamove.c:881` | `vgem_dmamove.c:862` | unchanged |
| 2 | `vgem_dmamove.c:885` | `vgem_dmamove.c:866` | unchanged |
| 2 | `vgem_dmamove.c:896` | `vgem_dmamove.c:877` | unchanged |
| 2 | `vgem_dmamove.c:904` | `vgem_dmamove.c:885` | unchanged |
| 2 | `vgem_dmamove.c:931` | `vgem_dmamove.c:912` | unchanged |
| 2 | `vgem_dmamove.c:935` | `vgem_dmamove.c:916` | unchanged |
| 2 | `vgem_dmamove.c:939` | `vgem_dmamove.c:920` | unchanged |
| 2 | `vgem_dmamove.c:943` | `vgem_dmamove.c:924` | unchanged |
| 2 | `vgem_dmamove.c:1027` | `vgem_dmamove.c:1008` | unchanged |
| 2 | `vgem_dmamove.c:1033` | `vgem_dmamove.c:1014` | unchanged |
| 2 | `vgem_dmamove.c:1164` | `vgem_dmamove.c:1145` | unchanged |
| 2 | `vgem_dmamove.c:1167` | `vgem_dmamove.c:1148` | unchanged |
| 2 | `vgem_dmamove.c:1169` | `vgem_dmamove.c:1150` | unchanged |
| 2 | `vgem_dmamove.c:1171` | `vgem_dmamove.c:1152` | unchanged |
| 2 | `vgem_dmamove.c:1172` | `vgem_dmamove.c:1153` | unchanged |
| 2 | `vgem_dmamove.c:1174` | `vgem_dmamove.c:1155` | unchanged |
| 2 | `vgem_dmamove.c:1175` | `vgem_dmamove.c:1156` | unchanged |
| 2 | `vgem_dmamove.c:1204` | `vgem_dmamove.c:1185` | unchanged |
| 2 | `vgem_pipeline.c:98` | `vgem_pipeline.c:98` | unchanged |
| 2 | `vgem_pipeline.c:112` | `vgem_pipeline.c:112` | unchanged |
| 2 | `vgem_pipeline.c:150` | `vgem_pipeline.c:150` | unchanged |
| 2 | `vgem_pipeline.c:208` | `vgem_pipeline.c:208` | unchanged |
| 3 | `vgem_dmamove.c:243` | `vgem_dmamove.c:243` | unchanged |
| 3 | `vgem_dmamove.c:266` | `vgem_dmamove.c:266` | unchanged |
| 3 | `vgem_dmamove.c:267` | `vgem_dmamove.c:267` | unchanged |
| 3 | `vgem_dmamove.c:798` | `vgem_dmamove.c:802` | unchanged |
| 3 | `vgem_pipeline.c:98` | `vgem_pipeline.c:98` | unchanged |
| 3 | `vgem_postproc.c:213` | `vgem_postproc.c:213` | unchanged |
| 3 | `vgem_postproc.c:483` | `vgem_postproc.c:483` | unchanged |
| 4 | `vgem_dmamove.c:515` | `vgem_dmamove.c:519` | unchanged |

</details>
