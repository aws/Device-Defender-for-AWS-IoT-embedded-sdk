/*
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file defender_config_defaults.h
 * @brief Default config values for the Device Defender library.
 */

#ifndef DEFENDER_CONFIG_DEFAULTS_H_
#define DEFENDER_CONFIG_DEFAULTS_H_

/**
 * @brief Set it to 1 to enable use of long key names in the defender report.
 *
 * AWS IoT Device Defender Service supports both long and short names for keys
 * in the report sent by a device. For example,
 *
 * A device defender report using long key names:
 * {
 *     "header": {
 *         "report_id": 1530304554,
 *         "version": "1.0"
 *     },
 *     "metrics": {
 *         "network_stats": {
 *             "bytes_in": 29358693495,
 *             "bytes_out": 26485035,
 *             "packets_in": 10013573555,
 *             "packets_out": 11382615
 *         }
 *     }
 * }
 *
 * An equivalent report using short key names:
 * {
 *     "hed": {
 *         "rid": 1530304554,
 *         "v": "1.0"
 *     },
 *     "met": {
 *         "ns": {
 *             "bi": 29358693495,
 *             "bo": 26485035,
 *             "pi": 10013573555,
 *             "po": 11382615
 *         }
 *     }
 * }
 *
 * Short key names are preferred option for resource constrained devices because
 * they result in smaller report size. If you want to use long key names instead,
 * set DEFENDER_USE_LONG_KEYS to 1 in defender_config.h.
 */
#ifndef DEFENDER_USE_LONG_KEYS
    #define DEFENDER_USE_LONG_KEYS    0
#endif

/**
 * @brief Macro used in the Device Defender client library to log error messages.
 *
 * To enable error logging, this macro should be mapped to an
 * application-specific logging implementation.
 */
#ifndef LogError
    #define LogError( message )
#endif

/**
 * @brief Macro used in the Device Defender client library to log warning messages.
 *
 * To enable warning logging, this macro should be mapped to an
 * application-specific logging implementation.
 */
#ifndef LogWarn
    #define LogWarn( message )
#endif

/**
 * @brief Macro used in the Device Defender client library to log info messages.
 *
 * To enable info logging, this macro should be mapped to an
 * application-specific logging implementation.
 */
#ifndef LogInfo
    #define LogInfo( message )
#endif

/**
 * @brief Macro used in the Device Defender client library to log debug messages.
 *
 * To enable debug logging, this macro should be mapped to an
 * application-specific logging implementation.
 */
#ifndef LogDebug
    #define LogDebug( message )
#endif

#endif /* DEFENDER_CONFIG_DEFAULTS_H_ */
