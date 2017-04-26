#pragma once

#include <vector>
#include "application.h"

inline std::vector<uint8_t> spi_transfer(std::vector<uint8_t> &tx_buffer)
{
    std::vector<uint8_t> rx_buffer;
    rx_buffer.resize(tx_buffer.size());
    SPI.transfer(tx_buffer.data(), rx_buffer.data(), rx_buffer.size(), NULL);
    return rx_buffer;
}
