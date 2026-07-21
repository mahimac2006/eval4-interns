; ModuleID = '/results/psmgr_6_12_28/3_se_confirm/cand51.bc'
source_filename = "/results/psmgr_6_12_28/3_se_confirm/cand51_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"write_count\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"token\00", align 1
@.str.2 = private unnamed_addr constant [89 x i8] c"write_count == PSMGR_BUF_COMMITTED || write_count < PSMGR_BUF_WRITE_THRESH || token == 0\00", align 1
@.str.3 = private unnamed_addr constant [50 x i8] c"/results/psmgr_6_12_28/3_se_confirm/cand51_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !9 {
entry:
  %retval = alloca i32, align 4
  %write_count = alloca i32, align 4
  %token = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %write_count, metadata !14, metadata !DIExpression()), !dbg !16
  %0 = bitcast i32* %write_count to i8*, !dbg !17
  call void @klee_make_symbolic(i8* %0, i64 4, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i64 0, i64 0)), !dbg !18
  call void @llvm.dbg.declare(metadata i32* %token, metadata !19, metadata !DIExpression()), !dbg !20
  %1 = bitcast i32* %token to i8*, !dbg !21
  call void @klee_make_symbolic(i8* %1, i64 4, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i64 0, i64 0)), !dbg !22
  %2 = load i32, i32* %write_count, align 4, !dbg !23
  %conv = zext i32 %2 to i64, !dbg !23
  %cmp = icmp eq i64 %conv, 4294967295, !dbg !23
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !23

lor.lhs.false:                                    ; preds = %entry
  %3 = load i32, i32* %write_count, align 4, !dbg !23
  %cmp2 = icmp ult i32 %3, 1, !dbg !23
  br i1 %cmp2, label %if.then, label %lor.lhs.false4, !dbg !23

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %4 = load i32, i32* %token, align 4, !dbg !23
  %cmp5 = icmp eq i32 %4, 0, !dbg !23
  br i1 %cmp5, label %if.then, label %if.else, !dbg !26

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false, %entry
  br label %if.end, !dbg !26

if.else:                                          ; preds = %lor.lhs.false4
  call void @__assert_fail(i8* getelementptr inbounds ([89 x i8], [89 x i8]* @.str.2, i64 0, i64 0), i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.3, i64 0, i64 0), i32 14, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !23
  unreachable, !dbg !23

if.end:                                           ; preds = %if.then
  ret i32 0, !dbg !27
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @klee_make_symbolic(i8*, i64, i8*) #2

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
!1 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand51_wmi2.c", directory: "/repo")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1 (https://github.com/llvm/llvm-project.git 75e33f71c2dae584b13a7d1186ae0a038ba98838)"}
!9 = distinct !DISubprogram(name: "main", scope: !10, file: !10, line: 11, type: !11, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "/results/psmgr_6_12_28/3_se_confirm/cand51_wmi2.c", directory: "")
!11 = !DISubroutineType(types: !12)
!12 = !{!13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DILocalVariable(name: "write_count", scope: !9, file: !10, line: 12, type: !15)
!15 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!16 = !DILocation(line: 12, column: 16, scope: !9)
!17 = !DILocation(line: 12, column: 48, scope: !9)
!18 = !DILocation(line: 12, column: 29, scope: !9)
!19 = !DILocalVariable(name: "token", scope: !9, file: !10, line: 13, type: !15)
!20 = !DILocation(line: 13, column: 16, scope: !9)
!21 = !DILocation(line: 13, column: 42, scope: !9)
!22 = !DILocation(line: 13, column: 23, scope: !9)
!23 = !DILocation(line: 14, column: 3, scope: !24)
!24 = distinct !DILexicalBlock(scope: !25, file: !10, line: 14, column: 3)
!25 = distinct !DILexicalBlock(scope: !9, file: !10, line: 14, column: 3)
!26 = !DILocation(line: 14, column: 3, scope: !25)
!27 = !DILocation(line: 15, column: 3, scope: !9)
