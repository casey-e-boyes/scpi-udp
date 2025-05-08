/**
 * @file      scpi_udp.h
 * @author    Casey Boyes (github.com@casey-e-boyes)
 * @date      2025-05-08
 * @copyright Copyright (c) 2025 Casey Boyes. All rights reserved.
 * 
 * @brief
 */
#ifndef SCPI_UDP_H_INCLUDED
#define SCPI_UDP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <strings.h>
#include <unistd.h> 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>

// TODO: Implement macros to handle commands and queries in a more compact manner
// #define scpi_command(dev, fmt, ...)
// #define scpi_query(dev, fmt, ...)

typedef enum scpi_error_t {
    SCPI_ERROR_NONE = 0U,
    SCPI_ERROR_FAIL = 1U,
} scpi_error_t;

typedef struct scpi_device_udp_t {
    in_addr_t addr;
    uint16_t  port;
} scpi_device_udp_t;


scpi_error_t
scpi_udp_query(
    const scpi_device_udp_t* const dev,
    const uint8_t* const message,
    const size_t sz_message,
    uint8_t* const reply,
    const size_t sz_reply_limit,
    ssize_t* const sz_reply
);

scpi_error_t
scpi_udp_command(
    const scpi_device_udp_t* const dev,
    const uint8_t* const message,
    const size_t sz_message
);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SCPI_UDP_H_INCLUDED */
