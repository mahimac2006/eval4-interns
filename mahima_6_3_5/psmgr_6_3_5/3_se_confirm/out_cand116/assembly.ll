; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand116.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand116_wmi4.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [8 x i8] c"handler\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"token\00", align 1
@.str.2 = private unnamed_addr constant [12 x i8] c"write_count\00", align 1
@.str.3 = private unnamed_addr constant [25 x i8] c"handler == VALID_HANDLER\00", align 1
@.str.4 = private unnamed_addr constant [126 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand116_wmi4.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i64, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i64* %2, metadata !16, metadata !DIExpression()), !dbg !18
  %5 = bitcast i64* %2 to i8*, !dbg !19
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 8, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i64 0, i64 0)), !dbg !20
  call void @llvm.dbg.declare(metadata i32* %3, metadata !21, metadata !DIExpression()), !dbg !23
  %6 = bitcast i32* %3 to i8*, !dbg !24
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i64 0, i64 0)), !dbg !25
  call void @llvm.dbg.declare(metadata i32* %4, metadata !26, metadata !DIExpression()), !dbg !27
  %7 = bitcast i32* %4 to i8*, !dbg !28
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.2, i64 0, i64 0)), !dbg !29
  %8 = load i32, i32* %4, align 4, !dbg !30
  %9 = icmp eq i32 %8, 1, !dbg !31
  %10 = zext i1 %9 to i32, !dbg !31
  %11 = sext i32 %10 to i64, !dbg !30
  call void @klee_assume(i64 noundef %11), !dbg !32
  %12 = load i32, i32* %3, align 4, !dbg !33
  %13 = icmp ne i32 %12, 0, !dbg !34
  %14 = zext i1 %13 to i32, !dbg !34
  %15 = sext i32 %14 to i64, !dbg !33
  call void @klee_assume(i64 noundef %15), !dbg !35
  %16 = load i64, i64* %2, align 8, !dbg !36
  %17 = icmp ne i64 %16, 0, !dbg !37
  %18 = zext i1 %17 to i32, !dbg !37
  %19 = sext i32 %18 to i64, !dbg !36
  call void @klee_assume(i64 noundef %19), !dbg !38
  %20 = load i64, i64* %2, align 8, !dbg !39
  %21 = icmp eq i64 %20, 4096, !dbg !39
  br i1 %21, label %22, label %23, !dbg !42

22:                                               ; preds = %0
  br label %24, !dbg !42

23:                                               ; preds = %0
  call void @__assert_fail(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([126 x i8], [126 x i8]* @.str.4, i64 0, i64 0), i32 noundef 18, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !39
  unreachable, !dbg !39

24:                                               ; preds = %22
  ret i32 0, !dbg !43
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand116_wmi4.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "e9a6f3d4ad9269fbb591aa6ed50fe943")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 11, type: !12, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand116_wmi4.c", directory: "", checksumkind: CSK_MD5, checksum: "e9a6f3d4ad9269fbb591aa6ed50fe943")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "handler", scope: !10, file: !11, line: 12, type: !17)
!17 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 12, column: 17, scope: !10)
!19 = !DILocation(line: 12, column: 45, scope: !10)
!20 = !DILocation(line: 12, column: 26, scope: !10)
!21 = !DILocalVariable(name: "token", scope: !10, file: !11, line: 13, type: !22)
!22 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!23 = !DILocation(line: 13, column: 16, scope: !10)
!24 = !DILocation(line: 13, column: 42, scope: !10)
!25 = !DILocation(line: 13, column: 23, scope: !10)
!26 = !DILocalVariable(name: "write_count", scope: !10, file: !11, line: 14, type: !22)
!27 = !DILocation(line: 14, column: 16, scope: !10)
!28 = !DILocation(line: 14, column: 48, scope: !10)
!29 = !DILocation(line: 14, column: 29, scope: !10)
!30 = !DILocation(line: 15, column: 15, scope: !10)
!31 = !DILocation(line: 15, column: 27, scope: !10)
!32 = !DILocation(line: 15, column: 3, scope: !10)
!33 = !DILocation(line: 16, column: 15, scope: !10)
!34 = !DILocation(line: 16, column: 21, scope: !10)
!35 = !DILocation(line: 16, column: 3, scope: !10)
!36 = !DILocation(line: 17, column: 15, scope: !10)
!37 = !DILocation(line: 17, column: 23, scope: !10)
!38 = !DILocation(line: 17, column: 3, scope: !10)
!39 = !DILocation(line: 18, column: 3, scope: !40)
!40 = distinct !DILexicalBlock(scope: !41, file: !11, line: 18, column: 3)
!41 = distinct !DILexicalBlock(scope: !10, file: !11, line: 18, column: 3)
!42 = !DILocation(line: 18, column: 3, scope: !41)
!43 = !DILocation(line: 19, column: 3, scope: !10)
