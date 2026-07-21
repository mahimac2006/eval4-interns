; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand114.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand114_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [6 x i8] c"width\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@.str.2 = private unnamed_addr constant [49 x i8] c"height <= (PP_MAX_BUFFER_SIZE / ELEM_SZ) / width\00", align 1
@.str.3 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand114_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1
@.str.4 = private unnamed_addr constant [58 x i8] c"/home/mahima/klee/runtime/Intrinsic/klee_div_zero_check.c\00", align 1
@.str.1.5 = private unnamed_addr constant [15 x i8] c"divide by zero\00", align 1
@.str.2.6 = private unnamed_addr constant [8 x i8] c"div.err\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !14 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !20, metadata !DIExpression()), !dbg !22
  %4 = bitcast i32* %2 to i8*, !dbg !23
  call void @klee_make_symbolic(i8* noundef %4, i64 noundef 4, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0)), !dbg !24
  call void @llvm.dbg.declare(metadata i32* %3, metadata !25, metadata !DIExpression()), !dbg !26
  %5 = bitcast i32* %3 to i8*, !dbg !27
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 4, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0)), !dbg !28
  %6 = load i32, i32* %2, align 4, !dbg !29
  %7 = icmp ne i32 %6, 0, !dbg !30
  %8 = zext i1 %7 to i32, !dbg !30
  %9 = sext i32 %8 to i64, !dbg !29
  call void @klee_assume(i64 noundef %9), !dbg !31
  %10 = load i32, i32* %3, align 4, !dbg !32
  %11 = icmp ne i32 %10, 0, !dbg !33
  %12 = zext i1 %11 to i32, !dbg !33
  %13 = sext i32 %12 to i64, !dbg !32
  call void @klee_assume(i64 noundef %13), !dbg !34
  %14 = load i32, i32* %2, align 4, !dbg !35
  %15 = zext i32 %14 to i64, !dbg !36
  %16 = load i32, i32* %3, align 4, !dbg !37
  %17 = zext i32 %16 to i64, !dbg !38
  %18 = mul i64 %15, %17, !dbg !39
  %19 = mul i64 %18, 4, !dbg !40
  %20 = icmp ule i64 %19, 67108864, !dbg !41
  %21 = zext i1 %20 to i32, !dbg !41
  %22 = sext i32 %21 to i64, !dbg !42
  call void @klee_assume(i64 noundef %22), !dbg !43
  %23 = load i32, i32* %3, align 4, !dbg !44
  %24 = load i32, i32* %2, align 4, !dbg !44
  %int_cast_to_i64 = zext i32 %24 to i64, !dbg !44
  call void @klee_div_zero_check(i64 %int_cast_to_i64), !dbg !44
  %25 = udiv i32 16777216, %24, !dbg !44, !klee.check.div !47
  %26 = icmp ule i32 %23, %25, !dbg !44
  br i1 %26, label %27, label %28, !dbg !48

27:                                               ; preds = %0
  br label %29, !dbg !48

28:                                               ; preds = %0
  call void @__assert_fail(i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.2, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.3, i64 0, i64 0), i32 noundef 17, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #6, !dbg !44
  unreachable, !dbg !44

29:                                               ; preds = %27
  ret i32 0, !dbg !49
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @klee_make_symbolic(i8* noundef, i64 noundef, i8* noundef) #2

declare void @klee_assume(i64 noundef) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) #3

; Function Attrs: noinline nounwind uwtable
define dso_local void @klee_div_zero_check(i64 noundef %0) #4 !dbg !50 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  call void @llvm.dbg.declare(metadata i64* %2, metadata !55, metadata !DIExpression()), !dbg !56
  %3 = load i64, i64* %2, align 8, !dbg !57
  %4 = icmp eq i64 %3, 0, !dbg !59
  br i1 %4, label %5, label %6, !dbg !60

5:                                                ; preds = %1
  call void @klee_report_error(i8* noundef getelementptr inbounds ([58 x i8], [58 x i8]* @.str.4, i64 0, i64 0), i32 noundef 14, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.1.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.2.6, i64 0, i64 0)) #7, !dbg !61
  unreachable, !dbg !61

6:                                                ; preds = %1
  ret void, !dbg !62
}

; Function Attrs: noreturn
declare void @klee_report_error(i8* noundef, i32 noundef, i8* noundef, i8* noundef) #5

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { noreturn nounwind }
attributes #7 = { noreturn }

!llvm.dbg.cu = !{!0, !4}
!llvm.module.flags = !{!6, !7, !8, !9, !10, !11, !12}
!llvm.ident = !{!13, !13}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 14.0.0-1ubuntu1.1", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand114_wmi2.c", directory: "/home/mahima/eval4-main/eval4-mahima/stase_6_3_5/_tools", checksumkind: CSK_MD5, checksum: "c85057771d17a772e3d02ae7517cb776")
!2 = !{!3}
!3 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!4 = distinct !DICompileUnit(language: DW_LANG_C89, file: !5, producer: "Ubuntu clang version 14.0.0-1ubuntu1.1", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!5 = !DIFile(filename: "/home/mahima/klee/runtime/Intrinsic/klee_div_zero_check.c", directory: "/home/mahima/klee/build/runtime/Intrinsic", checksumkind: CSK_MD5, checksum: "ac97458b4bebcea5cefe50ebb216db13")
!6 = !{i32 7, !"Dwarf Version", i32 5}
!7 = !{i32 2, !"Debug Info Version", i32 3}
!8 = !{i32 1, !"wchar_size", i32 4}
!9 = !{i32 7, !"PIC Level", i32 2}
!10 = !{i32 7, !"PIE Level", i32 2}
!11 = !{i32 7, !"uwtable", i32 1}
!12 = !{i32 7, !"frame-pointer", i32 2}
!13 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!14 = distinct !DISubprogram(name: "main", scope: !15, file: !15, line: 11, type: !16, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !19)
!15 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_vgem/3_se_confirm/cand114_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "c85057771d17a772e3d02ae7517cb776")
!16 = !DISubroutineType(types: !17)
!17 = !{!18}
!18 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!19 = !{}
!20 = !DILocalVariable(name: "width", scope: !14, file: !15, line: 12, type: !21)
!21 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!22 = !DILocation(line: 12, column: 16, scope: !14)
!23 = !DILocation(line: 12, column: 42, scope: !14)
!24 = !DILocation(line: 12, column: 23, scope: !14)
!25 = !DILocalVariable(name: "height", scope: !14, file: !15, line: 13, type: !21)
!26 = !DILocation(line: 13, column: 16, scope: !14)
!27 = !DILocation(line: 13, column: 43, scope: !14)
!28 = !DILocation(line: 13, column: 24, scope: !14)
!29 = !DILocation(line: 14, column: 15, scope: !14)
!30 = !DILocation(line: 14, column: 21, scope: !14)
!31 = !DILocation(line: 14, column: 3, scope: !14)
!32 = !DILocation(line: 15, column: 15, scope: !14)
!33 = !DILocation(line: 15, column: 22, scope: !14)
!34 = !DILocation(line: 15, column: 3, scope: !14)
!35 = !DILocation(line: 16, column: 31, scope: !14)
!36 = !DILocation(line: 16, column: 16, scope: !14)
!37 = !DILocation(line: 16, column: 54, scope: !14)
!38 = !DILocation(line: 16, column: 39, scope: !14)
!39 = !DILocation(line: 16, column: 37, scope: !14)
!40 = !DILocation(line: 16, column: 61, scope: !14)
!41 = !DILocation(line: 16, column: 72, scope: !14)
!42 = !DILocation(line: 16, column: 15, scope: !14)
!43 = !DILocation(line: 16, column: 3, scope: !14)
!44 = !DILocation(line: 17, column: 3, scope: !45)
!45 = distinct !DILexicalBlock(scope: !46, file: !15, line: 17, column: 3)
!46 = distinct !DILexicalBlock(scope: !14, file: !15, line: 17, column: 3)
!47 = !{!"True"}
!48 = !DILocation(line: 17, column: 3, scope: !46)
!49 = !DILocation(line: 18, column: 3, scope: !14)
!50 = distinct !DISubprogram(name: "klee_div_zero_check", scope: !51, file: !51, line: 12, type: !52, scopeLine: 12, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !4, retainedNodes: !19)
!51 = !DIFile(filename: "runtime/Intrinsic/klee_div_zero_check.c", directory: "/home/mahima/klee", checksumkind: CSK_MD5, checksum: "ac97458b4bebcea5cefe50ebb216db13")
!52 = !DISubroutineType(types: !53)
!53 = !{null, !54}
!54 = !DIBasicType(name: "long long", size: 64, encoding: DW_ATE_signed)
!55 = !DILocalVariable(name: "z", arg: 1, scope: !50, file: !51, line: 12, type: !54)
!56 = !DILocation(line: 12, column: 36, scope: !50)
!57 = !DILocation(line: 13, column: 7, scope: !58)
!58 = distinct !DILexicalBlock(scope: !50, file: !51, line: 13, column: 7)
!59 = !DILocation(line: 13, column: 9, scope: !58)
!60 = !DILocation(line: 13, column: 7, scope: !50)
!61 = !DILocation(line: 14, column: 5, scope: !58)
!62 = !DILocation(line: 15, column: 1, scope: !50)
