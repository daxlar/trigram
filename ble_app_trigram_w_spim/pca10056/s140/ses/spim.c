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
#include "nrf_spim.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_delay.h"
#include "spim.h"

void spim_init(){
  nrf_spim_pins_set(NRF_SPIM0, SER_APP_SPIM0_SCK_PIN, SER_APP_SPIM0_MOSI_PIN, SER_APP_SPIM0_MISO_PIN);
  nrf_spim_frequency_set(NRF_SPIM0, NRF_SPIM_FREQ_125K);
  //SCK active high, sample on leading edge of clock, most significant bit shifted out first.
  nrf_spim_configure(NRF_SPIM0, NRF_SPIM_MODE_0, NRF_SPIM_BIT_ORDER_MSB_FIRST);
  nrf_spim_enable(NRF_SPIM0);
}

void spim_tx(char* tx_buffer, char* rx_buffer, uint8_t buffer_length){
    //set tx EASYDMA buffer
    nrf_spim_tx_buffer_set(NRF_SPIM0, tx_buffer, buffer_length);
    nrf_spim_rx_buffer_set(NRF_SPIM0, rx_buffer, buffer_length);
    //setup gpio for CS line
    nrf_gpio_cfg_output(SER_APP_SPIM0_SS_PIN);
    //set CS line low to begin transaction
    nrf_gpio_pin_clear(SER_APP_SPIM0_SS_PIN);
    //reset NRF_SPIM_EVENT_END event to reset EASYDMA
    nrf_spim_event_clear(NRF_SPIM0, NRF_SPIM_EVENT_END);
    //start SPIM transaction
    nrf_spim_task_trigger(NRF_SPIM0, NRF_SPIM_TASK_START);
    while(!nrf_spim_event_check(NRF_SPIM0, NRF_SPIM_EVENT_END)){
    }
    nrf_gpio_pin_set(SER_APP_SPIM0_SS_PIN);
}
