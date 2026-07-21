; ModuleID = '/results/psmgr_6_12_28/3_se_confirm/cand38.bc'
source_filename = "/results/psmgr_6_12_28/3_se_confirm/cand38_wmi1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [8 x i8] c"peer_sk\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"sk_change_fn\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"sk_change_fn != 0\00", align 1
@.str.3 = private unnamed_addr constant [50 x i8] c"/results/psmgr_6_12_28/3_se_confirm/cand38_wmi1.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !9 {
entry:
  %retval = alloca i32, align 4
  %peer_sk = alloca i64, align 8
  %sk_change_fn = alloca i64, align 8
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i64* %peer_sk, metadata !14, metadata !DIExpression()), !dbg !16
  %0 = bitcast i64* %peer_sk to i8*, !dbg !17
  call void @klee_make_symbolic(i8* %0, i64 8, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i64 0, i64 0)), !dbg !18
  call void @llvm.dbg.declare(metadata i64* %sk_change_fn, metadata !19, metadata !DIExpression()), !dbg !20
  %1 = bitcast i64* %sk_change_fn to i8*, !dbg !21
  call void @klee_make_symbolic(i8* %1, i64 8, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i64 0, i64 0)), !dbg !22
  %2 = load i64, i64* %peer_sk, align 8, !dbg !23
  %cmp = icmp ne i64 %2, 0, !dbg !24
  %conv = zext i1 %cmp to i32, !dbg !24
  %conv1 = sext i32 %conv to i64, !dbg !23
  call void @klee_assume(i64 %conv1), !dbg !25
  %3 = load i64, i64* %sk_change_fn, align 8, !dbg !26
  %cmp2 = icmp ne i64 %3, 0, !dbg !26
  br i1 %cmp2, label %if.then, label %if.else, !dbg !29

if.then:                                          ; preds = %entry
  br label %if.end, !dbg !29

if.else:                                          ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.2, i64 0, i64 0), i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.3, i64 0, i64 0), i32 13, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !26
  unreachable, !dbg !26

if.end:                                           ; preds = %if.then
  ret i32 0, !dbg !30
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @klee_make_symbolic(i8*, i64, i8*) #2

declare dso_local void @klee_assume(i64) #2

; Function Attrs: noreturn nounwind
declare dso_local void @__assert_fail(i8*, i8*, i32, i8*) #3

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1 (https://github.com/llvm/llvm-project.git 75e33f71c2dae584b13a7d1186ae0a038ba98838)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand38_wmi1.c", directory: "/repo")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1 (https://github.com/llvm/llvm-project.git 75e33f71c2dae584b13a7d1186ae0a038ba98838)"}
!9 = distinct !DISubprogram(name: "main", scope: !10, file: !10, line: 9, type: !11, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand38_wmi1.c", directory: "")
!11 = !DISubroutineType(types: !12)
!12 = !{!13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DILocalVariable(name: "peer_sk", scope: !9, file: !10, line: 10, type: !15)
!15 = !DIBasicType(name: "long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!16 = !DILocation(line: 10, column: 17, scope: !9)
!17 = !DILocation(line: 10, column: 45, scope: !9)
!18 = !DILocation(line: 10, column: 26, scope: !9)
!19 = !DILocalVariable(name: "sk_change_fn", scope: !9, file: !10, line: 11, type: !15)
!20 = !DILocation(line: 11, column: 17, scope: !9)
!21 = !DILocation(line: 11, column: 50, scope: !9)
!22 = !DILocation(line: 11, column: 31, scope: !9)
!23 = !DILocation(line: 12, column: 15, scope: !9)
!24 = !DILocation(line: 12, column: 23, scope: !9)
!25 = !DILocation(line: 12, column: 3, scope: !9)
!26 = !DILocation(line: 13, column: 3, scope: !27)
!27 = distinct !DILexicalBlock(scope: !28, file: !10, line: 13, column: 3)
!28 = distinct !DILexicalBlock(scope: !9, file: !10, line: 13, column: 3)
!29 = !DILocation(line: 13, column: 3, scope: !28)
!30 = !DILocation(line: 14, column: 3, scope: !9)
