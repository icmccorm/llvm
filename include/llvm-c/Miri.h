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

typedef struct Provenance {
    unsigned long long int alloc_id; 
    unsigned long long int tag;
} Provenance;


typedef void (*MiriMemoryHook)(Provenance p);
typedef void (*MiriStackHook)(void);

#endif // LLVM_C_MIRI_H
