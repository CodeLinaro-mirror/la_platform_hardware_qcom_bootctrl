/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <fuzzbinder/libbinder_ndk_driver.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "BootControl.h"
#include "BootControl.cpp"

using aidl::android::hardware::boot::BootControl;

std::shared_ptr<BootControl> gService = ndk::SharedRefBase::make<BootControl>();

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv) {
    gService = ndk::SharedRefBase::make<BootControl>();
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if  (gService == nullptr ) {
        return -1;
    }

    android::fuzzService(gService->asBinder().get(), FuzzedDataProvider(data, size));

    return 0;
}
