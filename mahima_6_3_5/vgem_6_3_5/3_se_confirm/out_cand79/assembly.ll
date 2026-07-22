; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand79.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand79_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"desc_count\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"desc_buf_size\00", align 1
@.str.2 = private unnamed_addr constant [58 x i8] c"(unsigned long)desc_count * MOVE_DESC_SZ <= desc_buf_size\00", align 1
@.str.3 = private unnamed_addr constant [124 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand79_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !12 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !18, metadata !DIExpression()), !dbg !20
  %4 = bitcast i32* %2 to i8*, !dbg !21
  call void @klee_make_symbolic(i8* noundef %4, i64 noundef 4, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i64 0, i64 0)), !dbg !22
  call void @llvm.dbg.declare(metadata i64* %3, metadata !23, metadata !DIExpression()), !dbg !24
  %5 = bitcast i64* %3 to i8*, !dbg !25
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 8, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i64 0, i64 0)), !dbg !26
  %6 = load i32, i32* %2, align 4, !dbg !27
  %7 = zext i32 %6 to i64, !dbg !28
  %8 = mul i64 %7, 32, !dbg !29
  %9 = load i64, i64* %3, align 8, !dbg !30
  %10 = icmp ule i64 %8, %9, !dbg !31
  %11 = zext i1 %10 to i32, !dbg !31
  %12 = sext i32 %11 to i64, !dbg !28
  call void @klee_assume(i64 noundef %12), !dbg !32
  %13 = load i32, i32* %2, align 4, !dbg !33
  %14 = zext i32 %13 to i64, !dbg !33
  %15 = mul i64 %14, 32, !dbg !33
  %16 = load i64, i64* %3, align 8, !dbg !33
  %17 = icmp ule i64 %15, %16, !dbg !33
  br i1 %17, label %18, label %19, !dbg !36

18:                                               ; preds = %0
  br label %20, !dbg !36

19:                                               ; preds = %0
  call void @__assert_fail(i8* noundef getelementptr inbounds ([58 x i8], [58 x i8]* @.str.2, i64 0, i64 0), i8* noundef getelementptr inbounds ([124 x i8], [124 x i8]* @.str.3, i64 0, i64 0), i32 noundef 14, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !33
  unreachable, !dbg !33

20:                                               ; preds = %18
  ret i32 0, !dbg !37
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
!llvm.module.flags = !{!4, !5, !6, !7, !8, !9, !10}
!llvm.ident = !{!11}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 14.0.0-1ubuntu1.1", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand79_wmi2.c", directory: "/home/mahima/eval4-main/eval4-mahima/stase_6_3_5/_tools", checksumkind: CSK_MD5, checksum: "a15f558e33d85eaff2a140ce0d3a5a6c")
!2 = !{!3}
!3 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!4 = !{i32 7, !"Dwarf Version", i32 5}
!5 = !{i32 2, !"Debug Info Version", i32 3}
!6 = !{i32 1, !"wchar_size", i32 4}
!7 = !{i32 7, !"PIC Level", i32 2}
!8 = !{i32 7, !"PIE Level", i32 2}
!9 = !{i32 7, !"uwtable", i32 1}
!10 = !{i32 7, !"frame-pointer", i32 2}
!11 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!12 = distinct !DISubprogram(name: "main", scope: !13, file: !13, line: 10, type: !14, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !17)
!13 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand79_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "a15f558e33d85eaff2a140ce0d3a5a6c")
!14 = !DISubroutineType(types: !15)
!15 = !{!16}
!16 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!17 = !{}
!18 = !DILocalVariable(name: "desc_count", scope: !12, file: !13, line: 11, type: !19)
!19 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!20 = !DILocation(line: 11, column: 16, scope: !12)
!21 = !DILocation(line: 11, column: 47, scope: !12)
!22 = !DILocation(line: 11, column: 28, scope: !12)
!23 = !DILocalVariable(name: "desc_buf_size", scope: !12, file: !13, line: 12, type: !3)
!24 = !DILocation(line: 12, column: 17, scope: !12)
!25 = !DILocation(line: 12, column: 51, scope: !12)
!26 = !DILocation(line: 12, column: 32, scope: !12)
!27 = !DILocation(line: 13, column: 30, scope: !12)
!28 = !DILocation(line: 13, column: 15, scope: !12)
!29 = !DILocation(line: 13, column: 41, scope: !12)
!30 = !DILocation(line: 13, column: 59, scope: !12)
!31 = !DILocation(line: 13, column: 56, scope: !12)
!32 = !DILocation(line: 13, column: 3, scope: !12)
!33 = !DILocation(line: 14, column: 3, scope: !34)
!34 = distinct !DILexicalBlock(scope: !35, file: !13, line: 14, column: 3)
!35 = distinct !DILexicalBlock(scope: !12, file: !13, line: 14, column: 3)
!36 = !DILocation(line: 14, column: 3, scope: !35)
!37 = !DILocation(line: 15, column: 3, scope: !12)
