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
 * @file defender.h
 * @brief Interface for the Device Defender library.
 */

#ifndef DEFENDER_H_
#define DEFENDER_H_

/* Standard includes. */
#include <stdint.h>

/* DEFENDER_DO_NOT_USE_CUSTOM_CONFIG allows building the Device Defender library
 * without a config file. If a config file is provided, DEFENDER_DO_NOT_USE_CUSTOM_CONFIG
 * macro must not be defined.
 */
#ifndef DEFENDER_DO_NOT_USE_CUSTOM_CONFIG
    #include "defender_config.h"
#endif

/* Default config values. */
#include "defender_config_defaults.h"

/**
 * @brief Return codes from defender APIs.
 */
typedef enum DefenderStatus
{
    DefenderError = 0,
    DefenderSuccess,
    DefenderNoMatch,
    DefenderBadParameter,
    DefenderBufferTooSmall
} DefenderStatus_t;

/**
 * @brief Topic values for subscription requests.
 */
typedef enum DefenderTopic
{
    DefenderInvalidTopic = -1,
    DefenderJsonReportPublish,
    DefenderJsonReportAccepted,
    DefenderJsonReportRejected,
    DefenderCborReportPublish,
    DefenderCborReportAccepted,
    DefenderCborReportRejected,
    DefenderMaxTopic
} DefenderTopic_t;

/*-----------------------------------------------------------*/

/**
 * @brief Helper macro to calculate the length of a string literal.
 */
#define STRING_LITERAL_LENGTH( literal )    ( sizeof( literal ) - 1U )

/*-----------------------------------------------------------*/

#define DEFENDER_THINGNAME_MAX_LENGTH         128   /* Per AWS IoT Core Reference. */
#define DEFENDER_REPORT_MIN_PERIOD_SECONDS    300   /* Per AWS IoT Device Defender Reference. */

/*-----------------------------------------------------------*/

/*
 * A Defender topic has the following format:
 *
 * <Prefix><Thing Name><Bridge><Report Format><Suffix>
 *
 * Where:
 * <Prefix> = $aws/things/
 * <Thing Name> = Name of the thing.
 * <Bridge> = /defender/metrics/
 * <Report Format> = json or cbor
 * <Suffix> = /accepted or /rejected or empty
 *
 * Examples:
 * $aws/things/THING_NAME/defender/metrics/json
 * $aws/things/THING_NAME/defender/metrics/json/accepted
 * $aws/things/THING_NAME/defender/metrics/json/rejected
 * $aws/things/THING_NAME/defender/metrics/cbor
 * $aws/things/THING_NAME/defender/metrics/cbor/accepted
 * $aws/things/THING_NAME/defender/metrics/json/rejected
 */

#define DEFENDER_API_PREFIX                       "$aws/things/"
#define DEFENDER_API_PREFIX_LENGTH                STRING_LITERAL_LENGTH( DEFENDER_API_PREFIX )

#define DEFENDER_API_BRIDGE                       "/defender/metrics/"
#define DEFENDER_API_BRIDGE_LENGTH                STRING_LITERAL_LENGTH( DEFENDER_API_BRIDGE )

#define DEFENDER_API_JSON_REPORT_FORMAT           "json"
#define DEFENDER_API_JSON_REPORT_FORMAT_LENGTH    STRING_LITERAL_LENGTH( DEFENDER_API_JSON_REPORT_FORMAT )

#define DEFENDER_API_CBOR_REPORT_FORMAT           "cbor"
#define DEFENDER_API_CBOR_REPORT_FORMAT_LENGTH    STRING_LITERAL_LENGTH( DEFENDER_API_CBOR_REPORT_FORMAT )

#define DEFENDER_API_ACCEPTED_SUFFIX              "/accepted"
#define DEFENDER_API_ACCEPTED_SUFFIX_LENGTH       STRING_LITERAL_LENGTH( DEFENDER_API_ACCEPTED_SUFFIX )

#define DEFENDER_API_REJECTED_SUFFIX              "/rejected"
#define DEFENDER_API_REJECTED_SUFFIX_LENGTH       STRING_LITERAL_LENGTH( DEFENDER_API_REJECTED_SUFFIX )

#define DEFENDER_API_NULL_SUFFIX                  ""
#define DEFENDER_API_NULL_SUFFIX_LENGTH           ( 0U )

/*-----------------------------------------------------------*/

/* Defender API topic lengths. */
#define DEFENDER_API_COMMON_LENGTH( thingNameLength, reportFormatLength, suffixLength ) \
    ( DEFENDER_API_PREFIX_LENGTH +                                                      \
      ( thingNameLength ) +                                                             \
      DEFENDER_API_BRIDGE_LENGTH +                                                      \
      ( reportFormatLength ) +                                                          \
      ( suffixLength ) )

#define DEFENDER_API_JSON_REPORT_PUBLISH_LENGTH( thingNameLength )      \
    DEFENDER_API_COMMON_LENGTH( thingNameLength,                        \
                                DEFENDER_API_JSON_REPORT_FORMAT_LENGTH, \
                                DEFENDER_API_NULL_SUFFIX_LENGTH )

#define DEFENDER_API_JSON_REPORT_ACCEPTED_LENGTH( thingNameLength )     \
    DEFENDER_API_COMMON_LENGTH( thingNameLength,                        \
                                DEFENDER_API_JSON_REPORT_FORMAT_LENGTH, \
                                DEFENDER_API_ACCEPTED_SUFFIX_LENGTH )

#define DEFENDER_API_JSON_REPORT_REJECTED_LENGTH( thingNameLength )     \
    DEFENDER_API_COMMON_LENGTH( thingNameLength,                        \
                                DEFENDER_API_JSON_REPORT_FORMAT_LENGTH, \
                                DEFENDER_API_REJECTED_SUFFIX_LENGTH )

#define DEFENDER_API_CBOR_REPORT_PUBLISH_LENGTH( thingNameLength )      \
    DEFENDER_API_COMMON_LENGTH( thingNameLength,                        \
                                DEFENDER_API_CBOR_REPORT_FORMAT_LENGTH, \
                                DEFENDER_API_NULL_SUFFIX_LENGTH )

#define DEFENDER_API_CBOR_REPORT_ACCEPTED_LENGTH( thingNameLength )     \
    DEFENDER_API_COMMON_LENGTH( thingNameLength,                        \
                                DEFENDER_API_CBOR_REPORT_FORMAT_LENGTH, \
                                DEFENDER_API_ACCEPTED_SUFFIX_LENGTH )

#define DEFENDER_API_CBOR_REPORT_REJECTED_LENGTH( thingNameLength )     \
    DEFENDER_API_COMMON_LENGTH( thingNameLength,                        \
                                DEFENDER_API_CBOR_REPORT_FORMAT_LENGTH, \
                                DEFENDER_API_REJECTED_SUFFIX_LENGTH )

#define DEFENDER_API_MAX_LENGTH( thingNameLength ) \
    DEFENDER_API_CBOR_REPORT_ACCEPTED_LENGTH( thingNameLength )

/*-----------------------------------------------------------*/

/* Defender API topics. */
#define DEFENDER_API_COMMON( thingName, reportFormat, suffix ) \
    ( DEFENDER_API_PREFIX                                      \
      thingName                                                \
      DEFENDER_API_BRIDGE                                      \
      reportFormat                                             \
      suffix )

#define DEFENDER_API_JSON_REPORT_PUBLISH( thingName )     \
    DEFENDER_API_COMMON( thingName,                       \
                         DEFENDER_API_JSON_REPORT_FORMAT, \
                         DEFENDER_API_NULL_SUFFIX )

#define DEFENDER_API_JSON_REPORT_ACCEPTED( thingName )    \
    DEFENDER_API_COMMON( thingName,                       \
                         DEFENDER_API_JSON_REPORT_FORMAT, \
                         DEFENDER_API_ACCEPTED_SUFFIX )

#define DEFENDER_API_JSON_REPORT_REJECTED( thingName )    \
    DEFENDER_API_COMMON( thingName,                       \
                         DEFENDER_API_JSON_REPORT_FORMAT, \
                         DEFENDER_API_REJECTED_SUFFIX )

#define DEFENDER_API_CBOR_REPORT_PUBLISH( thingName )     \
    DEFENDER_API_COMMON( thingName,                       \
                         DEFENDER_API_CBOR_REPORT_FORMAT, \
                         DEFENDER_API_NULL_SUFFIX )

#define DEFENDER_API_CBOR_REPORT_ACCEPTED( thingName )    \
    DEFENDER_API_COMMON( thingName,                       \
                         DEFENDER_API_CBOR_REPORT_FORMAT, \
                         DEFENDER_API_ACCEPTED_SUFFIX )

#define DEFENDER_API_CBOR_REPORT_REJECTED( thingName )    \
    DEFENDER_API_COMMON( thingName,                       \
                         DEFENDER_API_CBOR_REPORT_FORMAT, \
                         DEFENDER_API_REJECTED_SUFFIX )

/*-----------------------------------------------------------*/

/* Keys used in defender report. */
#if ( defined( DEFENDER_USE_LONG_KEYS ) && ( DEFENDER_USE_LONG_KEYS == 1 ) )
    #define DEFENDER_REPORT_SELECT_KEY( longKey, shortKey )    ( longKey )
#else
    #define DEFENDER_REPORT_SELECT_KEY( longKey, shortKey )    ( shortKey )
#endif

#define DEFENDER_REPORT_HEADER_KEY                            DEFENDER_REPORT_SELECT_KEY( "header", "hed" )
#define DEFENDER_REPORT_HEADER_KEY_LENGTH                     STRING_LITERAL_LENGTH( DEFENDER_REPORT_HEADER_KEY )

#define DEFENDER_REPORT_METRICS_KEY                           DEFENDER_REPORT_SELECT_KEY( "metrics", "met" )
#define DEFENDER_REPORT_METRICS_KEY_LENGTH                    STRING_LITERAL_LENGTH( DEFENDER_REPORT_METRICS_KEY )

#define DEFENDER_REPORT_ID_KEY                                DEFENDER_REPORT_SELECT_KEY( "report_id", "rid" )
#define DEFENDER_REPORT_ID_KEY_LENGTH                         STRING_LITERAL_LENGTH( DEFENDER_REPORT_ID_KEY )

#define DEFENDER_REPORT_VERSION_KEY                           DEFENDER_REPORT_SELECT_KEY( "version", "v" )
#define DEFENDER_REPORT_VERSION_KEY_LENGTH                    STRING_LITERAL_LENGTH( DEFENDER_REPORT_VERSION_KEY )

#define DEFENDER_REPORT_TCP_CONNECTIONS_KEY                   DEFENDER_REPORT_SELECT_KEY( "tcp_connections", "tc" )
#define DEFENDER_REPORT_TCP_CONNECTIONS_KEY_LENGTH            STRING_LITERAL_LENGTH( DEFENDER_REPORT_TCP_CONNECTIONS_KEY )

#define DEFENDER_REPORT_ESTABLISHED_CONNECTIONS_KEY           DEFENDER_REPORT_SELECT_KEY( "established_connections", "ec" )
#define DEFENDER_REPORT_ESTABLISHED_CONNECTIONS_KEY_LENGTH    STRING_LITERAL_LENGTH( DEFENDER_REPORT_ESTABLISHED_CONNECTIONS_KEY )

#define DEFENDER_REPORT_CONNECTIONS_KEY                       DEFENDER_REPORT_SELECT_KEY( "connections", "cs" )
#define DEFENDER_REPORT_CONNECTIONS_KEY_LENGTH                STRING_LITERAL_LENGTH( DEFENDER_REPORT_CONNECTIONS_KEY )

#define DEFENDER_REPORT_REMOTE_ADDR_KEY                       DEFENDER_REPORT_SELECT_KEY( "remote_addr", "rad" )
#define DEFENDER_REPORT_REMOTE_ADDR_KEY_LENGTH                STRING_LITERAL_LENGTH( DEFENDER_REPORT_REMOTE_ADDR_KEY )

#define DEFENDER_REPORT_LOCAL_PORT_KEY                        DEFENDER_REPORT_SELECT_KEY( "local_port", "lp" )
#define DEFENDER_REPORT_LOCAL_PORT_KEY_LENGTH                 STRING_LITERAL_LENGTH( DEFENDER_REPORT_LOCAL_PORT_KEY )

#define DEFENDER_REPORT_LOCAL_INTERFACE_KEY                   DEFENDER_REPORT_SELECT_KEY( "local_interface", "li" )
#define DEFENDER_REPORT_LOCAL_INTERFACE_KEY_LENGTH            STRING_LITERAL_LENGTH( DEFENDER_REPORT_LOCAL_INTERFACE_KEY )

#define DEFENDER_REPORT_TOTAL_KEY                             DEFENDER_REPORT_SELECT_KEY( "total", "t" )
#define DEFENDER_REPORT_TOTAL_KEY_LENGTH                      STRING_LITERAL_LENGTH( DEFENDER_REPORT_TOTAL_KEY )

#define DEFENDER_REPORT_LISTENING_TCP_PORTS_KEY               DEFENDER_REPORT_SELECT_KEY( "listening_tcp_ports", "tp" )
#define DEFENDER_REPORT_LISTENING_TCP_PORTS_KEY_LENGTH        STRING_LITERAL_LENGTH( DEFENDER_REPORT_LISTENING_TCP_PORTS_KEY )

#define DEFENDER_REPORT_PORTS_KEY                             DEFENDER_REPORT_SELECT_KEY( "ports", "pts" )
#define DEFENDER_REPORT_PORTS_KEYLENGTH                       STRING_LITERAL_LENGTH( DEFENDER_REPORT_PORTS_KEY )

#define DEFENDER_REPORT_PORT_KEY                              DEFENDER_REPORT_SELECT_KEY( "port", "pt" )
#define DEFENDER_REPORT_PORT_KEY_LENGTH                       STRING_LITERAL_LENGTH( DEFENDER_REPORT_PORT_KEY )

#define DEFENDER_REPORT_INTERFACE_KEY                         DEFENDER_REPORT_SELECT_KEY( "interface", "if" )
#define DEFENDER_REPORT_INTERFACE_KEY_LENGTH                  STRING_LITERAL_LENGTH( DEFENDER_REPORT_INTERFACE_KEY )

#define DEFENDER_REPORT_LISTENING_UDP_PORTS_KEY               DEFENDER_REPORT_SELECT_KEY( "listening_udp_ports", "up" )
#define DEFENDER_REPORT_LISTENING_UDP_PORTS_KEY_LENGTH        STRING_LITERAL_LENGTH( DEFENDER_REPORT_LISTENING_UDP_PORTS_KEY )

#define DEFENDER_REPORT_NETWORK_STATS_KEY                     DEFENDER_REPORT_SELECT_KEY( "network_stats", "ns" )
#define DEFENDER_REPORT_NETWORK_STATS_KEY_LENGTH              STRING_LITERAL_LENGTH( DEFENDER_REPORT_NETWORK_STATS_KEY )

#define DEFENDER_REPORT_BYTES_IN_KEY                          DEFENDER_REPORT_SELECT_KEY( "bytes_in", "bi" )
#define DEFENDER_REPORT_BYTES_IN_KEY_LENGTH                   STRING_LITERAL_LENGTH( DEFENDER_REPORT_BYTES_IN_KEY )

#define DEFENDER_REPORT_BYTES_OUT_KEY                         DEFENDER_REPORT_SELECT_KEY( "bytes_out", "bo" )
#define DEFENDER_REPORT_BYTES_OUT_KEY_LENGTH                  STRING_LITERAL_LENGTH( DEFENDER_REPORT_BYTES_OUT_KEY )

#define DEFENDER_REPORT_PACKETS_IN_KEY                        DEFENDER_REPORT_SELECT_KEY( "packets_in", "pi" )
#define DEFENDER_REPORT_PACKETS_IN_KEY_LENGTH                 STRING_LITERAL_LENGTH( DEFENDER_REPORT_PACKETS_IN_KEY )

#define DEFENDER_REPORT_PACKETS_OUT_KEY                       DEFENDER_REPORT_SELECT_KEY( "packets_out", "po" )
#define DEFENDER_REPORT_PACKETS_OUT_KEY_LENGTH                STRING_LITERAL_LENGTH( DEFENDER_REPORT_PACKETS_OUT_KEY )

/*-----------------------------------------------------------*/

/**
 * @brief Populate topic string for a subscription request.
 *
 * @param[in] pBuffer The buffer to write the topic string into.
 * @param[in] bufferLength The length of the buffer.
 * @param[in] pThingName The device's thingName as registered with AWS IoT.
 * @param[in] thingNameLength The length of the thing name.
 * @param[in] api The desired Device Defender API.
 * @param[out] pOutLength The length of the topic string written to the buffer.
 *
 * @return #DefenderSuccess if the topic string is written to the buffer;
 * #DefenderBadParameter if invalid parameters are passed;
 * #DefenderBufferTooSmall if the buffer cannot hold the full topic string.
 */
DefenderStatus_t Defender_GetTopic( char * pBuffer,
                                    uint32_t bufferLength,
                                    const char * pThingName,
                                    uint16_t thingNameLength,
                                    DefenderTopic_t api,
                                    uint32_t * pOutLength );

/*-----------------------------------------------------------*/

/**
 * @brief Check if the given topic is one of the Device Defender topics.
 *
 * The function outputs which API the topic is for. It also optionally outputs
 * the starting location and length of the thing name in the given topic.
 *
 * @param[in] pTopic The topic string to check.
 * @param[in] topicLength The length of the topic string.
 * @param[out] pOutApi The defender topic API value.
 * @param[out] ppOutThingName Optional parameter to output the beginning of the
 *             thing name in the topic string. Pass NULL if not needed.
 * @param[out] pOutThingNameLength Optional parameter to output the length of
 *             the thing name in the topic string. Pass NULL if not needed.
 *
 * @return #DefenderSuccess if the topic is one of the defender topics;
 * #DefenderBadParameter if invalid parameters are passed;
 * #DefenderNoMatch if the topic is NOT one of the defender topics (parameter
 * pOutApi gets #DefenderInvalidTopic).
 */
DefenderStatus_t Defender_MatchTopic( const char * pTopic,
                                      uint16_t topicLength,
                                      DefenderTopic_t * pOutApi,
                                      const char ** ppOutThingName,
                                      uint16_t * pOutThingNameLength );

/*-----------------------------------------------------------*/

#endif /* DEFENDER_H_ */
