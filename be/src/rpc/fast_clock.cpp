// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved

// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "compat.h"
#include "fast_clock.h"

extern "C" {
#include <sys/time.h>
}

std::chrono::FastClock::time_point std::chrono::FastClock::now() noexcept {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return std::chrono::FastClock::time_point(std::chrono::microseconds((tv.tv_sec * 1000000LL) + tv.tv_usec));
}

time_t std::chrono::FastClock::to_time_t (const std::chrono::FastClock::time_point& __t) noexcept {
    return (time_t)(__t.time_since_epoch().count() / 1000000LL);
}

std::chrono::FastClock::time_point std::chrono::FastClock::from_time_t(time_t __t) noexcept {
    return std::chrono::FastClock::time_point(std::chrono::microseconds(__t * 1000000LL));
}