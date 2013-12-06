//===--- Compilation.h - Compilation Task Data Structure --------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// TODO: Document me
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_DRIVER_COMPILATION_H
#define SWIFT_DRIVER_COMPILATION_H

#include <memory>

namespace llvm {
namespace opt {
  class InputArgList;
  class DerivedArgList;
}
}

namespace swift {
namespace driver {
  class Driver;
  class Job;
  class JobList;
  class ToolChain;

class Compilation {
  /// The driver we were created by.
  const Driver &TheDriver;

  /// The default tool chain.
  const ToolChain &DefaultToolChain;

  /// The Jobs which will be performed by this compilation.
  std::unique_ptr<JobList> Jobs;

  // The original (untranslated) input argument list.
  std::unique_ptr<llvm::opt::InputArgList> InputArgs;

  // The translated input arg list.
  std::unique_ptr<llvm::opt::DerivedArgList> TranslatedArgs;

public:
  Compilation(const Driver &D, const ToolChain &DefaultToolChain,
              std::unique_ptr<llvm::opt::InputArgList> InputArgs,
              std::unique_ptr<llvm::opt::DerivedArgList> TranslatedArgs);
  ~Compilation();

  const Driver &getDriver() const { return TheDriver; }

  const ToolChain &getDefaultToolChain() const { return DefaultToolChain; }

  JobList &getJobs() const { return *Jobs; }
  void addJob(Job *J);

  const llvm::opt::InputArgList &getInputArgs() const { return *InputArgs; }

  const llvm::opt::DerivedArgList &getArgs() const { return *TranslatedArgs; }
};

} // end namespace driver
} // end namespace swift

#endif
