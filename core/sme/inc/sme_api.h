/*
 * Copyright (c) 2012-2018 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#if !defined(__SME_API_H)
#define __SME_API_H

/**
 * file  smeApi.h
 *
 * brief prototype for SME APIs
 */

/*--------------------------------------------------------------------------
  Include Files
  ------------------------------------------------------------------------*/
#include "csr_api.h"
#include "qdf_lock.h"
#include "qdf_types.h"
#include "sir_api.h"
#include "cds_regdomain.h"
#include "sme_internal.h"
#include "wma_tgt_cfg.h"
#include "wma_fips_public_structs.h"
#include "wma_sar_public_structs.h"

#include "sme_rrm_internal.h"
#include "sir_types.h"
#include "scheduler_api.h"
#include "wlan_serialization_legacy_api.h"

/*--------------------------------------------------------------------------
  Preprocessor definitions and constants
  ------------------------------------------------------------------------*/

#define SME_SUMMARY_STATS         (1 << eCsrSummaryStats)
#define SME_GLOBAL_CLASSA_STATS   (1 << eCsrGlobalClassAStats)
#define SME_GLOBAL_CLASSD_STATS   (1 << eCsrGlobalClassDStats)
#define SME_PER_CHAIN_RSSI_STATS  (1 << csr_per_chain_rssi_stats)

#define sme_alert(params...) QDF_TRACE_FATAL(QDF_MODULE_ID_SME, params)
#define sme_err(params...) QDF_TRACE_ERROR(QDF_MODULE_ID_SME, params)
#define sme_warn(params...) QDF_TRACE_WARN(QDF_MODULE_ID_SME, params)
#define sme_info(params...) QDF_TRACE_INFO(QDF_MODULE_ID_SME, params)
#define sme_debug(params...) QDF_TRACE_DEBUG(QDF_MODULE_ID_SME, params)

#define sme_nofl_alert(params...) \
	QDF_TRACE_FATAL_NO_FL(QDF_MODULE_ID_SME, params)
#define sme_nofl_err(params...) \
	QDF_TRACE_ERROR_NO_FL(QDF_MODULE_ID_SME, params)
#define sme_nofl_warn(params...) \
	QDF_TRACE_WARN_NO_FL(QDF_MODULE_ID_SME, params)
#define sme_nofl_info(params...) \
	QDF_TRACE_INFO_NO_FL(QDF_MODULE_ID_SME, params)
#define sme_nofl_debug(params...) \
	QDF_TRACE_DEBUG_NO_FL(QDF_MODULE_ID_SME, params)

#define sme_alert_rl(params...) QDF_TRACE_FATAL_RL(QDF_MODULE_ID_SME, params)
#define sme_err_rl(params...) QDF_TRACE_ERROR_RL(QDF_MODULE_ID_SME, params)
#define sme_warn_rl(params...) QDF_TRACE_WARN_RL(QDF_MODULE_ID_SME, params)
#define sme_info_rl(params...) QDF_TRACE_INFO_RL(QDF_MODULE_ID_SME, params)
#define sme_debug_rl(params...) QDF_TRACE_DEBUG_RL(QDF_MODULE_ID_SME, params)

#define SME_ENTER() QDF_TRACE_ENTER(QDF_MODULE_ID_SME, "enter")
#define SME_EXIT() QDF_TRACE_EXIT(QDF_MODULE_ID_SME, "exit")

#define SME_SESSION_ID_ANY        50
#define SME_SESSION_ID_BROADCAST  0xFF

#define SME_INVALID_COUNTRY_CODE "XX"
#define INVALID_ROAM_ID 0

#define SME_SET_CHANNEL_REG_POWER(reg_info_1, val) do {	\
	reg_info_1 &= 0xff00ffff;	      \
	reg_info_1 |= ((val & 0xff) << 16);   \
} while (0)

#define SME_SET_CHANNEL_MAX_TX_POWER(reg_info_2, val) do { \
	reg_info_2 &= 0xffff00ff;	      \
	reg_info_2 |= ((val & 0xff) << 8);   \
} while (0)

#define SME_CONFIG_TO_ROAM_CONFIG 1
#define ROAM_CONFIG_TO_SME_CONFIG 2

#define NUM_OF_BANDS 2

#define SME_ACTIVE_LIST_CMD_TIMEOUT_VALUE (30*1000)
#define SME_CMD_TIMEOUT_VALUE (SME_ACTIVE_LIST_CMD_TIMEOUT_VALUE + 1000)

/* SME timeout for Start/Stop BSS commands is set to 10 secs */
#define SME_START_STOP_BSS_CMD_TIMEOUT (10 * 1000)
#define SME_CMD_START_STOP_BSS_TIMEOUT (SME_START_STOP_BSS_CMD_TIMEOUT + 1000)

/* SME timeout for vdev delete is set to 10 secs */
#define SME_VDEV_DELETE_CMD_TIMEOUT (10 * 1000)
#define SME_CMD_VDEV_CREATE_DELETE_TIMEOUT (SME_VDEV_DELETE_CMD_TIMEOUT + 1000)

/*--------------------------------------------------------------------------
  Type declarations
  ------------------------------------------------------------------------*/
typedef struct _smeConfigParams {
	tCsrConfigParam csrConfig;
	struct rrm_config_param rrmConfig;
	bool snr_monitor_enabled;
} tSmeConfigParams, *tpSmeConfigParams;

#ifdef FEATURE_WLAN_TDLS
#define SME_TDLS_MAX_SUPP_CHANNELS       128
#define SME_TDLS_MAX_SUPP_OPER_CLASSES   32

typedef struct _smeTdlsPeerCapParams {
	uint8_t isPeerResponder;
	uint8_t peerUapsdQueue;
	uint8_t peerMaxSp;
	uint8_t peerBuffStaSupport;
	uint8_t peerOffChanSupport;
	uint8_t peerCurrOperClass;
	uint8_t selfCurrOperClass;
	uint8_t peerChanLen;
	uint8_t peerChan[SME_TDLS_MAX_SUPP_CHANNELS];
	uint8_t peerOperClassLen;
	uint8_t peerOperClass[SME_TDLS_MAX_SUPP_OPER_CLASSES];
	uint8_t prefOffChanNum;
	uint8_t prefOffChanBandwidth;
	uint8_t opClassForPrefOffChan;
} tSmeTdlsPeerCapParams;

/**
 * eSmeTdlsPeerState - tdls peer state
 * @eSME_TDLS_PEER_STATE_PEERING: tdls connection in progress
 * @eSME_TDLS_PEER_STATE_CONNECTED: tdls peer is connected
 * @eSME_TDLS_PEER_STATE_TEARDOWN: tdls peer is tear down
 * @eSME_TDLS_PEER_ADD_MAC_ADDR: add peer mac into connection table
 * @eSME_TDLS_PEER_REMOVE_MAC_ADDR: remove peer mac from connection table
 */
typedef enum {
	eSME_TDLS_PEER_STATE_PEERING,
	eSME_TDLS_PEER_STATE_CONNECTED,
	eSME_TDLS_PEER_STATE_TEARDOWN,
	eSME_TDLS_PEER_ADD_MAC_ADDR,
	eSME_TDLS_PEER_REMOVE_MAC_ADDR,
} eSmeTdlsPeerState;

typedef struct _smeTdlsPeerStateParams {
	uint32_t vdevId;
	tSirMacAddr peerMacAddr;
	uint32_t peerState;
	tSmeTdlsPeerCapParams peerCap;
} tSmeTdlsPeerStateParams;

#define ENABLE_CHANSWITCH  1
#define DISABLE_CHANSWITCH 2
#define BW_20_OFFSET_BIT   0
#define BW_40_OFFSET_BIT   1
#define BW_80_OFFSET_BIT   2
#define BW_160_OFFSET_BIT  3
typedef struct sme_tdls_chan_switch_param_struct {
	uint32_t vdev_id;
	tSirMacAddr peer_mac_addr;
	uint16_t tdls_off_ch_bw_offset;/* Target Off Channel Bandwidth offset */
	uint8_t tdls_off_channel;      /* Target Off Channel */
	uint8_t tdls_off_ch_mode;      /* TDLS Off Channel Mode */
	uint8_t is_responder;          /* is peer responder or initiator */
	uint8_t opclass;           /* tdls operating class */
} sme_tdls_chan_switch_params;
#endif /* FEATURE_WLAN_TDLS */

/* Thermal Mitigation*/
typedef struct {
	uint16_t smeMinTempThreshold;
	uint16_t smeMaxTempThreshold;
} tSmeThermalLevelInfo;

#define SME_MAX_THERMAL_LEVELS (4)
#define SME_MAX_THROTTLE_LEVELS (4)

typedef struct {
	/* Array of thermal levels */
	tSmeThermalLevelInfo smeThermalLevels[SME_MAX_THERMAL_LEVELS];
	uint8_t smeThermalMgmtEnabled;
	uint32_t smeThrottlePeriod;
	uint8_t sme_throttle_duty_cycle_tbl[SME_MAX_THROTTLE_LEVELS];
} tSmeThermalParams;

typedef enum {
	SME_AC_BK = 0,
	SME_AC_BE = 1,
	SME_AC_VI = 2,
	SME_AC_VO = 3
} sme_ac_enum_type;

/*
 * Enumeration of the various TSPEC directions
 * From 802.11e/WMM specifications
 */
enum sme_qos_wmm_dir_type {
	SME_QOS_WMM_TS_DIR_UPLINK = 0,
	SME_QOS_WMM_TS_DIR_DOWNLINK = 1,
	SME_QOS_WMM_TS_DIR_RESV = 2,    /* Reserved */
	SME_QOS_WMM_TS_DIR_BOTH = 3,
};

/**
 * struct sme_oem_capability - OEM capability to be exchanged between host
 *                             and userspace
 * @ftm_rr: FTM range report capability bit
 * @lci_capability: LCI capability bit
 * @reserved1: reserved
 * @reserved2: reserved
 */
struct sme_oem_capability {
	uint32_t ftm_rr:1;
	uint32_t lci_capability:1;
	uint32_t reserved1:30;
	uint32_t reserved2;
};

/**
 * struct sme_5g_pref_params : 5G preference params to be read from ini
 * @rssi_boost_threshold_5g: RSSI threshold above which 5 GHz is favored
 * @rssi_boost_factor_5g: Factor by which 5GHz RSSI is boosted
 * @max_rssi_boost_5g: Maximum boost that can be applied to 5GHz RSSI
 * @rssi_penalize_threshold_5g: RSSI threshold below which 5G is not favored
 * @rssi_penalize_factor_5g: Factor by which 5GHz RSSI is penalized
 * @max_rssi_penalize_5g: Maximum penalty that can be applied to 5G RSSI
 */
struct sme_5g_band_pref_params {
	int8_t      rssi_boost_threshold_5g;
	uint8_t     rssi_boost_factor_5g;
	uint8_t     max_rssi_boost_5g;
	int8_t      rssi_penalize_threshold_5g;
	uint8_t     rssi_penalize_factor_5g;
	uint8_t     max_rssi_penalize_5g;
};

/**
 * struct sme_session_params: Session creation params passed by HDD layer
 * @session_open_cb: callback to be registered with SME for opening the session
 * @session_close_cb: callback to be registered with SME for closing the session
 * @callback: callback to be invoked for roaming events
 * @callback_ctx: user-supplied context to be passed back on roaming events
 * @self_mac_addr: Self mac address
 * @sme_session_id: SME session id
 * @type_of_persona: person type
 * @subtype_of_persona: sub type of persona
 */
struct sme_session_params {
	csr_session_open_cb  session_open_cb;
	csr_session_close_cb session_close_cb;
	csr_roam_complete_cb callback;
	void *callback_ctx;
	uint8_t *self_mac_addr;
	uint8_t sme_session_id;
	uint32_t type_of_persona;
	uint32_t subtype_of_persona;
};

#define MAX_CANDIDATE_INFO 10

/**
 * struct bss_candidate_info - Candidate bss information
 *
 * @bssid : BSSID of candidate bss
 * @status : status code for candidate bss
 */
struct bss_candidate_info {
	struct qdf_mac_addr bssid;
	uint32_t status;
};

/*
 * MBO transition reason codes
 */
enum {
	MBO_TRANSITION_REASON_UNSPECIFIED,
	MBO_TRANSITION_REASON_EXCESSIVE_FRAME_LOSS_RATE,
	MBO_TRANSITION_REASON_EXCESSIVE_DELAY_FOR_CURRENT_TRAFFIC,
	MBO_TRANSITION_REASON_INSUFFICIENT_BANDWIDTH_FOR_CURRENT_TRAFFIC,
	MBO_TRANSITION_REASON_LOAD_BALANCING,
	MBO_TRANSITION_REASON_LOW_RSSI,
	MBO_TRANSITION_REASON_RECEIVED_EXCESSIVE_RETRANSMISSIONS,
	MBO_TRANSITION_REASON_HIGH_INTERFERENCE,
	MBO_TRANSITION_REASON_GRAY_ZONE,
	MBO_TRANSITION_REASON_TRANSITIONING_TO_PREMIUM_AP,
};

/*-------------------------------------------------------------------------
  Function declarations and documenation
  ------------------------------------------------------------------------*/
QDF_STATUS sme_open(mac_handle_t mac_handle);
QDF_STATUS sme_init_chan_list(mac_handle_t hal, uint8_t *alpha2,
		enum country_src cc_src);
QDF_STATUS sme_close(mac_handle_t mac_handle);
QDF_STATUS sme_start(mac_handle_t mac_handle);

/**
 * sme_stop() - Stop all SME modules and put them at idle state
 * @mac_handle: Opaque handle to the MAC context
 *
 * The function stops each module in SME. Upon return, all modules are
 * at idle state ready to start.
 *
 * This is a synchronous call
 *
 * Return: QDF_STATUS_SUCCESS if SME is stopped.  Other status means
 *         SME failed to stop one or more modules but caller should
 *         still consider SME is stopped.
 */
QDF_STATUS sme_stop(mac_handle_t mac_handle);

/*
 * sme_open_session() - Open a session for given persona
 *
 * This is a synchronous API. For any protocol stack related activity
 * requires session to be opened. This API needs to be called to open
 * the session in SME module.
 *
 * hal: The handle returned by mac_open.
 * params: to initialize the session open params
 *
 * Return:
 * QDF_STATUS_SUCCESS - session is opened.
 * Other status means SME is failed to open the session.
 */
QDF_STATUS sme_open_session(mac_handle_t hal, struct sme_session_params *params);

/*
 * sme_close_session() - Close a session for given persona
 *
 * This is a synchronous API. This API needs to be called to close the session
 * in SME module before terminating the session completely.
 *
 * hal: The handle returned by mac_open.
 * session_id: A previous opened session's ID.
 *
 * Return:
 * QDF_STATUS_SUCCESS - session is closed.
 * Other status means SME is failed to open the session.
 */
QDF_STATUS sme_close_session(mac_handle_t hal, uint8_t sessionId);
void sme_set_curr_device_mode(mac_handle_t mac_handle,
			      enum QDF_OPMODE currDeviceMode);
QDF_STATUS sme_update_roam_params(mac_handle_t mac_handle,
				  uint8_t session_id,
				  struct roam_ext_params *roam_params_src,
				  int update_param);
QDF_STATUS sme_update_config(mac_handle_t mac_handle,
			     tpSmeConfigParams pSmeConfigParams);

QDF_STATUS sme_set11dinfo(mac_handle_t mac_handle,
			  tpSmeConfigParams pSmeConfigParams);
QDF_STATUS sme_get_soft_ap_domain(mac_handle_t mac_handle,
				  v_REGDOMAIN_t *domainIdSoftAp);
QDF_STATUS sme_hdd_ready_ind(mac_handle_t mac_handle);
/**
 * sme_ser_cmd_callback() - callback from serialization module
 * @buf: serialization command buffer
 * @reason: reason why serialization module has given this callback
 *
 * Serialization module will give callback to SME for why it triggered
 * the callback
 *
 * Return: QDF_STATUS_SUCCESS
 */
QDF_STATUS sme_ser_cmd_callback(void *buf,
				enum wlan_serialization_cb_reason reason);

/*
 * sme_process_msg() - The main message processor for SME.
 * @mac: The global mac context
 * @msg: The message to be processed.
 *
 * This function is called by a message dispatcher when to process a message
 * targeted for SME.
 * This is a synchronous call
 *
 * Return: QDF_STATUS_SUCCESS - SME successfully processed the message.
 * Other status means SME failed to process the message to HAL.
 */
QDF_STATUS sme_process_msg(tpAniSirGlobal pMac, struct scheduler_msg *pMsg);

QDF_STATUS sme_mc_process_handler(struct scheduler_msg *msg);
QDF_STATUS sme_scan_get_result(mac_handle_t mac_handle, uint8_t sessionId,
		tCsrScanResultFilter *pFilter,
		tScanResultHandle *phResult);
QDF_STATUS sme_get_ap_channel_from_scan_cache(
		struct csr_roam_profile *profile,
		tScanResultHandle *scan_cache,
		uint8_t *ap_chnl_id);
QDF_STATUS sme_get_ap_channel_from_scan(void *profile,
		tScanResultHandle *scan_cache,
		uint8_t *ap_chnl_id);
bool sme_store_joinreq_param(mac_handle_t mac_handle,
		struct csr_roam_profile *profile,
		tScanResultHandle scan_cache,
		uint32_t *roam_id,
		uint32_t session_id);
bool sme_clear_joinreq_param(mac_handle_t mac_handle,
		uint32_t session_id);
QDF_STATUS sme_issue_stored_joinreq(mac_handle_t mac_handle,
		uint32_t *roam_id,
		uint32_t session_id);
QDF_STATUS sme_scan_flush_result(mac_handle_t mac_handle);
QDF_STATUS sme_filter_scan_results(mac_handle_t mac_handle, uint8_t sessionId);
QDF_STATUS sme_scan_flush_p2p_result(mac_handle_t mac_handle,
				     uint8_t sessionId);
tCsrScanResultInfo *sme_scan_result_get_first(mac_handle_t,
		tScanResultHandle hScanResult);
tCsrScanResultInfo *sme_scan_result_get_next(mac_handle_t,
		tScanResultHandle hScanResult);
QDF_STATUS sme_scan_result_purge(tScanResultHandle hScanResult);
QDF_STATUS sme_roam_connect(mac_handle_t mac_handle, uint8_t sessionId,
		struct csr_roam_profile *pProfile, uint32_t *pRoamId);
QDF_STATUS sme_roam_reassoc(mac_handle_t mac_handle, uint8_t sessionId,
		struct csr_roam_profile *pProfile,
		tCsrRoamModifyProfileFields modProfileFields,
		uint32_t *pRoamId, bool fForce);
QDF_STATUS sme_roam_connect_to_last_profile(mac_handle_t mac_handle,
					    uint8_t sessionId);

/**
 * sme_roam_disconnect() - API to request CSR to disconnect
 * @hal: HAL context
 * @session: SME session identifier
 * @reason: Reason to disconnect
 *
 * Return: QDF Status success or failure
 */
QDF_STATUS sme_roam_disconnect(mac_handle_t hal, uint8_t session,
			       eCsrRoamDisconnectReason reason);

void sme_dhcp_done_ind(mac_handle_t hal, uint8_t session_id);
QDF_STATUS sme_roam_stop_bss(mac_handle_t mac_handle, uint8_t sessionId);
QDF_STATUS sme_roam_get_associated_stas(mac_handle_t mac_handle,
					uint8_t sessionId,
					QDF_MODULE_ID modId, void *pUsrContext,
					void *pfnSapEventCallback,
					uint8_t *pAssocStasBuf);
QDF_STATUS sme_roam_disconnect_sta(mac_handle_t mac_handle, uint8_t sessionId,
		struct csr_del_sta_params *p_del_sta_params);
QDF_STATUS sme_roam_deauth_sta(mac_handle_t mac_handle, uint8_t sessionId,
		struct csr_del_sta_params *pDelStaParams);
QDF_STATUS sme_roam_get_connect_state(mac_handle_t mac_handle,
				      uint8_t sessionId,
				      eCsrConnectState *pState);
QDF_STATUS sme_roam_get_connect_profile(mac_handle_t mac_handle,
					uint8_t sessionId,
					tCsrRoamConnectedProfile *pProfile);
void sme_roam_free_connect_profile(tCsrRoamConnectedProfile *profile);
QDF_STATUS sme_roam_set_pmkid_cache(mac_handle_t mac_handle, uint8_t sessionId,
		tPmkidCacheInfo *pPMKIDCache,
		uint32_t numItems,
		bool update_entire_cache);

#ifdef WLAN_FEATURE_ROAM_OFFLOAD
/**
 * sme_get_pmk_info(): A wrapper function to request CSR to save PMK
 * @hal: Global structure
 * @session_id: SME session_id
 * @pmk_cache: pointer to a structure of pmk
 *
 * Return: none
 */
void sme_get_pmk_info(mac_handle_t hal, uint8_t session_id,
		      tPmkidCacheInfo *pmk_cache);

QDF_STATUS sme_roam_set_psk_pmk(mac_handle_t mac_handle, uint8_t sessionId,
		uint8_t *pPSK_PMK, size_t pmk_len);
#endif

/**
 * sme_roam_get_wpa_rsn_req_ie() - Retrieve WPA/RSN Request IE
 * @hal: HAL handle
 * @session_id: ID of the specific session
 * @len: Caller allocated memory that has the length of @buf as input.
 *	Upon returned, @len has the length of the IE store in @buf
 * @buf: Caller allocated memory that contain the IE field, if any,
 *	upon return
 *
 * A wrapper function to request CSR to return the WPA or RSN IE CSR
 * passes to PE to JOIN request or START_BSS request
 * This is a synchronous call.
 *
 * Return: QDF_STATUS - when fail, it usually means the buffer allocated is not
 *			 big enough
 */
QDF_STATUS sme_roam_get_wpa_rsn_req_ie(mac_handle_t hal, uint8_t session_id,
				       uint32_t *len, uint8_t *buf);

/**
 * sme_roam_get_wpa_rsn_rsp_ie() - Retrieve WPA/RSN Response IE
 * @hal: HAL handle
 * @session_id: ID of the specific session
 * @len: Caller allocated memory that has the length of @buf as input.
 *	Upon returned, @len has the length of the IE store in @buf
 * @buf: Caller allocated memory that contain the IE field, if any,
 *	upon return
 *
 * A wrapper function to request CSR to return the WPA or RSN IE CSR
 * passes to PE to JOIN request or START_BSS request
 * This is a synchronous call.
 *
 * Return: QDF_STATUS - when fail, it usually means the buffer allocated is not
 *			 big enough
 */
QDF_STATUS sme_roam_get_wpa_rsn_rsp_ie(mac_handle_t hal, uint8_t session_id,
				       uint32_t *len, uint8_t *buf);

uint32_t sme_roam_get_num_pmkid_cache(mac_handle_t mac_handle,
				      uint8_t sessionId);
QDF_STATUS sme_roam_get_pmkid_cache(mac_handle_t mac_handle, uint8_t sessionId,
		uint32_t *pNum,
		tPmkidCacheInfo *pPmkidCache);
QDF_STATUS sme_get_config_param(mac_handle_t mac_handle,
				tSmeConfigParams *pParam);
#ifndef QCA_SUPPORT_CP_STATS
QDF_STATUS sme_get_statistics(mac_handle_t mac_handle,
		eCsrStatsRequesterType requesterId,
		uint32_t statsMask, tCsrStatsCallback callback,
		uint8_t staId, void *pContext, uint8_t sessionId);
#endif
QDF_STATUS sme_get_rssi(mac_handle_t mac_handle,
		tCsrRssiCallback callback,
		uint8_t staId, struct qdf_mac_addr bssId, int8_t lastRSSI,
		void *pContext);
QDF_STATUS sme_get_snr(mac_handle_t mac_handle,
		tCsrSnrCallback callback,
		uint8_t staId, struct qdf_mac_addr bssId, void *pContext);
#ifdef FEATURE_WLAN_ESE
QDF_STATUS sme_get_tsm_stats(mac_handle_t mac_handle,
		tCsrTsmStatsCallback callback,
		uint8_t staId, struct qdf_mac_addr bssId,
		void *pContext, uint8_t tid);
QDF_STATUS sme_set_cckm_ie(mac_handle_t mac_handle,
		uint8_t sessionId,
		uint8_t *pCckmIe, uint8_t cckmIeLen);
QDF_STATUS sme_set_ese_beacon_request(mac_handle_t mac_handle,
				      const uint8_t sessionId,
				      const tCsrEseBeaconReq *pEseBcnReq);
QDF_STATUS sme_set_plm_request(mac_handle_t mac_handle, tpSirPlmReq pPlm);
#endif /*FEATURE_WLAN_ESE */
QDF_STATUS sme_cfg_set_int(mac_handle_t hal, uint16_t cfg_id, uint32_t value);
QDF_STATUS sme_cfg_set_str(mac_handle_t hal, uint16_t cfg_id, uint8_t *str,
		uint32_t length);
QDF_STATUS sme_cfg_get_int(mac_handle_t hal, uint16_t cfg_id,
		uint32_t *cfg_value);
QDF_STATUS sme_cfg_get_str(mac_handle_t hal, uint16_t cfg_id, uint8_t *str,
		uint32_t *length);
QDF_STATUS sme_get_modify_profile_fields(mac_handle_t mac_handle,
					 uint8_t sessionId,
					 tCsrRoamModifyProfileFields *
					 pModifyProfileFields);

QDF_STATUS sme_set_host_power_save(mac_handle_t mac_handle, bool psMode);

void sme_set_dhcp_till_power_active_flag(mac_handle_t mac_handle, uint8_t flag);

#ifdef FEATURE_OEM_DATA_SUPPORT
QDF_STATUS sme_register_oem_data_rsp_callback(mac_handle_t mac_handle,
		sme_send_oem_data_rsp_msg callback);
void sme_deregister_oem_data_rsp_callback(mac_handle_t mac_handle);

#else
static inline
QDF_STATUS sme_register_oem_data_rsp_callback(mac_handle_t hal,
					      void *callback)
{
	return QDF_STATUS_SUCCESS;
}

static inline
void sme_deregister_oem_data_rsp_callback(mac_handle_t mac_handle)
{
}

#endif

QDF_STATUS sme_roam_set_key(mac_handle_t mac_handle, uint8_t sessionId,
			    tCsrRoamSetKey *pSetKey, uint32_t *pRoamId);
QDF_STATUS sme_get_country_code(mac_handle_t mac_handle, uint8_t *pBuf,
				uint8_t *pbLen);


/* some support functions */
bool sme_is11d_supported(mac_handle_t mac_handle);
bool sme_is11h_supported(mac_handle_t mac_handle);
bool sme_is_wmm_supported(mac_handle_t mac_handle);

QDF_STATUS sme_generic_change_country_code(mac_handle_t mac_handle,
					   uint8_t *pCountry);


/**
 * sme_update_channel_list() - Update configured channel list to fwr
 * This is a synchronous API.
 * @hal: HAL handle returned by mac_open.
 *
 * Return: QDF_STATUS  SUCCESS.
 * FAILURE or RESOURCES  The API finished and failed.
 */
QDF_STATUS sme_update_channel_list(mac_handle_t hal);

QDF_STATUS sme_tx_fail_monitor_start_stop_ind(mac_handle_t mac_handle,
		uint8_t tx_fail_count,
		void *txFailIndCallback);
QDF_STATUS sme_dhcp_start_ind(mac_handle_t mac_handle,
		uint8_t device_mode,
		uint8_t *macAddr, uint8_t sessionId);
QDF_STATUS sme_dhcp_stop_ind(mac_handle_t mac_handle,
		uint8_t device_mode,
		uint8_t *macAddr, uint8_t sessionId);
void sme_get_recovery_stats(mac_handle_t mac_handle);
QDF_STATUS sme_neighbor_report_request(mac_handle_t mac_handle,
		 uint8_t sessionId,
		tpRrmNeighborReq pRrmNeighborReq,
		tpRrmNeighborRspCallbackInfo callbackInfo);
QDF_STATUS sme_get_wcnss_wlan_compiled_version(mac_handle_t mac_handle,
		tSirVersionType * pVersion);
QDF_STATUS sme_get_wcnss_wlan_reported_version(mac_handle_t mac_handle,
		tSirVersionType *pVersion);
QDF_STATUS sme_get_wcnss_software_version(mac_handle_t mac_handle,
		uint8_t *pVersion, uint32_t versionBufferSize);
QDF_STATUS sme_get_wcnss_hardware_version(mac_handle_t mac_handle,
		uint8_t *pVersion, uint32_t versionBufferSize);
#ifdef FEATURE_OEM_DATA_SUPPORT
QDF_STATUS sme_oem_data_req(mac_handle_t mac_handle,
			    struct oem_data_req *hdd_oem_req);
QDF_STATUS sme_oem_update_capability(mac_handle_t mac_handle,
				     struct sme_oem_capability *cap);
QDF_STATUS sme_oem_get_capability(mac_handle_t mac_handle,
				  struct sme_oem_capability *cap);
#endif /*FEATURE_OEM_DATA_SUPPORT */
QDF_STATUS sme_change_mcc_beacon_interval(uint8_t sessionId);
QDF_STATUS sme_set_host_offload(mac_handle_t mac_handle, uint8_t sessionId,
		tpSirHostOffloadReq pRequest);
QDF_STATUS sme_set_keep_alive(mac_handle_t mac_handle, uint8_t sessionId,
		tpSirKeepAliveReq pRequest);
QDF_STATUS sme_get_operation_channel(mac_handle_t mac_handle,
				     uint32_t *pChannel,
				     uint8_t sessionId);
QDF_STATUS sme_register_mgmt_frame(mac_handle_t mac_handle, uint8_t sessionId,
		uint16_t frameType, uint8_t *matchData,
		uint16_t matchLen);
QDF_STATUS sme_deregister_mgmt_frame(mac_handle_t mac_handle,
				     uint8_t sessionId,
				     uint16_t frameType, uint8_t *matchData,
				     uint16_t matchLen);
QDF_STATUS sme_ConfigureAppsCpuWakeupState(mac_handle_t mac_handle,
					   bool isAppsAwake);
#ifdef WLAN_FEATURE_EXTWOW_SUPPORT
QDF_STATUS sme_configure_ext_wow(mac_handle_t mac_handle,
		tpSirExtWoWParams wlanExtParams,
		csr_readyToSuspendCallback callback,
		void *callbackContext);
QDF_STATUS sme_configure_app_type1_params(mac_handle_t mac_handle,
		tpSirAppType1Params wlanAppType1Params);
QDF_STATUS sme_configure_app_type2_params(mac_handle_t mac_handle,
		tpSirAppType2Params wlanAppType2Params);
#endif
int8_t sme_get_infra_session_id(mac_handle_t mac_handle);
uint8_t sme_get_infra_operation_channel(mac_handle_t mac_handle,
					uint8_t sessionId);
uint8_t sme_get_concurrent_operation_channel(mac_handle_t mac_handle);
#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
uint16_t sme_check_concurrent_channel_overlap(mac_handle_t mac_handle,
					      uint16_t sap_ch,
					      eCsrPhyMode sapPhyMode,
					      uint8_t cc_switch_mode);
#endif
QDF_STATUS sme_get_cfg_valid_channels(uint8_t *aValidChannels,
		uint32_t *len);
#ifdef WLAN_FEATURE_PACKET_FILTERING
QDF_STATUS sme_8023_multicast_list(mac_handle_t mac_handle, uint8_t sessionId,
		tpSirRcvFltMcAddrList pMulticastAddrs);
#endif /* WLAN_FEATURE_PACKET_FILTERING */
bool sme_is_channel_valid(mac_handle_t mac_handle, uint8_t channel);
QDF_STATUS sme_get_freq_band(mac_handle_t mac_handle, enum band_info *pBand);
uint16_t sme_chn_to_freq(uint8_t chanNum);
bool sme_is_channel_valid(mac_handle_t mac_handle, uint8_t channel);
QDF_STATUS sme_set_max_tx_power(mac_handle_t mac_handle,
				struct qdf_mac_addr pBssid,
				struct qdf_mac_addr pSelfMacAddress, int8_t dB);
QDF_STATUS sme_set_max_tx_power_per_band(enum band_info band, int8_t db);
QDF_STATUS sme_set_tx_power(mac_handle_t mac_handle, uint8_t sessionId,
		struct qdf_mac_addr bssid,
		enum QDF_OPMODE dev_mode, int power);
QDF_STATUS sme_set_custom_mac_addr(tSirMacAddr customMacAddr);
QDF_STATUS sme_hide_ssid(mac_handle_t mac_handle, uint8_t sessionId,
		uint8_t ssidHidden);
QDF_STATUS sme_set_tm_level(mac_handle_t mac_handle, uint16_t newTMLevel,
		uint16_t tmMode);
void sme_feature_caps_exchange(mac_handle_t mac_handle);
void sme_disable_feature_capablity(uint8_t feature_index);
void sme_reset_power_values_for5_g(mac_handle_t mac_handle);
QDF_STATUS sme_update_roam_prefer5_g_hz(mac_handle_t mac_handle,
					bool nRoamPrefer5GHz);
QDF_STATUS sme_set_roam_intra_band(mac_handle_t mac_handle,
				   const bool nRoamIntraBand);
QDF_STATUS sme_update_roam_scan_n_probes(mac_handle_t mac_handle,
					 uint8_t sessionId,
					 const uint8_t nProbes);
QDF_STATUS sme_update_roam_scan_home_away_time(mac_handle_t mac_handle,
		uint8_t sessionId,
		const uint16_t nRoamScanHomeAwayTime,
		const bool bSendOffloadCmd);

bool sme_get_roam_intra_band(mac_handle_t mac_handle);
uint8_t sme_get_roam_scan_n_probes(mac_handle_t mac_handle);
uint16_t sme_get_roam_scan_home_away_time(mac_handle_t mac_handle);
QDF_STATUS sme_update_roam_rssi_diff(mac_handle_t mac_handle, uint8_t sessionId,
		uint8_t RoamRssiDiff);
QDF_STATUS sme_update_fast_transition_enabled(mac_handle_t mac_handle,
		bool isFastTransitionEnabled);
QDF_STATUS sme_update_wes_mode(mac_handle_t mac_handle, bool isWESModeEnabled,
		uint8_t sessionId);
QDF_STATUS sme_set_roam_scan_control(mac_handle_t mac_handle, uint8_t sessionId,
		bool roamScanControl);

QDF_STATUS sme_update_is_fast_roam_ini_feature_enabled(mac_handle_t mac_handle,
		uint8_t sessionId,
		const bool
		isFastRoamIniFeatureEnabled);

QDF_STATUS sme_config_fast_roaming(mac_handle_t hal, uint8_t session_id,
		const bool is_fast_roam_enabled);

QDF_STATUS sme_update_is_mawc_ini_feature_enabled(mac_handle_t mac_handle,
		const bool MAWCEnabled);
QDF_STATUS sme_stop_roaming(mac_handle_t mac_handle, uint8_t sessionId,
			    uint8_t reason);

QDF_STATUS sme_start_roaming(mac_handle_t mac_handle, uint8_t sessionId,
		uint8_t reason);
QDF_STATUS sme_update_enable_fast_roam_in_concurrency(mac_handle_t mac_handle,
		bool bFastRoamInConIniFeatureEnabled);
#ifdef FEATURE_WLAN_ESE
QDF_STATUS sme_update_is_ese_feature_enabled(mac_handle_t mac_handle,
					     uint8_t sessionId,
					     const bool isEseIniFeatureEnabled);
#endif /* FEATURE_WLAN_ESE */
QDF_STATUS sme_set_roam_rescan_rssi_diff(mac_handle_t mac_handle,
		uint8_t sessionId,
		const uint8_t nRoamRescanRssiDiff);
uint8_t sme_get_roam_rescan_rssi_diff(mac_handle_t mac_handle);

QDF_STATUS sme_set_roam_opportunistic_scan_threshold_diff(
		mac_handle_t mac_handle,
		uint8_t sessionId,
		const uint8_t nOpportunisticThresholdDiff);
uint8_t sme_get_roam_opportunistic_scan_threshold_diff(mac_handle_t mac_handle);
QDF_STATUS sme_set_neighbor_lookup_rssi_threshold(mac_handle_t mac_handle,
		uint8_t sessionId, uint8_t neighborLookupRssiThreshold);
QDF_STATUS sme_set_delay_before_vdev_stop(mac_handle_t mac_handle,
		uint8_t sessionId, uint8_t delay_before_vdev_stop);
uint8_t sme_get_neighbor_lookup_rssi_threshold(mac_handle_t mac_handle);
QDF_STATUS sme_set_neighbor_scan_refresh_period(mac_handle_t mac_handle,
		uint8_t sessionId, uint16_t neighborScanResultsRefreshPeriod);
uint16_t sme_get_neighbor_scan_refresh_period(mac_handle_t mac_handle);
uint16_t sme_get_empty_scan_refresh_period(mac_handle_t mac_handle);
QDF_STATUS sme_update_empty_scan_refresh_period(mac_handle_t mac_handle,
		uint8_t sessionId, uint16_t nEmptyScanRefreshPeriod);
QDF_STATUS sme_set_neighbor_scan_min_chan_time(mac_handle_t mac_handle,
		const uint16_t nNeighborScanMinChanTime,
		uint8_t sessionId);
QDF_STATUS sme_set_neighbor_scan_max_chan_time(mac_handle_t mac_handle,
				uint8_t sessionId,
				const uint16_t nNeighborScanMaxChanTime);
uint16_t sme_get_neighbor_scan_min_chan_time(mac_handle_t mac_handle,
					     uint8_t sessionId);
uint32_t sme_get_neighbor_roam_state(mac_handle_t mac_handle,
				     uint8_t sessionId);
uint32_t sme_get_current_roam_state(mac_handle_t mac_handle, uint8_t sessionId);
uint32_t sme_get_current_roam_sub_state(mac_handle_t mac_handle,
					uint8_t sessionId);
uint32_t sme_get_lim_sme_state(mac_handle_t mac_handle);
uint32_t sme_get_lim_mlm_state(mac_handle_t mac_handle);
bool sme_is_lim_session_valid(mac_handle_t mac_handle, uint8_t sessionId);
uint32_t sme_get_lim_sme_session_state(mac_handle_t mac_handle,
				       uint8_t sessionId);
uint32_t sme_get_lim_mlm_session_state(mac_handle_t mac_handle,
				       uint8_t sessionId);
uint16_t sme_get_neighbor_scan_max_chan_time(mac_handle_t mac_handle,
					     uint8_t sessionId);
QDF_STATUS sme_set_neighbor_scan_period(mac_handle_t mac_handle,
		uint8_t sessionId,
		const uint16_t nNeighborScanPeriod);
uint16_t sme_get_neighbor_scan_period(mac_handle_t mac_handle,
				      uint8_t sessionId);
QDF_STATUS sme_set_neighbor_scan_min_period(mac_handle_t mac_handle,
		uint8_t session_id, const uint16_t neighbor_scan_min_period);
QDF_STATUS sme_set_roam_bmiss_first_bcnt(mac_handle_t mac_handle,
		uint8_t sessionId, const uint8_t nRoamBmissFirstBcnt);
uint8_t sme_get_roam_bmiss_first_bcnt(mac_handle_t mac_handle);
QDF_STATUS sme_set_roam_bmiss_final_bcnt(mac_handle_t mac_handle,
					 uint8_t sessionId,
					 const uint8_t nRoamBmissFinalBcnt);
uint8_t sme_get_roam_bmiss_final_bcnt(mac_handle_t mac_handle);
QDF_STATUS sme_set_roam_beacon_rssi_weight(mac_handle_t mac_handle,
					   uint8_t sessionId,
					   const uint8_t nRoamBeaconRssiWeight);
uint8_t sme_get_roam_beacon_rssi_weight(mac_handle_t mac_handle);
uint8_t sme_get_roam_rssi_diff(mac_handle_t mac_handle);
QDF_STATUS sme_change_roam_scan_channel_list(mac_handle_t mac_handle,
					     uint8_t sessionId,
					     uint8_t *pChannelList,
					     uint8_t numChannels);
QDF_STATUS sme_set_ese_roam_scan_channel_list(mac_handle_t mac_handle,
					      uint8_t sessionId,
					      uint8_t *pChannelList,
					      uint8_t numChannels);
QDF_STATUS sme_get_roam_scan_channel_list(mac_handle_t mac_handle,
					  uint8_t *pChannelList,
					  uint8_t *pNumChannels,
					  uint8_t sessionId);
bool sme_get_is_ese_feature_enabled(mac_handle_t mac_handle);
bool sme_get_wes_mode(mac_handle_t mac_handle);
bool sme_get_roam_scan_control(mac_handle_t mac_handle);
bool sme_get_is_lfr_feature_enabled(mac_handle_t mac_handle);
bool sme_get_is_ft_feature_enabled(mac_handle_t mac_handle);
QDF_STATUS sme_update_roam_scan_offload_enabled(mac_handle_t mac_handle,
		bool nRoamScanOffloadEnabled);
bool sme_is_feature_supported_by_fw(enum cap_bitmap feature);

/*
 * SME API to enable/disable WLAN driver initiated SSR
 */
void sme_update_enable_ssr(mac_handle_t mac_handle, bool enableSSR);
QDF_STATUS sme_set_phy_mode(mac_handle_t mac_handle, eCsrPhyMode phyMode);
eCsrPhyMode sme_get_phy_mode(mac_handle_t mac_handle);
QDF_STATUS sme_handoff_request(mac_handle_t mac_handle, uint8_t sessionId,
			       tCsrHandoffRequest *pHandoffInfo);
QDF_STATUS sme_is_sta_p2p_client_connected(mac_handle_t mac_handle);
QDF_STATUS sme_add_periodic_tx_ptrn(mac_handle_t mac_handle,
		tSirAddPeriodicTxPtrn *addPeriodicTxPtrnParams);
QDF_STATUS sme_del_periodic_tx_ptrn(mac_handle_t mac_handle,
		tSirDelPeriodicTxPtrn *delPeriodicTxPtrnParams);
QDF_STATUS sme_send_rate_update_ind(mac_handle_t mac_handle,
		tSirRateUpdateInd *rateUpdateParams);
QDF_STATUS sme_roam_del_pmkid_from_cache(mac_handle_t mac_handle,
					 uint8_t sessionId,
					 tPmkidCacheInfo *pmksa,
					 bool flush_cache);
void sme_get_command_q_status(mac_handle_t mac_handle);

#ifdef FEATURE_WLAN_RMC
QDF_STATUS sme_enable_rmc(mac_handle_t mac_handle, uint32_t sessionId);
QDF_STATUS sme_disable_rmc(mac_handle_t mac_handle, uint32_t sessionId);
QDF_STATUS sme_send_rmc_action_period(mac_handle_t mac_handle,
				      uint32_t sessionId);
#endif
QDF_STATUS sme_request_ibss_peer_info(mac_handle_t mac_handle,
				      void *pUserData,
				      pIbssPeerInfoCb peerInfoCbk,
				      bool allPeerInfoReqd,
				      uint8_t staIdx);
QDF_STATUS sme_send_cesium_enable_ind(mac_handle_t mac_handle,
				      uint32_t sessionId);

/**
 * sme_set_wlm_latency_level_ind() - Used to set the latency level to fw
 * @hal
 * @session_id
 * @latency_level
 *
 * Return QDF_STATUS
 */
QDF_STATUS sme_set_wlm_latency_level(mac_handle_t hal,
				     uint16_t session_id,
				     uint16_t latency_level);
/*
 * SME API to enable/disable idle mode powersave
 * This should be called only if powersave offload
 * is enabled
 */
QDF_STATUS sme_set_idle_powersave_config(bool value);
QDF_STATUS sme_notify_modem_power_state(mac_handle_t mac_handle,
					uint32_t value);

/*SME API to convert convert the ini value to the ENUM used in csr and MAC*/
ePhyChanBondState sme_get_cb_phy_state_from_cb_ini_value(uint32_t cb_ini_value);
int sme_update_ht_config(mac_handle_t mac_handle, uint8_t sessionId,
			 uint16_t htCapab,
			 int value);
int16_t sme_get_ht_config(mac_handle_t mac_handle, uint8_t session_id,
			  uint16_t ht_capab);
#ifdef QCA_HT_2040_COEX
QDF_STATUS sme_notify_ht2040_mode(mac_handle_t mac_handle, uint16_t staId,
				  struct qdf_mac_addr macAddrSTA,
				  uint8_t sessionId,
				  uint8_t channel_type);
QDF_STATUS sme_set_ht2040_mode(mac_handle_t mac_handle, uint8_t sessionId,
			       uint8_t channel_type, bool obssEnabled);
#endif
QDF_STATUS sme_get_reg_info(mac_handle_t mac_handle, uint8_t chanId,
			    uint32_t *regInfo1, uint32_t *regInfo2);
#ifdef FEATURE_WLAN_TDLS
QDF_STATUS sme_update_fw_tdls_state(mac_handle_t mac_handle,
				    void *psmeTdlsParams,
				    bool useSmeLock);
#endif /* FEATURE_WLAN_TDLS */

#ifdef FEATURE_WLAN_CH_AVOID
QDF_STATUS sme_ch_avoid_update_req(mac_handle_t mac_handle);
#else
static inline
QDF_STATUS sme_ch_avoid_update_req(mac_handle_t mac_handle)
{
	return QDF_STATUS_SUCCESS;
}
#endif
#ifdef FEATURE_WLAN_AUTO_SHUTDOWN
QDF_STATUS sme_set_auto_shutdown_cb(mac_handle_t mac_handle,
				    void (*pCallbackfn)(void));
QDF_STATUS sme_set_auto_shutdown_timer(mac_handle_t mac_handle,
				       uint32_t timer_value);
#endif
QDF_STATUS sme_roam_channel_change_req(mac_handle_t mac_handle,
				       struct qdf_mac_addr bssid,
				       struct ch_params *ch_params,
				       struct csr_roam_profile *profile);

QDF_STATUS sme_roam_start_beacon_req(mac_handle_t mac_handle,
				     struct qdf_mac_addr bssid,
				     uint8_t dfsCacWaitStatus);

#ifdef CONFIG_VDEV_SM
/**
 * sme_csa_restart() - request CSA IE transmission from PE
 * @mac_ctx: mac context
 * @session_id: SAP session id
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_csa_restart(tpAniSirGlobal mac_ctx, uint8_t session_id);
#endif

QDF_STATUS sme_roam_csa_ie_request(mac_handle_t mac_handle,
				   struct qdf_mac_addr bssid,
				   uint8_t targetChannel, uint8_t csaIeReqd,
				   struct ch_params *ch_params);

/**
 * sme_set_addba_accept() - Allow/Reject the ADDBA req session
 * @hal: handle returned by mac_open
 * @session_id: sme session id
 * @value: Allow/Reject AddBA session
 *
 * Allows/Rejects the ADDBA req session
 *
 * Return: 0 on success else errno
 */
int sme_set_addba_accept(mac_handle_t hal, uint8_t session_id, int value);

QDF_STATUS sme_init_thermal_info(mac_handle_t mac_handle,
				 tSmeThermalParams thermalParam);

QDF_STATUS sme_set_thermal_level(mac_handle_t mac_handle, uint8_t level);
QDF_STATUS sme_txpower_limit(mac_handle_t mac_handle, tSirTxPowerLimit *psmetx);
QDF_STATUS sme_get_link_speed(mac_handle_t mac_handle,
			      tSirLinkSpeedInfo *lsReq,
			      void *plsContext,
			      void (*pCallbackfn)(tSirLinkSpeedInfo *indParam,
						  void *pContext));
QDF_STATUS sme_modify_add_ie(mac_handle_t mac_handle,
		tSirModifyIE *pModifyIE, eUpdateIEsType updateType);
QDF_STATUS sme_update_add_ie(mac_handle_t mac_handle,
		tSirUpdateIE *pUpdateIE, eUpdateIEsType updateType);
QDF_STATUS sme_update_connect_debug(mac_handle_t mac_handle,
				    uint32_t set_value);
const char *sme_bss_type_to_string(const uint8_t bss_type);
QDF_STATUS sme_ap_disable_intra_bss_fwd(mac_handle_t mac_handle,
					uint8_t sessionId,
					bool disablefwd);
QDF_STATUS sme_get_channel_bonding_mode5_g(mac_handle_t mac_handle,
					   uint32_t *mode);
QDF_STATUS sme_get_channel_bonding_mode24_g(mac_handle_t mac_handle,
					    uint32_t *mode);

/**
 * sme_send_unit_test_cmd() - send unit test command to lower layer
 * @session_id: sme session id to be filled while forming the command
 * @module_id: module id given by user to be filled in the command
 * @arg_count: number of argument count
 * @arg: pointer to argument list
 *
 * This API exposed to HDD layer which takes the argument from user and sends
 * down to lower layer for further processing
 *
 * Return: QDF_STATUS based on overall success
 */
QDF_STATUS sme_send_unit_test_cmd(uint32_t vdev_id, uint32_t module_id,
				  uint32_t arg_count, uint32_t *arg);

typedef struct sStatsExtRequestReq {
	uint32_t request_data_len;
	uint8_t *request_data;
} tStatsExtRequestReq, *tpStatsExtRequestReq;

#ifdef WLAN_FEATURE_STATS_EXT
/**
 * sme_stats_ext_register_callback() - Register stats ext callback
 * @mac_handle: Opaque handle to the MAC context
 * @callback: Function to be invoked for stats ext events
 *
 * This function is called to register the callback that send vendor
 * event for stats ext
 */
void sme_stats_ext_register_callback(mac_handle_t mac_handle,
				     stats_ext_cb callback);

/**
 * sme_stats_ext_deregister_callback() - Deregister stats ext callback
 * @mac_handle: Opaque handle to the MAC context
 *
 * This function is called to deregister the callback that send vendor
 * event for stats ext
 */
void sme_stats_ext_deregister_callback(mac_handle_t mac_handle);

/**
 * sme_stats_ext2_register_callback() - Register stats ext2 callback
 * @mac_handle: Opaque handle to the MAC context
 * @callback: Function to be invoked for stats ext2 events
 *
 * This function will register a callback for frame aggregation failure
 * indications processing.
 *
 * Return: void
 */
void sme_stats_ext2_register_callback(mac_handle_t mac_handle,
				      stats_ext2_cb callback);

QDF_STATUS sme_stats_ext_request(uint8_t session_id,
				 tpStatsExtRequestReq input);
#else
static inline void
sme_stats_ext_register_callback(mac_handle_t mac_handle,
				stats_ext_cb callback)
{
}

static inline void
sme_stats_ext2_register_callback(mac_handle_t mac_handle,
				 stats_ext2_cb callback)
{
}
#endif /* WLAN_FEATURE_STATS_EXT */
QDF_STATUS sme_update_dfs_scan_mode(mac_handle_t mac_handle,
		uint8_t sessionId,
		uint8_t allowDFSChannelRoam);
uint8_t sme_get_dfs_scan_mode(mac_handle_t mac_handle);

#ifdef FEATURE_WLAN_EXTSCAN
QDF_STATUS sme_get_valid_channels_by_band(mac_handle_t mac_handle,
					  uint8_t wifiBand,
					  uint32_t *aValidChannels,
					  uint8_t *pNumChannels);

/**
 * sme_ext_scan_get_capabilities() - SME API to fetch extscan capabilities
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan capabilities request structure
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_ext_scan_get_capabilities(mac_handle_t mac_handle,
			      struct extscan_capabilities_params *params);

/**
 * sme_ext_scan_start() - SME API to issue extscan start
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan start structure
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_ext_scan_start(mac_handle_t mac_handle,
		   struct wifi_scan_cmd_req_params *params);

/**
 * sme_ext_scan_stop() - SME API to issue extscan stop
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan stop structure
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ext_scan_stop(mac_handle_t mac_handle,
			     struct extscan_stop_req_params *params);

/**
 * sme_set_bss_hotlist() - SME API to set BSSID hotlist
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan set hotlist structure
 *
 * Handles the request to set the BSSID hotlist in firmware.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_set_bss_hotlist(mac_handle_t mac_handle,
		    struct extscan_bssid_hotlist_set_params *params);

/**
 * sme_reset_bss_hotlist() - SME API to reset BSSID hotlist
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan reset hotlist structure
 *
 * Handles the request to reset the BSSID hotlist in firmware.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_reset_bss_hotlist(mac_handle_t mac_handle,
		      struct extscan_bssid_hotlist_reset_params *params);

/**
 * sme_set_significant_change() - SME API to set significant change
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan set significant change structure
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_set_significant_change(mac_handle_t mac_handle,
			   struct extscan_set_sig_changereq_params *params);

/**
 * sme_reset_significant_change() -  SME API to reset significant change
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan reset significant change structure
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_reset_significant_change(mac_handle_t mac_handle,
			     struct extscan_capabilities_reset_params *params);

/**
 * sme_get_cached_results() - SME API to get cached results
 * @mac_handle: Opaque handle to the MAC context
 * @params: extscan get cached results structure
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_get_cached_results(mac_handle_t mac_handle,
		       struct extscan_cached_result_params *params);

/**
 * sme_set_epno_list() - set epno network list
 * @mac_handle: Opaque handle to the MAC context
 * @params: request message
 *
 * This function sends an Enhanced PNO configuration to firmware.
 *
 * Return: QDF_STATUS enumeration
 */
QDF_STATUS sme_set_epno_list(mac_handle_t mac_handle,
			     struct wifi_enhanced_pno_params *params);

/**
 * sme_set_passpoint_list() - set passpoint network list
 * @mac_handle: Opaque handle to the MAC context
 * @params: set passpoint list request parameters
 *
 * This function constructs the cds message and fill in message type,
 * bodyptr with @params and posts it to WDA queue.
 *
 * Return: QDF_STATUS enumeration
 */
QDF_STATUS sme_set_passpoint_list(mac_handle_t mac_handle,
				  struct wifi_passpoint_req_param *params);

/**
 * sme_reset_passpoint_list() - reset passpoint network list
 * @mac_handle: Opaque handle to the MAC context
 * @params: reset passpoint list request parameters
 *
 * Return: QDF_STATUS enumeration
 */
QDF_STATUS sme_reset_passpoint_list(mac_handle_t mac_handle,
				    struct wifi_passpoint_req_param *params);

QDF_STATUS sme_ext_scan_register_callback(mac_handle_t mac_handle,
					  ext_scan_ind_cb ext_scan_ind_cb);
#else
static inline
QDF_STATUS sme_ext_scan_register_callback(mac_handle_t mac_handle,
					  ext_scan_ind_cb ext_scan_ind_cb)
{
	return QDF_STATUS_SUCCESS;
}
#endif /* FEATURE_WLAN_EXTSCAN */
QDF_STATUS sme_abort_roam_scan(mac_handle_t mac_handle, uint8_t sessionId);
#ifdef WLAN_FEATURE_LINK_LAYER_STATS
QDF_STATUS sme_ll_stats_clear_req(mac_handle_t mac_handle,
		tSirLLStatsClearReq * pclearStatsReq);
QDF_STATUS sme_ll_stats_set_req(mac_handle_t mac_handle,
		tSirLLStatsSetReq *psetStatsReq);

/**
 * sme_ll_stats_get_req() - SME API to get the Link Layer Statistics
 * @mac_handle: Global MAC handle
 * @get_stats_req: Link Layer get stats request params structure
 * @context: Callback context
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ll_stats_get_req(mac_handle_t mac_handle,
				tSirLLStatsGetReq *get_stats_req,
				void *context);

/**
 * sme_set_link_layer_stats_ind_cb() -
 * SME API to trigger the stats are available after get request
 * @mac_handle: MAC handle
 * @callback: HDD callback which needs to be invoked after
 *    getting status notification from FW
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_link_layer_stats_ind_cb(mac_handle_t mac_handle,
					   link_layer_stats_cb callback);

QDF_STATUS sme_set_link_layer_ext_cb(mac_handle_t hal,
		     void (*ll_stats_ext_cb)(hdd_handle_t callback_ctx,
					     tSirLLStatsResults * rsp));
QDF_STATUS sme_reset_link_layer_stats_ind_cb(mac_handle_t mac_handle);
QDF_STATUS sme_ll_stats_set_thresh(mac_handle_t hal,
				struct sir_ll_ext_stats_threshold *threshold);
#else /* WLAN_FEATURE_LINK_LAYER_STATS */
static inline QDF_STATUS
sme_set_link_layer_ext_cb(mac_handle_t hal, void (*ll_stats_ext_cb)
			  (hdd_handle_t callback_ctx, tSirLLStatsResults
			  *rsp))
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS
sme_set_link_layer_stats_ind_cb(mac_handle_t mac_handle,
				link_layer_stats_cb callback)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS
sme_reset_link_layer_stats_ind_cb(mac_handle_t mac_handle)
{
	return QDF_STATUS_SUCCESS;
}
#endif /* WLAN_FEATURE_LINK_LAYER_STATS */

QDF_STATUS sme_set_wisa_params(mac_handle_t hal,
				struct sir_wisa_params *wisa_params);
#ifdef WLAN_FEATURE_ROAM_OFFLOAD
QDF_STATUS sme_update_roam_offload_enabled(mac_handle_t mac_handle,
		bool nRoamOffloadEnabled);
QDF_STATUS sme_update_roam_key_mgmt_offload_enabled(mac_handle_t hal_ctx,
		uint8_t session_id,
		bool key_mgmt_offload_enabled,
		struct pmkid_mode_bits *pmkid_modes);
#endif
QDF_STATUS sme_get_link_status(mac_handle_t mac_handle,
			       csr_link_status_callback callback,
			       void *context, uint8_t session_id);
QDF_STATUS sme_get_temperature(mac_handle_t mac_handle,
		void *tempContext,
		void (*pCallbackfn)(int temperature,
			void *pContext));
QDF_STATUS sme_set_scanning_mac_oui(mac_handle_t mac_handle,
		tSirScanMacOui *pScanMacOui);

#ifdef DHCP_SERVER_OFFLOAD
QDF_STATUS sme_set_dhcp_srv_offload(mac_handle_t mac_handle,
		tSirDhcpSrvOffloadInfo * pDhcpSrvInfo);
#endif /* DHCP_SERVER_OFFLOAD */
#ifdef WLAN_FEATURE_GPIO_LED_FLASHING
QDF_STATUS sme_set_led_flashing(mac_handle_t mac_handle, uint8_t type,
		uint32_t x0, uint32_t x1);
#endif
QDF_STATUS sme_handle_dfs_chan_scan(mac_handle_t mac_handle, uint8_t dfs_flag);
QDF_STATUS sme_enable_dfs_chan_scan(mac_handle_t mac_handle, uint8_t dfs_flag);
QDF_STATUS sme_set_mas(uint32_t val);
QDF_STATUS sme_set_miracast(mac_handle_t hal, uint8_t filter_type);
QDF_STATUS sme_ext_change_channel(mac_handle_t mac_handle, uint32_t channel,
					  uint8_t session_id);

QDF_STATUS sme_configure_stats_avg_factor(mac_handle_t hal, uint8_t session_id,
					  uint16_t stats_avg_factor);

QDF_STATUS sme_configure_guard_time(mac_handle_t hal, uint8_t session_id,
				    uint32_t guard_time);

QDF_STATUS sme_wifi_start_logger(mac_handle_t hal,
		struct sir_wifi_start_log start_log);

bool sme_neighbor_middle_of_roaming(mac_handle_t mac_handle,
						uint8_t sessionId);

/*
 * sme_is_any_session_in_middle_of_roaming() - check if roaming is in progress
 * @hal: MAC Handle
 *
 * Checks if any SME session is in middle of roaming
 *
 * Return : true if roaming is in progress else false
 */
bool sme_is_any_session_in_middle_of_roaming(mac_handle_t hal);

/**
 * sme_enable_uapsd_for_ac() - enable uapsd for access category request to WMA
 * @sta_id: station id
 * @ac: access category
 * @tid: tid value
 * @pri: user priority
 * @srvc_int: service interval
 * @sus_int: suspend interval
 * @dir: tspec direction
 * @psb: PSB value
 * @sessionId: session id
 * @delay_interval: delay interval
 *
 * Return: QDF status
 */
QDF_STATUS sme_enable_uapsd_for_ac(uint8_t sta_id,
				      sme_ac_enum_type ac, uint8_t tid,
				      uint8_t pri, uint32_t srvc_int,
				      uint32_t sus_int,
				      enum sme_qos_wmm_dir_type dir,
				      uint8_t psb, uint32_t sessionId,
				      uint32_t delay_interval);

/**
 * sme_disable_uapsd_for_ac() - disable uapsd access category request to WMA
 * @sta_id: station id
 * @ac: access category
 * @sessionId: session id
 *
 * Return: QDF status
 */
QDF_STATUS sme_disable_uapsd_for_ac(uint8_t sta_id,
				       sme_ac_enum_type ac,
				       uint32_t sessionId);

#ifdef FEATURE_RSSI_MONITOR
QDF_STATUS sme_set_rssi_monitoring(mac_handle_t hal,
					struct rssi_monitor_req *input);

/**
 * sme_set_rssi_threshold_breached_cb() - Set RSSI threshold breached callback
 * @mac_handle: global MAC handle
 * @cb: callback function pointer
 *
 * This function registers the RSSI threshold breached callback function.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_set_rssi_threshold_breached_cb(mac_handle_t mac_handle,
					      rssi_threshold_breached_cb cb);
#else /* FEATURE_RSSI_MONITOR */
static inline
QDF_STATUS sme_set_rssi_threshold_breached_cb(mac_handle_t mac_handle,
					      rssi_threshold_breached_cb cb)
{
	return QDF_STATUS_SUCCESS;
}
#endif
/**
 * sme_reset_rssi_threshold_breached_cb() - Reset RSSI threshold breached
 *                                          callback
 * @mac_handle: global MAC handle
 *
 * This function de-registers the RSSI threshold breached callback function.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_reset_rssi_threshold_breached_cb(mac_handle_t mac_handle);

QDF_STATUS sme_register_mgmt_frame_ind_callback(mac_handle_t hal,
			sir_mgmt_frame_ind_callback callback);

QDF_STATUS sme_update_nss(mac_handle_t mac_handle, uint8_t nss);
void sme_update_user_configured_nss(mac_handle_t hal, uint8_t nss);

bool sme_is_any_session_in_connected_state(mac_handle_t mac_handle);

QDF_STATUS sme_pdev_set_pcl(struct policy_mgr_pcl_list *msg);
QDF_STATUS sme_pdev_set_hw_mode(struct policy_mgr_hw_mode msg);
void sme_register_hw_mode_trans_cb(mac_handle_t hal,
		hw_mode_transition_cb callback);
QDF_STATUS sme_nss_update_request(uint32_t vdev_id,
				uint8_t  new_nss, policy_mgr_nss_update_cback cback,
				uint8_t next_action, struct wlan_objmgr_psoc *psoc,
				enum policy_mgr_conn_update_reason reason,
				uint32_t original_vdev_id);

typedef void (*sme_peer_authorized_fp) (uint32_t vdev_id);
QDF_STATUS sme_set_peer_authorized(uint8_t *peer_addr,
				   sme_peer_authorized_fp auth_fp,
				   uint32_t vdev_id);
QDF_STATUS sme_soc_set_dual_mac_config(struct policy_mgr_dual_mac_config msg);
QDF_STATUS sme_soc_set_antenna_mode(mac_handle_t hal,
		struct sir_antenna_mode_param *msg);

void sme_set_scan_disable(mac_handle_t mac_handle, int value);
void sme_setdef_dot11mode(mac_handle_t hal);

QDF_STATUS sme_handle_set_fcc_channel(mac_handle_t mac_handle,
				      bool fcc_constraint,
				      bool scan_pending);

QDF_STATUS sme_update_roam_scan_hi_rssi_scan_params(mac_handle_t mac_handle,
	uint8_t session_id,
	uint32_t notify_id,
	int32_t val);

/**
 * sme_update_tx_bfee_supp() - sets the Tx Bfee support
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @cfg_val: Tx Bfee config value
 *
 * Return: 0 on success else err code
 */
int sme_update_tx_bfee_supp(mac_handle_t hal, uint8_t session_id,
		uint8_t cfg_val);

/**
 * sme_update_tx_bfee_nsts() - sets the Tx Bfee nsts
 * @hal: MAC handle
 * @session_id: SME session id
 * @usr_cfg_val: user config value
 * @nsts_val: Tx Bfee nsts config value
 *
 * Return: 0 on success else err code
 */
int sme_update_tx_bfee_nsts(mac_handle_t hal, uint8_t session_id,
			    uint8_t usr_cfg_val, uint8_t nsts_val);

void wlan_sap_enable_phy_error_logs(mac_handle_t hal, uint32_t enable_log);
#ifdef WLAN_FEATURE_DSRC
QDF_STATUS sme_ocb_set_config(mac_handle_t mac_handle, void *context,
			      ocb_callback callback,
			      struct sir_ocb_config *config);

QDF_STATUS sme_ocb_set_utc_time(mac_handle_t mac_handle,
				struct sir_ocb_utc *utc);

QDF_STATUS sme_ocb_start_timing_advert(mac_handle_t mac_handle,
	struct sir_ocb_timing_advert *timing_advert);

QDF_STATUS sme_ocb_stop_timing_advert(mac_handle_t mac_handle,
	struct sir_ocb_timing_advert *timing_advert);

int sme_ocb_gen_timing_advert_frame(mac_handle_t mac_handle,
				    tSirMacAddr self_addr,
				    uint8_t **buf, uint32_t *timestamp_offset,
				    uint32_t *time_value_offset);

QDF_STATUS sme_ocb_get_tsf_timer(mac_handle_t mac_handle, void *context,
				 ocb_callback callback,
				 struct sir_ocb_get_tsf_timer *request);

QDF_STATUS sme_dcc_get_stats(mac_handle_t mac_handle, void *context,
			     ocb_callback callback,
			     struct sir_dcc_get_stats *request);

QDF_STATUS sme_dcc_clear_stats(mac_handle_t mac_handle, uint32_t vdev_id,
			       uint32_t dcc_stats_bitmap);

QDF_STATUS sme_dcc_update_ndl(mac_handle_t mac_handle, void *context,
			      ocb_callback callback,
			      struct sir_dcc_update_ndl *request);

QDF_STATUS sme_register_for_dcc_stats_event(mac_handle_t mac_handle,
					    void *context,
					    ocb_callback callback);
QDF_STATUS sme_deregister_for_dcc_stats_event(mac_handle_t mac_handle);

static inline void
sme_set_etsi13_srd_ch_in_master_mode(mac_handle_t hal,
				     bool etsi13_srd_chan_support)
{
}
#else
static inline
QDF_STATUS sme_ocb_set_config(mac_handle_t mac_handle, void *context,
			      ocb_callback callback,
			      struct sir_ocb_config *config)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS sme_ocb_set_utc_time(struct sir_ocb_utc *utc)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS sme_ocb_start_timing_advert(
		struct sir_ocb_timing_advert *timing_advert)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS sme_ocb_stop_timing_advert(struct sir_ocb_timing_advert
		*timing_advert)
{
	return QDF_STATUS_SUCCESS;
}

static inline
int sme_ocb_gen_timing_advert_frame(mac_handle_t mac_handle,
				    tSirMacAddr self_addr, uint8_t **buf,
				    uint32_t *timestamp_offset,
				    uint32_t *time_value_offset)
{
	return 0;
}

static inline
QDF_STATUS sme_ocb_get_tsf_timer(mac_handle_t mac_handle, void *context,
				 ocb_callback callback,
				 struct sir_ocb_get_tsf_timer *request)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_dcc_get_stats(mac_handle_t mac_handle, void *context,
			     ocb_callback callback,
			     struct sir_dcc_get_stats *request)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_dcc_clear_stats(uint32_t vdev_id,
			       uint32_t dcc_stats_bitmap)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_dcc_update_ndl(mac_handle_t mac_handle, void *context,
			      ocb_callback callback,
			      struct sir_dcc_update_ndl *request)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_register_for_dcc_stats_event(mac_handle_t mac_handle,
					    void *context,
					    ocb_callback callback)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_deregister_for_dcc_stats_event(mac_handle_t mac_handle)
{
	return QDF_STATUS_SUCCESS;
}

/**
 * sme_set_etsi13_srd_ch_in_master_mode() - master mode UNI-III band ch support
 * @hal: HAL pointer
 * @srd_chan_support: ETSI SRD channel support
 *
 * This function set master ETSI SRD channel support
 *
 * Return: None
 */
void sme_set_etsi13_srd_ch_in_master_mode(mac_handle_t hal,
					  bool etsi13_srd_chan_support);
#endif

void sme_add_set_thermal_level_callback(mac_handle_t hal,
		sme_set_thermal_level_callback callback);

void sme_update_tgt_services(mac_handle_t hal, struct wma_tgt_services *cfg);
bool sme_validate_sap_channel_switch(mac_handle_t hal,
		uint16_t sap_ch, eCsrPhyMode sap_phy_mode,
		uint8_t cc_switch_mode, uint8_t session_id);

bool sme_is_session_id_valid(mac_handle_t hal, uint32_t session_id);

#ifdef FEATURE_WLAN_TDLS
void sme_get_opclass(mac_handle_t hal, uint8_t channel, uint8_t bw_offset,
		uint8_t *opclass);
#else
static inline void
sme_get_opclass(mac_handle_t hal, uint8_t channel, uint8_t bw_offset,
		uint8_t *opclass)
{
}
#endif

#ifdef FEATURE_LFR_SUBNET_DETECTION
QDF_STATUS sme_gateway_param_update(mac_handle_t mac_handle,
				struct gateway_param_update_req *request);
#endif

void sme_update_fine_time_measurement_capab(mac_handle_t mac_handle,
					    uint8_t session_id,
					    uint32_t val);
QDF_STATUS sme_ht40_stop_obss_scan(mac_handle_t mac_handle, uint32_t vdev_id);
QDF_STATUS sme_set_fw_test(struct set_fwtest_params *fw_test);
QDF_STATUS sme_set_tsfcb(mac_handle_t mac_handle,
	int (*cb_fn)(void *cb_ctx, struct stsf *ptsf), void *cb_ctx);

QDF_STATUS sme_reset_tsfcb(mac_handle_t mac_handle);

#if defined(WLAN_FEATURE_TSF) && !defined(WLAN_FEATURE_TSF_PLUS_NOIRQ)
QDF_STATUS sme_set_tsf_gpio(mac_handle_t mac_handle, uint32_t pinvalue);
#endif

QDF_STATUS sme_update_mimo_power_save(mac_handle_t mac_handle,
				      uint8_t is_ht_smps_enabled,
				      uint8_t ht_smps_mode,
				      bool send_smps_action);

bool sme_is_sta_smps_allowed(mac_handle_t mac_handle, uint8_t session_id);
QDF_STATUS sme_add_beacon_filter(mac_handle_t hal,
				uint32_t session_id, uint32_t *ie_map);
QDF_STATUS sme_remove_beacon_filter(mac_handle_t hal, uint32_t session_id);

#ifdef FEATURE_WLAN_APF
/**
 * sme_get_apf_capabilities() - Get APF capabilities
 * @hal: Global HAL handle
 * @callback: Callback function to be called with the result
 * @context: Opaque context to be used by the caller to associate the
 *   request with the response
 *
 * This function constructs the cds message and fill in message type,
 * post the same to WDA.
 *
 * Return: QDF_STATUS enumeration
 */
QDF_STATUS sme_get_apf_capabilities(mac_handle_t hal,
				    apf_get_offload_cb callback,
				    void *context);

/**
 * sme_set_apf_instructions() - Set APF apf filter instructions.
 * @hal: HAL handle
 * @apf_set_offload: struct to set apf filter instructions.
 *
 * APFv2 (Legacy APF) API to set the APF packet filter.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_set_apf_instructions(mac_handle_t hal,
				    struct sir_apf_set_offload
							*apf_set_offload);

/**
 * sme_set_apf_enable_disable - Send apf enable/disable cmd
 * @hal: global hal handle
 * @vdev_id: vdev id
 * @apf_enable: true: Enable APF Int., false: Disable APF Int.
 *
 * API to either enable or disable the APF interpreter.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_set_apf_enable_disable(mac_handle_t hal, uint8_t vdev_id,
				      bool apf_enable);

/**
 * sme_apf_write_work_memory - Write into the apf work memory
 * @hal: global hal handle
 * @write_params: APF parameters for the write operation
 *
 * API for writing into the APF work memory.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_apf_write_work_memory(mac_handle_t hal,
				    struct wmi_apf_write_memory_params
								*write_params);

/**
 * sme_apf_read_work_memory - Read part of apf work memory
 * @hal: global hal handle
 * @read_params: APF parameters for the get operation
 * @callback: callback to handle the the read response
 *
 * API for issuing a APF read memory request.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS
sme_apf_read_work_memory(mac_handle_t hal,
			 struct wmi_apf_read_memory_params *read_params,
			 apf_read_mem_cb callback);

#endif /* FEATURE_WLAN_APF */

uint32_t sme_get_wni_dot11_mode(mac_handle_t hal);
QDF_STATUS sme_create_mon_session(mac_handle_t mac_handle, uint8_t *bssid,
				  uint8_t vdev_id);
QDF_STATUS sme_set_adaptive_dwelltime_config(mac_handle_t hal,
			struct adaptive_dwelltime_params *dwelltime_params);

void sme_set_vdev_ies_per_band(mac_handle_t hal, uint8_t vdev_id);
void sme_set_pdev_ht_vht_ies(mac_handle_t mac_handle, bool enable2x2);

void sme_update_vdev_type_nss(mac_handle_t hal, uint8_t max_supp_nss,
		uint32_t vdev_type_nss, enum band_info band);
void sme_update_hw_dbs_capable(mac_handle_t hal, uint8_t hw_dbs_capable);
#ifdef FEATURE_P2P_LISTEN_OFFLOAD
void sme_register_p2p_lo_event(mac_handle_t mac_handle, void *context,
					p2p_lo_callback callback);
#else
static inline void sme_register_p2p_lo_event(mac_handle_t mac_handle,
					     void *context,
					     p2p_lo_callback callback)
{
}
#endif

QDF_STATUS sme_remove_bssid_from_scan_list(mac_handle_t hal,
	tSirMacAddr bssid);

QDF_STATUS sme_process_mac_pwr_dbg_cmd(mac_handle_t hal, uint32_t session_id,
				       struct sir_mac_pwr_dbg_cmd*
				       dbg_args);

void sme_get_vdev_type_nss(enum QDF_OPMODE dev_mode,
			   uint8_t *nss_2g, uint8_t *nss_5g);
QDF_STATUS sme_roam_set_default_key_index(mac_handle_t hal, uint8_t session_id,
					  uint8_t default_idx);
void sme_send_disassoc_req_frame(mac_handle_t hal, uint8_t session_id, uint8_t
				*peer_mac, uint16_t reason, uint8_t
				wait_for_ack);
QDF_STATUS sme_update_access_policy_vendor_ie(mac_handle_t hal,
					uint8_t session_id, uint8_t *vendor_ie,
					int access_policy);

/**
 * sme_set_peer_param() - set peer param
 * @vdev_id: vdev ID
 * @peer_addr: peer MAC address
 * @param_id: param ID to be updated
 * @param_Value: paraam value
 *
 * This SME API is used to send the peer param to WMA to be sent to FW.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_peer_param(uint8_t *peer_addr, uint32_t param_id,
			      uint32_t param_value, uint32_t vdev_id);

QDF_STATUS sme_update_sta_roam_policy(mac_handle_t hal,
		enum sta_roam_policy_dfs_mode dfs_mode,
		bool skip_unsafe_channels,
		uint8_t session_id, uint8_t sap_operating_band);
QDF_STATUS sme_enable_disable_chanavoidind_event(mac_handle_t hal,
					uint8_t set_value);
QDF_STATUS sme_set_default_scan_ie(mac_handle_t hal, uint16_t session_id,
				uint8_t *ie_data, uint16_t ie_len);
/**
 * sme_update_session_param() - API to update PE session param
 * @hal: HAL handle for device
 * @session_id: Session ID
 * @param_type: Param type to be updated
 * @param_val: Param value to be update
 *
 * Note: this setting will not persist over reboots.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_update_session_param(mac_handle_t hal, uint8_t session_id,
		uint32_t param_type, uint32_t param_val);
#ifdef WLAN_FEATURE_FIPS
/**
 * sme_fips_request() - Perform a FIPS certification operation
 * @hal: Hal handle for the object being certified
 * @param: The FIPS certification parameters
 * @callback: Callback function to invoke with the results
 * @context: Opaque context to pass back to caller in the callback
 *
 * Return: QDF_STATUS_SUCCESS if the request is successfully sent
 * to firmware for processing, otherwise an error status.
 */
QDF_STATUS sme_fips_request(mac_handle_t hal, struct fips_params *param,
			    wma_fips_cb callback, void *context);
#else
static inline
QDF_STATUS sme_fips_request(mac_handle_t hal, struct fips_params *param,
			    wma_fips_cb callback, void *context)
{
	return QDF_STATUS_E_NOSUPPORT;
}
#endif /* WLAN_FEATURE_FIPS */

/**
 * sme_set_cts2self_for_p2p_go() - sme function to set ini parms to FW.
 * @hal:                    reference to the HAL
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_cts2self_for_p2p_go(mac_handle_t hal);
void sme_set_prefer_80MHz_over_160MHz(mac_handle_t hal,
		bool sta_prefer_80MHz_over_160MHz);
QDF_STATUS sme_update_tx_fail_cnt_threshold(mac_handle_t mac_handle,
		uint8_t session_id, uint32_t tx_fail_count);
QDF_STATUS sme_update_short_retry_limit_threshold(mac_handle_t mac_handle,
		struct sme_short_retry_limit *short_retry_limit_th);
QDF_STATUS sme_update_long_retry_limit_threshold(mac_handle_t mac_handle,
		struct sme_long_retry_limit  *long_retry_limit_th);
/**
 * sme_roam_is_ese_assoc() - Check if association type is ESE
 * @roam_info: Pointer to roam info
 *
 * Return: true if ESE Association, false otherwise.
 */
#ifdef FEATURE_WLAN_ESE
bool sme_roam_is_ese_assoc(struct csr_roam_info *roam_info);
#else
static inline bool sme_roam_is_ese_assoc(struct csr_roam_info *roam_info)
{
	return false;
}
#endif
/**
 * sme_neighbor_roam_is11r_assoc() - Check if association type is 11R
 * @hal_ctx: HAL handle
 * @session_id: session id
 *
 * Return: true if 11r Association, false otherwise.
 */
bool sme_neighbor_roam_is11r_assoc(mac_handle_t hal_ctx, uint8_t session_id);

/**
 * sme_update_sta_inactivity_timeout(): Update sta_inactivity_timeout to FW
 * @hal: Handle returned by mac_open
 * @sta_inactivity_timer:  struct for sta inactivity timer
 *
 * If a station does not send anything in sta_inactivity_timeout seconds, an
 * empty data frame is sent to it in order to verify whether it is
 * still in range. If this frame is not ACKed, the station will be
 * disassociated and then deauthenticated.
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure.
*/
QDF_STATUS sme_update_sta_inactivity_timeout(mac_handle_t mac_handle,
		struct sme_sta_inactivity_timeout  *sta_inactivity_timer);

/**
 * sme_set_lost_link_info_cb() - plug in callback function for receiving
 * @mac_handle: Opaque handle to the MAC context
 * @cb: callback function
 *
 * Return: HAL status
 */
QDF_STATUS sme_set_lost_link_info_cb(mac_handle_t mac_handle,
				     lost_link_info_cb cb);

/**
 * sme_update_new_channel_event() - update new channel event for sapFsm
 * @hal: HAL handle
 * @session_id: session id
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure.
 */
QDF_STATUS sme_update_new_channel_event(mac_handle_t hal, uint8_t session_id);
#ifdef WLAN_POWER_DEBUGFS
QDF_STATUS sme_power_debug_stats_req(mac_handle_t hal, void (*callback_fn)
				(struct  power_stats_response *response,
				void *context), void *power_stats_context);
#endif

/**
 * sme_get_sar_power_limits() - get SAR limits
 * @hal: HAL handle
 * @callback: Callback function to invoke with the results
 * @context: Opaque context to pass back to caller in the callback
 *
 * Return: QDF_STATUS_SUCCESS if the request is successfully sent
 * to firmware for processing, otherwise an error status.
 */
QDF_STATUS sme_get_sar_power_limits(mac_handle_t hal,
				    wma_sar_cb callback, void *context);

/**
 * sme_set_sar_power_limits() - set sar limits
 * @hal: HAL handle
 * @sar_limit_cmd: struct to send sar limit cmd.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_set_sar_power_limits(mac_handle_t hal,
		struct sar_limit_cmd_params *sar_limit_cmd);

/**
 * sme_send_coex_config_cmd() - Send COEX config params
 * @coex_cfg_params: struct to coex config params
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_send_coex_config_cmd(struct coex_config_params *coex_cfg_params);

void sme_set_cc_src(mac_handle_t mac_handle, enum country_src);


#ifdef WLAN_FEATURE_WOW_PULSE
QDF_STATUS sme_set_wow_pulse(struct wow_pulse_mode *wow_pulse_set_info);
#endif

/* ARP DEBUG STATS */
QDF_STATUS sme_set_nud_debug_stats(mac_handle_t hal,
				   struct set_arp_stats_params
				   *set_stats_param);
QDF_STATUS sme_get_nud_debug_stats(mac_handle_t hal,
				   struct get_arp_stats_params
				   *get_stats_param);
QDF_STATUS sme_set_nud_debug_stats_cb(mac_handle_t hal,
			void (*cb)(void *, struct rsp_stats *, void *context),
			void *context);

/**
 * sme_set_chan_info_callback() - Register chan info callback
 * @hal - MAC global handle
 * @callback_routine - callback routine from HDD
 *
 * This API is invoked by HDD to register its callback to mac
 *
 * Return: QDF_STATUS
 */
void sme_set_chan_info_callback(mac_handle_t mac_handle,
			void (*callback)(struct scan_chan_info *chan_info));

/**
 * sme_get_rssi_snr_by_bssid() - gets the rssi and snr by bssid from scan cache
 * @hal: handle returned by mac_open
 * @profile: current connected profile
 * @bssid: bssid to look for in scan cache
 * @rssi: rssi value found
 * @snr: snr value found
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_get_rssi_snr_by_bssid(mac_handle_t hal,
				     struct csr_roam_profile *profile,
				     const uint8_t *bssid, int8_t *rssi,
				     int8_t *snr);

/**
 * sme_get_beacon_frm() - gets the bss descriptor from scan cache and prepares
 * beacon frame
 * @mac_handle: handle returned by mac_open
 * @profile: current connected profile
 * @bssid: bssid to look for in scan cache
 * @frame_buf: frame buffer to populate
 * @frame_len: length of constructed frame
 * @channel: Pointer to channel info to be filled
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_get_beacon_frm(mac_handle_t mac_handle,
			      struct csr_roam_profile *profile,
			      const tSirMacAddr bssid,
			      uint8_t **frame_buf, uint32_t *frame_len,
			      int *channel);

#ifdef WLAN_FEATURE_ROAM_OFFLOAD
/**
 * sme_fast_reassoc() - invokes FAST REASSOC command
 * @hal: handle returned by mac_open
 * @profile: current connected profile
 * @bssid: bssid to look for in scan cache
 * @channel: channel on which reassoc should be send
 * @vdev_id: vdev id
 * @connected_bssid: bssid of currently connected profile
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_fast_reassoc(mac_handle_t hal, struct csr_roam_profile *profile,
			    const tSirMacAddr bssid, int channel,
			    uint8_t vdev_id, const tSirMacAddr connected_bssid);
#endif
/**
 * sme_congestion_register_callback() - registers congestion callback
 * @hal: handler for HAL
 * @congestion_cb: congestion callback
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_congestion_register_callback(mac_handle_t hal,
					    congestion_cb congestion_cb);

/**
 * sme_register_tx_queue_cb(): Register tx queue callback
 * @mac_handle: Opaque handle for MAC context
 * @tx_queue_cb: Transmit Queues callback
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_register_tx_queue_cb(mac_handle_t mac_handle,
				    tx_queue_cb tx_queue_cb);

/**
 * sme_deregister_tx_queue_cb() - Deregister the tx queue callback
 * @mac_handle: Opaque handle for MAC context
 *
 * Return: QDF status
 */
QDF_STATUS sme_deregister_tx_queue_cb(mac_handle_t mac_handle);

/**
 * sme_rso_cmd_status_cb() - Set RSO cmd status callback
 * @mac_handle: Opaque handle for the MAC context
 * @cb: HDD Callback to rso command status read
 *
 * This function is used to save HDD RSO Command status callback in MAC
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_rso_cmd_status_cb(mac_handle_t mac_handle,
				 rso_cmd_status_cb cb);

/**
 * sme_register_set_connection_info_cb() - Register connection
 * info callback
 * @hal - MAC global handle
 * @set_connection_info_cb - callback routine from HDD to set
 *                   connection info flag
 * @get_connection_info_cb - callback routine from HDD to get
 *                         connection info
 *
 * This API is invoked by HDD to register its callback to mac
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_register_set_connection_info_cb(mac_handle_t mac_handle,
				bool (*set_connection_info_cb)(bool),
				bool (*get_connection_info_cb)(uint8_t *session_id,
				enum scan_reject_states *reason));

/**
 * sme_set_dbs_scan_selection_config() - Update DBS scan selection
 * configuration
 * @hal: The handle returned by macOpen
 * @params: wmi_dbs_scan_sel_params config
 *
 * Return: QDF_STATUS if DBS scan selection update
 * configuration success else failure status
 */
QDF_STATUS sme_set_dbs_scan_selection_config(mac_handle_t hal,
		struct wmi_dbs_scan_sel_params *params);

/**
 * sme_store_pdev() - store pdev
 * @hal - MAC global handle
 * @pdev - pdev ptr
 *
 * Return: QDF_STATUS
 */
void sme_store_pdev(mac_handle_t hal, struct wlan_objmgr_pdev *pdev);

/**
 * sme_ipa_uc_stat_request() - set ipa config parameters
 * @vdev_id: virtual device for the command
 * @param_id: parameter id
 * @param_val: parameter value
 * @req_cat: parameter category
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */
QDF_STATUS sme_ipa_uc_stat_request(mac_handle_t hal,
			uint32_t vdev_id, uint32_t param_id,
			uint32_t param_val, uint32_t req_cat);

/**
 * sme_set_reorder_timeout() - set reorder timeout value
 * including Voice,Video,Besteffort,Background parameters
 * @hal: hal handle for getting global mac struct
 * @reg: struct sir_set_rx_reorder_timeout_val
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure.
 */
QDF_STATUS sme_set_reorder_timeout(mac_handle_t hal,
		struct sir_set_rx_reorder_timeout_val *req);

/**
 * sme_set_rx_set_blocksize() - set blocksize value
 * including mac_addr and win_limit parameters
 * @hal: hal handle for getting global mac struct
 * @reg: struct sir_peer_set_rx_blocksize
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure.
 */

QDF_STATUS sme_set_rx_set_blocksize(mac_handle_t hal,
		struct sir_peer_set_rx_blocksize *req);

/**
 * sme_get_rcpi() - gets the rcpi value for peer mac addr
 * @hal: handle returned by mac_open
 * @rcpi: rcpi request containing peer mac addr, callback and related info
 *
 * This function posts the rcpi measurement request message to wma queue
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_get_rcpi(mac_handle_t hal, struct sme_rcpi_req *rcpi);

/**
 * sme_set_chip_pwr_save_fail_cb() - set chip power save failure callback
 * @mac_handle: opaque handle to the MAC context
 * @cb: callback function pointer
 *
 * This function stores the chip power save failure callback function.
 *
 * Return: QDF_STATUS enumeration.
 */

QDF_STATUS sme_set_chip_pwr_save_fail_cb(mac_handle_t mac_handle,
					 pwr_save_fail_cb cb);
/**
 * sme_cli_set_command() - SME wrapper API over WMA "set" command
 * processor cmd
 * @vdev_id: virtual device for the command
 * @param_id: parameter id
 * @sval: parameter value
 * @vpdev: parameter category
 *
 * Command handler for set operations
 *
 * Return: 0 on success, errno on failure
 */
int sme_cli_set_command(int vdev_id, int param_id, int sval, int vpdev);

/**
 * sme_set_bt_activity_info_cb - set the callback handler for bt events
 * @mac_handle: handle returned by mac_open
 * @cb: callback handler
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_bt_activity_info_cb(mac_handle_t mac_handle,
				       bt_activity_info_cb cb);

/**
 * sme_set_enable_mem_deep_sleep - set the mem deep sleep config to FW
 * @mac_handle: handle returned by mac_open
 * @vdev_id: vdev id
 *
 * Return: 0 for success else failure code
 */
int sme_set_enable_mem_deep_sleep(mac_handle_t mac_handle, int vdev_id);

/**
 * sme_set_cck_tx_fir_override - set the CCK TX FIR Override to FW
 * @mac_handle: handle returned by mac_open
 * @vdev_id: vdev id
 *
 * Return: 0 for success else failure code
 */
int sme_set_cck_tx_fir_override(mac_handle_t mac_handle, int vdev_id);

/**
 * sme_set_smps_cfg() - set SMPS config params
 * @vdev_id: virtual device for the command
 * @param_id: parameter id
 * @param_val: parameter value
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */

QDF_STATUS sme_set_smps_cfg(uint32_t vdev_id, uint32_t param_id,
				uint32_t param_val);

/**
 * sme_get_peer_stats() - sme api to post peer info request
 * @mac: mac handle
 * @req: peer info request struct send to wma
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */

QDF_STATUS sme_get_peer_stats(tpAniSirGlobal mac,
			      struct sir_peer_info_req req);

/**
 * sme_get_peer_info() - sme api to get peer info
 * @hal: hal handle for getting global mac struct
 * @req: peer info request struct send to wma
 * @context: context of callback function
 * @callbackfn: hdd callback function when receive response
 *
 * This function will send WMA_GET_PEER_INFO to WMA
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */
QDF_STATUS sme_get_peer_info(mac_handle_t hal,
		struct sir_peer_info_req req,
		void *context,
		void (*callbackfn)(struct sir_peer_info_resp *param,
			void *pcontext));

/**
 * sme_get_peer_info_ext() - sme api to get peer ext info
 * @hal: hal handle for getting global mac struct
 * @req: peer ext info request struct send to wma
 * @context: context of callback function
 * @callbackfn: hdd callback function when receive response
 *
 * This function will send WMA_GET_PEER_INFO_EXT to WMA
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */
QDF_STATUS sme_get_peer_info_ext(mac_handle_t hal,
		struct sir_peer_info_ext_req *req,
		void *context,
		void (*callbackfn)(struct sir_peer_info_ext_resp *param,
			void *pcontext));

/**
 * sme_get_chain_rssi() - Get chain rssi
 * @hal: Global HAL handle
 * @input: get chain rssi req params
 * @callback: Callback function to be called with the result
 * @context: Opaque context to be used by the caller to associate the
 *   request with the response
 *
 * This function constructs the cds message and fill in message type,
 * post the same to WDA.
 *
 * Return: QDF_STATUS enumeration
 */
QDF_STATUS sme_get_chain_rssi(mac_handle_t hal,
			      struct get_chain_rssi_req_params *input,
			      get_chain_rssi_callback callback,
			      void *context);

/**
 * sme_get_valid_channels() - sme api to get valid channels for
 * current regulatory domain
 * @chan_list: list of the valid channels
 * @list_len: length of the channel list
 *
 * This function will get valid channels for current regulatory
 * domain
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */
QDF_STATUS sme_get_valid_channels(uint8_t *chan_list, uint32_t *list_len);

/**
 * sme_get_mac_context() - sme api to get the pmac context
 *
 * This function will return the pmac context
 *
 * Return: pointer to pmac context
 */
tpAniSirGlobal sme_get_mac_context(void);

/**
 * sme_display_disconnect_stats() - Display per session Disconnect stats
 * @hal: hal global context
 * session_id: SME session id
 *
 * Return: None
 */
void sme_display_disconnect_stats(mac_handle_t hal, uint8_t session_id);

/**
 * sme_process_msg_callback() - process callback message from LIM
 * @mac: global mac context
 * @msg: scheduler message
 *
 * This function process the callback messages from LIM.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_process_msg_callback(tpAniSirGlobal mac,
				    struct scheduler_msg *msg);

/**
 * sme_set_bmiss_bcnt() - set bmiss config parameters
 * @vdev_id: virtual device for the command
 * @first_cnt: bmiss first value
 * @final_cnt: bmiss final value
 *
 * Return: QDF_STATUS_SUCCESS or non-zero on failure
 */
QDF_STATUS sme_set_bmiss_bcnt(uint32_t vdev_id, uint32_t first_cnt,
		uint32_t final_cnt);

/**
 * sme_send_limit_off_channel_params() - send limit off channel parameters
 * @hal: global hal handle
 * @vdev_id: vdev id
 * @is_tos_active: tos active or inactive
 * @max_off_chan_time: max off channel time
 * @rest_time: rest time
 * @skip_dfs_chan: skip dfs channel
 *
 * This function sends command to WMA for setting limit off channel command
 * parameters.
 *
 * Return: QDF_STATUS enumeration.
 */
QDF_STATUS sme_send_limit_off_channel_params(mac_handle_t hal, uint8_t vdev_id,
		bool is_tos_active, uint32_t max_off_chan_time,
		uint32_t rest_time, bool skip_dfs_chan);

#ifdef FEATURE_WLAN_DYNAMIC_CVM
/**
 * sme_set_vc_mode_config() - Set voltage corner config to FW.
 * @bitmap:	Bitmap that refers to voltage corner config with
 * different phymode and bw configuration
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_vc_mode_config(uint32_t vc_bitmap);
#endif

/**
 * sme_set_del_pmkid_cache() - API to update PMKID cache
 * @hal: HAL handle for device
 * @session_id: Session id
 * @pmk_cache_info: Pointer to PMK cache info
 * @is_add: boolean that implies whether to add or delete PMKID entry
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_del_pmkid_cache(mac_handle_t hal, uint8_t session_id,
				   tPmkidCacheInfo *pmk_cache_info,
				   bool is_add);

/**
 * sme_send_hlp_ie_info() - API to send HLP IE info to fw
 * @hal: HAL handle for device
 * @session_id: Session id
 * @profile: CSR Roam profile
 * @if_addr: IP address
 *
 * This API is used to send HLP IE info along with IP address
 * to fw if LFR3 is enabled.
 *
 * Return: QDF_STATUS
 */
void sme_send_hlp_ie_info(mac_handle_t hal, uint8_t session_id,
			  struct csr_roam_profile *profile, uint32_t if_addr);

#if defined(WLAN_FEATURE_FILS_SK)
/**
 * sme_update_fils_config - Update FILS config to CSR roam session
 * @hal: HAL handle for device
 * @session_id: session id
 * @src_profile: Source profile having latest FILS config
 *
 * API to update FILS config to roam csr session and update the same
 * to fw if LFR3 is enabled.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_update_fils_config(mac_handle_t hal, uint8_t session_id,
				struct csr_roam_profile *src_profile);

/**
 * sme_free_join_rsp_fils_params - free fils params
 * @roam_info: roam info
 *
 * Return: void
 */
void sme_free_join_rsp_fils_params(struct csr_roam_info *roam_info);
#else
static inline QDF_STATUS sme_update_fils_config(mac_handle_t hal,
				uint8_t session_id,
				struct csr_roam_profile *src_profile)
{
	return QDF_STATUS_SUCCESS;
}

static inline
void sme_free_join_rsp_fils_params(struct csr_roam_info *roam_info)
{}

#endif

#ifdef WLAN_FEATURE_11AX_BSS_COLOR
/**
 * sme_set_he_bss_color() - Sets the HE BSS color
 *
 * @hal: The handle returned by mac_open
 * @session_id: session_id of the request
 * @bss_color: HE BSS color value to set
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_set_he_bss_color(mac_handle_t hal, uint8_t session_id,
		uint8_t bss_color);
#else
static inline QDF_STATUS sme_set_he_bss_color(mac_handle_t hal,
		uint8_t session_id, uint8_t bss_color)
{
	return QDF_STATUS_SUCCESS;
}
#endif

/**
 * sme_is_conn_state_connected() -- check if SME connection state is connected
 * @hal: global hal handle
 * @session_id: current Session Id
 *
 * This API checks if the current SME connection state is connected for the
 * given session id.
 *
 * Return: True if connected, false if any other state.
 */
bool sme_is_conn_state_connected(mac_handle_t hal, uint8_t session_id);

/**
 * sme_scan_get_result_for_bssid - gets the scan result from scan cache for the
 * bssid specified
 * @hal: handle returned by mac_open
 * @bssid: bssid to get the scan result for
 * @res: pointer to tCsrScanResultInfo allocated from caller
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_scan_get_result_for_bssid(mac_handle_t mac_handle,
					 struct qdf_mac_addr *bssid,
					 tCsrScanResultInfo *res);

/**
 * sme_get_bss_transition_status() - get bss transition status all cadidates
 * @hal: handle returned by mac_open
 * @transition_reason : Transition reason
 * @bssid: bssid to get BSS transition status
 * @info : bss candidate information
 * @n_candidates : number of candidates
 * @is_bt_in_progress: bt activity indicator
 *
 * Return : 0 on success otherwise errno
 */
int sme_get_bss_transition_status(mac_handle_t hal,
		uint8_t transition_reason,
		struct qdf_mac_addr *bssid,
		struct bss_candidate_info *info,
		uint16_t n_candidates,
		bool is_bt_in_progress);

/**
 * sme_unpack_rsn_ie: wrapper to unpack RSN IE and update def RSN params
 * if optional fields are not present.
 * @hal: handle returned by mac_open
 * @buf: rsn ie buffer pointer
 * @buf_len: rsn ie buffer length
 * @rsn_ie: outframe rsn ie structure
 * @append_ie: flag to indicate if the rsn_ie need to be appended from buf
 *
 * Return: parse status
 */
uint32_t sme_unpack_rsn_ie(mac_handle_t hal, uint8_t *buf,
				  uint8_t buf_len, tDot11fIERSN *rsn_ie,
				  bool append_ie);
/**
 * sme_get_oper_chan_freq - gets the operating channel freq
 * @vdev: vdev handle
 *
 * Return: operating channel frequency
 */
int16_t sme_get_oper_chan_freq(struct wlan_objmgr_vdev *vdev);

/**
 * sme_get_oper_ch_width - gets the operating channel width
 * @vdev: vdev handle
 *
 * Return: operating channel width
 */
enum phy_ch_width sme_get_oper_ch_width(struct wlan_objmgr_vdev *vdev);

/**
 * sme_get_oper_ch_width - gets the secondary channel frequency
 * @vdev: vdev handle
 * @sec20chan_freq: secondary channel frequency
 *
 * Return: secondary channel frequency
 */
int sme_get_sec20chan_freq_mhz(struct wlan_objmgr_vdev *vdev,
						uint16_t *sec20chan_freq);

/**
 * sme_enable_roaming_on_connected_sta() - Enable roaming on an connected sta
 * @hal: handle returned by mac_open
 *
 * The function check if any connected STA is present on which roaming is not
 * enabled and if present enabled roaming on that STA.
 *
 * Return: none
 */
void sme_enable_roaming_on_connected_sta(mac_handle_t hal);

/**
 * sme_send_mgmt_tx() - Sends mgmt frame from CSR to LIM
 * @hal: The handle returned by mac_open
 * @session_id: session id
 * @buf: pointer to frame
 * @len: frame length
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_send_mgmt_tx(mac_handle_t hal, uint8_t session_id,
			   const uint8_t *buf, uint32_t len);

#ifdef WLAN_FEATURE_SAE
/**
 * sme_handle_sae_msg() - Sends SAE message received from supplicant
 * @hal: The handle returned by mac_open
 * @session_id: session id
 * @sae_status: status of SAE authentication
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_handle_sae_msg(mac_handle_t hal, uint8_t session_id,
		uint8_t sae_status);
#else
static inline QDF_STATUS sme_handle_sae_msg(mac_handle_t hal, uint8_t session_id,
		uint8_t sae_status)
{
	return QDF_STATUS_SUCCESS;
}
#endif

/**
 * sme_set_ba_buff_size() - sets BA buffer size
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @buff_size: BA buffer size
 *
 * Return: 0 on success else err code
 */
int sme_set_ba_buff_size(mac_handle_t hal, uint8_t session_id,
		uint16_t buff_size);

/**
 * sme_send_addba_req() - send ADDBA request with user config
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @tid: tid val for BA session
 * @buff_size: BA buffer size
 *
 * Return: 0 on success else err code
 */
int sme_send_addba_req(mac_handle_t hal, uint8_t session_id, uint8_t tid,
		uint16_t buff_size);

/**
 * sme_set_no_ack_policy() - Sets no ack policy for AC
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @val: no ack policy value
 * @ac: access category
 *
 * Return: 0 on success else err code
 */
int sme_set_no_ack_policy(mac_handle_t hal, uint8_t session_id,
		uint8_t val, uint8_t ac);

/**
 * sme_set_auto_rate_he_sgi() - Sets SGI for auto rate
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @cfg_val: SGI configuration value
 *
 * Return: 0 on success else err code
 */
int sme_set_auto_rate_he_sgi(mac_handle_t hal, uint8_t session_id,
		uint8_t cfg_val);

/**
 * sme_set_auto_rate_he_ltf() - Sets HE LTF for auto rate
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @cfg_val: LTF configuration value
 *
 * Return: 0 on success else err code
 */
int sme_set_auto_rate_he_ltf(mac_handle_t hal, uint8_t session_id,
		uint8_t cfg_val);

#ifdef WLAN_FEATURE_11AX
/**
 * sme_update_tgt_he_cap() - sets the HE caps to pmac
 * @mac_handle: Pointer to MAC handle
 * @cfg: Pointer to WMA target CFG
 * @he_cap_ini: Pointer to HE CAP configured by INI
 *
 * Return: None
 */
void sme_update_tgt_he_cap(mac_handle_t mac_handle,
			   struct wma_tgt_cfg *cfg,
			   tDot11fIEhe_cap *he_cap_ini);

/**
 * sme_update_he_cap_nss() - sets the nss based on user request
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @nss: no.of spatial streams value
 *
 * Return: None
 */
void sme_update_he_cap_nss(mac_handle_t hal, uint8_t session_id,
		uint8_t nss);

/**
 * sme_update_he_tx_bfee_supp() - sets the HE Tx Bfee support
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @cfg_val: Tx Bfee config value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_tx_bfee_supp(mac_handle_t hal, uint8_t session_id,
		uint8_t cfg_val);

/**
 * sme_update_he_tx_bfee_nsts() - sets the HE Tx Bfee NSTS
 * @hal: MAC handle
 * @session_id: SME session id
 * @cfg_val: Tx Bfee NSTS value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_tx_bfee_nsts(mac_handle_t hal, uint8_t session_id,
			       uint8_t cfg_val);

/**
 * sme_set_he_tx_bf_cbf_rates() - sets the HE Tx Bfee CBF frame rates to FW
 * @session_id: SME session id
 *
 * Return: None
 */
void sme_set_he_tx_bf_cbf_rates(uint8_t session_id);

/**
 * sme_config_su_ppdu_queue() - Configures SU PPDU queue enable/disable in FW
 * @session_id: SME session id
 * @enable: Enable/Disable config
 *
 * Return: None
 */
void sme_config_su_ppdu_queue(uint8_t session_id, bool enable);

/**
 * sme_update_he_mcs() - sets the HE MCS based on user request
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @he_mcs: HE MCS value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_mcs(mac_handle_t hal, uint8_t session_id, uint16_t he_mcs);

/**
 * sme_update_he_trigger_frm_mac_pad() - sets the HE MAC padding capability
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @cfg_val: HE MAC padding duration value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_trigger_frm_mac_pad(mac_handle_t hal, uint8_t session_id,
				      uint8_t cfg_val);

/**
 * sme_update_he_om_ctrl_supp() - sets the HE OM control capability
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @cfg_val: HE OM control config
 *
 * Return: 0 on success else err code
 */
int sme_update_he_om_ctrl_supp(mac_handle_t hal, uint8_t session_id,
			       uint8_t cfg_val);

#define NUM_OM_CTRL_UPDATE_CFG_PARAMS 7
#define OM_CTRL_CMD_MAC_BITS31 1
#define OM_CTRL_CMD_MAC_BITS47 2
#define OM_CTRL_CMD_RX_NSS 3
#define OM_CTRL_CMD_BW 4
#define OM_CTRL_CMD_ULMU 5
#define OM_CTRL_CMD_TX_NSS 6
int sme_send_he_om_ctrl_bw_update(mac_handle_t hal, uint8_t session_id,
				  uint8_t cfg_val);

int sme_send_he_om_ctrl_nss_update(mac_handle_t hal, uint8_t session_id,
				   uint8_t cfg_val);

void sme_reset_he_om_ctrl(mac_handle_t hal);

/**
 * sme_set_usr_cfg_mu_edca() - sets the user cfg MU EDCA params flag
 * @hal: Pointer to HAL
 * @val: value to be set
 *
 * Return: none
 */
void sme_set_usr_cfg_mu_edca(mac_handle_t hal, bool val);

/**
 * sme_set_he_mu_edca_def_cfg() - sets the default MU EDCA params values
 * @hal: Pointer to HAL
 *
 * Return: none
 */
void sme_set_he_mu_edca_def_cfg(mac_handle_t hal);

/**
 * sme_update_mu_edca_params() - updates MU EDCA params values
 * @hal: Pointer to HAL
 * @session_id: SME session id
 *
 * Return: 0 on success else err code
 */
int sme_update_mu_edca_params(mac_handle_t hal, uint8_t session_id);

/**
 * sme_update_he_tx_stbc_cap() - Sets the HE Tx STBC capability
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @value: set value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_tx_stbc_cap(mac_handle_t hal, uint8_t session_id, int value);

/**
 * sme_update_he_rx_stbc_cap() - Sets the HE Rx STBC capability
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @value: set value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_rx_stbc_cap(mac_handle_t hal, uint8_t session_id, int value);

/**
 * sme_update_he_frag_supp() - sets the HE fragmentation support
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @he_frag: HE fragmention support value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_frag_supp(mac_handle_t hal, uint8_t session_id,
		uint16_t he_frag);

/**
 * sme_update_he_ldpc_supp() - sets the HE LDPC support
 * @hal: Pointer to HAL
 * @session_id: SME session id
 * @he_ldpc: HE LDPC support value
 *
 * Return: 0 on success else err code
 */
int sme_update_he_ldpc_supp(mac_handle_t hal, uint8_t session_id,
			    uint16_t he_ldpc);
#else
static inline void sme_update_tgt_he_cap(mac_handle_t mac_handle,
					 struct wma_tgt_cfg *cfg,
					 tDot11fIEhe_cap *he_cap_ini)
{}
static inline void sme_update_he_cap_nss(mac_handle_t hal, uint8_t session_id,
		uint8_t nss)
{}
static inline int sme_update_he_mcs(mac_handle_t hal, uint8_t session_id,
				    uint16_t he_mcs)
{
	return 0;
}

static inline void sme_set_he_mu_edca_def_cfg(mac_handle_t hal)
{
}

static inline int sme_update_mu_edca_params(mac_handle_t hal,
					    uint8_t session_id)
{
	return 0;
}
static inline int sme_update_he_trigger_frm_mac_pad(mac_handle_t hal,
						    uint8_t session_id,
						    uint8_t cfg_val)
{
	return 0;
}

static inline int sme_update_he_om_ctrl_supp(mac_handle_t hal,
					     uint8_t session_id,
					     uint8_t cfg_val)
{
	return 0;
}

static inline int sme_send_he_om_ctrl_bw_update(mac_handle_t hal,
						uint8_t session_id,
						uint8_t cfg_val)
{
	return 0;
}

static inline int sme_send_he_om_ctrl_nss_update(mac_handle_t hal,
						 uint8_t session_id,
						 uint8_t cfg_val)
{
	return 0;
}

static inline void sme_reset_he_om_ctrl(mac_handle_t hal)
{
}

static inline void sme_set_usr_cfg_mu_edca(mac_handle_t hal, bool val)
{
}

static inline int sme_update_he_tx_stbc_cap(mac_handle_t hal, uint8_t session_id,
					    int value)
{
	return 0;
}

static inline int sme_update_he_rx_stbc_cap(mac_handle_t hal, uint8_t session_id,
					    int value)
{
	return 0;
}

static inline int sme_update_he_frag_supp(mac_handle_t hal, uint8_t session_id,
		uint16_t he_frag)
{
	return 0;
}

static inline int sme_update_he_ldpc_supp(mac_handle_t hal, uint8_t session_id,
					  uint16_t he_ldpc)
{
	return 0;
}

static inline int sme_update_he_tx_bfee_supp(mac_handle_t hal, uint8_t session_id,
		uint8_t cfg_val)
{
	return 0;
}
static inline int sme_update_he_tx_bfee_nsts(mac_handle_t hal, uint8_t session_id,
					     uint8_t cfg_val)
{
	return 0;
}

static inline void sme_set_he_tx_bf_cbf_rates(uint8_t session_id)
{
}

static inline void sme_config_su_ppdu_queue(uint8_t session_id, bool enable)
{
}
#endif

/**
 * sme_is_sta_key_exchange_in_progress() - checks whether the STA/P2P client
 * session has key exchange in progress
 *
 * @hal: global hal handle
 * @session_id: session id
 *
 * Return: true - if key exchange in progress
 *         false - if not in progress
 */
bool sme_is_sta_key_exchange_in_progress(mac_handle_t hal, uint8_t session_id);

/*
 * sme_validate_channel_list() - Validate the given channel list
 * @hal: handle to global hal context
 * @chan_list: Pointer to the channel list
 * @num_channels: number of channels present in the chan_list
 *
 * Validates the given channel list with base channels in mac context
 *
 * Return: True if all channels in the list are valid, false otherwise
 */
bool sme_validate_channel_list(mac_handle_t hal,
				      uint8_t *chan_list,
				      uint8_t num_channels);
/**
 * sme_set_amsdu() - set amsdu enable/disable based on user cfg
 * @hal: Pointer to HAL
 * @enable: enable or disable
 *
 * Return: None
 */
void sme_set_amsdu(mac_handle_t hal, bool enable);

/**
 * sme_get_mcs_idx() - gets mcs index
 * @max_rate: max rate
 * @rate_flags: rate flags
 * @nss: number of nss
 * @mcs_rate_flags: mcs rate flag
 *
 * Return: return mcs index
 */
uint8_t sme_get_mcs_idx(uint16_t max_rate, uint8_t rate_flags,
			uint8_t *nss, uint8_t *mcs_rate_flags);

#ifdef WLAN_SUPPORT_TWT
/**
 * sme_register_twt_enable_complete_cb() - TWT enable registrar
 * @mac_handle: MAC handle
 * @twt_enable_cb: Function callback to handle enable event
 *
 * Return: QDF Status
 */
QDF_STATUS sme_register_twt_enable_complete_cb(mac_handle_t mac_handle,
					       twt_enable_cb twt_enable_cb);

/**
 * sme_register_twt_disable_complete_cb - TWT disable registrar
 * @mac_handle: MAC handle
 * @twt_disable_cb: Function callback to handle disable event
 *
 * Return: QDF Status
 */
QDF_STATUS sme_register_twt_disable_complete_cb(mac_handle_t mac_handle,
						twt_disable_cb twt_disable_cb);

/**
 * sme_deregister_twt_enable_complete_cb() - TWT enable deregistrar
 * @hal: HAL handle
 *
 * Return: QDF Status
 */
QDF_STATUS sme_deregister_twt_enable_complete_cb(mac_handle_t mac_handle);

/**
 * sme_deregister_twt_disable_complete_cb - TWT disable deregistrar
 * @hal: HAL handle
 *
 * Return: QDF Status
 */
QDF_STATUS sme_deregister_twt_disable_complete_cb(mac_handle_t mac_handle);

#else
static inline
QDF_STATUS sme_register_twt_enable_complete_cb(mac_handle_t mac_handle,
					       twt_enable_cb twt_enable_cb)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_register_twt_disable_complete_cb(mac_handle_t mac_handle,
						twt_disable_cb twt_disable_cb)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_deregister_twt_enable_complete_cb(mac_handle_t mac_handle)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS sme_deregister_twt_disable_complete_cb(mac_handle_t mac_handle)
{
	return QDF_STATUS_SUCCESS;
}
#endif

/**
 * sme_find_session_by_bssid() - checks whether has session
 * with given bssid
 * @hal: global hal handle
 * @bssid: bssid
 * Return: true - if has the session
 *         false - if not has the session
 */
bool sme_find_session_by_bssid(mac_handle_t hal, uint8_t *bssid);

/**
 * sme_get_roam_scan_stats() - Send roam scan stats cmd to wma
 * @hal: handle returned by mac_open
 * @cb: call-back invoked for roam scan stats response
 * @context: context of callback
 * @vdev_id: vdev id
 *
 * Return: QDF_STATUS
 */
QDF_STATUS
sme_get_roam_scan_stats(mac_handle_t hal, roam_scan_stats_cb cb, void *context,
			uint32_t vdev_id);

/**
 * sme_update_score_config() - Update the Scoring Config from MLME
 * @hal: Mac Handle
 * @score_config: Pointer to the scoring config structure to be populated
 *
 * Return: None
 */
void sme_update_score_config(mac_handle_t hal,
			     struct scoring_config *score_config);
#endif /* #if !defined( __SME_API_H ) */
