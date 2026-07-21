; ModuleID = '/results/psmgr_6_12_28/3_se_confirm/cand21_tmpl.bc'
source_filename = "/results/psmgr_6_12_28/3_se_confirm/cand21_tmpl.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"attacker_input\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"producer_view\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"consumer_view\00", align 1
@.str.3 = private unnamed_addr constant [31 x i8] c"producer_view == consumer_view\00", align 1
@.str.4 = private unnamed_addr constant [50 x i8] c"/results/psmgr_6_12_28/3_se_confirm/cand21_tmpl.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !9 {
entry:
  %retval = alloca i32, align 4
  %attacker_input = alloca i32, align 4
  %producer_view = alloca i32, align 4
  %consumer_view = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %attacker_input, metadata !14, metadata !DIExpression()), !dbg !15
  %0 = bitcast i32* %attacker_input to i8*, !dbg !16
  call void @klee_make_symbolic(i8* %0, i64 4, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i64 0, i64 0)), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %producer_view, metadata !18, metadata !DIExpression()), !dbg !19
  %1 = bitcast i32* %producer_view to i8*, !dbg !20
  call void @klee_make_symbolic(i8* %1, i64 4, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i64 0, i64 0)), !dbg !21
  call void @llvm.dbg.declare(metadata i32* %consumer_view, metadata !22, metadata !DIExpression()), !dbg !23
  %2 = bitcast i32* %consumer_view to i8*, !dbg !24
  call void @klee_make_symbolic(i8* %2, i64 4, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i64 0, i64 0)), !dbg !25
  %3 = load i32, i32* %attacker_input, align 4, !dbg !26
  %cmp = icmp eq i32 %3, 1, !dbg !27
  %conv = zext i1 %cmp to i32, !dbg !27
  %conv1 = sext i32 %conv to i64, !dbg !26
  call void @klee_assume(i64 %conv1), !dbg !28
  %4 = load i32, i32* %producer_view, align 4, !dbg !29
  %5 = load i32, i32* %consumer_view, align 4, !dbg !29
  %cmp2 = icmp eq i32 %4, %5, !dbg !29
  br i1 %cmp2, label %if.then, label %if.else, !dbg !32

if.then:                                          ; preds = %entry
  br label %if.end, !dbg !32

if.else:                                          ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.3, i64 0, i64 0), i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.4, i64 0, i64 0), i32 14, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !29
  unreachable, !dbg !29

if.end:                                           ; preds = %if.then
  ret i32 0, !dbg !33
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
!1 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand21_tmpl.c", directory: "/repo")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1 (https://github.com/llvm/llvm-project.git 75e33f71c2dae584b13a7d1186ae0a038ba98838)"}
!9 = distinct !DISubprogram(name: "main", scope: !10, file: !10, line: 9, type: !11, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand21_tmpl.c", directory: "")
!11 = !DISubroutineType(types: !12)
!12 = !{!13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DILocalVariable(name: "attacker_input", scope: !9, file: !10, line: 10, type: !13)
!15 = !DILocation(line: 10, column: 7, scope: !9)
!16 = !DILocation(line: 10, column: 42, scope: !9)
!17 = !DILocation(line: 10, column: 23, scope: !9)
!18 = !DILocalVariable(name: "producer_view", scope: !9, file: !10, line: 11, type: !13)
!19 = !DILocation(line: 11, column: 7, scope: !9)
!20 = !DILocation(line: 11, column: 41, scope: !9)
!21 = !DILocation(line: 11, column: 22, scope: !9)
!22 = !DILocalVariable(name: "consumer_view", scope: !9, file: !10, line: 12, type: !13)
!23 = !DILocation(line: 12, column: 7, scope: !9)
!24 = !DILocation(line: 12, column: 41, scope: !9)
!25 = !DILocation(line: 12, column: 22, scope: !9)
!26 = !DILocation(line: 13, column: 15, scope: !9)
!27 = !DILocation(line: 13, column: 30, scope: !9)
!28 = !DILocation(line: 13, column: 3, scope: !9)
!29 = !DILocation(line: 14, column: 3, scope: !30)
!30 = distinct !DILexicalBlock(scope: !31, file: !10, line: 14, column: 3)
!31 = distinct !DILexicalBlock(scope: !9, file: !10, line: 14, column: 3)
!32 = !DILocation(line: 14, column: 3, scope: !31)
!33 = !DILocation(line: 15, column: 3, scope: !9)
