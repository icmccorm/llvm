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
#include "llvm-c/ExecutionEngine.h"
#include "llvm-c/ExternC.h"
#include "llvm-c/Types.h"
#include <stddef.h>

LLVM_C_EXTERN_C_BEGIN

typedef struct LLVMOpaqueGenericValue *LLVMGenericValueRef;

typedef struct MiriProvenance {
  unsigned long long int alloc_id;
  unsigned long long int tag;
} MiriProvenance;

typedef struct MiriPointer {
  unsigned long long int addr;
  MiriProvenance prov;
} MiriPointer;

const MiriProvenance NULL_PROVENANCE = {0, 0};
typedef struct MiriErrorTrace {
  const char *directory;
  size_t directory_len;
  const char *file;
  size_t file_len;
  unsigned int line;
  unsigned int column;
} MiriErrorTrace;

typedef MiriPointer (*MiriAllocationHook)(void *, uint64_t, uint64_t);
typedef LLVMBool (*MiriFreeHook)(void *, MiriPointer);
typedef LLVMBool (*MiriLoadStoreHook)(void *, LLVMGenericValueRef, MiriPointer,
                                      LLVMTypeRef, uint64_t, uint64_t);
typedef void (*MiriStackTraceRecorderHook)(void *, MiriErrorTrace *const,
                                           uint64_t);
typedef LLVMGenericValueRef (*MiriCallbackHook)(void *, LLVMGenericValueRef,
                                                LLVMGenericValueRef, uint64_t,
                                                const char *, uint64_t,
                                                LLVMTypeRef);
LLVM_C_EXTERN_C_END
#endif // LLVM_C_MIRI_H
