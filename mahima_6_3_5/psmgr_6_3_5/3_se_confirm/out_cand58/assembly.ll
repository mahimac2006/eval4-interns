; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand58.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand58_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"out_offset\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c"payload_len\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"token\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"base_limit\00", align 1
@.str.4 = private unnamed_addr constant [12 x i8] c"write_limit\00", align 1
@.str.5 = private unnamed_addr constant [9 x i8] c"copy_len\00", align 1
@.str.6 = private unnamed_addr constant [53 x i8] c"copy_len == 0 || (out_offset + copy_len) <= TOTAL_SZ\00", align 1
@.str.7 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand58_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !18
  %8 = bitcast i32* %2 to i8*, !dbg !19
  call void @klee_make_symbolic(i8* noundef %8, i64 noundef 4, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i64 0, i64 0)), !dbg !20
  call void @llvm.dbg.declare(metadata i32* %3, metadata !21, metadata !DIExpression()), !dbg !22
  %9 = bitcast i32* %3 to i8*, !dbg !23
  call void @klee_make_symbolic(i8* noundef %9, i64 noundef 4, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i64 0, i64 0)), !dbg !24
  call void @llvm.dbg.declare(metadata i32* %4, metadata !25, metadata !DIExpression()), !dbg !26
  %10 = bitcast i32* %4 to i8*, !dbg !27
  call void @klee_make_symbolic(i8* noundef %10, i64 noundef 4, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0)), !dbg !28
  call void @llvm.dbg.declare(metadata i32* %5, metadata !29, metadata !DIExpression()), !dbg !30
  %11 = bitcast i32* %5 to i8*, !dbg !31
  call void @klee_make_symbolic(i8* noundef %11, i64 noundef 4, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i64 0, i64 0)), !dbg !32
  call void @llvm.dbg.declare(metadata i32* %6, metadata !33, metadata !DIExpression()), !dbg !34
  %12 = bitcast i32* %6 to i8*, !dbg !35
  call void @klee_make_symbolic(i8* noundef %12, i64 noundef 4, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.4, i64 0, i64 0)), !dbg !36
  call void @llvm.dbg.declare(metadata i32* %7, metadata !37, metadata !DIExpression()), !dbg !38
  %13 = bitcast i32* %7 to i8*, !dbg !39
  call void @klee_make_symbolic(i8* noundef %13, i64 noundef 4, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.5, i64 0, i64 0)), !dbg !40
  %14 = load i32, i32* %5, align 4, !dbg !41
  %15 = load i32, i32* %4, align 4, !dbg !42
  %16 = icmp ne i32 %15, 0, !dbg !43
  %17 = zext i1 %16 to i64, !dbg !42
  %18 = select i1 %16, i32 144, i32 132, !dbg !42
  %19 = icmp eq i32 %14, %18, !dbg !44
  %20 = zext i1 %19 to i32, !dbg !44
  %21 = sext i32 %20 to i64, !dbg !41
  call void @klee_assume(i64 noundef %21), !dbg !45
  %22 = load i32, i32* %6, align 4, !dbg !46
  %23 = load i32, i32* %2, align 4, !dbg !47
  %24 = icmp ult i32 %23, 128, !dbg !48
  br i1 %24, label %25, label %29, !dbg !49

25:                                               ; preds = %0
  %26 = load i32, i32* %5, align 4, !dbg !50
  %27 = icmp ugt i32 %26, 128, !dbg !51
  br i1 %27, label %28, label %29, !dbg !52

28:                                               ; preds = %25
  br label %31, !dbg !52

29:                                               ; preds = %25, %0
  %30 = load i32, i32* %5, align 4, !dbg !53
  br label %31, !dbg !52

31:                                               ; preds = %29, %28
  %32 = phi i32 [ 128, %28 ], [ %30, %29 ], !dbg !52
  %33 = icmp eq i32 %22, %32, !dbg !54
  %34 = zext i1 %33 to i32, !dbg !54
  %35 = sext i32 %34 to i64, !dbg !46
  call void @klee_assume(i64 noundef %35), !dbg !55
  %36 = load i32, i32* %7, align 4, !dbg !56
  %37 = load i32, i32* %3, align 4, !dbg !57
  %38 = load i32, i32* %6, align 4, !dbg !58
  %39 = load i32, i32* %2, align 4, !dbg !59
  %40 = load i32, i32* %6, align 4, !dbg !60
  %41 = icmp ult i32 %39, %40, !dbg !61
  br i1 %41, label %42, label %44, !dbg !59

42:                                               ; preds = %31
  %43 = load i32, i32* %2, align 4, !dbg !62
  br label %46, !dbg !59

44:                                               ; preds = %31
  %45 = load i32, i32* %6, align 4, !dbg !63
  br label %46, !dbg !59

46:                                               ; preds = %44, %42
  %47 = phi i32 [ %43, %42 ], [ %45, %44 ], !dbg !59
  %48 = sub i32 %38, %47, !dbg !64
  %49 = icmp ult i32 %37, %48, !dbg !65
  br i1 %49, label %50, label %52, !dbg !66

50:                                               ; preds = %46
  %51 = load i32, i32* %3, align 4, !dbg !67
  br label %64, !dbg !66

52:                                               ; preds = %46
  %53 = load i32, i32* %6, align 4, !dbg !68
  %54 = load i32, i32* %2, align 4, !dbg !69
  %55 = load i32, i32* %6, align 4, !dbg !70
  %56 = icmp ult i32 %54, %55, !dbg !71
  br i1 %56, label %57, label %59, !dbg !69

57:                                               ; preds = %52
  %58 = load i32, i32* %2, align 4, !dbg !72
  br label %61, !dbg !69

59:                                               ; preds = %52
  %60 = load i32, i32* %6, align 4, !dbg !73
  br label %61, !dbg !69

61:                                               ; preds = %59, %57
  %62 = phi i32 [ %58, %57 ], [ %60, %59 ], !dbg !69
  %63 = sub i32 %53, %62, !dbg !74
  br label %64, !dbg !66

64:                                               ; preds = %61, %50
  %65 = phi i32 [ %51, %50 ], [ %63, %61 ], !dbg !66
  %66 = icmp eq i32 %36, %65, !dbg !75
  %67 = zext i1 %66 to i32, !dbg !75
  %68 = sext i32 %67 to i64, !dbg !56
  call void @klee_assume(i64 noundef %68), !dbg !76
  %69 = load i32, i32* %7, align 4, !dbg !77
  %70 = icmp eq i32 %69, 0, !dbg !77
  br i1 %70, label %76, label %71, !dbg !77

71:                                               ; preds = %64
  %72 = load i32, i32* %2, align 4, !dbg !77
  %73 = load i32, i32* %7, align 4, !dbg !77
  %74 = add i32 %72, %73, !dbg !77
  %75 = icmp ule i32 %74, 144, !dbg !77
  br i1 %75, label %76, label %77, !dbg !80

76:                                               ; preds = %71, %64
  br label %78, !dbg !80

77:                                               ; preds = %71
  call void @__assert_fail(i8* noundef getelementptr inbounds ([53 x i8], [53 x i8]* @.str.6, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.7, i64 0, i64 0), i32 noundef 22, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !77
  unreachable, !dbg !77

78:                                               ; preds = %76
  ret i32 0, !dbg !81
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand58_wmi2.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "f7f00ea53ff645a3056c8c1d8a8c82f1")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 12, type: !12, scopeLine: 12, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand58_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "f7f00ea53ff645a3056c8c1d8a8c82f1")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "out_offset", scope: !10, file: !11, line: 13, type: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 13, column: 16, scope: !10)
!19 = !DILocation(line: 13, column: 47, scope: !10)
!20 = !DILocation(line: 13, column: 28, scope: !10)
!21 = !DILocalVariable(name: "payload_len", scope: !10, file: !11, line: 14, type: !17)
!22 = !DILocation(line: 14, column: 16, scope: !10)
!23 = !DILocation(line: 14, column: 48, scope: !10)
!24 = !DILocation(line: 14, column: 29, scope: !10)
!25 = !DILocalVariable(name: "token", scope: !10, file: !11, line: 15, type: !17)
!26 = !DILocation(line: 15, column: 16, scope: !10)
!27 = !DILocation(line: 15, column: 42, scope: !10)
!28 = !DILocation(line: 15, column: 23, scope: !10)
!29 = !DILocalVariable(name: "base_limit", scope: !10, file: !11, line: 16, type: !17)
!30 = !DILocation(line: 16, column: 16, scope: !10)
!31 = !DILocation(line: 16, column: 47, scope: !10)
!32 = !DILocation(line: 16, column: 28, scope: !10)
!33 = !DILocalVariable(name: "write_limit", scope: !10, file: !11, line: 17, type: !17)
!34 = !DILocation(line: 17, column: 16, scope: !10)
!35 = !DILocation(line: 17, column: 48, scope: !10)
!36 = !DILocation(line: 17, column: 29, scope: !10)
!37 = !DILocalVariable(name: "copy_len", scope: !10, file: !11, line: 18, type: !17)
!38 = !DILocation(line: 18, column: 16, scope: !10)
!39 = !DILocation(line: 18, column: 45, scope: !10)
!40 = !DILocation(line: 18, column: 26, scope: !10)
!41 = !DILocation(line: 19, column: 15, scope: !10)
!42 = !DILocation(line: 19, column: 30, scope: !10)
!43 = !DILocation(line: 19, column: 36, scope: !10)
!44 = !DILocation(line: 19, column: 26, scope: !10)
!45 = !DILocation(line: 19, column: 3, scope: !10)
!46 = !DILocation(line: 20, column: 15, scope: !10)
!47 = !DILocation(line: 20, column: 32, scope: !10)
!48 = !DILocation(line: 20, column: 43, scope: !10)
!49 = !DILocation(line: 20, column: 53, scope: !10)
!50 = !DILocation(line: 20, column: 56, scope: !10)
!51 = !DILocation(line: 20, column: 67, scope: !10)
!52 = !DILocation(line: 20, column: 31, scope: !10)
!53 = !DILocation(line: 20, column: 90, scope: !10)
!54 = !DILocation(line: 20, column: 27, scope: !10)
!55 = !DILocation(line: 20, column: 3, scope: !10)
!56 = !DILocation(line: 21, column: 15, scope: !10)
!57 = !DILocation(line: 21, column: 29, scope: !10)
!58 = !DILocation(line: 21, column: 44, scope: !10)
!59 = !DILocation(line: 21, column: 59, scope: !10)
!60 = !DILocation(line: 21, column: 72, scope: !10)
!61 = !DILocation(line: 21, column: 70, scope: !10)
!62 = !DILocation(line: 21, column: 86, scope: !10)
!63 = !DILocation(line: 21, column: 99, scope: !10)
!64 = !DILocation(line: 21, column: 56, scope: !10)
!65 = !DILocation(line: 21, column: 41, scope: !10)
!66 = !DILocation(line: 21, column: 28, scope: !10)
!67 = !DILocation(line: 21, column: 116, scope: !10)
!68 = !DILocation(line: 21, column: 131, scope: !10)
!69 = !DILocation(line: 21, column: 146, scope: !10)
!70 = !DILocation(line: 21, column: 159, scope: !10)
!71 = !DILocation(line: 21, column: 157, scope: !10)
!72 = !DILocation(line: 21, column: 173, scope: !10)
!73 = !DILocation(line: 21, column: 186, scope: !10)
!74 = !DILocation(line: 21, column: 143, scope: !10)
!75 = !DILocation(line: 21, column: 24, scope: !10)
!76 = !DILocation(line: 21, column: 3, scope: !10)
!77 = !DILocation(line: 22, column: 3, scope: !78)
!78 = distinct !DILexicalBlock(scope: !79, file: !11, line: 22, column: 3)
!79 = distinct !DILexicalBlock(scope: !10, file: !11, line: 22, column: 3)
!80 = !DILocation(line: 22, column: 3, scope: !79)
!81 = !DILocation(line: 23, column: 3, scope: !10)
