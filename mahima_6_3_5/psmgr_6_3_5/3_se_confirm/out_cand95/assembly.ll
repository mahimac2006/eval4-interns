; ModuleID = '/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand95.bc'
source_filename = "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand95_wmi2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"xfrm_type\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"enc_mode\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"param_max\00", align 1
@.str.3 = private unnamed_addr constant [23 x i8] c"param_max <= MAX_PARAM\00", align 1
@.str.4 = private unnamed_addr constant [125 x i8] c"/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand95_wmi2.c\00", align 1
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
  call void @klee_make_symbolic(i8* noundef %7, i64 noundef 4, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0)), !dbg !28
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
  %24 = icmp ne i32 %23, 1, !dbg !42
  br i1 %24, label %48, label %25, !dbg !43

25:                                               ; preds = %19
  %26 = load i32, i32* %3, align 4, !dbg !44
  %27 = icmp eq i32 %26, 1, !dbg !45
  br i1 %27, label %28, label %31, !dbg !46

28:                                               ; preds = %25
  %29 = load i32, i32* %4, align 4, !dbg !47
  %30 = icmp eq i32 %29, 63, !dbg !48
  br i1 %30, label %48, label %31, !dbg !49

31:                                               ; preds = %28, %25
  %32 = load i32, i32* %3, align 4, !dbg !50
  %33 = icmp eq i32 %32, 2, !dbg !51
  br i1 %33, label %34, label %37, !dbg !52

34:                                               ; preds = %31
  %35 = load i32, i32* %4, align 4, !dbg !53
  %36 = icmp eq i32 %35, 31, !dbg !54
  br i1 %36, label %48, label %37, !dbg !55

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
  %45 = icmp eq i32 %44, 15, !dbg !63
  br label %46

46:                                               ; preds = %43, %40, %37
  %47 = phi i1 [ false, %40 ], [ false, %37 ], [ %45, %43 ], !dbg !64
  br label %48, !dbg !55

48:                                               ; preds = %46, %34, %28, %19
  %49 = phi i1 [ true, %34 ], [ true, %28 ], [ true, %19 ], [ %47, %46 ]
  %50 = zext i1 %49 to i32, !dbg !55
  %51 = sext i32 %50 to i64, !dbg !65
  call void @klee_assume(i64 noundef %51), !dbg !66
  %52 = load i32, i32* %2, align 4, !dbg !67
  %53 = icmp ne i32 %52, 2, !dbg !68
  br i1 %53, label %54, label %57, !dbg !69

54:                                               ; preds = %48
  %55 = load i32, i32* %2, align 4, !dbg !70
  %56 = icmp ne i32 %55, 3, !dbg !71
  br i1 %56, label %80, label %57, !dbg !72

57:                                               ; preds = %54, %48
  %58 = load i32, i32* %3, align 4, !dbg !73
  %59 = icmp eq i32 %58, 1, !dbg !74
  br i1 %59, label %60, label %63, !dbg !75

60:                                               ; preds = %57
  %61 = load i32, i32* %4, align 4, !dbg !76
  %62 = icmp eq i32 %61, 127, !dbg !77
  br i1 %62, label %80, label %63, !dbg !78

63:                                               ; preds = %60, %57
  %64 = load i32, i32* %3, align 4, !dbg !79
  %65 = icmp eq i32 %64, 2, !dbg !80
  br i1 %65, label %66, label %69, !dbg !81

66:                                               ; preds = %63
  %67 = load i32, i32* %4, align 4, !dbg !82
  %68 = icmp eq i32 %67, 63, !dbg !83
  br i1 %68, label %80, label %69, !dbg !84

69:                                               ; preds = %66, %63
  %70 = load i32, i32* %3, align 4, !dbg !85
  %71 = icmp ne i32 %70, 1, !dbg !86
  br i1 %71, label %72, label %78, !dbg !87

72:                                               ; preds = %69
  %73 = load i32, i32* %3, align 4, !dbg !88
  %74 = icmp ne i32 %73, 2, !dbg !89
  br i1 %74, label %75, label %78, !dbg !90

75:                                               ; preds = %72
  %76 = load i32, i32* %4, align 4, !dbg !91
  %77 = icmp eq i32 %76, 31, !dbg !92
  br label %78

78:                                               ; preds = %75, %72, %69
  %79 = phi i1 [ false, %72 ], [ false, %69 ], [ %77, %75 ], !dbg !64
  br label %80, !dbg !84

80:                                               ; preds = %78, %66, %60, %54
  %81 = phi i1 [ true, %66 ], [ true, %60 ], [ true, %54 ], [ %79, %78 ]
  %82 = zext i1 %81 to i32, !dbg !84
  %83 = sext i32 %82 to i64, !dbg !93
  call void @klee_assume(i64 noundef %83), !dbg !94
  %84 = load i32, i32* %2, align 4, !dbg !95
  %85 = icmp ne i32 %84, 4, !dbg !96
  br i1 %85, label %109, label %86, !dbg !97

86:                                               ; preds = %80
  %87 = load i32, i32* %3, align 4, !dbg !98
  %88 = icmp eq i32 %87, 1, !dbg !99
  br i1 %88, label %89, label %92, !dbg !100

89:                                               ; preds = %86
  %90 = load i32, i32* %4, align 4, !dbg !101
  %91 = icmp eq i32 %90, 31, !dbg !102
  br i1 %91, label %109, label %92, !dbg !103

92:                                               ; preds = %89, %86
  %93 = load i32, i32* %3, align 4, !dbg !104
  %94 = icmp eq i32 %93, 2, !dbg !105
  br i1 %94, label %95, label %98, !dbg !106

95:                                               ; preds = %92
  %96 = load i32, i32* %4, align 4, !dbg !107
  %97 = icmp eq i32 %96, 15, !dbg !108
  br i1 %97, label %109, label %98, !dbg !109

98:                                               ; preds = %95, %92
  %99 = load i32, i32* %3, align 4, !dbg !110
  %100 = icmp ne i32 %99, 1, !dbg !111
  br i1 %100, label %101, label %107, !dbg !112

101:                                              ; preds = %98
  %102 = load i32, i32* %3, align 4, !dbg !113
  %103 = icmp ne i32 %102, 2, !dbg !114
  br i1 %103, label %104, label %107, !dbg !115

104:                                              ; preds = %101
  %105 = load i32, i32* %4, align 4, !dbg !116
  %106 = icmp eq i32 %105, 7, !dbg !117
  br label %107

107:                                              ; preds = %104, %101, %98
  %108 = phi i1 [ false, %101 ], [ false, %98 ], [ %106, %104 ], !dbg !64
  br label %109, !dbg !109

109:                                              ; preds = %107, %95, %89, %80
  %110 = phi i1 [ true, %95 ], [ true, %89 ], [ true, %80 ], [ %108, %107 ]
  %111 = zext i1 %110 to i32, !dbg !109
  %112 = sext i32 %111 to i64, !dbg !118
  call void @klee_assume(i64 noundef %112), !dbg !119
  %113 = load i32, i32* %4, align 4, !dbg !120
  %114 = icmp ule i32 %113, 127, !dbg !120
  br i1 %114, label %115, label %116, !dbg !123

115:                                              ; preds = %109
  br label %117, !dbg !123

116:                                              ; preds = %109
  call void @__assert_fail(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([125 x i8], [125 x i8]* @.str.4, i64 0, i64 0), i32 noundef 24, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #4, !dbg !120
  unreachable, !dbg !120

117:                                              ; preds = %115
  ret i32 0, !dbg !124
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
!1 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand95_wmi2.c", directory: "/home/mahima/eval4-main/stase3-main", checksumkind: CSK_MD5, checksum: "d5a91a84743651e22a8f86d3a6e4494f")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!10 = distinct !DISubprogram(name: "main", scope: !11, file: !11, line: 16, type: !12, scopeLine: 16, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DIFile(filename: "/tmp/claude-1000/-home-mahima-eval4-main/a348d2cf-cf87-4370-82e7-e7db81fe1239/scratchpad/se_psmgr/3_se_confirm/cand95_wmi2.c", directory: "", checksumkind: CSK_MD5, checksum: "d5a91a84743651e22a8f86d3a6e4494f")
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "xfrm_type", scope: !10, file: !11, line: 17, type: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DILocation(line: 17, column: 16, scope: !10)
!19 = !DILocation(line: 17, column: 46, scope: !10)
!20 = !DILocation(line: 17, column: 27, scope: !10)
!21 = !DILocalVariable(name: "enc_mode", scope: !10, file: !11, line: 18, type: !17)
!22 = !DILocation(line: 18, column: 16, scope: !10)
!23 = !DILocation(line: 18, column: 45, scope: !10)
!24 = !DILocation(line: 18, column: 26, scope: !10)
!25 = !DILocalVariable(name: "param_max", scope: !10, file: !11, line: 19, type: !17)
!26 = !DILocation(line: 19, column: 16, scope: !10)
!27 = !DILocation(line: 19, column: 46, scope: !10)
!28 = !DILocation(line: 19, column: 27, scope: !10)
!29 = !DILocation(line: 20, column: 15, scope: !10)
!30 = !DILocation(line: 20, column: 25, scope: !10)
!31 = !DILocation(line: 20, column: 41, scope: !10)
!32 = !DILocation(line: 20, column: 44, scope: !10)
!33 = !DILocation(line: 20, column: 54, scope: !10)
!34 = !DILocation(line: 20, column: 69, scope: !10)
!35 = !DILocation(line: 20, column: 72, scope: !10)
!36 = !DILocation(line: 20, column: 82, scope: !10)
!37 = !DILocation(line: 20, column: 98, scope: !10)
!38 = !DILocation(line: 20, column: 101, scope: !10)
!39 = !DILocation(line: 20, column: 111, scope: !10)
!40 = !DILocation(line: 20, column: 3, scope: !10)
!41 = !DILocation(line: 21, column: 16, scope: !10)
!42 = !DILocation(line: 21, column: 26, scope: !10)
!43 = !DILocation(line: 21, column: 43, scope: !10)
!44 = !DILocation(line: 21, column: 47, scope: !10)
!45 = !DILocation(line: 21, column: 56, scope: !10)
!46 = !DILocation(line: 21, column: 71, scope: !10)
!47 = !DILocation(line: 21, column: 74, scope: !10)
!48 = !DILocation(line: 21, column: 84, scope: !10)
!49 = !DILocation(line: 21, column: 91, scope: !10)
!50 = !DILocation(line: 21, column: 95, scope: !10)
!51 = !DILocation(line: 21, column: 104, scope: !10)
!52 = !DILocation(line: 21, column: 123, scope: !10)
!53 = !DILocation(line: 21, column: 126, scope: !10)
!54 = !DILocation(line: 21, column: 136, scope: !10)
!55 = !DILocation(line: 21, column: 143, scope: !10)
!56 = !DILocation(line: 21, column: 147, scope: !10)
!57 = !DILocation(line: 21, column: 156, scope: !10)
!58 = !DILocation(line: 21, column: 171, scope: !10)
!59 = !DILocation(line: 21, column: 174, scope: !10)
!60 = !DILocation(line: 21, column: 183, scope: !10)
!61 = !DILocation(line: 21, column: 202, scope: !10)
!62 = !DILocation(line: 21, column: 205, scope: !10)
!63 = !DILocation(line: 21, column: 215, scope: !10)
!64 = !DILocation(line: 0, scope: !10)
!65 = !DILocation(line: 21, column: 15, scope: !10)
!66 = !DILocation(line: 21, column: 3, scope: !10)
!67 = !DILocation(line: 22, column: 17, scope: !10)
!68 = !DILocation(line: 22, column: 27, scope: !10)
!69 = !DILocation(line: 22, column: 43, scope: !10)
!70 = !DILocation(line: 22, column: 47, scope: !10)
!71 = !DILocation(line: 22, column: 57, scope: !10)
!72 = !DILocation(line: 22, column: 75, scope: !10)
!73 = !DILocation(line: 22, column: 79, scope: !10)
!74 = !DILocation(line: 22, column: 88, scope: !10)
!75 = !DILocation(line: 22, column: 103, scope: !10)
!76 = !DILocation(line: 22, column: 106, scope: !10)
!77 = !DILocation(line: 22, column: 116, scope: !10)
!78 = !DILocation(line: 22, column: 124, scope: !10)
!79 = !DILocation(line: 22, column: 128, scope: !10)
!80 = !DILocation(line: 22, column: 137, scope: !10)
!81 = !DILocation(line: 22, column: 156, scope: !10)
!82 = !DILocation(line: 22, column: 159, scope: !10)
!83 = !DILocation(line: 22, column: 169, scope: !10)
!84 = !DILocation(line: 22, column: 176, scope: !10)
!85 = !DILocation(line: 22, column: 180, scope: !10)
!86 = !DILocation(line: 22, column: 189, scope: !10)
!87 = !DILocation(line: 22, column: 204, scope: !10)
!88 = !DILocation(line: 22, column: 207, scope: !10)
!89 = !DILocation(line: 22, column: 216, scope: !10)
!90 = !DILocation(line: 22, column: 235, scope: !10)
!91 = !DILocation(line: 22, column: 238, scope: !10)
!92 = !DILocation(line: 22, column: 248, scope: !10)
!93 = !DILocation(line: 22, column: 15, scope: !10)
!94 = !DILocation(line: 22, column: 3, scope: !10)
!95 = !DILocation(line: 23, column: 16, scope: !10)
!96 = !DILocation(line: 23, column: 26, scope: !10)
!97 = !DILocation(line: 23, column: 42, scope: !10)
!98 = !DILocation(line: 23, column: 46, scope: !10)
!99 = !DILocation(line: 23, column: 55, scope: !10)
!100 = !DILocation(line: 23, column: 70, scope: !10)
!101 = !DILocation(line: 23, column: 73, scope: !10)
!102 = !DILocation(line: 23, column: 83, scope: !10)
!103 = !DILocation(line: 23, column: 90, scope: !10)
!104 = !DILocation(line: 23, column: 94, scope: !10)
!105 = !DILocation(line: 23, column: 103, scope: !10)
!106 = !DILocation(line: 23, column: 122, scope: !10)
!107 = !DILocation(line: 23, column: 125, scope: !10)
!108 = !DILocation(line: 23, column: 135, scope: !10)
!109 = !DILocation(line: 23, column: 142, scope: !10)
!110 = !DILocation(line: 23, column: 146, scope: !10)
!111 = !DILocation(line: 23, column: 155, scope: !10)
!112 = !DILocation(line: 23, column: 170, scope: !10)
!113 = !DILocation(line: 23, column: 173, scope: !10)
!114 = !DILocation(line: 23, column: 182, scope: !10)
!115 = !DILocation(line: 23, column: 201, scope: !10)
!116 = !DILocation(line: 23, column: 204, scope: !10)
!117 = !DILocation(line: 23, column: 214, scope: !10)
!118 = !DILocation(line: 23, column: 15, scope: !10)
!119 = !DILocation(line: 23, column: 3, scope: !10)
!120 = !DILocation(line: 24, column: 3, scope: !121)
!121 = distinct !DILexicalBlock(scope: !122, file: !11, line: 24, column: 3)
!122 = distinct !DILexicalBlock(scope: !10, file: !11, line: 24, column: 3)
!123 = !DILocation(line: 24, column: 3, scope: !122)
!124 = !DILocation(line: 25, column: 3, scope: !10)
