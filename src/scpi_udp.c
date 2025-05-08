/**
 * @file      scpi_udp.c
 * @author    Casey Boyes (github.com@casey-e-boyes)
 * @date      2025-05-08
 * @copyright Copyright (c) 2025 Casey Boyes. All rights reserved.
 * 
 * @brief
 */
#include "scpi_udp.h"

scpi_error_t
scpi_udp_query(
    const scpi_device_udp_t* const dev,
    const uint8_t* const message,
    const size_t sz_message,
    uint8_t* const reply,
    const size_t sz_reply_limit,
    ssize_t* const sz_reply
) {
    int soc_rx = socket(AF_INET, SOCK_DGRAM, 0);

    if (soc_rx == -1) {
        goto cleanup;
    }

    struct sockaddr_in soc_addr_in = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port        = dev->port,
        .sin_family      = AF_INET
    };
    socklen_t soc_addr_in_len = sizeof(soc_addr_in);

    int soc_tx = socket(AF_INET, SOCK_DGRAM, 0);

    if (soc_tx == -1) {
        goto cleanup;
    }
    
    struct sockaddr_in soc_addr_out = {
        .sin_addr.s_addr = dev->addr,
        .sin_port        = dev->port,
        .sin_family      = AF_INET
    };

    if (bind(soc_rx, (struct sockaddr*)(&soc_addr_in), sizeof(soc_addr_in)) < 0) {
        goto cleanup;
    }

    ssize_t bytes_sent = sendto(soc_tx, (void*)(message), sz_message, 0, 
                                (struct sockaddr*)(&soc_addr_out), 
                                sizeof(soc_addr_out));

    if (bytes_sent != sz_message) {
        goto cleanup;
    }

    *sz_reply = recvfrom(soc_rx, reply, sz_reply_limit, 0, 
                         (struct sockaddr*)(&soc_addr_in),
                         &soc_addr_in_len);

    if (*sz_reply == -1) {
        goto cleanup;
    }

    close(soc_rx);
    close(soc_tx);

    return SCPI_ERROR_NONE;

    cleanup:
        close(soc_rx);
        close(soc_tx);
        return SCPI_ERROR_FAIL;
}

scpi_error_t
scpi_udp_command(
    const scpi_device_udp_t* const dev,
    const uint8_t* const message,
    const size_t sz_message
) {
    int soc_tx = socket(AF_INET, SOCK_DGRAM, 0);

    if (soc_tx == -1) {
        goto cleanup;
    }

    struct sockaddr_in soc_addr_out = {
        .sin_addr.s_addr = dev->addr,
        .sin_port        = dev->port,
        .sin_family      = AF_INET
    };

    ssize_t bytes_sent = sendto(soc_tx, (void*)(message), sz_message, 0, 
                                (struct sockaddr*)(&soc_addr_out), 
                                sizeof(soc_addr_out));

    if (bytes_sent != sz_message) {
        goto cleanup;
    }

    close(soc_tx);

    return SCPI_ERROR_NONE;

    cleanup:
        close(soc_tx);
        return SCPI_ERROR_FAIL;
}
