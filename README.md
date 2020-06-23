# trigram

Overview:

Trigram is a tool that helps track how well you socially distance by using SCAN_REQUEST packets from the cellphones of those around you
The idea is to tune the TX power of NRF52 bluetooth radio to limit advertisement range, so that NRF52 is local maximum and global minimum
If NRF52 BLE stack can receive SCAN_REQUEST, a device must be within NRF52 advertisement range

After testing in open environment, -40dBM TX power seems to limit range to about ~8ft
We can use rate of SCAN_REQUEST packets, combined with the trigram_app to calculate a probable device within 6ft
The trigram_app uses a magnetometer to try to calibrate real-time readings that may be influenced by ferromagnetic metals in environment

Getting started:  

Get NRF52840 DK and NRF52832 DK  
Download the latest NRF_SDK from : https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download  
Place ble_app_trigram_recv_w_spim and ble_app_uart_trigram_send_w_spis in NRF_SDK/examples/ble_peripheral  

Note: firmware in ble_app_trigram_recv_w_spim is flashed onto NRF52840 DK  
Open ble_app_trigram_recv_w_spim/pca10056/s140/ses to get started  
Note: firmware in ble_app_uart_trigram_send_w_spis in flashed onto NRF52832 DK  
Open ble_app_uart_trigram_send_w_spis/pca10040/s132/ses to get started  

Connect SPIM, SPIS pins and GND  
NRF52840 DK         ->          NRF52832  
P0.27(CLK)          ->          P0.27  
P0.26(MISO)         ->          P0.26  
P0.02(MOSI)         ->          P0.02  
P1.13(CS)           ->          P0.23  
GND                 ->          GND  

Operation process:

If you have not downloaded trigram_app yet, please do so  
Power NRF52832 DK first, and it will advertise as NORDIC_UART. Connect the trigram_app to it.  
Power NRF52840 DK second, and bluetooth MAC addresses will begin streaming to app.
