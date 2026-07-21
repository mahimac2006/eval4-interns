; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand87.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand87_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"sess_role\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"peer_role\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"sess_state\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"peer_state\00", align 1
@.str.4 = private unnamed_addr constant [57 x i8] c"sess_state == STATE_NEGO_2 && peer_state == STATE_NEGO_2\00", align 1
@.str.5 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand87_wmi2.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !10 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !18
  %6 = bitcast i32* %2 to i8*, !dbg !19
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0)), !dbg !20
  call void @llvm.dbg.declare(metadata i32* %3, metadata !21, metadata !DIExpression()), !dbg !22
  %7 = bitcast i32* %3 to i8*, !dbg !23
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i64 0, i64 0)), !dbg !24
  call void @llvm.dbg.declare(metadata i32* %4, metadata !25, metadata !DIExpression()), !dbg !26
  %8 = bitcast i32* %4 to i8*, !dbg !27
  call void @klee_make_symbolic(i8* noundef %8, i64 noundef 4, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)), !dbg !28
  call void @llvm.dbg.declare(metadata i32* %5, metadata !29, metadata !DIExpression()), !dbg !30
  %9 = bitcast i32* %5 to i8*, !dbg !31
  call void @klee_make_symbolic(i8* noundef %9, i64 noundef 4, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i64 0, i64 0)), !dbg !32
  %10 = load i32, i32* %2, align 4, !dbg !33
  %11 = icmp eq i32 %10, 1, !dbg !34
  %12 = zext i1 %11 to i32, !dbg !34
  %13 = sext i32 %12 to i64, !dbg !33
  call void @klee_assume(i64 noundef %13), !dbg !35
  %14 = load i32, i32* %2, align 4, !dbg !36
  %15 = icmp eq i32 %14, 1, !dbg !37
  br i1 %15, label %16, label %19, !dbg !38

16:                                               ; preds = %0
  %17 = load i32, i32* %3, align 4, !dbg !39
  %18 = icmp ne i32 %17, 2, !dbg !40
  br label %19

19:                                               ; preds = %16, %0
  %20 = phi i1 [ false, %0 ], [ %18, %16 ], !dbg !41
  %21 = xor i1 %20, true, !dbg !42
  %22 = zext i1 %21 to i32, !dbg !42
  %23 = sext i32 %22 to i64, !dbg !42
  call void @klee_assume(i64 noundef %23), !dbg !43
  %24 = load i32, i32* %2, align 4, !dbg !44
  %25 = icmp eq i32 %24, 2, !dbg !45
  br i1 %25, label %26, label %29, !dbg !46

26:                                               ; preds = %19
  %27 = load i32, i32* %3, align 4, !dbg !47
  %28 = icmp ne i32 %27, 1, !dbg !48
  br label %29

29:                                               ; preds = %26, %19
  %30 = phi i1 [ false, %19 ], [ %28, %26 ], !dbg !41
  %31 = xor i1 %30, true, !dbg !49
  %32 = zext i1 %31 to i32, !dbg !49
  %33 = sext i32 %32 to i64, !dbg !49
  call void @klee_assume(i64 noundef %33), !dbg !50
  %34 = load i32, i32* %2, align 4, !dbg !51
  %35 = icmp eq i32 %34, 3, !dbg !52
  br i1 %35, label %36, label %39, !dbg !53

36:                                               ; preds = %29
  %37 = load i32, i32* %3, align 4, !dbg !54
  %38 = icmp ne i32 %37, 3, !dbg !55
  br label %39

39:                                               ; preds = %36, %29
  %40 = phi i1 [ false, %29 ], [ %38, %36 ], !dbg !41
  %41 = xor i1 %40, true, !dbg !56
  %42 = zext i1 %41 to i32, !dbg !56
  %43 = sext i32 %42 to i64, !dbg !56
  call void @klee_assume(i64 noundef %43), !dbg !57
  %44 = load i32, i32* %2, align 4, !dbg !58
  %45 = icmp eq i32 %44, 1, !dbg !59
  br i1 %45, label %49, label %46, !dbg !60

46:                                               ; preds = %39
  %47 = load i32, i32* %2, align 4, !dbg !61
  %48 = icmp eq i32 %47, 2, !dbg !62
  br i1 %48, label %49, label %58, !dbg !63

49:                                               ; preds = %46, %39
  %50 = load i32, i32* %4, align 4, !dbg !64
  %51 = icmp eq i32 %50, 2, !dbg !65
  br i1 %51, label %52, label %55, !dbg !66

52:                                               ; preds = %49
  %53 = load i32, i32* %5, align 4, !dbg !67
  %54 = icmp eq i32 %53, 2, !dbg !68
  br label %55

55:                                               ; preds = %52, %49
  %56 = phi i1 [ false, %49 ], [ %54, %52 ], !dbg !41
  %57 = zext i1 %56 to i32, !dbg !66
  br label %59, !dbg !63

58:                                               ; preds = %46
  br label %59, !dbg !63

59:                                               ; preds = %58, %55
  %60 = phi i32 [ %57, %55 ], [ 1, %58 ], !dbg !63
  %61 = sext i32 %60 to i64, !dbg !63
  call void @klee_assume(i64 noundef %61), !dbg !69
  %62 = load i32, i32* %4, align 4, !dbg !70
  %63 = icmp eq i32 %62, 2, !dbg !70
  br i1 %63, label %64, label %68, !dbg !70

64:                                               ; preds = %59
  %65 = load i32, i32* %5, align 4, !dbg !70
  %66 = icmp eq i32 %65, 2, !dbg !70
  br i1 %66, label %67, label %68, !dbg !73

67:                                               ; preds = %64
  br label %69, !dbg !73

68:                                               ; preds = %64, %59
  call void @__assert_fail(i8* noundef getelementptr inbounds ([57 x i8], [57 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.5, i64 0, i64 0), i32 noundef 23, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !70
  unreachable, !dbg !70

69:                                               ; preds = %67
  ret i32 0, !dbg !74
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand87_wmi2.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "1a4fa7a18dc63beeb14d10742d33dc54")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 13, type: !12, scopeLine: 13, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand87_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "1a4fa7a18dc63beeb14d10742d33dc54")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "sess_role", scope: !10, file: !11, line: 14, type: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 14, column: 16, scope: !10)
!19 = !DILocation(line: 14, column: 46, scope: !10)
!20 = !DILocation(line: 14, column: 27, scope: !10)
!21 = !DILocalVariable(name: "peer_role", scope: !10, file: !11, line: 15, type: !17)
!22 = !DILocation(line: 15, column: 16, scope: !10)
!23 = !DILocation(line: 15, column: 46, scope: !10)
!24 = !DILocation(line: 15, column: 27, scope: !10)
!25 = !DILocalVariable(name: "sess_state", scope: !10, file: !11, line: 16, type: !17)
!26 = !DILocation(line: 16, column: 16, scope: !10)
!27 = !DILocation(line: 16, column: 47, scope: !10)
!28 = !DILocation(line: 16, column: 28, scope: !10)
!29 = !DILocalVariable(name: "peer_state", scope: !10, file: !11, line: 17, type: !17)
!30 = !DILocation(line: 17, column: 16, scope: !10)
!31 = !DILocation(line: 17, column: 47, scope: !10)
!32 = !DILocation(line: 17, column: 28, scope: !10)
!33 = !DILocation(line: 18, column: 15, scope: !10)
!34 = !DILocation(line: 18, column: 25, scope: !10)
!35 = !DILocation(line: 18, column: 3, scope: !10)
!36 = !DILocation(line: 19, column: 17, scope: !10)
!37 = !DILocation(line: 19, column: 27, scope: !10)
!38 = !DILocation(line: 19, column: 43, scope: !10)
!39 = !DILocation(line: 19, column: 46, scope: !10)
!40 = !DILocation(line: 19, column: 56, scope: !10)
!41 = !DILocation(line: 0, scope: !10)
!42 = !DILocation(line: 19, column: 15, scope: !10)
!43 = !DILocation(line: 19, column: 3, scope: !10)
!44 = !DILocation(line: 20, column: 17, scope: !10)
!45 = !DILocation(line: 20, column: 27, scope: !10)
!46 = !DILocation(line: 20, column: 45, scope: !10)
!47 = !DILocation(line: 20, column: 48, scope: !10)
!48 = !DILocation(line: 20, column: 58, scope: !10)
!49 = !DILocation(line: 20, column: 15, scope: !10)
!50 = !DILocation(line: 20, column: 3, scope: !10)
!51 = !DILocation(line: 21, column: 17, scope: !10)
!52 = !DILocation(line: 21, column: 27, scope: !10)
!53 = !DILocation(line: 21, column: 43, scope: !10)
!54 = !DILocation(line: 21, column: 46, scope: !10)
!55 = !DILocation(line: 21, column: 56, scope: !10)
!56 = !DILocation(line: 21, column: 15, scope: !10)
!57 = !DILocation(line: 21, column: 3, scope: !10)
!58 = !DILocation(line: 22, column: 16, scope: !10)
!59 = !DILocation(line: 22, column: 26, scope: !10)
!60 = !DILocation(line: 22, column: 42, scope: !10)
!61 = !DILocation(line: 22, column: 45, scope: !10)
!62 = !DILocation(line: 22, column: 55, scope: !10)
!63 = !DILocation(line: 22, column: 15, scope: !10)
!64 = !DILocation(line: 22, column: 77, scope: !10)
!65 = !DILocation(line: 22, column: 88, scope: !10)
!66 = !DILocation(line: 22, column: 104, scope: !10)
!67 = !DILocation(line: 22, column: 107, scope: !10)
!68 = !DILocation(line: 22, column: 118, scope: !10)
!69 = !DILocation(line: 22, column: 3, scope: !10)
!70 = !DILocation(line: 23, column: 3, scope: !71)
!71 = distinct !DILexicalBlock(scope: !72, file: !11, line: 23, column: 3)
!72 = distinct !DILexicalBlock(scope: !10, file: !11, line: 23, column: 3)
!73 = !DILocation(line: 23, column: 3, scope: !72)
!74 = !DILocation(line: 24, column: 3, scope: !10)
