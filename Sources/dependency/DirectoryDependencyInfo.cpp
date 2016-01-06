/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#include <dependency/DirectoryDependencyInfo.h>
#include <dependency/DependencyInfo.h>
#include <libutil/FSUtil.h>

using dependency::DirectoryDependencyInfo;
using dependency::DependencyInfo;
using libutil::FSUtil;

DirectoryDependencyInfo::
DirectoryDependencyInfo(std::string const &directory, DependencyInfo const &dependencyInfo) :
    _directory     (directory),
    _dependencyInfo(dependencyInfo)
{
}

std::unique_ptr<DirectoryDependencyInfo> DirectoryDependencyInfo::
Create(std::string const &directory)
{
    std::vector<std::string> inputs;

    /* Recursively add all paths under this directory. */
    FSUtil::EnumerateRecursive(directory, [&](std::string const &path) -> bool {
        inputs.push_back(path);
        return true;
    });

    /* Create dependency info. */
    auto info = DependencyInfo(inputs, std::vector<std::string>());
    auto directoryInfo = DirectoryDependencyInfo(directory, info);

    return std::unique_ptr<DirectoryDependencyInfo>(new DirectoryDependencyInfo(directoryInfo));
}
