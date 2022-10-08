#pragma once

/**
 * Copyright (C) 2021 Parrot Drones SAS
 */

namespace cfgreader {

__attribute__ ((format (printf, 1, 2)))
void logW(const char * __restrict__ format, ... );

__attribute__ ((format (printf, 1, 2)))
void logC(const char * __restrict__ format, ... );

}