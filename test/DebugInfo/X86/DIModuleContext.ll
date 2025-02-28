; RUN: llvm-as < %s -o %t.bc
; RUN: llvm-spirv --spirv-ext=+SPV_INTEL_debug_module %t.bc -o %t.spv
; RUN: llvm-spirv -r %t.spv -o - | llvm-dis -o %t.ll

; RUN: llvm-spirv --spirv-ext=+SPV_INTEL_debug_module %t.bc -o %t.spv --spirv-debug-info-version=nonsemantic-shader-100
; RUN: llvm-spirv -r %t.spv -o - | llvm-dis -o %t.ll
; RUN: llc -mtriple=x86_64-apple-macosx %t.ll -o - -filetype=obj \
; RUN:   | llvm-dwarfdump -debug-info - | FileCheck %s

; RUN: llvm-spirv %t.bc -o %t.spv --spirv-debug-info-version=nonsemantic-shader-200
; RUN: llvm-spirv -r %t.spv -o - | llvm-dis -o %t.ll
; RUN: llc -mtriple=x86_64-apple-macosx %t.ll -o - -filetype=obj \
; RUN:   | llvm-dwarfdump -debug-info - | FileCheck %s
; CHECK: DW_TAG_module
; CHECK-NOT: NULL
; CHECK: DW_TAG_structure_type

; Hand-crafted based on
; struct s;
; struct s *s;

source_filename = "test/DebugInfo/X86/DIModuleContext.ll"
target triple = "spir64-unknown-unknown"

%struct.s = type opaque

@i = common addrspace(1) global %struct.s* null, align 8, !dbg !0

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!11, !12}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = !DIGlobalVariable(name: "s", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, imports: !6)
!3 = !DIFile(filename: "test.c", directory: "/")
!4 = !{}
!5 = !{!0}
!6 = !{!7}
!7 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !2, entity: !8, file: !3, line: 11)
!8 = !DIModule(scope: null, name: "Module", includePath: ".")
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "s", scope: !8, file: !3, line: 1, flags: DIFlagFwdDecl)
!11 = !{i32 2, !"Dwarf Version", i32 2}
!12 = !{i32 2, !"Debug Info Version", i32 3}

