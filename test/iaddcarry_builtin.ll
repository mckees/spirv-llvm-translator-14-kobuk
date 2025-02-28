; REQUIRES: spirv-dis
; RUN: llvm-as %s -o %t.bc
; RUN: llvm-spirv %t.bc -o %t.spv
; RUN: spirv-dis --raw-id %t.spv | FileCheck --check-prefix CHECK-SPIRV %s
; RUN: spirv-val %t.spv
; RUN: llvm-spirv -r %t.spv -o %t.rev.bc
; RUN: llvm-dis %t.rev.bc -o - | FileCheck --check-prefix CHECK-LLVM %s

target triple = "spir64-unknown-unknown"

%i8struct = type {i8, i8}
%i16struct = type {i16, i16}
%i32struct = type {i32, i32}
%i64struct = type {i64, i64}
%vecstruct = type {<4 x i32>, <4 x i32>}

; CHECK-SPIRV-DAG:                     [[uchar:%[a-z0-9_]+]] = OpTypeInt 8
; CHECK-SPIRV-DAG:                    [[ushort:%[a-z0-9_]+]] = OpTypeInt 16
; CHECK-SPIRV-DAG:                      [[uint:%[a-z0-9_]+]] = OpTypeInt 32
; CHECK-SPIRV-DAG:                     [[ulong:%[a-z0-9_]+]] = OpTypeInt 64
; CHECK-SPIRV-DAG:                      [[void:%[a-z0-9_]+]] = OpTypeVoid
; CHECK-SPIRV-DAG:                  [[i8struct:%[a-z0-9_]+]] = OpTypeStruct [[uchar]] [[uchar]]
; CHECK-SPIRV-DAG:    [[_ptr_Function_i8struct:%[a-z0-9_]+]] = OpTypePointer Function [[i8struct]]
; CHECK-SPIRV-DAG:                 [[i16struct:%[a-z0-9_]+]] = OpTypeStruct [[ushort]] [[ushort]]
; CHECK-SPIRV-DAG:   [[_ptr_Function_i16struct:%[a-z0-9_]+]] = OpTypePointer Function [[i16struct]]
; CHECK-SPIRV-DAG:                 [[i32struct:%[a-z0-9_]+]] = OpTypeStruct [[uint]] [[uint]]
; CHECK-SPIRV-DAG:   [[_ptr_Function_i32struct:%[a-z0-9_]+]] = OpTypePointer Function [[i32struct]]
; CHECK-SPIRV-DAG:                 [[i64struct:%[a-z0-9_]+]] = OpTypeStruct [[ulong]] [[ulong]]
; CHECK-SPIRV-DAG:   [[_ptr_Function_i64struct:%[a-z0-9_]+]] = OpTypePointer Function [[i64struct]]
; CHECK-SPIRV-DAG:                    [[v4uint:%[a-z0-9_]+]] = OpTypeVector [[uint]] 4
; CHECK-SPIRV-DAG:                 [[vecstruct:%[a-z0-9_]+]] = OpTypeStruct [[v4uint]] [[v4uint]]
; CHECK-SPIRV-DAG:   [[_ptr_Function_vecstruct:%[a-z0-9_]+]] = OpTypePointer Function [[vecstruct]]
; CHECK-SPIRV-DAG:               [[struct_anon:%[a-z0-9_.]+]] = OpTypeStruct [[uint]] [[uint]]
; CHECK-SPIRV-DAG: [[_ptr_Function_struct_anon:%[a-z0-9_]+]] = OpTypePointer Function [[struct_anon]]
; CHECK-SPIRV-DAG:  [[_ptr_Generic_struct_anon:%[a-z0-9_]+]] = OpTypePointer Generic [[struct_anon]]

; CHECK-LLVM-DAG: [[i8struct:%[a-z0-9_.]+]] = type { i8, i8 }
; CHECK-LLVM-DAG: [[i16struct:%[a-z0-9_.]+]] = type { i16, i16 }
; CHECK-LLVM-DAG: [[i32struct:%[a-z0-9_.]+]] = type { i32, i32 }
; CHECK-LLVM-DAG: [[i64struct:%[a-z0-9_.]+]] = type { i64, i64 }
; CHECK-LLVM-DAG: [[vecstruct:%[a-z0-9_.]+]] = type { <4 x i32>, <4 x i32> }
; CHECK-LLVM-DAG: [[struct_anon:%[a-z0-9_.]+]] = type { i32, i32 }

define spir_func void @test_builtin_iaddcarrycc(i8 %a, i8 %b) {
  entry:
  %0 = alloca %i8struct
  call void @_Z17__spirv_IAddCarrycc(%i8struct* %0, i8 %a, i8 %b)
  ret void
}

; CHECK-SPIRV:           [[a:%[a-z0-9_]+]] = OpFunctionParameter [[uchar]]
; CHECK-SPIRV:           [[b:%[a-z0-9_]+]] = OpFunctionParameter [[uchar]]
; CHECK-SPIRV:       [[entry:%[a-z0-9_]+]] = OpLabel
; CHECK-SPIRV:      [[var_11:%[a-z0-9_]+]] = OpVariable [[_ptr_Function_i8struct]] Function
; CHECK-SPIRV:      [[var_12:%[a-z0-9_]+]] = OpIAddCarry [[i8struct]] [[a]] [[b]]
; CHECK-SPIRV:                               OpStore [[var_11]] [[var_12]] 
; CHECK-SPIRV:                               OpReturn
; CHECK-SPIRV:                               OpFunctionEnd

; CHECK-LLVM:   %0 = alloca [[i8struct]], align 8
; CHECK-LLVM:   call spir_func void @_Z17__spirv_IAddCarrycc([[i8struct]]* sret([[i8struct]]) %0, i8 %a, i8 %b)
; CHECK-LLVM:   ret void
define spir_func void @test_builtin_iaddcarryss(i16 %a, i16 %b) {
  entry:
  %0 = alloca %i16struct
  call void @_Z17__spirv_IAddCarryss(%i16struct* %0, i16 %a, i16 %b)
  ret void
}
; CHECK-SPIRV:         [[a_0:%[a-z0-9_]+]] = OpFunctionParameter [[ushort]]
; CHECK-SPIRV:         [[b_0:%[a-z0-9_]+]] = OpFunctionParameter [[ushort]]
; CHECK-SPIRV:     [[entry_0:%[a-z0-9_]+]] = OpLabel
; CHECK-SPIRV:      [[var_21:%[a-z0-9_]+]] = OpVariable [[_ptr_Function_i16struct]] Function
; CHECK-SPIRV:      [[var_22:%[a-z0-9_]+]] = OpIAddCarry [[i16struct]] [[a_0]] [[b_0]]
; CHECK-SPIRV:                               OpStore [[var_21]] [[var_22]] 
; CHECK-SPIRV:                               OpReturn
; CHECK-SPIRV:                               OpFunctionEnd

; CHECK-LLVM:   %0 = alloca [[i16struct]], align 8
; CHECK-LLVM:   call spir_func void @_Z17__spirv_IAddCarryss([[i16struct]]* sret([[i16struct]]) %0, i16 %a, i16 %b)
; CHECK-LLVM:   ret void
define spir_func void @test_builtin_iaddcarryii(i32 %a, i32 %b) {
  entry:
  %0 = alloca %i32struct
  call void @_Z17__spirv_IAddCarryii(%i32struct* %0, i32 %a, i32 %b)
  ret void
}
; CHECK-SPIRV:         [[a_1:%[a-z0-9_]+]] = OpFunctionParameter [[uint]]
; CHECK-SPIRV:         [[b_1:%[a-z0-9_]+]] = OpFunctionParameter [[uint]]
; CHECK-SPIRV:     [[entry_1:%[a-z0-9_]+]] = OpLabel
; CHECK-SPIRV:      [[var_31:%[a-z0-9_]+]] = OpVariable [[_ptr_Function_i32struct]] Function
; CHECK-SPIRV:      [[var_32:%[a-z0-9_]+]] = OpIAddCarry [[i32struct]] [[a_1]] [[b_1]]
; CHECK-SPIRV:                               OpStore [[var_31]] [[var_32]] 
; CHECK-SPIRV:                               OpReturn
; CHECK-SPIRV:                               OpFunctionEnd

; CHECK-LLVM:   %0 = alloca [[i32struct]], align 8
; CHECK-LLVM:   call spir_func void @_Z17__spirv_IAddCarryii([[i32struct]]* sret([[i32struct]]) %0, i32 %a, i32 %b)
; CHECK-LLVM:   ret void
define spir_func void @test_builtin_iaddcarryll(i64 %a, i64 %b) {
  entry:
  %0 = alloca %i64struct
  call void @_Z17__spirv_IAddCarryll(%i64struct* %0, i64 %a, i64 %b)
  ret void
}
; CHECK-SPIRV:         [[a_2:%[a-z0-9_]+]] = OpFunctionParameter [[ulong]]
; CHECK-SPIRV:         [[b_2:%[a-z0-9_]+]] = OpFunctionParameter [[ulong]]
; CHECK-SPIRV:     [[entry_2:%[a-z0-9_]+]] = OpLabel
; CHECK-SPIRV:      [[var_41:%[a-z0-9_]+]] = OpVariable [[_ptr_Function_i64struct]] Function
; CHECK-SPIRV:      [[var_42:%[a-z0-9_]+]] = OpIAddCarry [[i64struct]] [[a_2]] [[b_2]]
; CHECK-SPIRV:                               OpStore [[var_41]] [[var_42]] 
; CHECK-SPIRV:                               OpReturn
; CHECK-SPIRV:                               OpFunctionEnd

; CHECK-LLVM:   %0 = alloca [[i64struct]]
; CHECK-LLVM:   call spir_func void @_Z17__spirv_IAddCarryll([[i64struct]]* sret([[i64struct]]) %0, i64 %a, i64 %b)
; CHECK-LLVM:   ret void
define spir_func void @test_builtin_iaddcarryDv4_xS_(<4 x i32> %a, <4 x i32> %b) {
  entry:
  %0 = alloca %vecstruct
  call void @_Z17__spirv_IAddCarryDv4_iS_(%vecstruct* %0, <4 x i32> %a, <4 x i32> %b)
  ret void
}
; CHECK-SPIRV:         [[a_3:%[a-z0-9_]+]] = OpFunctionParameter [[v4uint]]
; CHECK-SPIRV:         [[b_3:%[a-z0-9_]+]] = OpFunctionParameter [[v4uint]]
; CHECK-SPIRV:     [[entry_3:%[a-z0-9_]+]] = OpLabel
; CHECK-SPIRV:      [[var_51:%[a-z0-9_]+]] = OpVariable [[_ptr_Function_vecstruct]] Function
; CHECK-SPIRV:      [[var_52:%[a-z0-9_]+]] = OpIAddCarry [[vecstruct]] [[a_3]] [[b_3]]
; CHECK-SPIRV:                               OpStore [[var_51]] [[var_52]] 
; CHECK-SPIRV:                               OpReturn
; CHECK-SPIRV:                               OpFunctionEnd

; CHECK-LLVM:   %0 = alloca [[vecstruct]]
; CHECK-LLVM:   call spir_func void @_Z17__spirv_IAddCarryDv4_iS_([[vecstruct]]* sret([[vecstruct]]) %0, <4 x i32> %a, <4 x i32> %b)
; CHECK-LLVM:   ret void

%struct.anon = type { i32, i32 }

define spir_func void @test_builtin_iaddcarry_anon(i32 %a, i32 %b) {
  entry:
  %0 = alloca %struct.anon
  %1 = addrspacecast %struct.anon* %0 to %struct.anon addrspace(4)*
  call spir_func void @_Z17__spirv_IAddCarryIiiE4anonIT_T0_ES1_S2_(%struct.anon addrspace(4)* %1, i32 %a, i32 %b)
  ret void
}
; CHECK-SPIRV:        [[a_4:%[a-z0-9_]+]] = OpFunctionParameter [[uint]]
; CHECK-SPIRV:        [[b_4:%[a-z0-9_]+]] = OpFunctionParameter [[uint]]
; CHECK-SPIRV:    [[entry_4:%[a-z0-9_]+]] = OpLabel
; CHECK-SPIRV:     [[var_59:%[a-z0-9_]+]] = OpVariable [[_ptr_Function_struct_anon]] Function
; CHECK-SPIRV:     [[var_61:%[a-z0-9_]+]] = OpPtrCastToGeneric [[_ptr_Generic_struct_anon]] [[var_59]]
; CHECK-SPIRV:     [[var_62:%[a-z0-9_]+]] = OpIAddCarry [[struct_anon]] [[a_4]] [[b_4]]
; CHECK-SPIRV:                              OpStore [[var_61]] [[var_62]]

; CHECK-LLVM:  %0 = alloca [[struct_anon]], align 8
; CHECK-LLVM:  %1 = addrspacecast [[struct_anon]]* %0 to [[struct_anon]] addrspace(4)*
; CHECK-LLVM:  call spir_func void @_Z17__spirv_IAddCarryii.1([[struct_anon]] addrspace(4)* sret([[struct_anon]]) %1, i32 %a, i32 %b)
; CHECK-LLVM:  ret void

declare void @_Z17__spirv_IAddCarryIiiE4anonIT_T0_ES1_S2_(%struct.anon addrspace(4)*, i32, i32)
declare void @_Z17__spirv_IAddCarrycc(%i8struct*, i8, i8)
declare void @_Z17__spirv_IAddCarryss(%i16struct*, i16, i16)
declare void @_Z17__spirv_IAddCarryii(%i32struct*, i32, i32)
declare void @_Z17__spirv_IAddCarryll(%i64struct*, i64, i64)
declare void @_Z17__spirv_IAddCarryDv4_iS_(%vecstruct*, <4 x i32>, <4 x i32>)
