; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand13.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand13_wmi1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"cur_state\00", align 1
@.str.1 = private unnamed_addr constant [77 x i8] c"cur_state == VGEM_BUF_STATE_POSTPROC || cur_state == VGEM_BUF_STATE_COMPLETE\00", align 1
@.str.2 = private unnamed_addr constant [124 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand13_wmi1.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !17
  %3 = bitcast i32* %2 to i8*, !dbg !18
  call void @klee_make_symbolic(i8* noundef %3, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0)), !dbg !19
  %4 = load i32, i32* %2, align 4, !dbg !20
  %5 = icmp ne i32 %4, 1, !dbg !21
  br i1 %5, label %6, label %9, !dbg !22

6:                                                ; preds = %0
  %7 = load i32, i32* %2, align 4, !dbg !23
  %8 = icmp ne i32 %7, 2, !dbg !24
  br label %9

9:                                                ; preds = %6, %0
  %10 = phi i1 [ false, %0 ], [ %8, %6 ], !dbg !25
  %11 = zext i1 %10 to i64, !dbg !20
  %12 = select i1 %10, i32 0, i32 1, !dbg !20
  %13 = sext i32 %12 to i64, !dbg !20
  call void @klee_assume(i64 noundef %13), !dbg !26
  %14 = load i32, i32* %2, align 4, !dbg !27
  %15 = icmp eq i32 %14, 1, !dbg !27
  br i1 %15, label %19, label %16, !dbg !27

16:                                               ; preds = %9
  %17 = load i32, i32* %2, align 4, !dbg !27
  %18 = icmp eq i32 %17, 2, !dbg !27
  br i1 %18, label %19, label %20, !dbg !30

19:                                               ; preds = %16, %9
  br label %21, !dbg !30

20:                                               ; preds = %16
  call void @__assert_fail(i8* noundef getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([124 x i8], [124 x i8]* @.str.2, i64 0, i64 0), i32 noundef 15, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !27
  unreachable, !dbg !27

21:                                               ; preds = %19
  ret i32 0, !dbg !31
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand13_wmi1.c", directory: "/home/mahima/eval4-main/eval4-mahima/stase_6_3_5/_tools", checksumkind: CSK_MD5, checksum: "c48c9f95da1b1a0d3912bae6177275f3")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 12, type: !12, scopeLine: 12, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand13_wmi1.c", directory: "", checksumkind: CSK_MD5, checksum: "c48c9f95da1b1a0d3912bae6177275f3")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "cur_state", scope: !10, file: !11, line: 13, type: !14)
!17 = !DILocation(line: 13, column: 7, scope: !10)
!18 = !DILocation(line: 13, column: 37, scope: !10)
!19 = !DILocation(line: 13, column: 18, scope: !10)
!20 = !DILocation(line: 14, column: 15, scope: !10)
!21 = !DILocation(line: 14, column: 25, scope: !10)
!22 = !DILocation(line: 14, column: 52, scope: !10)
!23 = !DILocation(line: 14, column: 55, scope: !10)
!24 = !DILocation(line: 14, column: 65, scope: !10)
!25 = !DILocation(line: 0, scope: !10)
!26 = !DILocation(line: 14, column: 3, scope: !10)
!27 = !DILocation(line: 15, column: 3, scope: !28)
!28 = distinct !DILexicalBlock(scope: !29, file: !11, line: 15, column: 3)
!29 = distinct !DILexicalBlock(scope: !10, file: !11, line: 15, column: 3)
!30 = !DILocation(line: 15, column: 3, scope: !29)
!31 = !DILocation(line: 16, column: 3, scope: !10)
