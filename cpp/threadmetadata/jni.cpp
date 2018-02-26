// Copyright 2004-present Facebook. All Rights Reserved.

#include <jni.h>
#include <fbjni/fbjni.h>
#include <fb/xplat_init.h>

#include <loom/threadmetadata/ThreadMetadata.h>

using namespace facebook::profilo;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void*) {
  return facebook::xplat::initialize(vm, [] {
    facebook::jni::registerNatives(
      "com/facebook/loom/provider/threadmetadata/ThreadMetadataProvider",
      {
        makeNativeMethod("nativeLogThreadMetadata", threadmetadata::logThreadMetadata),
      });
  });
}
