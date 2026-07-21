; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand47_tmpl.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand47_tmpl.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [18 x i8] c"signal_ungoverned\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"view_a\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"view_b\00", align 1
@.str.3 = private unnamed_addr constant [6 x i8] c"freed\00", align 1
@.str.4 = private unnamed_addr constant [17 x i8] c"view_a == view_b\00", align 1
@.str.5 = private unnamed_addr constant [124 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand47_tmpl.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

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
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str, i64 0, i64 0)), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %3, metadata !20, metadata !DIExpression()), !dbg !21
  %7 = bitcast i32* %3 to i8*, !dbg !22
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0)), !dbg !23
  call void @llvm.dbg.declare(metadata i32* %4, metadata !24, metadata !DIExpression()), !dbg !25
  %8 = bitcast i32* %4 to i8*, !dbg !26
  call void @klee_make_symbolic(i8* noundef %8, i64 noundef 4, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i64 0, i64 0)), !dbg !27
  call void @llvm.dbg.declare(metadata i32* %5, metadata !28, metadata !DIExpression()), !dbg !29
  %9 = bitcast i32* %5 to i8*, !dbg !30
  call void @klee_make_symbolic(i8* noundef %9, i64 noundef 4, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i64 0, i64 0)), !dbg !31
  %10 = load i32, i32* %2, align 4, !dbg !32
  %11 = icmp eq i32 %10, 1, !dbg !33
  %12 = zext i1 %11 to i32, !dbg !33
  %13 = sext i32 %12 to i64, !dbg !32
  call void @klee_assume(i64 noundef %13), !dbg !34
  %14 = load i32, i32* %5, align 4, !dbg !35
  %15 = icmp eq i32 %14, 0, !dbg !36
  %16 = zext i1 %15 to i32, !dbg !36
  %17 = sext i32 %16 to i64, !dbg !35
  call void @klee_assume(i64 noundef %17), !dbg !37
  %18 = load i32, i32* %3, align 4, !dbg !38
  %19 = load i32, i32* %4, align 4, !dbg !38
  %20 = icmp eq i32 %18, %19, !dbg !38
  br i1 %20, label %21, label %22, !dbg !41

21:                                               ; preds = %0
  br label %23, !dbg !41

22:                                               ; preds = %0
  call void @__assert_fail(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([124 x i8], [124 x i8]* @.str.5, i64 0, i64 0), i32 noundef 16, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !38
  unreachable, !dbg !38

23:                                               ; preds = %21
  ret i32 0, !dbg !42
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand47_tmpl.c", directory: "/home/mahima/eval4-main/eval4-mahima/stase_6_3_5/_tools", checksumkind: CSK_MD5, checksum: "df7ba011a4c4f341c3988432c6ec3686")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 9, type: !12, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand47_tmpl.c", directory: "", checksumkind: CSK_MD5, checksum: "df7ba011a4c4f341c3988432c6ec3686")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "signal_ungoverned", scope: !10, file: !11, line: 10, type: !14)
!17 = !DILocation(line: 10, column: 7, scope: !10)
!18 = !DILocation(line: 10, column: 45, scope: !10)
!19 = !DILocation(line: 10, column: 26, scope: !10)
!20 = !DILocalVariable(name: "view_a", scope: !10, file: !11, line: 11, type: !14)
!21 = !DILocation(line: 11, column: 7, scope: !10)
!22 = !DILocation(line: 11, column: 34, scope: !10)
!23 = !DILocation(line: 11, column: 15, scope: !10)
!24 = !DILocalVariable(name: "view_b", scope: !10, file: !11, line: 12, type: !14)
!25 = !DILocation(line: 12, column: 7, scope: !10)
!26 = !DILocation(line: 12, column: 34, scope: !10)
!27 = !DILocation(line: 12, column: 15, scope: !10)
!28 = !DILocalVariable(name: "freed", scope: !10, file: !11, line: 13, type: !14)
!29 = !DILocation(line: 13, column: 7, scope: !10)
!30 = !DILocation(line: 13, column: 33, scope: !10)
!31 = !DILocation(line: 13, column: 14, scope: !10)
!32 = !DILocation(line: 14, column: 15, scope: !10)
!33 = !DILocation(line: 14, column: 33, scope: !10)
!34 = !DILocation(line: 14, column: 3, scope: !10)
!35 = !DILocation(line: 15, column: 15, scope: !10)
!36 = !DILocation(line: 15, column: 21, scope: !10)
!37 = !DILocation(line: 15, column: 3, scope: !10)
!38 = !DILocation(line: 16, column: 3, scope: !39)
!39 = distinct !DILexicalBlock(scope: !40, file: !11, line: 16, column: 3)
!40 = distinct !DILexicalBlock(scope: !10, file: !11, line: 16, column: 3)
!41 = !DILocation(line: 16, column: 3, scope: !40)
!42 = !DILocation(line: 17, column: 3, scope: !10)
