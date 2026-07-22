; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/wmi1.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/wmi1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"attacker_input\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"producer_view\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"consumer_view\00", align 1
@.str.3 = private unnamed_addr constant [31 x i8] c"producer_view == consumer_view\00", align 1
@.str.4 = private unnamed_addr constant [118 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/wmi1.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !17
  %5 = bitcast i32* %2 to i8*, !dbg !18
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 4, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i64 0, i64 0)), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %3, metadata !20, metadata !DIExpression()), !dbg !21
  %6 = bitcast i32* %3 to i8*, !dbg !22
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i64 0, i64 0)), !dbg !23
  call void @llvm.dbg.declare(metadata i32* %4, metadata !24, metadata !DIExpression()), !dbg !25
  %7 = bitcast i32* %4 to i8*, !dbg !26
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i64 0, i64 0)), !dbg !27
  %8 = load i32, i32* %2, align 4, !dbg !28
  %9 = icmp eq i32 %8, 1, !dbg !29
  %10 = zext i1 %9 to i32, !dbg !29
  %11 = sext i32 %10 to i64, !dbg !28
  call void @klee_assume(i64 noundef %11), !dbg !30
  %12 = load i32, i32* %3, align 4, !dbg !31
  %13 = load i32, i32* %4, align 4, !dbg !31
  %14 = icmp eq i32 %12, %13, !dbg !31
  br i1 %14, label %15, label %16, !dbg !34

15:                                               ; preds = %0
  br label %17, !dbg !34

16:                                               ; preds = %0
  call void @__assert_fail(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([118 x i8], [118 x i8]* @.str.4, i64 0, i64 0), i32 noundef 14, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !31
  unreachable, !dbg !31

17:                                               ; preds = %15
  ret i32 0, !dbg !35
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @klee_make_symbolic(i8* noundef, i64 noundef, i8* noundef) #2

declare void @klee_assume(i64 noundef) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) #3

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 14.0.0-1ubuntu1.1", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/wmi1.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "642c305c598ac14962da259f6502076d")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 9, type: !12, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/wmi1.c", directory: "", checksumkind: CSK_MD5, checksum: "642c305c598ac14962da259f6502076d")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "attacker_input", scope: !10, file: !11, line: 10, type: !14)
!17 = !DILocation(line: 10, column: 7, scope: !10)
!18 = !DILocation(line: 10, column: 42, scope: !10)
!19 = !DILocation(line: 10, column: 23, scope: !10)
!20 = !DILocalVariable(name: "producer_view", scope: !10, file: !11, line: 11, type: !14)
!21 = !DILocation(line: 11, column: 7, scope: !10)
!22 = !DILocation(line: 11, column: 41, scope: !10)
!23 = !DILocation(line: 11, column: 22, scope: !10)
!24 = !DILocalVariable(name: "consumer_view", scope: !10, file: !11, line: 12, type: !14)
!25 = !DILocation(line: 12, column: 7, scope: !10)
!26 = !DILocation(line: 12, column: 41, scope: !10)
!27 = !DILocation(line: 12, column: 22, scope: !10)
!28 = !DILocation(line: 13, column: 15, scope: !10)
!29 = !DILocation(line: 13, column: 30, scope: !10)
!30 = !DILocation(line: 13, column: 3, scope: !10)
!31 = !DILocation(line: 14, column: 3, scope: !32)
!32 = distinct !DILexicalBlock(scope: !33, file: !11, line: 14, column: 3)
!33 = distinct !DILexicalBlock(scope: !10, file: !11, line: 14, column: 3)
!34 = !DILocation(line: 14, column: 3, scope: !33)
!35 = !DILocation(line: 15, column: 3, scope: !10)
