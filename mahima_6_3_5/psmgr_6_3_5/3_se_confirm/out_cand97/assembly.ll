; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand97.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand97_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"xfrm_type\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"enc_mode\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"proc_param\00", align 1
@.str.3 = private unnamed_addr constant [31 x i8] c"proc_param <= PARAM_MAX_GLOBAL\00", align 1
@.str.4 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand97_wmi2.c\00", align 1
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
  call void @klee_make_symbolic(i8* noundef %5, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0)), !dbg !20
  call void @llvm.dbg.declare(metadata i32* %3, metadata !21, metadata !DIExpression()), !dbg !22
  %6 = bitcast i32* %3 to i8*, !dbg !23
  call void @klee_make_symbolic(i8* noundef %6, i64 noundef 4, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.1, i64 0, i64 0)), !dbg !24
  call void @llvm.dbg.declare(metadata i32* %4, metadata !25, metadata !DIExpression()), !dbg !26
  %7 = bitcast i32* %4 to i8*, !dbg !27
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)), !dbg !28
  %8 = load i32, i32* %2, align 4, !dbg !29
  %9 = icmp eq i32 %8, 1, !dbg !30
  br i1 %9, label %19, label %10, !dbg !31

10:                                               ; preds = %0
  %11 = load i32, i32* %2, align 4, !dbg !32
  %12 = icmp eq i32 %11, 2, !dbg !33
  br i1 %12, label %19, label %13, !dbg !34

13:                                               ; preds = %10
  %14 = load i32, i32* %2, align 4, !dbg !35
  %15 = icmp eq i32 %14, 3, !dbg !36
  br i1 %15, label %19, label %16, !dbg !37

16:                                               ; preds = %13
  %17 = load i32, i32* %2, align 4, !dbg !38
  %18 = icmp eq i32 %17, 4, !dbg !39
  br label %19, !dbg !37

19:                                               ; preds = %16, %13, %10, %0
  %20 = phi i1 [ true, %13 ], [ true, %10 ], [ true, %0 ], [ %18, %16 ]
  %21 = zext i1 %20 to i32, !dbg !37
  %22 = sext i32 %21 to i64, !dbg !29
  call void @klee_assume(i64 noundef %22), !dbg !40
  %23 = load i32, i32* %2, align 4, !dbg !41
  %24 = icmp eq i32 %23, 1, !dbg !42
  br i1 %24, label %25, label %46, !dbg !43

25:                                               ; preds = %19
  %26 = load i32, i32* %3, align 4, !dbg !44
  %27 = icmp eq i32 %26, 1, !dbg !45
  br i1 %27, label %28, label %31, !dbg !46

28:                                               ; preds = %25
  %29 = load i32, i32* %4, align 4, !dbg !47
  %30 = icmp ule i32 %29, 63, !dbg !48
  br i1 %30, label %103, label %31, !dbg !49

31:                                               ; preds = %28, %25
  %32 = load i32, i32* %3, align 4, !dbg !50
  %33 = icmp eq i32 %32, 2, !dbg !51
  br i1 %33, label %34, label %37, !dbg !52

34:                                               ; preds = %31
  %35 = load i32, i32* %4, align 4, !dbg !53
  %36 = icmp ule i32 %35, 31, !dbg !54
  br i1 %36, label %103, label %37, !dbg !55

37:                                               ; preds = %34, %31
  %38 = load i32, i32* %3, align 4, !dbg !56
  %39 = icmp ne i32 %38, 1, !dbg !57
  br i1 %39, label %40, label %46, !dbg !58

40:                                               ; preds = %37
  %41 = load i32, i32* %3, align 4, !dbg !59
  %42 = icmp ne i32 %41, 2, !dbg !60
  br i1 %42, label %43, label %46, !dbg !61

43:                                               ; preds = %40
  %44 = load i32, i32* %4, align 4, !dbg !62
  %45 = icmp ule i32 %44, 15, !dbg !63
  br i1 %45, label %103, label %46, !dbg !64

46:                                               ; preds = %43, %40, %37, %19
  %47 = load i32, i32* %2, align 4, !dbg !65
  %48 = icmp eq i32 %47, 2, !dbg !66
  br i1 %48, label %52, label %49, !dbg !67

49:                                               ; preds = %46
  %50 = load i32, i32* %2, align 4, !dbg !68
  %51 = icmp eq i32 %50, 3, !dbg !69
  br i1 %51, label %52, label %73, !dbg !70

52:                                               ; preds = %49, %46
  %53 = load i32, i32* %3, align 4, !dbg !71
  %54 = icmp eq i32 %53, 1, !dbg !72
  br i1 %54, label %55, label %58, !dbg !73

55:                                               ; preds = %52
  %56 = load i32, i32* %4, align 4, !dbg !74
  %57 = icmp ule i32 %56, 127, !dbg !75
  br i1 %57, label %103, label %58, !dbg !76

58:                                               ; preds = %55, %52
  %59 = load i32, i32* %3, align 4, !dbg !77
  %60 = icmp eq i32 %59, 2, !dbg !78
  br i1 %60, label %61, label %64, !dbg !79

61:                                               ; preds = %58
  %62 = load i32, i32* %4, align 4, !dbg !80
  %63 = icmp ule i32 %62, 63, !dbg !81
  br i1 %63, label %103, label %64, !dbg !82

64:                                               ; preds = %61, %58
  %65 = load i32, i32* %3, align 4, !dbg !83
  %66 = icmp ne i32 %65, 1, !dbg !84
  br i1 %66, label %67, label %73, !dbg !85

67:                                               ; preds = %64
  %68 = load i32, i32* %3, align 4, !dbg !86
  %69 = icmp ne i32 %68, 2, !dbg !87
  br i1 %69, label %70, label %73, !dbg !88

70:                                               ; preds = %67
  %71 = load i32, i32* %4, align 4, !dbg !89
  %72 = icmp ule i32 %71, 31, !dbg !90
  br i1 %72, label %103, label %73, !dbg !91

73:                                               ; preds = %70, %67, %64, %49
  %74 = load i32, i32* %2, align 4, !dbg !92
  %75 = icmp eq i32 %74, 4, !dbg !93
  br i1 %75, label %76, label %101, !dbg !94

76:                                               ; preds = %73
  %77 = load i32, i32* %3, align 4, !dbg !95
  %78 = icmp eq i32 %77, 1, !dbg !96
  br i1 %78, label %79, label %82, !dbg !97

79:                                               ; preds = %76
  %80 = load i32, i32* %4, align 4, !dbg !98
  %81 = icmp ule i32 %80, 31, !dbg !99
  br i1 %81, label %99, label %82, !dbg !100

82:                                               ; preds = %79, %76
  %83 = load i32, i32* %3, align 4, !dbg !101
  %84 = icmp eq i32 %83, 2, !dbg !102
  br i1 %84, label %85, label %88, !dbg !103

85:                                               ; preds = %82
  %86 = load i32, i32* %4, align 4, !dbg !104
  %87 = icmp ule i32 %86, 15, !dbg !105
  br i1 %87, label %99, label %88, !dbg !106

88:                                               ; preds = %85, %82
  %89 = load i32, i32* %3, align 4, !dbg !107
  %90 = icmp ne i32 %89, 1, !dbg !108
  br i1 %90, label %91, label %97, !dbg !109

91:                                               ; preds = %88
  %92 = load i32, i32* %3, align 4, !dbg !110
  %93 = icmp ne i32 %92, 2, !dbg !111
  br i1 %93, label %94, label %97, !dbg !112

94:                                               ; preds = %91
  %95 = load i32, i32* %4, align 4, !dbg !113
  %96 = icmp ule i32 %95, 7, !dbg !114
  br label %97

97:                                               ; preds = %94, %91, %88
  %98 = phi i1 [ false, %91 ], [ false, %88 ], [ %96, %94 ], !dbg !115
  br label %99, !dbg !106

99:                                               ; preds = %97, %85, %79
  %100 = phi i1 [ true, %85 ], [ true, %79 ], [ %98, %97 ]
  br label %101

101:                                              ; preds = %99, %73
  %102 = phi i1 [ false, %73 ], [ %100, %99 ], !dbg !115
  br label %103, !dbg !91

103:                                              ; preds = %101, %70, %61, %55, %43, %34, %28
  %104 = phi i1 [ true, %70 ], [ true, %61 ], [ true, %55 ], [ true, %43 ], [ true, %34 ], [ true, %28 ], [ %102, %101 ]
  %105 = zext i1 %104 to i32, !dbg !91
  %106 = sext i32 %105 to i64, !dbg !116
  call void @klee_assume(i64 noundef %106), !dbg !117
  %107 = load i32, i32* %4, align 4, !dbg !118
  %108 = icmp ule i32 %107, 127, !dbg !118
  br i1 %108, label %109, label %110, !dbg !121

109:                                              ; preds = %103
  br label %111, !dbg !121

110:                                              ; preds = %103
  call void @__assert_fail(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.4, i64 0, i64 0), i32 noundef 31, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !118
  unreachable, !dbg !118

111:                                              ; preds = %109
  ret i32 0, !dbg !122
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand97_wmi2.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "c7635ca2d73fcec0065dc472f59aebed")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 25, type: !12, scopeLine: 25, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand97_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "c7635ca2d73fcec0065dc472f59aebed")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "xfrm_type", scope: !10, file: !11, line: 26, type: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 26, column: 16, scope: !10)
!19 = !DILocation(line: 26, column: 46, scope: !10)
!20 = !DILocation(line: 26, column: 27, scope: !10)
!21 = !DILocalVariable(name: "enc_mode", scope: !10, file: !11, line: 27, type: !17)
!22 = !DILocation(line: 27, column: 16, scope: !10)
!23 = !DILocation(line: 27, column: 45, scope: !10)
!24 = !DILocation(line: 27, column: 26, scope: !10)
!25 = !DILocalVariable(name: "proc_param", scope: !10, file: !11, line: 28, type: !17)
!26 = !DILocation(line: 28, column: 16, scope: !10)
!27 = !DILocation(line: 28, column: 47, scope: !10)
!28 = !DILocation(line: 28, column: 28, scope: !10)
!29 = !DILocation(line: 29, column: 15, scope: !10)
!30 = !DILocation(line: 29, column: 25, scope: !10)
!31 = !DILocation(line: 29, column: 41, scope: !10)
!32 = !DILocation(line: 29, column: 44, scope: !10)
!33 = !DILocation(line: 29, column: 54, scope: !10)
!34 = !DILocation(line: 29, column: 69, scope: !10)
!35 = !DILocation(line: 29, column: 72, scope: !10)
!36 = !DILocation(line: 29, column: 82, scope: !10)
!37 = !DILocation(line: 29, column: 98, scope: !10)
!38 = !DILocation(line: 29, column: 101, scope: !10)
!39 = !DILocation(line: 29, column: 111, scope: !10)
!40 = !DILocation(line: 29, column: 3, scope: !10)
!41 = !DILocation(line: 30, column: 16, scope: !10)
!42 = !DILocation(line: 30, column: 26, scope: !10)
!43 = !DILocation(line: 30, column: 42, scope: !10)
!44 = !DILocation(line: 30, column: 47, scope: !10)
!45 = !DILocation(line: 30, column: 56, scope: !10)
!46 = !DILocation(line: 30, column: 71, scope: !10)
!47 = !DILocation(line: 30, column: 74, scope: !10)
!48 = !DILocation(line: 30, column: 85, scope: !10)
!49 = !DILocation(line: 30, column: 108, scope: !10)
!50 = !DILocation(line: 30, column: 112, scope: !10)
!51 = !DILocation(line: 30, column: 121, scope: !10)
!52 = !DILocation(line: 30, column: 140, scope: !10)
!53 = !DILocation(line: 30, column: 143, scope: !10)
!54 = !DILocation(line: 30, column: 154, scope: !10)
!55 = !DILocation(line: 30, column: 181, scope: !10)
!56 = !DILocation(line: 30, column: 185, scope: !10)
!57 = !DILocation(line: 30, column: 194, scope: !10)
!58 = !DILocation(line: 30, column: 209, scope: !10)
!59 = !DILocation(line: 30, column: 212, scope: !10)
!60 = !DILocation(line: 30, column: 221, scope: !10)
!61 = !DILocation(line: 30, column: 240, scope: !10)
!62 = !DILocation(line: 30, column: 243, scope: !10)
!63 = !DILocation(line: 30, column: 254, scope: !10)
!64 = !DILocation(line: 30, column: 278, scope: !10)
!65 = !DILocation(line: 30, column: 283, scope: !10)
!66 = !DILocation(line: 30, column: 293, scope: !10)
!67 = !DILocation(line: 30, column: 308, scope: !10)
!68 = !DILocation(line: 30, column: 311, scope: !10)
!69 = !DILocation(line: 30, column: 321, scope: !10)
!70 = !DILocation(line: 30, column: 338, scope: !10)
!71 = !DILocation(line: 30, column: 343, scope: !10)
!72 = !DILocation(line: 30, column: 352, scope: !10)
!73 = !DILocation(line: 30, column: 367, scope: !10)
!74 = !DILocation(line: 30, column: 370, scope: !10)
!75 = !DILocation(line: 30, column: 381, scope: !10)
!76 = !DILocation(line: 30, column: 403, scope: !10)
!77 = !DILocation(line: 30, column: 407, scope: !10)
!78 = !DILocation(line: 30, column: 416, scope: !10)
!79 = !DILocation(line: 30, column: 435, scope: !10)
!80 = !DILocation(line: 30, column: 438, scope: !10)
!81 = !DILocation(line: 30, column: 449, scope: !10)
!82 = !DILocation(line: 30, column: 475, scope: !10)
!83 = !DILocation(line: 30, column: 479, scope: !10)
!84 = !DILocation(line: 30, column: 488, scope: !10)
!85 = !DILocation(line: 30, column: 503, scope: !10)
!86 = !DILocation(line: 30, column: 506, scope: !10)
!87 = !DILocation(line: 30, column: 515, scope: !10)
!88 = !DILocation(line: 30, column: 534, scope: !10)
!89 = !DILocation(line: 30, column: 537, scope: !10)
!90 = !DILocation(line: 30, column: 548, scope: !10)
!91 = !DILocation(line: 30, column: 571, scope: !10)
!92 = !DILocation(line: 30, column: 575, scope: !10)
!93 = !DILocation(line: 30, column: 585, scope: !10)
!94 = !DILocation(line: 30, column: 600, scope: !10)
!95 = !DILocation(line: 30, column: 605, scope: !10)
!96 = !DILocation(line: 30, column: 614, scope: !10)
!97 = !DILocation(line: 30, column: 629, scope: !10)
!98 = !DILocation(line: 30, column: 632, scope: !10)
!99 = !DILocation(line: 30, column: 643, scope: !10)
!100 = !DILocation(line: 30, column: 665, scope: !10)
!101 = !DILocation(line: 30, column: 669, scope: !10)
!102 = !DILocation(line: 30, column: 678, scope: !10)
!103 = !DILocation(line: 30, column: 697, scope: !10)
!104 = !DILocation(line: 30, column: 700, scope: !10)
!105 = !DILocation(line: 30, column: 711, scope: !10)
!106 = !DILocation(line: 30, column: 737, scope: !10)
!107 = !DILocation(line: 30, column: 741, scope: !10)
!108 = !DILocation(line: 30, column: 750, scope: !10)
!109 = !DILocation(line: 30, column: 765, scope: !10)
!110 = !DILocation(line: 30, column: 768, scope: !10)
!111 = !DILocation(line: 30, column: 777, scope: !10)
!112 = !DILocation(line: 30, column: 796, scope: !10)
!113 = !DILocation(line: 30, column: 799, scope: !10)
!114 = !DILocation(line: 30, column: 810, scope: !10)
!115 = !DILocation(line: 0, scope: !10)
!116 = !DILocation(line: 30, column: 15, scope: !10)
!117 = !DILocation(line: 30, column: 3, scope: !10)
!118 = !DILocation(line: 31, column: 3, scope: !119)
!119 = distinct !DILexicalBlock(scope: !120, file: !11, line: 31, column: 3)
!120 = distinct !DILexicalBlock(scope: !10, file: !11, line: 31, column: 3)
!121 = !DILocation(line: 31, column: 3, scope: !120)
!122 = !DILocation(line: 32, column: 3, scope: !10)
