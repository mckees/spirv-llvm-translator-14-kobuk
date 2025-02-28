; Test checks debug info of basic type is preserved during LLVM IR to spirv
; and spirv to LLVM IR translation.

; Original .cpp source:
;  int main() {
;    return 0;
;  }

; RUN: llvm-as %s -o %t.bc
; RUN: llvm-spirv %t.bc -spirv-text -o - | FileCheck %s --check-prefixes=CHECK-SPIRV,CHECK-SPIRV-OCL
; RUN: llvm-spirv %t.bc -o %t.spv
; RUN: llvm-spirv -r %t.spv -o %t.rev.bc
; RUN: llvm-dis %t.rev.bc -o %t.rev.ll
; RUN: FileCheck %s --input-file %t.rev.ll --check-prefix CHECK-LLVM

; RUN: llvm-spirv %t.bc -spirv-text --spirv-debug-info-version=nonsemantic-shader-100 -o - | FileCheck %s --check-prefixes=CHECK-SPIRV,CHECK-SPIRV-NONSEM
; RUN: llvm-spirv %t.bc --spirv-debug-info-version=nonsemantic-shader-100 -o %t.spv
; RUN: llvm-spirv -r %t.spv -o %t.rev.bc
; RUN: llvm-dis %t.rev.bc -o %t.rev.ll
; RUN: FileCheck %s --input-file %t.rev.ll --check-prefix CHECK-LLVM

; CHECK-LLVM: !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)

; CHECK-SPIRV: String [[#Name:]] "int"
; CHECK-SPIRV-NONSEM: Constant [[#]] [[#Encoding:]] 4
; CHECK-SPIRV: Constant [[#]] [[#Size:]] 32
; CHECK-SPIRV-OCL: DebugTypeBasic [[#Name]] [[#Size]] 4 {{$}}
; CHECK-SPIRV-NONSEM: [[#Flags:]] [[#]] DebugInfoNone
; CHECK-SPIRV-NONSEM: DebugTypeBasic [[#Name]] [[#Size]] [[#Encoding]] [[#Flags]] {{$}}

target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "spir64-unknown-unknown"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef i32 @_Z3foov() #0 !dbg !8 {
  ret i32 0, !dbg !14
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 14.0.0 (https://github.com/llvm/llvm-project.git 329fda39c507e8740978d10458451dcdb21563be)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/app/example.cpp", directory: "/app")
!2 = !{i32 7, !"Dwarf Version", i32 4}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"uwtable", i32 1}
!6 = !{i32 7, !"frame-pointer", i32 2}
!7 = !{!"clang version 14.0.0 (https://github.com/llvm/llvm-project.git 329fda39c507e8740978d10458451dcdb21563be)"}
!8 = distinct !DISubprogram(name: "foo", linkageName: "_Z3foov", scope: !9, file: !9, line: 1, type: !10, scopeLine: 1, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !13)
!9 = !DIFile(filename: "example.cpp", directory: "/app")
!10 = !DISubroutineType(types: !11)
!11 = !{!12}
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !{}
!14 = !DILocation(line: 1, column: 13, scope: !8)
