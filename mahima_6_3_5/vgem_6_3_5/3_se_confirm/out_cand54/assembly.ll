; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand54.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand54_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"state_val\00", align 1
@.str.1 = private unnamed_addr constant [21 x i8] c"intermediate_pending\00", align 1
@.str.2 = private unnamed_addr constant [25 x i8] c"intermediate_pending > 0\00", align 1
@.str.3 = private unnamed_addr constant [124 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand54_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !17
  %4 = bitcast i32* %2 to i8*, !dbg !18
  call void @klee_make_symbolic(i8* noundef %4, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0)), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %3, metadata !20, metadata !DIExpression()), !dbg !22
  %5 = bitcast i32* %3 to i8*, !dbg !23
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 4, i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.1, i64 0, i64 0)), !dbg !24
  %6 = load i32, i32* %2, align 4, !dbg !25
  %7 = icmp eq i32 %6, 2, !dbg !26
  br i1 %7, label %11, label %8, !dbg !27

8:                                                ; preds = %0
  %9 = load i32, i32* %2, align 4, !dbg !28
  %10 = icmp eq i32 %9, 3, !dbg !29
  br label %11, !dbg !27

11:                                               ; preds = %8, %0
  %12 = phi i1 [ true, %0 ], [ %10, %8 ]
  %13 = zext i1 %12 to i32, !dbg !27
  %14 = sext i32 %13 to i64, !dbg !25
  call void @klee_assume(i64 noundef %14), !dbg !30
  %15 = load i32, i32* %3, align 4, !dbg !31
  %16 = icmp ugt i32 %15, 0, !dbg !31
  br i1 %16, label %17, label %18, !dbg !34

17:                                               ; preds = %11
  br label %19, !dbg !34

18:                                               ; preds = %11
  call void @__assert_fail(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.2, i64 0, i64 0), i8* noundef getelementptr inbounds ([124 x i8], [124 x i8]* @.str.3, i64 0, i64 0), i32 noundef 16, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !31
  unreachable, !dbg !31

19:                                               ; preds = %17
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand54_wmi2.c", directory: "/home/mahima/eval4-main/eval4-mahima/stase_6_3_5/_tools", checksumkind: CSK_MD5, checksum: "ae8d6e5fda621f719a8b437db6a2b015")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 12, type: !12, scopeLine: 12, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand54_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "ae8d6e5fda621f719a8b437db6a2b015")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "state_val", scope: !10, file: !11, line: 13, type: !14)
!17 = !DILocation(line: 13, column: 7, scope: !10)
!18 = !DILocation(line: 13, column: 37, scope: !10)
!19 = !DILocation(line: 13, column: 18, scope: !10)
!20 = !DILocalVariable(name: "intermediate_pending", scope: !10, file: !11, line: 14, type: !21)
!21 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!22 = !DILocation(line: 14, column: 16, scope: !10)
!23 = !DILocation(line: 14, column: 57, scope: !10)
!24 = !DILocation(line: 14, column: 38, scope: !10)
!25 = !DILocation(line: 15, column: 15, scope: !10)
!26 = !DILocation(line: 15, column: 25, scope: !10)
!27 = !DILocation(line: 15, column: 52, scope: !10)
!28 = !DILocation(line: 15, column: 55, scope: !10)
!29 = !DILocation(line: 15, column: 65, scope: !10)
!30 = !DILocation(line: 15, column: 3, scope: !10)
!31 = !DILocation(line: 16, column: 3, scope: !32)
!32 = distinct !DILexicalBlock(scope: !33, file: !11, line: 16, column: 3)
!33 = distinct !DILexicalBlock(scope: !10, file: !11, line: 16, column: 3)
!34 = !DILocation(line: 16, column: 3, scope: !33)
!35 = !DILocation(line: 17, column: 3, scope: !10)
