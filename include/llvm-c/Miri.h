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

typedef struct PointerMetadata {
  unsigned long long int alloc_id;
  unsigned long long int tag;
  unsigned long long int offset;
} PointerMetadata;

typedef struct TrackedPointer {
  void *Pointer;
  PointerMetadata Metadata;
} TrackedPointer;

typedef TrackedPointer (*MiriAllocationHook)(void *, unsigned long long int);
typedef TrackedPointer (*MiriReallocationHook)(void *, TrackedPointer,
                                               unsigned long long int);
typedef void (*MiriFreeHook)(void *, TrackedPointer);
typedef void (*MiriStackedBorrowsHook)(void *, PointerMetadata p);

#endif // LLVM_C_MIRI_H
