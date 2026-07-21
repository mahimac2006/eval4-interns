; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand113.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand113_wmi4.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [22 x i8] c"content_authoritative\00", align 1
@.str.1 = private unnamed_addr constant [17 x i8] c"content_attacker\00", align 1
@.str.2 = private unnamed_addr constant [13 x i8] c"access_index\00", align 1
@.str.3 = private unnamed_addr constant [6 x i8] c"bound\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !17
  %6 = bitcast i32* %2 to i8*, !dbg !18
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str, i64 0, i64 0)), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %3, metadata !20, metadata !DIExpression()), !dbg !21
  %7 = bitcast i32* %3 to i8*, !dbg !22
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.1, i64 0, i64 0)), !dbg !23
  call void @llvm.dbg.declare(metadata i32* %4, metadata !24, metadata !DIExpression()), !dbg !25
  %8 = bitcast i32* %4 to i8*, !dbg !26
  call void @klee_make_symbolic(i8* noundef %8, i64 noundef 4, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.2, i64 0, i64 0)), !dbg !27
  call void @llvm.dbg.declare(metadata i32* %5, metadata !28, metadata !DIExpression()), !dbg !29
  %9 = bitcast i32* %5 to i8*, !dbg !30
  call void @klee_make_symbolic(i8* noundef %9, i64 noundef 4, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i64 0, i64 0)), !dbg !31
  %10 = load i32, i32* %2, align 4, !dbg !32
  %11 = icmp eq i32 %10, 1, !dbg !33
  %12 = zext i1 %11 to i32, !dbg !33
  %13 = sext i32 %12 to i64, !dbg !32
  call void @klee_assume(i64 noundef %13), !dbg !34
  %14 = load i32, i32* %3, align 4, !dbg !35
  %15 = icmp eq i32 %14, 1, !dbg !36
  %16 = zext i1 %15 to i32, !dbg !36
  %17 = sext i32 %16 to i64, !dbg !35
  call void @klee_assume(i64 noundef %17), !dbg !37
  %18 = load i32, i32* %5, align 4, !dbg !38
  %19 = icmp sge i32 %18, 1, !dbg !39
  %20 = zext i1 %19 to i32, !dbg !39
  %21 = sext i32 %20 to i64, !dbg !38
  call void @klee_assume(i64 noundef %21), !dbg !40
  %22 = load i32, i32* %4, align 4, !dbg !41
  %23 = icmp sge i32 %22, 0, !dbg !42
  %24 = zext i1 %23 to i32, !dbg !42
  %25 = sext i32 %24 to i64, !dbg !41
  call void @klee_assume(i64 noundef %25), !dbg !43
  ret i32 0, !dbg !44
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @klee_make_symbolic(i8* noundef, i64 noundef, i8* noundef) #2

declare void @klee_assume(i64 noundef) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 14.0.0-1ubuntu1.1", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand113_wmi4.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "9f0d0fba4e24b0439ebabf61eb2d007d")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 10, type: !12, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand113_wmi4.c", directory: "", checksumkind: CSK_MD5, checksum: "9f0d0fba4e24b0439ebabf61eb2d007d")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "content_authoritative", scope: !10, file: !11, line: 11, type: !14)
!17 = !DILocation(line: 11, column: 7, scope: !10)
!18 = !DILocation(line: 11, column: 49, scope: !10)
!19 = !DILocation(line: 11, column: 30, scope: !10)
!20 = !DILocalVariable(name: "content_attacker", scope: !10, file: !11, line: 12, type: !14)
!21 = !DILocation(line: 12, column: 7, scope: !10)
!22 = !DILocation(line: 12, column: 44, scope: !10)
!23 = !DILocation(line: 12, column: 25, scope: !10)
!24 = !DILocalVariable(name: "access_index", scope: !10, file: !11, line: 13, type: !14)
!25 = !DILocation(line: 13, column: 7, scope: !10)
!26 = !DILocation(line: 13, column: 40, scope: !10)
!27 = !DILocation(line: 13, column: 21, scope: !10)
!28 = !DILocalVariable(name: "bound", scope: !10, file: !11, line: 14, type: !14)
!29 = !DILocation(line: 14, column: 7, scope: !10)
!30 = !DILocation(line: 14, column: 33, scope: !10)
!31 = !DILocation(line: 14, column: 14, scope: !10)
!32 = !DILocation(line: 15, column: 15, scope: !10)
!33 = !DILocation(line: 15, column: 37, scope: !10)
!34 = !DILocation(line: 15, column: 3, scope: !10)
!35 = !DILocation(line: 16, column: 15, scope: !10)
!36 = !DILocation(line: 16, column: 32, scope: !10)
!37 = !DILocation(line: 16, column: 3, scope: !10)
!38 = !DILocation(line: 17, column: 15, scope: !10)
!39 = !DILocation(line: 17, column: 21, scope: !10)
!40 = !DILocation(line: 17, column: 3, scope: !10)
!41 = !DILocation(line: 18, column: 15, scope: !10)
!42 = !DILocation(line: 18, column: 28, scope: !10)
!43 = !DILocation(line: 18, column: 3, scope: !10)
!44 = !DILocation(line: 20, column: 3, scope: !10)
