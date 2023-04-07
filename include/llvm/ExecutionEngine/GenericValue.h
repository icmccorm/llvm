//===- GenericValue.h - Represent any type of LLVM value --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The GenericValue class is used to represent an LLVM value of arbitrary type.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_EXECUTIONENGINE_GENERICVALUE_H
#define LLVM_EXECUTIONENGINE_GENERICVALUE_H

#include "llvm-c/Miri.h"
#include "llvm/ADT/APInt.h"
#include <vector>

namespace llvm {

using PointerTy = void *;

struct GenericValue {
  struct IntPair {
    unsigned int first;
    unsigned int second;
  };
  union {
    double DoubleVal;
    float FloatVal;
    PointerTy PointerVal;
    struct IntPair UIntPairVal;
    unsigned char Untyped[8];
  };
  APInt IntVal; // also used for long doubles.
  // For aggregate data types.
  MiriPointer MiriPointerVal;
  MiriPointer MiriParentPointerVal;
  std::vector<GenericValue> AggregateVal;

  // to make code faster, set GenericValue to zero could be omitted, but it is
  // potentially can cause problems, since GenericValue to store garbage
  // instead of zero.
  GenericValue() : IntVal(1, 0) {
    UIntPairVal.first = 0;
    UIntPairVal.second = 0;
  }
  explicit GenericValue(MiriPointer Meta)
      : PointerVal(nullptr), IntVal(1, 0), MiriPointerVal(Meta) {}
  explicit GenericValue(void *V)
      : PointerVal(V), IntVal(1, 0),
        MiriPointerVal({.addr = 0, .alloc_id = 0, .tag = 0, .offset = 0}),
        MiriParentPointerVal(
            {.addr = 0, .alloc_id = 0, .tag = 0, .offset = 0}) {}
};
inline GenericValue MiriPointerTOGV(MiriPointer P) { return GenericValue(P); }
inline GenericValue PTOGV(void *P) { return GenericValue(P); }
inline void *GVTOP(const GenericValue &GV) { return GV.PointerVal; }
inline MiriPointer GVTOMiriPointer(const GenericValue &GV) {
  return GV.MiriPointerVal;
}
} // end namespace llvm

#endif // LLVM_EXECUTIONENGINE_GENERICVALUE_H
