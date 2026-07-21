# stase eval4 — drivers/vgem

## Pipeline summary

| Stage | What it does | Count |
|---|---|---|
| **SA (CodeQL + RbSA)** | WMI rules flag candidate sites; two SA engines, distinct union. | **179** distinct (133 CodeQL + 46 RbSA-only) |
| **Symex (KLEE)** | Replay symbolic execution over each candidate. | **133** confirmed / 0 discarded / 133 total |
| **Agent filter** | LLM review of SE replay + chain co-occurrence. | **78** kept / 55 dropped |
| **Concrete boot** | KASAN replay on real kernel. | pending |

_SA total is the distinct union of both static-analysis engines. RbSA-only = 46 module-scoped findings CodeQL missed (generic kernel-header sinks excluded, per the `drivers/` convention). These RbSA-only sites are **not** carried into the KLEE/agent/concrete stages below, which ran on the 133 CodeQL candidates. Source: `../rbsa_vs_codeql.csv`._

---

## WMI-1 — Signal Divergence (Ungoverned Signal)

**WMI-1: Shared State Divergence @ postproc_build_desc_ring**
Site: `vgem_postproc.c:postproc_build_desc_ring` — 8 sites, 8 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/03a1b276…/`](1_wmi_findings/findings/wmi-1/03a1b276-4e17-41e9-9c4c-120240367ff1/)

**WMI-1: Shared State Divergence @ dmamove_job_submit**
Site: `vgem_dmamove.c:dmamove_job_submit` — 4 sites, 4 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/0a32e5c1…/`](1_wmi_findings/findings/wmi-1/0a32e5c1-5412-4c27-ae22-180fee640cf7/)

**WMI-1: Shared State Divergence @ postproc_job_submit**
Site: `vgem_postproc.c:postproc_job_submit` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/14edf92a…/`](1_wmi_findings/findings/wmi-1/14edf92a-e05a-49b3-8171-c62504dbb959/)

**WMI-1: Shared State Divergence @ vgem_postproc_ctx_alloc**
Site: `vgem_postproc.c:vgem_postproc_ctx_alloc` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/155d3de0…/`](1_wmi_findings/findings/wmi-1/155d3de0-ce8d-4289-879e-3be0ab95f2ce/)

**WMI-1: Shared State Divergence @ vgem_dmamove_buf_state_get**
Site: `vgem_dmamove.c:vgem_dmamove_buf_state_get` — 8 sites, 8 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/18f66e3c…/`](1_wmi_findings/findings/wmi-1/18f66e3c-c568-45eb-a853-a6cb6f22bb54/)

**WMI-1: Shared State Divergence @ dmamove_job_execute**
Site: `vgem_dmamove.c:dmamove_job_execute` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/1f5f4435…/`](1_wmi_findings/findings/wmi-1/1f5f4435-96c7-44af-8ba3-c9cb54f30f04/)

**WMI-1: Shared State Divergence @ postproc_update_buf_state**
Site: `vgem_postproc.c:postproc_update_buf_state` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/232d8ea9…/`](1_wmi_findings/findings/wmi-1/232d8ea9-ed5f-4568-a809-2b7583b738a4/)

**WMI-1: Shared State Divergence @ vgem_dmamove_buf_mark_staged**
Site: `vgem_dmamove.c:vgem_dmamove_buf_mark_staged` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/24c1a724…/`](1_wmi_findings/findings/wmi-1/24c1a724-6f96-448f-ace5-ee5c7bd381e6/)

**WMI-1: Shared State Divergence @ vgem_dmamove_token_free**
Site: `vgem_dmamove.c:vgem_dmamove_token_free` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/2545f8ac…/`](1_wmi_findings/findings/wmi-1/2545f8ac-d019-494e-8789-8cf8e4c22af8/)

**WMI-1: Shared State Divergence @ dmamove_job_exec**
Site: `vgem_dmamove.c:dmamove_job_exec` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/40702bd4…/`](1_wmi_findings/findings/wmi-1/40702bd4-f722-4036-af1a-47e6db335a83/)

**WMI-1: Shared State Divergence @ vgem_dmamove_ctx_alloc**
Site: `vgem_dmamove.c:vgem_dmamove_ctx_alloc` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/46d10264…/`](1_wmi_findings/findings/wmi-1/46d10264-6fc3-48ce-a0e8-1f1e4c0da34e/)

**WMI-1: Shared State Divergence @ vgem_dmamove_token_alloc**
Site: `vgem_dmamove.c:vgem_dmamove_token_alloc` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/5fa6db37…/`](1_wmi_findings/findings/wmi-1/5fa6db37-9f40-40fd-942d-5d30404e94b2/)

**WMI-1: Shared State Divergence @ postproc_job_execute**
Site: `vgem_postproc.c:postproc_job_execute` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/680d9074…/`](1_wmi_findings/findings/wmi-1/680d9074-f5fa-4893-a313-f44eab1e089c/)

**WMI-1: Shared State Divergence @ dmamove_fetch_ring**
Site: `vgem_dmamove.c:dmamove_fetch_ring` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/689ca37a…/`](1_wmi_findings/findings/wmi-1/689ca37a-96cf-4f26-bf93-9ad474a31021/)

**WMI-1: Shared State Divergence @ dmamove_finalize_pending**
Site: `vgem_dmamove.c:dmamove_finalize_pending` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/7582957b…/`](1_wmi_findings/findings/wmi-1/7582957b-3dfc-48eb-a450-e9b6f6066569/)

**WMI-1: Shared State Divergence @ pipeline_ioctl_submit_pp**
Site: `vgem_pipeline.c:pipeline_ioctl_submit_pp` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/a38bcc30…/`](1_wmi_findings/findings/wmi-1/a38bcc30-9cfa-4178-a2c4-de525997c21c/)

**WMI-1: Shared State Divergence @ pipeline_ioctl_submit_dma**
Site: `vgem_pipeline.c:pipeline_ioctl_submit_dma` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/b2f8707f…/`](1_wmi_findings/findings/wmi-1/b2f8707f-936d-46d5-9216-cbe6566a50c2/)

**WMI-1: Shared State Divergence @ pipeline_open**
Site: `vgem_pipeline.c:pipeline_open` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-1/b71c91f0…/`](1_wmi_findings/findings/wmi-1/b71c91f0-ba64-4a92-96b4-c7099b6aa96a/)

---

## WMI-2 — Live Resource Inconsistency

**WMI-2: Live Resource Inconsistency @ dmamove_finalize_pending**
Site: `vgem_dmamove.c:dmamove_finalize_pending` — 5 sites, 5 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/00b8acfe…/`](1_wmi_findings/findings/wmi-2/00b8acfe-b85c-42f6-b588-a1f07c0cf20e/)

**WMI-2: Live Resource Inconsistency @ dmamove_fetch_ring**
Site: `vgem_dmamove.c:dmamove_fetch_ring` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/068c96bf…/`](1_wmi_findings/findings/wmi-2/068c96bf-596c-4f0e-8ba7-b2bd71373f4d/)

**WMI-2: Live Resource Inconsistency @ dmamove_job_query**
Site: `vgem_dmamove.c:dmamove_job_query` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/0720cde5…/`](1_wmi_findings/findings/wmi-2/0720cde5-7e67-416b-9bf9-a47818f2af8c/)

**WMI-2: Live Resource Inconsistency @ token_resolve_write**
Site: `vgem_dmamove.c:token_resolve_write` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/0ff5626d…/`](1_wmi_findings/findings/wmi-2/0ff5626d-63b7-4359-8bca-e0fc982685ee/)

**WMI-2: Live Resource Inconsistency @ dmamove_run_descs**
Site: `vgem_dmamove.c:dmamove_run_descs` — 9 sites, 9 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/1733c372…/`](1_wmi_findings/findings/wmi-2/1733c372-71d5-4416-91b9-a33b741874bf/)

**WMI-2: Live Resource Inconsistency @ vgem_dmamove_buf_state_get**
Site: `vgem_dmamove.c:vgem_dmamove_buf_state_get` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/1d168f41…/`](1_wmi_findings/findings/wmi-2/1d168f41-e9b5-4ff6-b5b7-ee200687a991/)

**WMI-2: Live Resource Inconsistency @ pipeline_open**
Site: `vgem_pipeline.c:pipeline_open` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/1fc4865c…/`](1_wmi_findings/findings/wmi-2/1fc4865c-9a69-4637-8c4a-f802e9e06456/)

**WMI-2: Live Resource Inconsistency @ pipeline_ioctl**
Site: `vgem_pipeline.c:pipeline_ioctl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/27a864ad…/`](1_wmi_findings/findings/wmi-2/27a864ad-77e1-4ff5-9033-b0a1a8f76122/)

**WMI-2: Live Resource Inconsistency @ dmamove_ioctl_validate**
Site: `vgem_dmamove.c:dmamove_ioctl_validate` — 7 sites, 7 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/27bda80d…/`](1_wmi_findings/findings/wmi-2/27bda80d-82e4-4d20-89f6-3cf63b6f0a8c/)

**WMI-2: Live Resource Inconsistency @ pipeline_ioctl_submit_dma**
Site: `vgem_pipeline.c:pipeline_ioctl_submit_dma` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/29423ebd…/`](1_wmi_findings/findings/wmi-2/29423ebd-daaa-4608-abd3-7135e6c6a26c/)

**WMI-2: Live Resource Inconsistency @ dmamove_open**
Site: `vgem_dmamove.c:dmamove_open` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/2a3e17c2…/`](1_wmi_findings/findings/wmi-2/2a3e17c2-36b9-4899-9493-f9101f704edc/)

**WMI-2: Live Resource Inconsistency @ dmamove_job_exec**
Site: `vgem_dmamove.c:dmamove_job_exec` — 4 sites, 4 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/2cb409fb…/`](1_wmi_findings/findings/wmi-2/2cb409fb-442c-42ae-9983-d03fec8d39b6/)

**WMI-2: Live Resource Inconsistency @ dmamove_job_submit**
Site: `vgem_dmamove.c:dmamove_job_submit` — 5 sites, 5 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/44848041…/`](1_wmi_findings/findings/wmi-2/44848041-3d33-43fd-ba08-ff8df56cd24d/)

**WMI-2: Live Resource Inconsistency @ postproc_job_reap**
Site: `vgem_postproc.c:postproc_job_reap` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/4da270d3…/`](1_wmi_findings/findings/wmi-2/4da270d3-9a09-44df-b9da-56665248f6f1/)

**WMI-2: Live Resource Inconsistency @ vgem_dmamove_buf_set_intermediate**
Site: `vgem_dmamove.c:vgem_dmamove_buf_set_intermediate` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/4fe8a43a…/`](1_wmi_findings/findings/wmi-2/4fe8a43a-d73e-4c33-bf72-b47a8d382169/)

**WMI-2: Live Resource Inconsistency @ postproc_release**
Site: `vgem_postproc.c:postproc_release` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/59f5576d…/`](1_wmi_findings/findings/wmi-2/59f5576d-eab5-40d0-9be5-dc588dfdb496/)

**WMI-2: Live Resource Inconsistency @ postproc_build_desc_ring**
Site: `vgem_postproc.c:postproc_build_desc_ring` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/6519c665…/`](1_wmi_findings/findings/wmi-2/6519c665-81c0-48e7-a39e-d825e97ca393/)

**WMI-2: Live Resource Inconsistency @ vgem_dmamove_ctx_free**
Site: `vgem_dmamove.c:vgem_dmamove_ctx_free` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/69b974e5…/`](1_wmi_findings/findings/wmi-2/69b974e5-1355-4991-af39-80b867394699/)

**WMI-2: Live Resource Inconsistency @ token_resolve**
Site: `vgem_dmamove.c:token_resolve` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/6b674e70…/`](1_wmi_findings/findings/wmi-2/6b674e70-37a0-4b45-acad-d320fd07174e/)

**WMI-2: Live Resource Inconsistency @ dmamove_job_reap**
Site: `vgem_dmamove.c:dmamove_job_reap` — 4 sites, 4 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/6d56a6f1…/`](1_wmi_findings/findings/wmi-2/6d56a6f1-b607-40e1-95e8-4abeab9c4fb3/)

**WMI-2: Live Resource Inconsistency @ pipeline_ioctl_reap_all**
Site: `vgem_pipeline.c:pipeline_ioctl_reap_all` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/74ead3e7…/`](1_wmi_findings/findings/wmi-2/74ead3e7-7e6a-49d8-821a-6e95f4b937e2/)

**WMI-2: Live Resource Inconsistency @ vgem_dmamove_buf_mark_staged**
Site: `vgem_dmamove.c:vgem_dmamove_buf_mark_staged` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/8473da4c…/`](1_wmi_findings/findings/wmi-2/8473da4c-d6ac-4ba8-863c-2e8a84c9d2d9/)

**WMI-2: Live Resource Inconsistency @ pipeline_ioctl_reap**
Site: `vgem_pipeline.c:pipeline_ioctl_reap` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/88056a91…/`](1_wmi_findings/findings/wmi-2/88056a91-573f-48b2-afba-f7fa8fa1709e/)

**WMI-2: Live Resource Inconsistency @ vgem_postproc_ctx_free**
Site: `vgem_postproc.c:vgem_postproc_ctx_free` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/8cb3fb02…/`](1_wmi_findings/findings/wmi-2/8cb3fb02-c623-40fb-a353-a8f809a42c88/)

**WMI-2: Live Resource Inconsistency @ vgem_dmamove_token_free**
Site: `vgem_dmamove.c:vgem_dmamove_token_free` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/96ec58e1…/`](1_wmi_findings/findings/wmi-2/96ec58e1-47d4-4917-b457-c25f988d6d4e/)

**WMI-2: Live Resource Inconsistency @ pipeline_ioctl_submit_pp**
Site: `vgem_pipeline.c:pipeline_ioctl_submit_pp` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/98758b67…/`](1_wmi_findings/findings/wmi-2/98758b67-8ebc-4779-a9a0-f81f1bdad6db/)

**WMI-2: Live Resource Inconsistency @ token_alloc_slot**
Site: `vgem_dmamove.c:token_alloc_slot` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/a324b24e…/`](1_wmi_findings/findings/wmi-2/a324b24e-851d-41b1-8614-b0bc245bac8c/)

**WMI-2: Live Resource Inconsistency @ dmamove_job_execute**
Site: `vgem_dmamove.c:dmamove_job_execute` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/b871cfd6…/`](1_wmi_findings/findings/wmi-2/b871cfd6-b0ab-429a-beac-390ecc177c76/)

**WMI-2: Live Resource Inconsistency @ postproc_update_buf_state**
Site: `vgem_postproc.c:postproc_update_buf_state` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/b8a50a6f…/`](1_wmi_findings/findings/wmi-2/b8a50a6f-5358-4110-8780-668425d67d35/)

**WMI-2: Live Resource Inconsistency @ postproc_job_submit**
Site: `vgem_postproc.c:postproc_job_submit` — 2 sites, 2 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/c2ae467f…/`](1_wmi_findings/findings/wmi-2/c2ae467f-b915-4919-b826-97b09d61cfd1/)

**WMI-2: Live Resource Inconsistency @ postproc_job_query**
Site: `vgem_postproc.c:postproc_job_query` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/c41c7f0a…/`](1_wmi_findings/findings/wmi-2/c41c7f0a-73f2-4e49-a639-eabf01d9f70c/)

**WMI-2: Live Resource Inconsistency @ dmamove_release**
Site: `vgem_dmamove.c:dmamove_release` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/c5da32de…/`](1_wmi_findings/findings/wmi-2/c5da32de-50b3-41f0-b089-c6ec2312254b/)

**WMI-2: Live Resource Inconsistency @ pipeline_ioctl_query_all**
Site: `vgem_pipeline.c:pipeline_ioctl_query_all` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/d316ba52…/`](1_wmi_findings/findings/wmi-2/d316ba52-cdc3-4b29-b35e-2d921c7c3e96/)

**WMI-2: Live Resource Inconsistency @ pipeline_release**
Site: `vgem_pipeline.c:pipeline_release` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/e02199da…/`](1_wmi_findings/findings/wmi-2/e02199da-559a-4558-a50b-a71097ee981f/)

**WMI-2: Live Resource Inconsistency @ postproc_job_desc_query**
Site: `vgem_postproc.c:postproc_job_desc_query` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/e24b3027…/`](1_wmi_findings/findings/wmi-2/e24b3027-5a5d-49ad-ab39-f44700af7abf/)

**WMI-2: Live Resource Inconsistency @ postproc_open**
Site: `vgem_postproc.c:postproc_open` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/e3c4e788…/`](1_wmi_findings/findings/wmi-2/e3c4e788-268a-4479-8857-8f83c73f4f41/)

**WMI-2: Live Resource Inconsistency @ postproc_ioctl**
Site: `vgem_postproc.c:postproc_ioctl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/e796711b…/`](1_wmi_findings/findings/wmi-2/e796711b-00e7-42dd-ac19-4736bb2500a6/)

**WMI-2: Live Resource Inconsistency @ dmamove_ioctl**
Site: `vgem_dmamove.c:dmamove_ioctl` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-2/faec54c5…/`](1_wmi_findings/findings/wmi-2/faec54c5-20bc-4624-95d7-6a0d1c76ca2b/)

---

## WMI-3 — Attacker Content in Authoritative Position

**WMI-3: Attacker-Determined Content in an Authoritative Position @ vgem_dmamove_buf_state_get**
Site: `vgem_dmamove.c:vgem_dmamove_buf_state_get` — 3 sites, 3 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/1251a6e6…/`](1_wmi_findings/findings/wmi-3/1251a6e6-e26f-495f-89d9-b94c53199e42/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ dmamove_job_submit**
Site: `vgem_dmamove.c:dmamove_job_submit` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/97cdccfc…/`](1_wmi_findings/findings/wmi-3/97cdccfc-7661-4232-8a68-a5862f6d7f38/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ postproc_job_submit**
Site: `vgem_postproc.c:postproc_job_submit` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/b2b370e6…/`](1_wmi_findings/findings/wmi-3/b2b370e6-4636-4ed8-a72d-c01601369fd2/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ postproc_update_buf_state**
Site: `vgem_postproc.c:postproc_update_buf_state` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/c2381f36…/`](1_wmi_findings/findings/wmi-3/c2381f36-c819-4f53-b2b7-cbb4dc46cfc5/)

**WMI-3: Attacker-Determined Content in an Authoritative Position @ pipeline_open**
Site: `vgem_pipeline.c:pipeline_open` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-3/d216d0ca…/`](1_wmi_findings/findings/wmi-3/d216d0ca-001c-43d4-bc43-298b2ff8fbaf/)

---

## WMI-4 — Arbitrary Access (Target or Extent from Field)

**WMI-4: Attacker-Shaped Data to Arbitrary Memory Access (RWX) @ dmamove_fetch_ring**
Site: `vgem_dmamove.c:dmamove_fetch_ring` — 1 site, 1 SA detections, verdict: `symex_explored`
Artifact: [`findings/wmi-4/fa6a93da…/`](1_wmi_findings/findings/wmi-4/fa6a93da-3e52-4842-82b4-fe20e7379253/)

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
