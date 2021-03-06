/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#include <xcdriver/ShowSDKsAction.h>
#include <xcdriver/Options.h>

#include <xcsdk/xcsdk.h>
#include <libutil/Filesystem.h>

using xcdriver::ShowSDKsAction;
using xcdriver::Options;
using libutil::Filesystem;

ShowSDKsAction::
ShowSDKsAction()
{
}

ShowSDKsAction::
~ShowSDKsAction()
{
}

int ShowSDKsAction::
Run(Filesystem const *filesystem, Options const &options)
{
    ext::optional<std::string> developerRoot = xcsdk::Environment::DeveloperRoot(filesystem);
    if (!developerRoot) {
        fprintf(stderr, "error: unable to find developer dir\n");
        return 1;
    }

    std::shared_ptr<xcsdk::SDK::Manager> manager = xcsdk::SDK::Manager::Open(filesystem, *developerRoot);
    if (manager == nullptr) {
        fprintf(stderr, "error: unable to open developer directory\n");
        return 1;
    }

    for (auto const &platform : manager->platforms()) {
        printf("%s SDKs:\n", platform->description().c_str());
        for (auto const &target : platform->targets()) {
            printf("\t%-32s-sdk %s\n", target->displayName().c_str(), target->canonicalName().c_str());
        }
        printf("\n");
    }

    return 0;
}
