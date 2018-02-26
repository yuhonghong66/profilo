// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <loom/logger/lfrb/LockFreeRingBuffer.h>

namespace facebook {
namespace profilo {
namespace logger {

using StreamID = uint32_t;

struct __attribute__((packed)) Packet {
  constexpr static auto kPacketIdNone = 0;

  StreamID stream;
  bool start:1;
  bool next:1;
  uint16_t size:14;

  alignas(4) char data[116];
};

//
// We go through the template indirection in order to have meaningful failure
// messages that show the actual size.
//
template <typename ToCheck, std::size_t RealSize = sizeof(ToCheck)>
struct check_size {
  static_assert(RealSize % 64 == 0, "Size must be a multiple of the cache line size");
};
struct check_size_0 {
  check_size<lfrb::detail::RingBufferSlot<Packet, std::atomic>> check;
};

} } } // facebook::profilo::logger
