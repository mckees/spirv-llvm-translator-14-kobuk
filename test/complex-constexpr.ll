; RUN: llvm-as %s -o %t.bc
; RUN: llvm-spirv %t.bc --spirv-max-version=1.3 -o %t.spv
; RUN: spirv-val %t.spv
; RUN: llvm-spirv %t.spv --spirv-max-version=1.3 -o %t.spt --to-text
; RUN: llvm-spirv -r %t.spv -o %t.rev.bc
; RUN: llvm-dis %t.rev.bc
; RUN: FileCheck %s --input-file %t.spt -check-prefix=CHECK-SPIRV
; RUN: FileCheck %s --input-file %t.rev.ll  -check-prefix=CHECK-LLVM

target datalayout = "e-i64:64-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024-n8:16:32:64"
target triple = "spir64"

; CHECK-SPIRV: TypeInt [[Int_Ty:[0-9]+]] 8 0
; CHECK-SPIRV: TypeVoid [[Void_Ty:[0-9]+]]
; CHECK-SPIRV: TypeFunction [[Func_Ty1:[0-9]+]] [[Void_Ty]]
; CHECK-SPIRV: TypePointer [[Ptr_Ty:[0-9]+]] 8 [[Int_Ty]]
; CHECK-SPIRV: TypeFunction [[Func_Ty2:[0-9]+]] [[Void_Ty]] [[Ptr_Ty]] [[Ptr_Ty]]

; CHECK-SPIRV-14: TypeInt [[Int_Ty:[0-9]+]] 8 0
; CHECK-SPIRV-14: TypeVoid [[Void_Ty:[0-9]+]]
; CHECK-SPIRV-14: TypeFunction [[Func_Ty1:[0-9]+]] [[Void_Ty]]
; CHECK-SPIRV-14: TypePointer [[Ptr_Ty:[0-9]+]] 8
; CHECK-SPIRV-14: TypeFunction [[Func_Ty2:[0-9]+]] [[Void_Ty]] [[Ptr_Ty]] [[Ptr_Ty]]

@.str.1 = private unnamed_addr addrspace(1) constant [1 x i8] zeroinitializer, align 1

define linkonce_odr hidden spir_func void @foo() {
entry:
; CHECK-SPIRV: PtrCastToGeneric {{[0-9]+}} [[Cast:[0-9]+]]
; CHECK-SPIRV: InBoundsPtrAccessChain {{[0-9]+}} [[Gep:[0-9]+]] [[Cast]]
; CHECK-SPIRV: InBoundsPtrAccessChain {{[0-9]+}} [[Gep1:[0-9]+]] [[Cast]]
; CHECK-SPIRV: ConvertPtrToU {{[0-9]+}} [[PtrToU1:[0-9]+]] [[Gep1]]
; CHECK-SPIRV: ConvertPtrToU {{[0-9]+}} [[PtrToU2:[0-9]+]]
; CHECK-SPIRV: IEqual {{[0-9]+}} [[IEq:[0-9]+]] [[PtrToU1]] [[PtrToU2]]
; CHECK-SPIRV: ConvertUToPtr {{[0-9]+}} [[UToPtr:[0-9]+]]
; CHECK-SPIRV: Select {{[0-9]+}} [[Sel:[0-9]+]] [[IEq]] [[UToPtr]] [[Gep1]]
; CHECK-SPIRV: FunctionCall [[Void_Ty]] {{[0-9]+}} [[Func:[0-9]+]] [[Gep]] [[Sel]]
; CHECK-LLVM:  %[[Cast:[0-9]+]] = addrspacecast [1 x i8] addrspace(1)* @.str.1 to [1 x i8] addrspace(4)*
; CHECK-LLVM:  %[[Gep:[0-9]+]] = getelementptr inbounds [1 x i8], [1 x i8] addrspace(4)* %0, i64 0, i64 0
; CHECK-LLVM:  %[[Gep1:[0-9]+]] = getelementptr inbounds [1 x i8], [1 x i8] addrspace(4)* %0, i64 0, i64 0
; CHECK-LLVM:  %[[PtrToU1:[0-9]+]] = ptrtoint i8 addrspace(4)* %[[Gep1]] to i64
; CHECK-LLVM:  %[[PtrToU2:[0-9]+]] = ptrtoint i8 addrspace(4)* null to i64
; CHECK-LLVM:  %[[IEq:[0-9]+]] = icmp eq i64 %[[PtrToU1]], %[[PtrToU2]]
; CHECK-LLVM:  %[[UToPtr:[0-9]+]] = inttoptr i64 -1 to i8 addrspace(4)*
; CHECK-LLVM:  %[[Sel:[0-9]+]] = select i1 %[[IEq]], i8 addrspace(4)* %[[UToPtr]], i8 addrspace(4)* %[[Gep1]]
; CHECK-LLVM:  call spir_func void @bar(i8 addrspace(4)* %[[Gep]], i8 addrspace(4)* %[[Sel]]) #0
  call spir_func void @bar(i8 addrspace(4)* getelementptr inbounds ([1 x i8], [1 x i8] addrspace(4)* addrspacecast ([1 x i8] addrspace(1)* @.str.1 to [1 x i8] addrspace(4)*), i64 0, i64 0), i8 addrspace(4)* select (i1 icmp eq (i8 addrspace(4)* getelementptr inbounds ([1 x i8], [1 x i8] addrspace(4)* addrspacecast ([1 x i8] addrspace(1)* @.str.1 to [1 x i8] addrspace(4)*), i64 0, i64 0), i8 addrspace(4)* null), i8 addrspace(4)* inttoptr (i64 -1 to i8 addrspace(4)*), i8 addrspace(4)* getelementptr inbounds ([1 x i8], [1 x i8] addrspace(4)* addrspacecast ([1 x i8] addrspace(1)* @.str.1 to [1 x i8] addrspace(4)*), i64 0, i64 0)))
  ret void
}

; CHECK-SPIRV: Function [[Void_Ty]] [[Func]] 0 [[Func_Ty2]]

define linkonce_odr hidden spir_func void @bar(i8 addrspace(4)* %__beg, i8 addrspace(4)* %__end) {
entry:
  ret void
}

