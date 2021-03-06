/*
 *
 * Copyright 2017 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 */

#ifndef INCLUDE_ARTIK_EAGLEYE530_PLATFORM_H_
#define INCLUDE_ARTIK_EAGLEYE530_PLATFORM_H_

/*! \file artik_eagleye530_platform.h
 *
 *  \brief Hardware specific definitions for the Seeed Eagleye530 Development
 *  platform
 *
 */

/* List of modules available for the platform */
static const artik_api_module artik_api_eagleye530_modules[] = {
	{ARTIK_MODULE_LOG,       (char *)"log",       (char *)"base"},
	{ARTIK_MODULE_LOOP,      (char *)"loop",      (char *)"base"},
	{ARTIK_MODULE_UTILS,     (char *)"utils",     (char *)"base"},
	{ARTIK_MODULE_GPIO,      (char *)"gpio",      (char *)"systemio"},
	{ARTIK_MODULE_I2C,       (char *)"i2c",       (char *)"systemio"},
	{ARTIK_MODULE_SERIAL,    (char *)"serial",    (char *)"systemio"},
	{ARTIK_MODULE_PWM,       (char *)"pwm",       (char *)"systemio"},
	{ARTIK_MODULE_ADC,       (char *)"adc",       (char *)"systemio"},
	{ARTIK_MODULE_HTTP,      (char *)"http",      (char *)"connectivity"},
	{ARTIK_MODULE_CLOUD,     (char *)"cloud",     (char *)"connectivity"},
	{ARTIK_MODULE_WIFI,      (char *)"wifi",      (char *)"wifi"},
	{ARTIK_MODULE_MEDIA,     (char *)"media",     (char *)"media"},
	{ARTIK_MODULE_TIME,      (char *)"time",      (char *)"base"},
	{ARTIK_MODULE_SECURITY,  (char *)"security",  (char *)"base"},
	{ARTIK_MODULE_SPI,       (char *)"spi",       (char *)"systemio"},
	{ARTIK_MODULE_BLUETOOTH, (char *)"bluetooth", (char *)"bluetooth"},
	{ARTIK_MODULE_ZIGBEE,    (char *)"zigbee",    (char *)"zigbee"},
	{ARTIK_MODULE_NETWORK,   (char *)"network",   (char *)"connectivity"},
	{ARTIK_MODULE_WEBSOCKET, (char *)"websocket", (char *)"connectivity"},
	{ARTIK_MODULE_LWM2M,     (char *)"lwm2m",     (char *)"lwm2m"},
	{ARTIK_MODULE_MQTT,      (char *)"mqtt",      (char *)"mqtt"},
	{ARTIK_MODULE_COAP,      (char *)"coap",      (char *)"coap"},
	{(artik_module_id_t)-1,  NULL,                NULL},
};

/* List of available GPIO IDs */
#define ARTIK_EAGLEYE530_GPIO0      128
#define ARTIK_EAGLEYE530_GPIO1      129
#define ARTIK_EAGLEYE530_GPIO2      130
#define ARTIK_EAGLEYE530_GPIO3      46
#define ARTIK_EAGLEYE530_GPIO4      14
#define ARTIK_EAGLEYE530_GPIO6      25
#define ARTIK_EAGLEYE530_GPIO7      0
#define ARTIK_EAGLEYE530_GPIO8      26
#define ARTIK_EAGLEYE530_GPIO9      27
#define ARTIK_EAGLEYE530_AGPIO0     161

/* List of available UART IDs */
#define ARTIK_EAGLEYE530_UART0      2

/* List of available PWMIO IDs */
#define ARTIK_EAGLEYE530_PWM0       ((0 << 8) | 0)
#define ARTIK_EAGLEYE530_PWM2       ((0 << 8) | 2)

/* List of available Analog Input IDs */
#define ARTIK_EAGLEYE530_ADC0       0
#define ARTIK_EAGLEYE530_ADC1       1

/* List of available I2C controllers  */
#define ARTIK_EAGLEYE530_I2C0       0

/* List of available SPI controllers  */
#define ARTIK_EAGLEYE530_SPI0       0

#endif /* INCLUDE_ARTIK_EAGLEYE530_PLATFORM_H_ */
