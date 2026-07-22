; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand67.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand67_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"write_count\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"token\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"mask\00", align 1
@.str.3 = private unnamed_addr constant [49 x i8] c"mask == BASE_MASK || mask == BASE_MASK + IN_BITS\00", align 1
@.str.4 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand67_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !18
  %5 = bitcast i32* %2 to i8*, !dbg !19
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 4, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i64 0, i64 0)), !dbg !20
  call void @llvm.dbg.declare(metadata i32* %3, metadata !21, metadata !DIExpression()), !dbg !22
  %6 = bitcast i32* %3 to i8*, !dbg !23
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i64 0, i64 0)), !dbg !24
  call void @llvm.dbg.declare(metadata i32* %4, metadata !25, metadata !DIExpression()), !dbg !26
  %7 = bitcast i32* %4 to i8*, !dbg !27
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0)), !dbg !28
  %8 = load i32, i32* %2, align 4, !dbg !29
  %9 = icmp ugt i32 %8, 0, !dbg !30
  br i1 %9, label %13, label %10, !dbg !31

10:                                               ; preds = %0
  %11 = load i32, i32* %3, align 4, !dbg !32
  %12 = icmp ne i32 %11, 0, !dbg !33
  br i1 %12, label %13, label %17, !dbg !34

13:                                               ; preds = %10, %0
  %14 = load i32, i32* %4, align 4, !dbg !35
  %15 = icmp eq i32 %14, 1093, !dbg !36
  %16 = zext i1 %15 to i32, !dbg !36
  br label %21, !dbg !34

17:                                               ; preds = %10
  %18 = load i32, i32* %4, align 4, !dbg !37
  %19 = icmp eq i32 %18, 1028, !dbg !38
  %20 = zext i1 %19 to i32, !dbg !38
  br label %21, !dbg !34

21:                                               ; preds = %17, %13
  %22 = phi i32 [ %16, %13 ], [ %20, %17 ], !dbg !34
  %23 = sext i32 %22 to i64, !dbg !34
  call void @klee_assume(i64 noundef %23), !dbg !39
  %24 = load i32, i32* %4, align 4, !dbg !40
  %25 = icmp eq i32 %24, 1028, !dbg !40
  br i1 %25, label %29, label %26, !dbg !40

26:                                               ; preds = %21
  %27 = load i32, i32* %4, align 4, !dbg !40
  %28 = icmp eq i32 %27, 1093, !dbg !40
  br i1 %28, label %29, label %30, !dbg !43

29:                                               ; preds = %26, %21
  br label %31, !dbg !43

30:                                               ; preds = %26
  call void @__assert_fail(i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.4, i64 0, i64 0), i32 noundef 16, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !40
  unreachable, !dbg !40

31:                                               ; preds = %29
  ret i32 0, !dbg !44
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand67_wmi2.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "c33907f17985bf0562ed7c7ceb7a6e83")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 11, type: !12, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand67_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "c33907f17985bf0562ed7c7ceb7a6e83")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "write_count", scope: !10, file: !11, line: 12, type: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 12, column: 16, scope: !10)
!19 = !DILocation(line: 12, column: 48, scope: !10)
!20 = !DILocation(line: 12, column: 29, scope: !10)
!21 = !DILocalVariable(name: "token", scope: !10, file: !11, line: 13, type: !17)
!22 = !DILocation(line: 13, column: 16, scope: !10)
!23 = !DILocation(line: 13, column: 42, scope: !10)
!24 = !DILocation(line: 13, column: 23, scope: !10)
!25 = !DILocalVariable(name: "mask", scope: !10, file: !11, line: 14, type: !17)
!26 = !DILocation(line: 14, column: 16, scope: !10)
!27 = !DILocation(line: 14, column: 41, scope: !10)
!28 = !DILocation(line: 14, column: 22, scope: !10)
!29 = !DILocation(line: 15, column: 16, scope: !10)
!30 = !DILocation(line: 15, column: 28, scope: !10)
!31 = !DILocation(line: 15, column: 32, scope: !10)
!32 = !DILocation(line: 15, column: 35, scope: !10)
!33 = !DILocation(line: 15, column: 41, scope: !10)
!34 = !DILocation(line: 15, column: 15, scope: !10)
!35 = !DILocation(line: 15, column: 49, scope: !10)
!36 = !DILocation(line: 15, column: 54, scope: !10)
!37 = !DILocation(line: 15, column: 79, scope: !10)
!38 = !DILocation(line: 15, column: 84, scope: !10)
!39 = !DILocation(line: 15, column: 3, scope: !10)
!40 = !DILocation(line: 16, column: 3, scope: !41)
!41 = distinct !DILexicalBlock(scope: !42, file: !11, line: 16, column: 3)
!42 = distinct !DILexicalBlock(scope: !10, file: !11, line: 16, column: 3)
!43 = !DILocation(line: 16, column: 3, scope: !42)
!44 = !DILocation(line: 17, column: 3, scope: !10)
