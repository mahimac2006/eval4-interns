# WMI-3 CodeQL sinks — drivers/block, kernel 6.6.25

STASE/SAILOR CodeQL **2.17.6** (in a linux/amd64 Docker container), the **4 WMI-3
detector queries** run unmodified over the whole `drivers/block` module.

- DB built the SAILOR way under **allmodconfig**: preprocess each `*.c` -> strip
  `__seg_*` -> traced `gcc -c` extract.
- Findings exported as SARIF, then **mapped from preprocessed-file coordinates back
  to original source `file:line`** via the `.i` `#line` markers, enclosing `func`
  added via ctags, and **deduped to distinct `file:line`**.
- Each record: `{file, line, func, callee, detail}` (callee empty — these are
  struct-field assignment sinks, not calls).

Distinct sink counts (whole drivers/block module):
| query | distinct sinks |
|---|---|
| WMI-3_AttackerContent_IntoAuthoritativePosition | 310 |
| WMI-3_ArbitraryFree_StaleTraversal | 9 |
| WMI-3b_AttackerContent_OffsetControlledWrite | 8 |
| WMI-3c_AttackerContent_PreinstalledPointerGate | 0 |

(loop.c alone: 10 distinct main-WMI-3 sinks.) These are broad candidate sinks, not
confirmed WMI-3s — reachability/oracle narrowing is a later step.
