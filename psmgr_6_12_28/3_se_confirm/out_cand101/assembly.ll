; ModuleID = '/results/psmgr_6_12_28/3_se_confirm/cand101.bc'
source_filename = "/results/psmgr_6_12_28/3_se_confirm/cand101_wmi3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [14 x i8] c"resource_live\00", align 1
@.str.1 = private unnamed_addr constant [22 x i8] c"resource_inconsistent\00", align 1
@.str.2 = private unnamed_addr constant [17 x i8] c"content_attacker\00", align 1
@.str.3 = private unnamed_addr constant [16 x i8] c"content_trusted\00", align 1
@.str.4 = private unnamed_addr constant [21 x i8] c"content_trusted == 1\00", align 1
@.str.5 = private unnamed_addr constant [51 x i8] c"/results/psmgr_6_12_28/3_se_confirm/cand101_wmi3.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !9 {
entry:
  %retval = alloca i32, align 4
  %resource_live = alloca i32, align 4
  %resource_inconsistent = alloca i32, align 4
  %content_attacker = alloca i32, align 4
  %content_trusted = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %resource_live, metadata !14, metadata !DIExpression()), !dbg !15
  %0 = bitcast i32* %resource_live to i8*, !dbg !16
  call void @klee_make_symbolic(i8* %0, i64 4, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i64 0, i64 0)), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %resource_inconsistent, metadata !18, metadata !DIExpression()), !dbg !19
  %1 = bitcast i32* %resource_inconsistent to i8*, !dbg !20
  call void @klee_make_symbolic(i8* %1, i64 4, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i64 0, i64 0)), !dbg !21
  call void @llvm.dbg.declare(metadata i32* %content_attacker, metadata !22, metadata !DIExpression()), !dbg !23
  %2 = bitcast i32* %content_attacker to i8*, !dbg !24
  call void @klee_make_symbolic(i8* %2, i64 4, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i64 0, i64 0)), !dbg !25
  call void @llvm.dbg.declare(metadata i32* %content_trusted, metadata !26, metadata !DIExpression()), !dbg !27
  %3 = bitcast i32* %content_trusted to i8*, !dbg !28
  call void @klee_make_symbolic(i8* %3, i64 4, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.3, i64 0, i64 0)), !dbg !29
  %4 = load i32, i32* %resource_live, align 4, !dbg !30
  %cmp = icmp eq i32 %4, 1, !dbg !31
  %conv = zext i1 %cmp to i32, !dbg !31
  %conv1 = sext i32 %conv to i64, !dbg !30
  call void @klee_assume(i64 %conv1), !dbg !32
  %5 = load i32, i32* %resource_inconsistent, align 4, !dbg !33
  %cmp2 = icmp eq i32 %5, 1, !dbg !34
  %conv3 = zext i1 %cmp2 to i32, !dbg !34
  %conv4 = sext i32 %conv3 to i64, !dbg !33
  call void @klee_assume(i64 %conv4), !dbg !35
  %6 = load i32, i32* %content_attacker, align 4, !dbg !36
  %cmp5 = icmp eq i32 %6, 1, !dbg !37
  %conv6 = zext i1 %cmp5 to i32, !dbg !37
  %conv7 = sext i32 %conv6 to i64, !dbg !36
  call void @klee_assume(i64 %conv7), !dbg !38
  %7 = load i32, i32* %content_trusted, align 4, !dbg !39
  %cmp8 = icmp eq i32 %7, 1, !dbg !39
  br i1 %cmp8, label %if.then, label %if.else, !dbg !42

if.then:                                          ; preds = %entry
  br label %if.end, !dbg !42

if.else:                                          ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.4, i64 0, i64 0), i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.5, i64 0, i64 0), i32 17, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !39
  unreachable, !dbg !39

if.end:                                           ; preds = %if.then
  ret i32 0, !dbg !43
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
!1 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand101_wmi3.c", directory: "/repo")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1 (https://github.com/llvm/llvm-project.git 75e33f71c2dae584b13a7d1186ae0a038ba98838)"}
!9 = distinct !DISubprogram(name: "main", scope: !10, file: !10, line: 9, type: !11, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand101_wmi3.c", directory: "")
!11 = !DISubroutineType(types: !12)
!12 = !{!13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DILocalVariable(name: "resource_live", scope: !9, file: !10, line: 10, type: !13)
!15 = !DILocation(line: 10, column: 7, scope: !9)
!16 = !DILocation(line: 10, column: 41, scope: !9)
!17 = !DILocation(line: 10, column: 22, scope: !9)
!18 = !DILocalVariable(name: "resource_inconsistent", scope: !9, file: !10, line: 11, type: !13)
!19 = !DILocation(line: 11, column: 7, scope: !9)
!20 = !DILocation(line: 11, column: 49, scope: !9)
!21 = !DILocation(line: 11, column: 30, scope: !9)
!22 = !DILocalVariable(name: "content_attacker", scope: !9, file: !10, line: 12, type: !13)
!23 = !DILocation(line: 12, column: 7, scope: !9)
!24 = !DILocation(line: 12, column: 44, scope: !9)
!25 = !DILocation(line: 12, column: 25, scope: !9)
!26 = !DILocalVariable(name: "content_trusted", scope: !9, file: !10, line: 13, type: !13)
!27 = !DILocation(line: 13, column: 7, scope: !9)
!28 = !DILocation(line: 13, column: 43, scope: !9)
!29 = !DILocation(line: 13, column: 24, scope: !9)
!30 = !DILocation(line: 14, column: 15, scope: !9)
!31 = !DILocation(line: 14, column: 29, scope: !9)
!32 = !DILocation(line: 14, column: 3, scope: !9)
!33 = !DILocation(line: 15, column: 15, scope: !9)
!34 = !DILocation(line: 15, column: 37, scope: !9)
!35 = !DILocation(line: 15, column: 3, scope: !9)
!36 = !DILocation(line: 16, column: 15, scope: !9)
!37 = !DILocation(line: 16, column: 32, scope: !9)
!38 = !DILocation(line: 16, column: 3, scope: !9)
!39 = !DILocation(line: 17, column: 3, scope: !40)
!40 = distinct !DILexicalBlock(scope: !41, file: !10, line: 17, column: 3)
!41 = distinct !DILexicalBlock(scope: !9, file: !10, line: 17, column: 3)
!42 = !DILocation(line: 17, column: 3, scope: !41)
!43 = !DILocation(line: 18, column: 3, scope: !9)
