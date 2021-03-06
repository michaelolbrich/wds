/*
 * This file is part of Wireless Display Software for Linux OS
 *
 * Copyright (C) 2014 Intel Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef LIBWDS_SOURCE_SESSION_STATE_H_
#define LIBWDS_SOURCE_SESSION_STATE_H_

#include "libwds/common/message_handler.h"

namespace wds {
namespace source {

// WFD session state for RTSP source.
// Includes M5, M6, M7 messages handling and optionally can handle M3, M4, M8
class SessionState : public MessageSequenceWithOptionalSetHandler {
 public:
  SessionState(const InitParams& init_params, uint& timer_id,
      MessageHandlerPtr& m16_sender);
  ~SessionState() override;
};

class M7Handler final : public MessageReceiver<rtsp::Request::M7> {
 public:
  M7Handler(const InitParams& init_params);

 private:
  std::unique_ptr<rtsp::Reply> HandleMessage(
      rtsp::Message* message) override;
};

class M16Sender final : public OptionalMessageSender<rtsp::Request::M16> {
 public:
  M16Sender(const InitParams& init_params);

 private:
  bool HandleReply(rtsp::Reply* reply) override;
};

}  // source
}  // wds

#endif // LIBWDS_SOURCE_SESSION_STATE_H_
