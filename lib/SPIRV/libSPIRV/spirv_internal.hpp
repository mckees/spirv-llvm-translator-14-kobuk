// Copyright (c) 2020 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and/or associated documentation files (the "Materials"),
// to deal in the Materials without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Materials, and to permit persons to whom the
// Materials are furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Materials.
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM,OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS
// IN THE MATERIALS.

// The header is for SPIR-V to LLVM IR internal definitions, that are not a part
// of Khronos SPIR-V specification.

#include "spirv/unified1/spirv.hpp"

#ifndef spirv_internal_HPP
#define spirv_internal_HPP

namespace spv {
namespace internal {

enum InternalSourceLanguageNonSemanticDI {
  ISourceLanguagePython = 200,
  ISourceLanguageJulia = 201,
  ISourceLanguageRust = 202,
  ISourceLanguageD = 203,
  ISourceLanguageFortran77 = 204,
  ISourceLanguageFortran90 = 205,
  ISourceLanguageFortran95 = 206,
  ISourceLanguageFortran2003 = 207,
  ISourceLanguageFortran2008 = 208,
  ISourceLanguageFortran2018 = 209,
  ISourceLanguageC = 210,
  ISourceLanguageC99 = 211,
  ISourceLanguageC11 = 212,
  ISourceLanguageC17 = 213,
  ISourceLanguageCPP = 214,
  ISourceLanguageCPP03 = 215,
  ISourceLanguageCPP11 = 216,
  ISourceLanguageCPP14 = 217,
  ISourceLanguageCPP17 = 218,
  ISourceLanguageCPP20 = 219,
};

enum InternalLinkageType {
  ILTPrev = LinkageTypeMax - 2,
  ILTInternal
};

enum InternalOp {
  IOpTypeTokenINTEL = 6113,
  IOpConvertFToBF16INTEL = 6116,
  IOpConvertBF16ToFINTEL = 6117,
  IOpTypeJointMatrixINTEL = 6119,
  IOpJointMatrixLoadINTEL = 6120,
  IOpJointMatrixStoreINTEL = 6121,
  IOpJointMatrixMadINTEL = 6122,
  IOpJointMatrixSUMadINTEL = 6128,
  IOpJointMatrixUSMadINTEL = 6129,
  IOpJointMatrixUUMadINTEL = 6130,
  IOpArithmeticFenceINTEL = 6145,
  IOpCooperativeMatrixLoadCheckedINTEL = 6193,
  IOpCooperativeMatrixStoreCheckedINTEL = 6194,
  IOpCooperativeMatrixConstructCheckedINTEL = 6195,
  IOpJointMatrixWorkItemLengthINTEL = 6410,
  IOpComplexFMulINTEL = 6415,
  IOpComplexFDivINTEL = 6416,
  IOpRoundFToTF32INTEL = 6426,
  IOpMaskedGatherINTEL = 6428,
  IOpMaskedScatterINTEL = 6429,
  IOpJointMatrixGetElementCoordINTEL = 6440,
  IOpCooperativeMatrixPrefetchINTEL = 6449,
  IOpConvertHandleToImageINTEL = 6529,
  IOpConvertHandleToSamplerINTEL = 6530,
  IOpConvertHandleToSampledImageINTEL = 6531,
  IOpPrev = OpMax - 2,
  IOpForward
};

enum InternalDecoration {
  IDecMathOpDSPModeINTEL = 5909,
  IDecInitiationIntervalINTEL = 5917,
  IDecMaxConcurrencyINTEL = 5918,
  IDecPipelineEnableINTEL = 5919,
  IDecRuntimeAlignedINTEL = 5940,
  IDecCallableFunctionINTEL = 6087,
  IDecHostAccessINTEL = 6147,
  IDecInitModeINTEL = 6148,
  IDecImplementInCSRINTEL = 6149,
  IDecArgumentAttributeINTEL = 6409,
  IDecCacheControlLoadINTEL = 6442,
  IDecCacheControlStoreINTEL = 6443
};

enum InternalCapability {
  ICapFPGADSPControlINTEL = 5908,
  ICapFPGAInvocationPipeliningAttributesINTEL = 5916,
  ICapRuntimeAlignedAttributeINTEL = 5939,
  ICapFastCompositeINTEL = 6093,
  ICapOptNoneINTEL = 6094,
  ICapTokenTypeINTEL = 6112,
  ICapBfloat16ConversionINTEL = 6115,
  ICapabilityJointMatrixINTEL = 6118,
  ICapabilityHWThreadQueryINTEL = 6134,
  ICapFPArithmeticFenceINTEL = 6144,
  ICapGlobalVariableDecorationsINTEL = 6146,
  ICapabilityCooperativeMatrixCheckedInstructionsINTEL = 6192,
  ICapabilityCooperativeMatrixPrefetchINTEL = 6411,
  ICapabilityComplexFloatMulDivINTEL = 6414,
  ICapabilityTensorFloat32RoundingINTEL = 6425,
  ICapabilityMaskedGatherScatterINTEL = 6427,
  ICapabilityJointMatrixWIInstructionsINTEL = 6435,
  ICapabilityCacheControlsINTEL = 6441,
  ICapRegisterLimitsINTEL = 6460,
  ICapabilityBindlessImagesINTEL = 6528
};

enum InternalFunctionControlMask { IFunctionControlOptNoneINTELMask = 0x10000 };

enum InternalExecutionMode {
  IExecModeFastCompositeKernelINTEL = 6088,
  IExecModeStreamingInterfaceINTEL = 6154,
  IExecModeMaximumRegistersINTEL = 6461,
  IExecModeMaximumRegistersIdINTEL = 6462,
  IExecModeNamedMaximumRegistersINTEL = 6463
};

enum InternalLoopControlMask {
  ILoopControlLoopCountINTELMask = 0x1000000,
  ILoopControlMaxReinvocationDelayINTELMask = 0x2000000
};

constexpr LinkageType LinkageTypeInternal =
    static_cast<LinkageType>(ILTInternal);

enum InternalJointMatrixLayout {
  RowMajor = 0,
  ColumnMajor = 1,
  PackedA = 2,
  PackedB = 3
};

enum InternalJointMatrixUse { MatrixA = 0, MatrixB = 1, Accumulator = 2 };

enum InternalBuiltIn {
  IBuiltInSubDeviceIDINTEL = 6135,
  IBuiltInGlobalHWThreadIDINTEL = 6136,
};

enum class LoadCacheControlINTEL {
  Uncached = 0,
  Cached = 1,
  Streaming = 2,
  InvalidateAfterRead = 3,
  ConstCached = 4
};

enum class StoreCacheControlINTEL {
  Uncached = 0,
  WriteThrough = 1,
  WriteBack = 2,
  Streaming = 3
};

enum InternalNamedMaximumNumberOfRegisters {
  NamedMaximumNumberOfRegistersAutoINTEL = 0,
};

#define _SPIRV_OP(x, y) constexpr x x##y = static_cast<x>(I##x##y);
_SPIRV_OP(Capability, JointMatrixINTEL)
_SPIRV_OP(Capability, JointMatrixWIInstructionsINTEL)
_SPIRV_OP(Op, TypeJointMatrixINTEL)
_SPIRV_OP(Op, JointMatrixLoadINTEL)
_SPIRV_OP(Op, JointMatrixStoreINTEL)
_SPIRV_OP(Op, JointMatrixMadINTEL)
_SPIRV_OP(Op, JointMatrixSUMadINTEL)
_SPIRV_OP(Op, JointMatrixUSMadINTEL)
_SPIRV_OP(Op, JointMatrixUUMadINTEL)
_SPIRV_OP(Op, JointMatrixWorkItemLengthINTEL)
_SPIRV_OP(Op, JointMatrixGetElementCoordINTEL)

_SPIRV_OP(Capability, CooperativeMatrixPrefetchINTEL)
_SPIRV_OP(Op, CooperativeMatrixPrefetchINTEL)

_SPIRV_OP(Capability, CooperativeMatrixCheckedInstructionsINTEL)
_SPIRV_OP(Op, CooperativeMatrixLoadCheckedINTEL)
_SPIRV_OP(Op, CooperativeMatrixStoreCheckedINTEL)
_SPIRV_OP(Op, CooperativeMatrixConstructCheckedINTEL)

_SPIRV_OP(Capability, HWThreadQueryINTEL)
_SPIRV_OP(BuiltIn, SubDeviceIDINTEL)
_SPIRV_OP(BuiltIn, GlobalHWThreadIDINTEL)

_SPIRV_OP(Capability, ComplexFloatMulDivINTEL)
_SPIRV_OP(Op, ComplexFMulINTEL)
_SPIRV_OP(Op, ComplexFDivINTEL)

_SPIRV_OP(Capability, MaskedGatherScatterINTEL)
_SPIRV_OP(Op, MaskedGatherINTEL)
_SPIRV_OP(Op, MaskedScatterINTEL)

_SPIRV_OP(Capability, TensorFloat32RoundingINTEL)
_SPIRV_OP(Op, RoundFToTF32INTEL)

_SPIRV_OP(Capability, CacheControlsINTEL)

_SPIRV_OP(Capability, BindlessImagesINTEL)
_SPIRV_OP(Op, ConvertHandleToImageINTEL)
_SPIRV_OP(Op, ConvertHandleToSamplerINTEL)
_SPIRV_OP(Op, ConvertHandleToSampledImageINTEL)
#undef _SPIRV_OP

constexpr SourceLanguage SourceLanguagePython =
    static_cast<SourceLanguage>(ISourceLanguagePython);
constexpr SourceLanguage SourceLanguageJulia =
    static_cast<SourceLanguage>(ISourceLanguageJulia);
constexpr SourceLanguage SourceLanguageRust =
    static_cast<SourceLanguage>(ISourceLanguageRust);
constexpr SourceLanguage SourceLanguageD =
    static_cast<SourceLanguage>(ISourceLanguageD);
constexpr SourceLanguage SourceLanguageFortran77 =
    static_cast<SourceLanguage>(ISourceLanguageFortran77);
constexpr SourceLanguage SourceLanguageFortran90 =
    static_cast<SourceLanguage>(ISourceLanguageFortran90);
constexpr SourceLanguage SourceLanguageFortran95 =
    static_cast<SourceLanguage>(ISourceLanguageFortran95);
constexpr SourceLanguage SourceLanguageFortran2003 =
    static_cast<SourceLanguage>(ISourceLanguageFortran2003);
constexpr SourceLanguage SourceLanguageFortran2008 =
    static_cast<SourceLanguage>(ISourceLanguageFortran2008);
constexpr SourceLanguage SourceLanguageFortran2018 =
    static_cast<SourceLanguage>(ISourceLanguageFortran2018);
constexpr SourceLanguage SourceLanguageC =
    static_cast<SourceLanguage>(ISourceLanguageC);
constexpr SourceLanguage SourceLanguageC99 =
    static_cast<SourceLanguage>(ISourceLanguageC99);
constexpr SourceLanguage SourceLanguageC11 =
    static_cast<SourceLanguage>(ISourceLanguageC11);
constexpr SourceLanguage SourceLanguageC17 =
    static_cast<SourceLanguage>(ISourceLanguageC17);
constexpr SourceLanguage SourceLanguageCPP =
    static_cast<SourceLanguage>(ISourceLanguageCPP);
constexpr SourceLanguage SourceLanguageCPP03 =
    static_cast<SourceLanguage>(ISourceLanguageCPP03);
constexpr SourceLanguage SourceLanguageCPP11 =
    static_cast<SourceLanguage>(ISourceLanguageCPP11);
constexpr SourceLanguage SourceLanguageCPP14 =
    static_cast<SourceLanguage>(ISourceLanguageCPP14);
constexpr SourceLanguage SourceLanguageCPP17 =
    static_cast<SourceLanguage>(ISourceLanguageCPP17);
constexpr SourceLanguage SourceLanguageCPP20 =
    static_cast<SourceLanguage>(ISourceLanguageCPP20);

constexpr Op OpForward = static_cast<Op>(IOpForward);
constexpr Op OpTypeTokenINTEL = static_cast<Op>(IOpTypeTokenINTEL);
constexpr Op OpArithmeticFenceINTEL = static_cast<Op>(IOpArithmeticFenceINTEL);
constexpr Op OpConvertFToBF16INTEL = static_cast<Op>(IOpConvertFToBF16INTEL);
constexpr Op OpConvertBF16ToFINTEL = static_cast<Op>(IOpConvertBF16ToFINTEL);

constexpr Decoration DecorationInitiationIntervalINTEL =
    static_cast<Decoration>(IDecInitiationIntervalINTEL);
constexpr Decoration DecorationMaxConcurrencyINTEL =
    static_cast<Decoration>(IDecMaxConcurrencyINTEL);
constexpr Decoration DecorationPipelineEnableINTEL =
    static_cast<Decoration>(IDecPipelineEnableINTEL);
constexpr Decoration DecorationCallableFunctionINTEL =
    static_cast<Decoration>(IDecCallableFunctionINTEL);
constexpr Decoration DecorationRuntimeAlignedINTEL =
    static_cast<Decoration>(IDecRuntimeAlignedINTEL);
constexpr Decoration DecorationHostAccessINTEL =
    static_cast<Decoration>(IDecHostAccessINTEL);
constexpr Decoration DecorationInitModeINTEL =
    static_cast<Decoration>(IDecInitModeINTEL);
constexpr Decoration DecorationImplementInCSRINTEL =
    static_cast<Decoration>(IDecImplementInCSRINTEL);
constexpr Decoration DecorationArgumentAttributeINTEL =
    static_cast<Decoration>(IDecArgumentAttributeINTEL);
constexpr Decoration DecorationCacheControlLoadINTEL =
    static_cast<Decoration>(IDecCacheControlLoadINTEL);
constexpr Decoration DecorationCacheControlStoreINTEL =
    static_cast<Decoration>(IDecCacheControlStoreINTEL);

constexpr Capability CapabilityFastCompositeINTEL =
    static_cast<Capability>(ICapFastCompositeINTEL);
constexpr Capability CapabilityOptNoneINTEL =
    static_cast<Capability>(ICapOptNoneINTEL);
constexpr Capability CapabilityFPGADSPControlINTEL =
    static_cast<Capability>(ICapFPGADSPControlINTEL);
constexpr Capability CapabilityFPGAInvocationPipeliningAttributesINTEL =
    static_cast<Capability>(ICapFPGAInvocationPipeliningAttributesINTEL);
constexpr Capability CapabilityTokenTypeINTEL =
    static_cast<Capability>(ICapTokenTypeINTEL);
constexpr Capability CapabilityRuntimeAlignedAttributeINTEL =
    static_cast<Capability>(ICapRuntimeAlignedAttributeINTEL);
constexpr Capability CapabilityFPArithmeticFenceINTEL =
    static_cast<Capability>(ICapFPArithmeticFenceINTEL);
constexpr Capability CapabilityBfloat16ConversionINTEL =
    static_cast<Capability>(ICapBfloat16ConversionINTEL);
constexpr Capability CapabilityGlobalVariableDecorationsINTEL =
    static_cast<Capability>(ICapGlobalVariableDecorationsINTEL);
constexpr Capability CapabilityRegisterLimitsINTEL =
    static_cast<Capability>(ICapRegisterLimitsINTEL);

constexpr FunctionControlMask FunctionControlOptNoneINTELMask =
    static_cast<FunctionControlMask>(IFunctionControlOptNoneINTELMask);

constexpr Decoration DecorationMathOpDSPModeINTEL =
    static_cast<Decoration>(IDecMathOpDSPModeINTEL);

constexpr ExecutionMode ExecutionModeFastCompositeKernelINTEL =
    static_cast<ExecutionMode>(IExecModeFastCompositeKernelINTEL);
constexpr ExecutionMode ExecutionModeStreamingInterfaceINTEL =
    static_cast<ExecutionMode>(IExecModeStreamingInterfaceINTEL);

constexpr LoopControlMask LoopControlLoopCountINTELMask =
    static_cast<LoopControlMask>(ILoopControlLoopCountINTELMask);
static const LoopControlMask LoopControlMaxReinvocationDelayINTELMask =
    static_cast<LoopControlMask>(ILoopControlMaxReinvocationDelayINTELMask);
constexpr ExecutionMode ExecutionModeMaximumRegistersINTEL =
    static_cast<ExecutionMode>(IExecModeMaximumRegistersINTEL);
constexpr ExecutionMode ExecutionModeMaximumRegistersIdINTEL =
    static_cast<ExecutionMode>(IExecModeMaximumRegistersIdINTEL);
constexpr ExecutionMode ExecutionModeNamedMaximumRegistersINTEL =
    static_cast<ExecutionMode>(IExecModeNamedMaximumRegistersINTEL);

} // namespace internal
} // namespace spv

#endif // #ifndef spirv_internal_HPP
