/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "sdk_config.h"
#include "nrf_spis.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_delay.h"
#include "spis.h"

void spis_init(){
  nrf_spis_pins_set(NRF_SPIS0, SER_CON_SPIS_SCK_PIN, SER_CON_SPIS_MOSI_PIN, SER_CON_SPIS_MISO_PIN, SER_CON_SPIS_CSN_PIN);
  //nrf_spis_frequency_set(NRF_SPIS0, NRF_SPIS_FREQ_1M);
  //SCK active high, sample on leading edge of clock, most significant bit shifted out first.
  nrf_spis_configure(NRF_SPIS0, NRF_SPIS_MODE_0, NRF_SPIS_BIT_ORDER_MSB_FIRST);
  nrf_spis_enable(NRF_SPIS0);
  nrf_gpio_cfg_input(SER_CON_SPIS_CSN_PIN, NRF_GPIO_PIN_PULLUP);
}

void spis_rx(char* tx_buffer, char* rx_buffer, uint8_t buffer_length){
  nrf_spis_rx_buffer_set(NRF_SPIS0, rx_buffer, buffer_length);
  nrf_spis_tx_buffer_set(NRF_SPIS0, tx_buffer, buffer_length);
  while(nrf_gpio_pin_read(SER_CON_SPIS_CSN_PIN)){
  }
  nrf_spis_event_clear(NRF_SPIS0, NRF_SPIS_EVENT_END);
  nrf_spis_task_trigger(NRF_SPIS0, NRF_SPIS_TASK_RELEASE);
  while(!nrf_spis_event_check(NRF_SPIS0, NRF_SPIS_EVENT_END)){
  }
}