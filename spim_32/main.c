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
 /*
#include "sdk_config.h"
//#include "nrf_drv_spis.h"
#include "nrf_spim.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

char tx_buff[9];
char rx_buff[9];


void spim_init(){
  nrf_spim_pins_set(NRF_SPIM0, SER_APP_SPIM0_SCK_PIN, SER_APP_SPIM0_MOSI_PIN, SER_APP_SPIM0_MISO_PIN);
  nrf_spim_frequency_set(NRF_SPIM0, NRF_SPIM_FREQ_125K);
  //SCK active high, sample on leading edge of clock, most significant bit shifted out first.
  nrf_spim_configure(NRF_SPIM0, NRF_SPIM_MODE_0, NRF_SPIM_BIT_ORDER_MSB_FIRST);
  nrf_spim_enable(NRF_SPIM0);
  nrf_spim_tx_buffer_set(NRF_SPIM0, tx_buff, 9);
  nrf_spim_rx_buffer_set(NRF_SPIM0, rx_buff, 9);

}

void fill_buffer(){
  tx_buff[0] = 'd';
  tx_buff[1] = 'e';
  tx_buff[2] = 'a';
  tx_buff[3] = 'd';
  tx_buff[4] = 'b';
  tx_buff[5] = 'e';
  tx_buff[6] = 'e';
  tx_buff[7] = 'f';
  tx_buff[8] = 'a';
  
}

void fill_buffer2(){
  tx_buff[0] = 'a';
  tx_buff[1] = 'b';
  tx_buff[2] = 'c';
  tx_buff[3] = 'd';
  tx_buff[4] = 'e';
  tx_buff[5] = 'f';
  tx_buff[6] = 'g';
  tx_buff[7] = 'h';
  tx_buff[8] = 'i';
  
}

void fill_buffer3(){
  tx_buff[0] = 'j';
  tx_buff[1] = 'k';
  tx_buff[2] = 'l';
  tx_buff[3] = 'm';
  tx_buff[4] = 'n';
  tx_buff[5] = 'o';
  tx_buff[6] = 'p';
  tx_buff[7] = 'q';
  tx_buff[8] = 'r';
}

int main(void)
{
    spim_init();
    fill_buffer();
    //nrf_gpio_cfg_pin_output(SER_CON_SPIS_CSN_PIN);
    nrf_gpio_cfg_output(SER_APP_SPIM0_SS_PIN);
    //nrf_gpio_pin_clear(SER_APP_SPIM0_SS_PIN);
    int counter = 0;
    
    
    while(1){
      //set CS LOW
      // DO THIS
      nrf_gpio_pin_clear(SER_APP_SPIM0_SS_PIN);
      nrf_spim_event_clear(NRF_SPIM0, NRF_SPIM_EVENT_END);
      nrf_spim_task_trigger(NRF_SPIM0, NRF_SPIM_TASK_START);
      //printf("stalling");
      bool check = false;
      while(!nrf_spim_event_check(NRF_SPIM0, NRF_SPIM_EVENT_END)){
      }
      nrf_gpio_pin_set(SER_APP_SPIM0_SS_PIN);
      nrf_delay_ms(1000);
      //printf("done?");
      //nrf_delay_ms(500);
      counter++;
      counter = counter % 3;
      if(counter == 0){
        fill_buffer();
      }
      if(counter == 1){
        fill_buffer2();
      }
      if(counter == 2){
        fill_buffer3();
      }
     
      nrf_spim_tx_buffer_set(NRF_SPIM0, tx_buff, 9);
      nrf_spim_rx_buffer_set(NRF_SPIM0, rx_buff, 9);
      //nrf_spim_enable(NRF_SPIM0);
    }
    return 0;
}
*/

#include "sdk_config.h"
#include "nrf_spis.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

char rx_buff[6];
char tx_buff[6];


void spis_init(){
  nrf_spis_pins_set(NRF_SPIS0, SER_CON_SPIS_SCK_PIN, SER_CON_SPIS_MOSI_PIN, SER_CON_SPIS_MISO_PIN, SER_CON_SPIS_CSN_PIN);
  //nrf_spis_frequency_set(NRF_SPIS0, NRF_SPIS_FREQ_1M);
  //SCK active high, sample on leading edge of clock, most significant bit shifted out first.
  nrf_spis_configure(NRF_SPIS0, NRF_SPIS_MODE_0, NRF_SPIS_BIT_ORDER_MSB_FIRST);
  nrf_spis_enable(NRF_SPIS0);
  nrf_spis_task_trigger(NRF_SPIS0, NRF_SPIS_TASK_RELEASE);
  nrf_spis_rx_buffer_set(NRF_SPIS0, rx_buff, 6);
  nrf_spis_tx_buffer_set(NRF_SPIS0, tx_buff, 6);
}

void fill_buffer(){
  rx_buff[0] = 'c';
  rx_buff[1] = 'a';
  rx_buff[2] = 'f';
  rx_buff[3] = 'e';
  rx_buff[4] = 'b';
  rx_buff[5] = 'a';
}

void print_buffer(){
  for(int i = 0; i < 6; i++){
    printf("%X", rx_buff[i]);
  }
  printf("\n");
}

int main(void)
{
    spis_init();
    fill_buffer();
    nrf_gpio_cfg_input(SER_CON_SPIS_CSN_PIN, NRF_GPIO_PIN_PULLUP);
    
    while(1){
      while(nrf_gpio_pin_read(SER_CON_SPIS_CSN_PIN)){
      }
      nrf_spis_event_clear(NRF_SPIS0, NRF_SPIS_EVENT_END);
      nrf_spis_task_trigger(NRF_SPIS0, NRF_SPIS_TASK_RELEASE);
      
      while(!nrf_spis_event_check(NRF_SPIS0, NRF_SPIS_EVENT_END)){
      }
      
      //nrf_delay_us(800);
      print_buffer();
      
      nrf_spis_task_trigger(NRF_SPIS0, NRF_SPIS_TASK_RELEASE);
      nrf_spis_rx_buffer_set(NRF_SPIS0, rx_buff, 6);
      nrf_spis_tx_buffer_set(NRF_SPIS0, tx_buff, 6);
      
    }
    return 0;
}