#include "esp_err.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include <stdint.h>
#include <memory.h>
#include <stdio.h>

#include "include/comunication.h"

Message controler_readings;

static uint8_t DRONE_MAC[]      = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
static uint8_t CONTROLLER_MAC[] = {0xDA, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

void OnDataSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status) {
	char* ss = status == ESP_NOW_SEND_SUCCESS ? "[ ] Delivery Success" : "[x] Delivery Fail";
	printf("%s", ss);
}

void print_controler_data(){
	printf("up: %d | down: %d | right: %d | left: %d | forward: %d | rear: %d\n",
		controler_readings.up, controler_readings.down, controler_readings.right, controler_readings.left, controler_readings.forward, controler_readings.rear);
}

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len) {
	memcpy(&controler_readings, data, sizeof(controler_readings));
	printf("Received %i from controller : \n", len);
	print_controler_data();
}

void comunication_init(enum device dev){
	const uint8_t *my_mac;
	const uint8_t *peer_mac;

	if (dev == drone) {
		my_mac   = DRONE_MAC;
		peer_mac = CONTROLLER_MAC;
	} else {
		my_mac   = CONTROLLER_MAC;
		peer_mac = DRONE_MAC;
	}

	// init wifi
	wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
	esp_wifi_init(&wifi_config);
	esp_wifi_set_mode(WIFI_MODE);
	esp_wifi_set_protocol(WIFI_IF, WIFI_PROTOCOL_LR);
	esp_wifi_set_mac(WIFI_IF, my_mac);
	esp_wifi_start();

	// init esp now
	if (esp_now_init() != ESP_OK){
		printf("[x] Failed to init ESP-NOW");
	};

	esp_now_register_send_cb(OnDataSent);

	esp_now_peer_info_t peer_info = {0};
	memcpy(peer_info.peer_addr, peer_mac, 6);
	peer_info.channel = 0;
	peer_info.encrypt = 0;

	if (esp_now_add_peer(&peer_info) != ESP_OK){
		printf("[x] Failed to add peer");
	};

	esp_now_register_recv_cb(OnDataRecv);
}

void controler_send_readings(){
	esp_now_send(DRONE_MAC, (uint8_t *) &controler_readings, sizeof(controler_readings));
}