/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include "redis_pubsub.h"

namespace redis {

rocksdb::Status PubSub::Publish(engine::Context &ctx, const Slice &channel, const Slice &value) {
  if (storage_->GetConfig()->IsSlave()) {
    return rocksdb::Status::NotSupported("can't publish to db in slave mode");
  }
  auto batch = storage_->GetWriteBatchBase();
  batch->Put(pubsub_cf_handle_, channel, value);
  return storage_->Write(ctx, storage_->DefaultWriteOptions(), batch->GetWriteBatch());
}

}  // namespace redis
