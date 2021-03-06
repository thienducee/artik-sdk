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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <gio/gio.h>
#pragma GCC diagnostic pop
#include "core.h"
#include "adapter.h"
#include "device.h"

artik_error bt_set_scan_filter(artik_bt_scan_filter * filter)
{
	GError *e = NULL;
	GVariantBuilder *b, *b1;
	GVariant *v, *f;
	gchar *type;
	guint i;

	if (filter != NULL) {
		log_dbg("bt_set_scan_filter");

		b = g_variant_builder_new(G_VARIANT_TYPE("a{sv}"));
		b1 = g_variant_builder_new(G_VARIANT_TYPE("as"));

		if (filter->type == 1)
			type = "bredr";
		else if (filter->type == 2)
			type = "le";
		else
			type = "auto";

		log_dbg("type: %s", type);
		g_variant_builder_add(b, "{sv}", "Transport",
				g_variant_new_string(type));

		if (filter->uuid_length < 1) {
			filter->uuid_length = 0;
			filter->uuid_list = NULL;
		}

		for (i = 0; i < filter->uuid_length; i++) {
			g_variant_builder_add(b1, "s", filter->uuid_list[i].uuid);
			log_dbg("uuid: %s", filter->uuid_list[i].uuid);
		}
		g_variant_builder_add(b, "{sv}", "UUIDs", g_variant_new("as", b1));

		g_variant_builder_add(b, "{sv}", "RSSI",
				g_variant_new_int16(filter->rssi));
		log_dbg("rssi: %d", filter->rssi);

		f = g_variant_new("(a{sv})", b);

		g_variant_builder_unref(b);
		g_variant_builder_unref(b1);
	} else {
		log_dbg("%s: remove filter", __func__);
		f = g_variant_new("(a{sv})", NULL);
	}

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_ADAPTER1,
		"SetDiscoveryFilter",
		f, NULL,
		G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_set_alias(const char *alias)
{
	GVariant *v;
	GError *e = NULL;

	if (alias == NULL)
		return S_OK;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES,
		"Set",
		g_variant_new("(ssv)", DBUS_IF_ADAPTER1, "Alias",
				g_variant_new_string(alias)),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_set_powered(bool powered)
{
	GVariant *v;
	GError *e = NULL;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES,
		"Set",
		g_variant_new("(ssv)", DBUS_IF_ADAPTER1, "Powered",
				g_variant_new_boolean(powered)),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_set_discoverable(bool discoverable)
{
	GVariant *v;
	GError *e = NULL;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES,
		"Set",
		g_variant_new("(ssv)", DBUS_IF_ADAPTER1, "Discoverable",
				g_variant_new_boolean(discoverable)),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_set_pairable(bool pairable)
{
	GVariant *v;
	GError *e = NULL;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES,
		"Set",
		g_variant_new("(ssv)", DBUS_IF_ADAPTER1, "Pairable",
				g_variant_new_boolean(pairable)),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_set_pairableTimeout(unsigned int timeout)
{
	GVariant *v;
	GError *e = NULL;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES,
		"Set",
		g_variant_new("(ssv)", DBUS_IF_ADAPTER1, "PairableTimeout",
				g_variant_new_uint32(timeout)),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_set_discoverableTimeout(unsigned int timeout)
{
	GVariant *v;
	GError *e = NULL;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES,
		"Set",
		g_variant_new("(ssv)", DBUS_IF_ADAPTER1, "DiscoverableTimeout",
				g_variant_new_uint32(timeout)),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_start_scan(void)
{
	GError *e = NULL;
	GVariant *v;

	log_dbg("%s", __func__);

	bt_remove_unpaired_devices();

	if (bt_is_scanning())
		return E_BT_ERROR;

	v = g_dbus_connection_call_sync(hci.conn, DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0, DBUS_IF_ADAPTER1,
		"StartDiscovery", NULL, G_VARIANT_TYPE("()"),
		G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

artik_error bt_stop_scan(void)
{
	GVariant *v;
	GError *e = NULL;

	log_dbg("%s", __func__);

	if (!bt_is_scanning())
		return E_BT_ERROR;

	v = g_dbus_connection_call_sync(hci.conn, DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_ADAPTER1, "StopDiscovery", NULL,
		G_VARIANT_TYPE("()"), G_DBUS_CALL_FLAGS_NONE, -1, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	g_variant_unref(v);

	return S_OK;
}

bool bt_is_scanning(void)
{
	GError *e = NULL;
	GVariant *rst, *v;
	gboolean b;

	log_dbg("%s", __func__);

	rst = g_dbus_connection_call_sync(hci.conn, DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0, DBUS_IF_PROPERTIES, "Get",
		g_variant_new("(ss)", DBUS_IF_ADAPTER1, "Discovering"),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (bt_check_error(e) != S_OK)
		return false;

	g_variant_get(rst, "(v)", &v);
	g_variant_get(v, "b", &b);
	g_variant_unref(rst);
	g_variant_unref(v);

	return b;
}

artik_error bt_get_adapter_info(artik_bt_adapter *adapter)
{
	GVariant *v;
	GError *e = NULL;

	log_dbg("%s", __func__);

	if (adapter == NULL)
		return E_BT_ERROR;

	v = g_dbus_connection_call_sync(
		hci.conn,
		DBUS_BLUEZ_BUS,
		DBUS_BLUEZ_OBJECT_PATH_HCI0,
		DBUS_IF_PROPERTIES, "GetAll",
		g_variant_new("(s)", DBUS_IF_ADAPTER1),
		NULL, G_DBUS_CALL_FLAGS_NONE, G_MAXINT, NULL, &e);

	if (e) {
		log_err(e->message);
		g_error_free(e);
		return E_BT_ERROR;
	}

	_get_adapter_properties(v, adapter);

	g_variant_unref(v);

	return S_OK;
}
