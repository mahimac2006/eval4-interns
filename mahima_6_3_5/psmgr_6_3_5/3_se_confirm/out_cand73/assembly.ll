; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand73.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand73_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"enc_class\00", align 1
@.str.1 = private unnamed_addr constant [24 x i8] c"enc_class < NUM_CLASSES\00", align 1
@.str.2 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand73_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !18
  %3 = bitcast i32* %2 to i8*, !dbg !19
  call void @klee_make_symbolic(i8* noundef %3, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0)), !dbg !20
  %4 = load i32, i32* %2, align 4, !dbg !21
  %5 = icmp eq i32 %4, 0, !dbg !22
  br i1 %5, label %12, label %6, !dbg !23

6:                                                ; preds = %0
  %7 = load i32, i32* %2, align 4, !dbg !24
  %8 = icmp eq i32 %7, 1, !dbg !25
  br i1 %8, label %12, label %9, !dbg !26

9:                                                ; preds = %6
  %10 = load i32, i32* %2, align 4, !dbg !27
  %11 = icmp eq i32 %10, 2, !dbg !28
  br label %12, !dbg !26

12:                                               ; preds = %9, %6, %0
  %13 = phi i1 [ true, %6 ], [ true, %0 ], [ %11, %9 ]
  %14 = zext i1 %13 to i32, !dbg !26
  %15 = sext i32 %14 to i64, !dbg !21
  call void @klee_assume(i64 noundef %15), !dbg !29
  %16 = load i32, i32* %2, align 4, !dbg !30
  %17 = icmp ult i32 %16, 3, !dbg !30
  br i1 %17, label %18, label %19, !dbg !33

18:                                               ; preds = %12
  br label %20, !dbg !33

19:                                               ; preds = %12
  call void @__assert_fail(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.2, i64 0, i64 0), i32 noundef 16, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !30
  unreachable, !dbg !30

20:                                               ; preds = %18
  ret i32 0, !dbg !34
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand73_wmi2.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "74d20f201de2592d464715391e59fe38")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 13, type: !12, scopeLine: 13, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand73_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "74d20f201de2592d464715391e59fe38")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "enc_class", scope: !10, file: !11, line: 14, type: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 14, column: 16, scope: !10)
!19 = !DILocation(line: 14, column: 46, scope: !10)
!20 = !DILocation(line: 14, column: 27, scope: !10)
!21 = !DILocation(line: 15, column: 15, scope: !10)
!22 = !DILocation(line: 15, column: 25, scope: !10)
!23 = !DILocation(line: 15, column: 40, scope: !10)
!24 = !DILocation(line: 15, column: 43, scope: !10)
!25 = !DILocation(line: 15, column: 53, scope: !10)
!26 = !DILocation(line: 15, column: 71, scope: !10)
!27 = !DILocation(line: 15, column: 74, scope: !10)
!28 = !DILocation(line: 15, column: 84, scope: !10)
!29 = !DILocation(line: 15, column: 3, scope: !10)
!30 = !DILocation(line: 16, column: 3, scope: !31)
!31 = distinct !DILexicalBlock(scope: !32, file: !11, line: 16, column: 3)
!32 = distinct !DILexicalBlock(scope: !10, file: !11, line: 16, column: 3)
!33 = !DILocation(line: 16, column: 3, scope: !32)
!34 = !DILocation(line: 17, column: 3, scope: !10)
