
#include <stdint.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <linux/rtnetlink.h>
#include <netpacket/packet.h>
#include <linux/filter.h>
#include <linux/errqueue.h>

#include <linux/pkt_sched.h>
#include <netlink/object-api.h>
#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/handlers.h>

#include "sync.h"

#define LOG_TAG  "WifiHAL"

#include <utils/Log.h>

#include "wifi_hal.h"
#include "common.h"
#include "cpp_bindings.h"

/* Internal radio statistics structure in the driver */
typedef struct {
	wifi_radio radio;
	uint32_t on_time;
	uint32_t tx_time;
	uint32_t rx_time;
	uint32_t on_time_scan;
	uint32_t on_time_nbd;
	uint32_t on_time_gscan;
	uint32_t on_time_roam_scan;
	uint32_t on_time_pno_scan;
	uint32_t on_time_hs20;
	uint32_t num_channels;
	wifi_channel_stat channels[];
} wifi_radio_stat_internal;

enum {
    LSTATS_SUBCMD_GET_INFO = ANDROID_NL80211_SUBCMD_LSTATS_RANGE_START,
	LSTATS_SUBCMD_SET_INFO,
	LSTATS_SUBCMD_CLEAR_INFO,
};

class GetLinkStatsCommand : public WifiCommand
{
    wifi_stats_result_handler mHandler;
public:
    GetLinkStatsCommand(wifi_interface_handle iface, wifi_stats_result_handler handler)
        : WifiCommand("GetLinkStatsCommand", iface, 0), mHandler(handler)
    { }

    virtual int create() {
        // ALOGI("Creating message to get link statistics; iface = %d", mIfaceInfo->id);

        int ret = mMsg.create(GOOGLE_OUI, LSTATS_SUBCMD_GET_INFO);
        if (ret < 0) {
            ALOGE("Failed to create %x - %d", LSTATS_SUBCMD_GET_INFO, ret);
            return ret;
        }

        return ret;
    }

protected:
    virtual int handleResponse(WifiEvent& reply) {

        // ALOGI("In GetLinkStatsCommand::handleResponse");

        if (reply.get_cmd() != NL80211_CMD_VENDOR) {
            ALOGD("Ignoring reply with cmd = %d", reply.get_cmd());
            return NL_SKIP;
        }

        int id = reply.get_vendor_id();
        int subcmd = reply.get_vendor_subcmd();

        // ALOGI("Id = %0x, subcmd = %d", id, subcmd);

        void *data = reply.get_vendor_data();
        int len = reply.get_vendor_data_len();
        wifi_radio_stat *radio_stat =
            convertToExternalRadioStatStructure((wifi_radio_stat_internal *)data);
        if (!radio_stat) {
            ALOGE("Invalid stats pointer received");
            return NL_SKIP;
        }
        if (radio_stat->num_channels > 11) {
            ALOGE("Incorrect number of channels = %d", radio_stat->num_channels);
            // dump data before num_channels
            ALOGE("radio: = %d", radio_stat->radio);
            ALOGE("on_time: = %d", radio_stat->on_time);
            ALOGE("tx_time: = %d", radio_stat->tx_time);
            ALOGE("rx_time: = %d", radio_stat->rx_time);
            ALOGE("on_time_scan: = %d", radio_stat->on_time_scan);
            ALOGE("on_time_nbd: = %d", radio_stat->on_time_nbd);
            ALOGE("on_time_gscan: = %d", radio_stat->on_time_gscan);
            ALOGE("on_time_pno_scan: = %d", radio_stat->on_time_pno_scan);
            ALOGE("on_time_hs20: = %d", radio_stat->on_time_hs20);
            free(radio_stat);
            return NL_SKIP;
        }
        wifi_iface_stat *iface_stat =
            (wifi_iface_stat *)((char *)&((wifi_radio_stat_internal *)data)->channels
                + radio_stat->num_channels * sizeof(wifi_channel_stat));
        (*mHandler.on_link_stats_results)(id, iface_stat, 1, radio_stat);
        free(radio_stat);
        return NL_OK;
    }

private:
    wifi_radio_stat *convertToExternalRadioStatStructure(wifi_radio_stat_internal *internal_stat_ptr) {
        wifi_radio_stat *external_stat_ptr = NULL;
        if (internal_stat_ptr) {
            uint32_t channel_size = internal_stat_ptr->num_channels * sizeof(wifi_channel_stat);
            uint32_t total_size = sizeof(wifi_radio_stat) + channel_size;
            external_stat_ptr = (wifi_radio_stat *)malloc(total_size);
            if (external_stat_ptr) {
                external_stat_ptr->radio = internal_stat_ptr->radio;
                external_stat_ptr->on_time = internal_stat_ptr->on_time;
                external_stat_ptr->tx_time = internal_stat_ptr->tx_time;
                external_stat_ptr->rx_time = internal_stat_ptr->rx_time;
                external_stat_ptr->tx_time_per_levels = NULL;
                external_stat_ptr->num_tx_levels = 0;
                external_stat_ptr->on_time_scan = internal_stat_ptr->on_time_scan;
                external_stat_ptr->on_time_nbd = internal_stat_ptr->on_time_nbd;
                external_stat_ptr->on_time_gscan = internal_stat_ptr->on_time_gscan;
                external_stat_ptr->on_time_roam_scan = internal_stat_ptr->on_time_roam_scan;
                external_stat_ptr->on_time_pno_scan = internal_stat_ptr->on_time_pno_scan;
                external_stat_ptr->on_time_hs20 = internal_stat_ptr->on_time_hs20;
                external_stat_ptr->num_channels = internal_stat_ptr->num_channels;
                if (internal_stat_ptr->num_channels) {
                    memcpy(&(external_stat_ptr->channels), &(internal_stat_ptr->channels),
                        channel_size);
                }
            }
        }
        return external_stat_ptr;
    }
};

class RTKGetLinkStatsCommand : public WifiCommand
{
    wifi_stats_result_handler mHandler;
public:
    RTKGetLinkStatsCommand(wifi_interface_handle iface, wifi_stats_result_handler handler)
        : WifiCommand("GetLinkStatsCommand", iface, 0), mHandler(handler)
    { }

    virtual int create() {
        // ALOGI("Creating message to get link statistics; iface = %d", mIfaceInfo->id);

        int ret = mMsg.create(GOOGLE_OUI, LSTATS_SUBCMD_GET_INFO);
        if (ret < 0) {
            ALOGE("Failed to create %x - %d", LSTATS_SUBCMD_GET_INFO, ret);
            return ret;
        }

        return ret;
    }

protected:
    virtual int handleResponse(WifiEvent& reply) {

        // ALOGI("In GetLinkStatsCommand::handleResponse");

        if (reply.get_cmd() != NL80211_CMD_VENDOR) {
            ALOGD("Ignoring reply with cmd = %d", reply.get_cmd());
            return NL_SKIP;
        }

        int id = reply.get_vendor_id();
        int subcmd = reply.get_vendor_subcmd();

        // ALOGI("Id = %0x, subcmd = %d", id, subcmd);

        void *data = reply.get_vendor_data();
        int len = reply.get_vendor_data_len();
        wifi_radio_stat *radio_stat = (wifi_radio_stat *)data;
	radio_stat->tx_time_per_levels = (u32*)((char*)data + sizeof(wifi_radio_stat) + sizeof(wifi_iface_stat));
#if 0
	ALOGE("radio: = %d", radio_stat->radio);
        ALOGE("on_time: = %u ms", radio_stat->on_time);
        ALOGE("tx_time: = %u ms", radio_stat->tx_time);
	ALOGE("num_tx_levels: = %u", radio_stat->num_tx_levels);
	ALOGE("tx_time_per_levels: = %u ms", radio_stat->tx_time_per_levels[0]);
        ALOGE("rx_time: = %u ms", radio_stat->rx_time);
        ALOGE("on_time_scan: = %u ms", radio_stat->on_time_scan);
        ALOGE("on_time_nbd: = %u ms", radio_stat->on_time_nbd);
        ALOGE("on_time_gscan: = %u ms", radio_stat->on_time_gscan);
        ALOGE("on_time_pno_scan: = %u ms", radio_stat->on_time_pno_scan);
        ALOGE("on_time_hs20: = %u ms", radio_stat->on_time_hs20);
#endif
	if (!radio_stat) {
            ALOGE("Invalid stats pointer received");
            return NL_SKIP;
        }
        if (radio_stat->num_channels > 11) {
            ALOGE("Incorrect number of channels = %d", radio_stat->num_channels);
            // dump data before num_channels
            ALOGE("radio: = %d", radio_stat->radio);
            ALOGE("on_time: = %u ms", radio_stat->on_time);
            ALOGE("tx_time: = %u ms", radio_stat->tx_time);
            ALOGE("rx_time: = %u ms", radio_stat->rx_time);
            ALOGE("on_time_scan: = %u ms", radio_stat->on_time_scan);
            ALOGE("on_time_nbd: = %u ms", radio_stat->on_time_nbd);
            ALOGE("on_time_gscan: = %u ms", radio_stat->on_time_gscan);
            ALOGE("on_time_pno_scan: = %u ms", radio_stat->on_time_pno_scan);
            ALOGE("on_time_hs20: = %u ms", radio_stat->on_time_hs20);
            free(radio_stat);
            return NL_SKIP;
        }
	wifi_iface_stat *iface_stat = NULL;
	iface_stat = (wifi_iface_stat *)((char* )data + sizeof(wifi_radio_stat));

	if(*mHandler.on_link_stats_results == NULL) {
		ALOGE("*mHandler.on_link_stats_results is NULL");
	} else {
		(*mHandler.on_link_stats_results)(id, iface_stat, 1, radio_stat);
	}
        //free(radio_stat);
        return NL_OK;
    }

};

class RTKSetLinkStatsCommand : public WifiCommand
{
    wifi_stats_result_handler mHandler;
public:
    RTKSetLinkStatsCommand(wifi_interface_handle iface)
        : WifiCommand("SetLinkStatsCommand", iface, 0)
    { }

    virtual int create() {
        // ALOGI("Creating message to get link statistics; iface = %d", mIfaceInfo->id);

        int ret = mMsg.create(GOOGLE_OUI, LSTATS_SUBCMD_SET_INFO);
        if (ret < 0) {
            ALOGE("Failed to create %x - %d", LSTATS_SUBCMD_SET_INFO, ret);
            return ret;
        }

        return ret;
    }

protected:
    virtual int handleResponse(WifiEvent& reply) {

        // ALOGI("In GetLinkStatsCommand::handleResponse");

        if (reply.get_cmd() != NL80211_CMD_VENDOR) {
            ALOGD("Ignoring reply with cmd = %d", reply.get_cmd());
            return NL_SKIP;
        }

        int id = reply.get_vendor_id();
        int subcmd = reply.get_vendor_subcmd();

        // ALOGI("Id = %0x, subcmd = %d", id, subcmd);

        void *data = reply.get_vendor_data();
        int len = reply.get_vendor_data_len();
         return NL_OK;
    }

};

class RTKClearLinkStatsCommand : public WifiCommand
{
    wifi_stats_result_handler mHandler;
public:
    RTKClearLinkStatsCommand(wifi_interface_handle iface)
        : WifiCommand("ClearLinkStatsCommand", iface, 0)
    { }

    virtual int create() {
        // ALOGI("Creating message to get link statistics; iface = %d", mIfaceInfo->id);

        int ret = mMsg.create(GOOGLE_OUI, LSTATS_SUBCMD_CLEAR_INFO);
        if (ret < 0) {
            ALOGE("Failed to create %x - %d", LSTATS_SUBCMD_CLEAR_INFO, ret);
            return ret;
        }

        return ret;
    }

protected:
    virtual int handleResponse(WifiEvent& reply) {

        // ALOGI("In GetLinkStatsCommand::handleResponse");

        if (reply.get_cmd() != NL80211_CMD_VENDOR) {
            ALOGD("Ignoring reply with cmd = %d", reply.get_cmd());
            return NL_SKIP;
        }

        int id = reply.get_vendor_id();
        int subcmd = reply.get_vendor_subcmd();

        // ALOGI("Id = %0x, subcmd = %d", id, subcmd);

        void *data = reply.get_vendor_data();
        int len = reply.get_vendor_data_len();
         return NL_OK;
    }

};
wifi_error wifi_get_link_stats(wifi_request_id id,
        wifi_interface_handle iface, wifi_stats_result_handler handler)
{
	if (check_wifi_chip_type() == REALTEK_WIFI) {
		RTKGetLinkStatsCommand command(iface, handler);
		return (wifi_error) command.requestResponse();
	}
	GetLinkStatsCommand command(iface, handler);
	return (wifi_error) command.requestResponse();
}

wifi_error wifi_set_link_stats(
        wifi_interface_handle iface, wifi_link_layer_params params)
{
	if (check_wifi_chip_type() == REALTEK_WIFI) {
		RTKSetLinkStatsCommand command(iface);
		return (wifi_error) command.requestResponse();
	}
    /* Return success here since bcom HAL does not need set link stats. */
    return WIFI_SUCCESS;
}

wifi_error wifi_clear_link_stats(wifi_interface_handle iface,
      u32 stats_clear_req_mask, u32 *stats_clear_rsp_mask, u8 stop_req, u8 *stop_rsp)
{
	if (check_wifi_chip_type() == REALTEK_WIFI) {
		RTKClearLinkStatsCommand command(iface);
		return (wifi_error) command.requestResponse();
	}
    /* Return success here since bcom HAL does not support clear link stats. */
    return WIFI_SUCCESS;
}