//===- LLVMToSPIRVDbgTran.h - Converts LLVM DebugInfo to SPIR-V -*- C++ -*-===//
//
//                     The LLVM/SPIR-V Translator
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Copyright (c) 2018 Intel Corporation. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal with the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimers.
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimers in the documentation
// and/or other materials provided with the distribution.
// Neither the names of Intel Corporation, nor the names of its
// contributors may be used to endorse or promote products derived from this
// Software without specific prior written permission.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH
// THE SOFTWARE.
//
//===----------------------------------------------------------------------===//
//
// This file implements translation of debug info from LLVM metadata to SPIR-V
//
//===----------------------------------------------------------------------===//

#ifndef LLVMTOSPIRVDBGTRAN_HPP_
#define LLVMTOSPIRVDBGTRAN_HPP_

#include "SPIRVModule.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Module.h"

using namespace llvm;

namespace SPIRV {
class LLVMToSPIRVBase;

class LLVMToSPIRVDbgTran {
public:
  typedef std::vector<SPIRVWord> SPIRVWordVec;

  LLVMToSPIRVDbgTran(Module *TM = nullptr, SPIRVModule *TBM = nullptr,
                     LLVMToSPIRVBase *Writer = nullptr)
      : BM(TBM), M(TM), SPIRVWriter(Writer), VoidT(nullptr),
        DebugInfoNone(nullptr) {}
  void transDebugMetadata();
  void setModule(Module *Mod) { M = Mod; }

  // Mixing translation of regular instructions and debug info creates a mess.
  // To avoid it we translate debug info intrinsics in two steps:
  // 1. First time we meet debug info intrinsic during translation of a basic
  //   block. At this time we create corresponding SPIRV debug info instruction,
  //   but with dummy operands. Doing so we a) map llvm value to spirv value,
  //   b) get a place for SPIRV debug info intrinsic in SPIRV basic block.
  //   We also remember all debug intrinsics.
  SPIRVValue *createDebugDeclarePlaceholder(const DbgVariableIntrinsic *DbgDecl,
                                            SPIRVBasicBlock *BB);
  SPIRVValue *createDebugValuePlaceholder(const DbgVariableIntrinsic *DbgValue,
                                          SPIRVBasicBlock *BB);

private:
  // 2. After translation of all regular instructions we deal with debug info.
  //   We iterate over debug intrinsics stored on the first step, get its mapped
  //   SPIRV instruction and tweak the operands.
  void finalizeDebugDeclare(const DbgVariableIntrinsic *DbgDecl);
  void finalizeDebugValue(const DbgVariableIntrinsic *DbgValue);

  // Emit DebugScope and OpLine instructions
  void transLocationInfo();

  // Dispatcher
  SPIRVEntry *transDbgEntry(const MDNode *DIEntry);
  SPIRVEntry *transDbgEntryImpl(const MDNode *MDN);

  // Helper methods
  SPIRVType *getVoidTy();
  SPIRVType *getInt32Ty();
  SPIRVEntry *getScope(DIScope *SR);
  SPIRVEntry *getGlobalVariable(const DIGlobalVariable *GV);
  inline bool isNonSemanticDebugInfo();
  void transformToConstant(std::vector<SPIRVWord> &Ops,
                           std::vector<SPIRVWord> Idxs);

  // No debug info
  SPIRVEntry *getDebugInfoNone();
  SPIRVId getDebugInfoNoneId();

  // Compilation unit
  SPIRVEntry *transDbgCompileUnit(const DICompileUnit *CU);

  /// The following methods (till the end of the file) implement translation
  /// of debug instrtuctions described in the spec.

  // Types
  SPIRVEntry *transDbgBaseType(const DIBasicType *BT);
  SPIRVEntry *transDbgPointerType(const DIDerivedType *PT);
  SPIRVEntry *transDbgQualifiedType(const DIDerivedType *QT);
  SPIRVEntry *transDbgArrayType(const DICompositeType *AT);
  SPIRVEntry *transDbgArrayTypeOpenCL(const DICompositeType *AT);
  SPIRVEntry *transDbgArrayTypeNonSemantic(const DICompositeType *AT);
  SPIRVEntry *transDbgArrayTypeDynamic(const DICompositeType *AT);
  SPIRVEntry *transDbgSubrangeType(const DISubrange *ST);
  SPIRVEntry *transDbgStringType(const DIStringType *ST);
  SPIRVEntry *transDbgTypeDef(const DIDerivedType *D);
  SPIRVEntry *transDbgSubroutineType(const DISubroutineType *FT);
  SPIRVEntry *transDbgEnumType(const DICompositeType *ET);
  SPIRVEntry *transDbgCompositeType(const DICompositeType *CT);
  SPIRVEntry *transDbgMemberType(const DIDerivedType *MT);
  SPIRVEntry *transDbgMemberTypeOpenCL(const DIDerivedType *MT);
  SPIRVEntry *transDbgMemberTypeNonSemantic(const DIDerivedType *MT);
  SPIRVEntry *transDbgInheritance(const DIDerivedType *DT);
  SPIRVEntry *transDbgPtrToMember(const DIDerivedType *DT);

  // Templates
  SPIRVEntry *transDbgTemplateParams(DITemplateParameterArray TPA,
                                     const SPIRVEntry *Target);
  SPIRVEntry *transDbgTemplateParameter(const DITemplateParameter *TP);
  SPIRVEntry *
  transDbgTemplateTemplateParameter(const DITemplateValueParameter *TP);
  SPIRVEntry *transDbgTemplateParameterPack(const DITemplateValueParameter *TP);

  // Global objects
  SPIRVEntry *transDbgGlobalVariable(const DIGlobalVariable *GV);
  SPIRVEntry *transDbgFunction(const DISubprogram *Func);

  SPIRVEntry *transDbgFuncDefinition(SPIRVValue *SPVFunc, SPIRVEntry *DbgFunc);
  SPIRVEntry *transDbgEntryPoint(const DISubprogram *Func, SPIRVEntry *DbgFunc);

  // Location information
  SPIRVEntry *transDbgScope(const DIScope *S);
  SPIRVEntry *transDebugLoc(const DebugLoc &Loc, SPIRVBasicBlock *BB,
                            SPIRVInstruction *InsertBefore = nullptr);
  SPIRVEntry *transDbgInlinedAt(const DILocation *D);
  SPIRVEntry *transDbgInlinedAtNonSemanticShader200(const DILocation *D);

  template <class T> SPIRVExtInst *getSource(const T *DIEntry);
  SPIRVEntry *transDbgFileType(const DIFile *F);

  // Generate instructions recording identifier and file where debug information
  // was split to
  void generateBuildIdentifierAndStoragePath(const DICompileUnit *DIEntry);

  // Local Variables
  SPIRVEntry *transDbgLocalVariable(const DILocalVariable *Var);

  // DWARF expressions
  SPIRVEntry *transDbgExpression(const DIExpression *Expr);

  // Imported declarations and modules
  SPIRVEntry *transDbgImportedEntry(const DIImportedEntity *IE);

  // A module in programming language. Example - Fortran module, clang module.
  SPIRVEntry *transDbgModule(const DIModule *IE);

  // Flags
  SPIRVWord mapDebugFlags(DINode::DIFlags DFlags);
  SPIRVWord transDebugFlags(const DINode *DN);

  SPIRVModule *BM;
  Module *M;
  LLVMToSPIRVBase *SPIRVWriter;
  std::unordered_map<const MDNode *, SPIRVEntry *> MDMap;
  std::unordered_map<std::string, SPIRVExtInst *> FileMap;
  DebugInfoFinder DIF;
  SPIRVType *VoidT = nullptr;
  SPIRVType *Int32T = nullptr;
  SPIRVEntry *DebugInfoNone;
  std::unordered_map<const DICompileUnit *, SPIRVExtInst *> SPIRVCUMap;
  std::vector<const DbgVariableIntrinsic *> DbgDeclareIntrinsics;
  std::vector<const DbgVariableIntrinsic *> DbgValueIntrinsics;

  SPIRVExtInst *BuildIdentifierInsn{nullptr};
  SPIRVExtInst *StoragePathInsn{nullptr};
}; // class LLVMToSPIRVDbgTran

} // namespace SPIRV

#endif // LLVMTOSPIRVDBGTRAN_HPP_
