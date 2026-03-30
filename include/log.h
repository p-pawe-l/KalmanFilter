#ifndef LOG_H
#define LOG_H

/*
 * Copyright (c) 2026 Paweł Kozikowski
 *
 * This file is part of a Kalman filter implementation in C.
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */

#include <stdio.h>

#define LOG_INFO(msg) printf("[INFO] %s\n", (msg))
#define LOG_WARN(msg) fprintf(stderr, "[WARN] %s\n", (msg))
#define LOG_ERR(msg) fprintf(stderr, "[ERROR] %s\n", (msg))

#endif
