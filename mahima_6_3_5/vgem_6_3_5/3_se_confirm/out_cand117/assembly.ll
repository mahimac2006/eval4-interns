; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand117.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand117_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"pixel_size\00", align 1
@.str.1 = private unnamed_addr constant [62 x i8] c"(pixel_size + PAGE_SIZE - 1) / PAGE_SIZE <= PP_MAX_DESC_COUNT\00", align 1
@.str.2 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand117_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i64, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i64* %2, metadata !16, metadata !DIExpression()), !dbg !18
  %3 = bitcast i64* %2 to i8*, !dbg !19
  call void @klee_make_symbolic(i8* noundef %3, i64 noundef 8, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i64 0, i64 0)), !dbg !20
  %4 = load i64, i64* %2, align 8, !dbg !21
  %5 = add i64 %4, 4096, !dbg !22
  %6 = sub i64 %5, 1, !dbg !23
  %7 = udiv i64 %6, 4096, !dbg !24
  %8 = urem i64 %7, 4294967296, !dbg !25
  %9 = icmp ule i64 %8, 1024, !dbg !26
  %10 = zext i1 %9 to i32, !dbg !26
  %11 = sext i32 %10 to i64, !dbg !27
  call void @klee_assume(i64 noundef %11), !dbg !28
  %12 = load i64, i64* %2, align 8, !dbg !29
  %13 = add i64 %12, 4096, !dbg !29
  %14 = sub i64 %13, 1, !dbg !29
  %15 = udiv i64 %14, 4096, !dbg !29
  %16 = icmp ule i64 %15, 1024, !dbg !29
  br i1 %16, label %17, label %18, !dbg !32

17:                                               ; preds = %0
  br label %19, !dbg !32

18:                                               ; preds = %0
  call void @__assert_fail(i8* noundef getelementptr inbounds ([62 x i8], [62 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.2, i64 0, i64 0), i32 noundef 15, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !29
  unreachable, !dbg !29

19:                                               ; preds = %17
  ret i32 0, !dbg !33
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand117_wmi2.c", directory: "/home/mahima/eval4-main/eval4-mahima/stase_6_3_5/_tools", checksumkind: CSK_MD5, checksum: "0a35ee5312fe734e8429111d68258b9e")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 12, type: !12, scopeLine: 12, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand117_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "0a35ee5312fe734e8429111d68258b9e")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "pixel_size", scope: !10, file: !11, line: 13, type: !17)
!17 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 13, column: 17, scope: !10)
!19 = !DILocation(line: 13, column: 48, scope: !10)
!20 = !DILocation(line: 13, column: 29, scope: !10)
!21 = !DILocation(line: 14, column: 17, scope: !10)
!22 = !DILocation(line: 14, column: 28, scope: !10)
!23 = !DILocation(line: 14, column: 40, scope: !10)
!24 = !DILocation(line: 14, column: 45, scope: !10)
!25 = !DILocation(line: 14, column: 58, scope: !10)
!26 = !DILocation(line: 14, column: 66, scope: !10)
!27 = !DILocation(line: 14, column: 15, scope: !10)
!28 = !DILocation(line: 14, column: 3, scope: !10)
!29 = !DILocation(line: 15, column: 3, scope: !30)
!30 = distinct !DILexicalBlock(scope: !31, file: !11, line: 15, column: 3)
!31 = distinct !DILexicalBlock(scope: !10, file: !11, line: 15, column: 3)
!32 = !DILocation(line: 15, column: 3, scope: !31)
!33 = !DILocation(line: 16, column: 3, scope: !10)
