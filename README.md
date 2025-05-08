# SCPI UDP Helper Library

Basic SCPI over UDP helper library

Usage:

```c
static scpi_device_udp_t tenma72_13200;
static uint8_t scpi_tx_buf[UINT16_MAX] = {0};
static size_t  scpi_tx_len = 0;
static uint8_t scpi_rx_buf[UINT16_MAX] = {0};
static size_t  scpi_rx_len = 0;

tenma72_13200.addr = inet_addr("10.10.0.2");
tenma72_13200.port = htons(18190);

scpi_tx_len = snprintf((char*)(scpi_tx_buf), UINT16_MAX, "*IDN?\r\n");
scpi_udp_query(&tenma72_13200, scpi_tx_buf, scpi_tx_len, scpi_rx_buf, 
               UINT16_MAX, &scpi_rx_len);

fprintf(stdout, "[ECHO]\t%s\r\n", scpi_tx_buf);
fprintf(stdout, "[RECV]\t%s\r\n", scpi_rx_buf);
```

