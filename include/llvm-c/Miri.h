//===- Miri.h --*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_C_MIRI_H
#define LLVM_C_MIRI_H
#include <stddef.h>
#include "llvm-c/ExternC.h"
#include "llvm-c/Types.h"
#include "llvm-c/ExecutionEngine.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct LLVMOpaqueGenericValue *LLVMGenericValueRef;

typedef struct PointerMetadata {
  unsigned long long int alloc_id;
  unsigned long long int tag;
  unsigned long long int offset;
} PointerMetadata;

typedef struct TrackedPointer {
  void *Pointer;
  PointerMetadata Metadata;
} TrackedPointer;

typedef TrackedPointer (*MiriAllocationHook)(void *, size_t);
typedef void (*MiriFreeHook)(void *, TrackedPointer);              
typedef void (*MiriLoadStoreHook)(void *, LLVMGenericValueRef, TrackedPointer, LLVMTypeRef, const unsigned);
typedef LLVMGenericValueRef (*MiriCallbackHook)(void *, LLVMGenericValueRef, size_t, const char *, size_t);

LLVM_C_EXTERN_C_END

#endif // LLVM_C_MIRI_H
