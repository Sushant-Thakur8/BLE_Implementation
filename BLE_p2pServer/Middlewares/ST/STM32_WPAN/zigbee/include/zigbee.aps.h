/**
 * @file zigbee.aps.h
 * @heading APS Layer
 * @brief APS header file
 * @author Exegin Technologies
 * @copyright Copyright [2009 - 2024] Exegin Technologies Limited. All rights reserved.
 */

#ifndef ZIGBEE_APS_H
# define ZIGBEE_APS_H

/*---------------------------------------------------------------
 * Definitions
 *---------------------------------------------------------------
 */

/* For FlexeLint */
#ifndef CONFIG_ZB_REV
#define CONFIG_ZB_REV 23
#endif

/* APS Constants */
/* Make sure apscMaxDescriptorSize never exceeds 0xff (length field is 1 byte) */
#define ZB_APS_CONST_MAX_DESCRIPTOR_SIZE            64U
#define ZB_APS_CONST_MIN_DUPLICATE_TABLE_SIZE       1U

/* I count 8 bytes as the minimum APS overhead, not 12 (0x0c)  */
#define ZB_APS_CONST_MIN_HEADER_OVERHEAD            8U

/* This is the count of APS relay command overhead includes,
 *   1. APS cmd header (2 bytes): Frame control (1 byte) + APS Counter (1 byte).
 *   2. APS relay payload (11 bytes): APS Command Id (1 byte) + Relay Message overhead (10 bytes).
 */
#define ZB_APS_CONST_RELAY_CMD_OVERHEAD             13U

#define ZB_APS_CONST_SECURITY_OVERHEAD              (5U + ZB_SEC_MIC_LENGTH_5)

/* For embedded application using the zigbee mempool, the maximum size
 * we can allocate is slightly larger than 2000 bytes */
#define ZB_APS_CONST_MAX_FRAG_SIZE                  2000U

/* Maximum APS payload size if no security at all */
#define ZB_APS_CONST_MAX_UNSECURED_PAYLOAD_SIZE     (ZB_NWK_CONST_MAX_PAYLOAD_SIZE /* 108 */ - \
                                                     ZB_APS_CONST_MIN_HEADER_OVERHEAD /* 8 */) /* = 100 */

/* Maximum (unfragmented) APS payload, assuming a NWK secured packet and no many-to-one source routing.
 * Note, if fragmentation is allowed, subtract 2 for the APS extended header, which gives a value of 80 */
#define ZB_APS_CONST_MAX_PAYLOAD_SIZE               (ZB_NWK_CONST_MAX_PAYLOAD_SIZE /* 108 */ - \
                                                     ZB_NWK_CONST_SECURITY_OVERHEAD /* 18 */ - \
                                                     ZB_APS_CONST_MIN_HEADER_OVERHEAD /* 8 */) /* = 82 */

/* Maximum (unfragmented) APS relay command payload, assuming a NWK secured packet
 * without many-to-one source routing. */
#define ZB_APS_CONST_SAFE_NWKSEC_RELAY_PAYLOAD_SIZE (ZB_NWK_CONST_MAX_PAYLOAD_SIZE /* 108 */ - \
                                                     ZB_NWK_CONST_SECURITY_OVERHEAD /* 18 */ - \
                                                     ZB_APS_CONST_RELAY_CMD_OVERHEAD /* 13 */) /* = 77 */

/* Maximum (unfragmented) APS payload, assuming a NWK secured packet
 * with many-to-one source routing (source routing level = 6) */
#define ZB_APS_CONST_SAFE_NWKSEC_PAYLOAD_SIZE       (ZB_NWK_CONST_MAX_PAYLOAD_SIZE /* 108 */ - \
                                                     ZB_NWK_CONST_SECURITY_OVERHEAD /* 18 */ - \
                                                     4U /* source router header */ - \
                                                     /* was using ZB_NWK_CONST_MAX_SOURCE_ROUTE */ \
                                                     (2U * ZB_NWK_CONST_DEFAULT_SOURCE_ROUTE) /* 12 */ - \
                                                     ZB_APS_CONST_MIN_HEADER_OVERHEAD /* 8 */) /* = 66 */

/* Maximum (unfragmented) APS payload, assuming an APS secured packet
 * with many-to-one source routing (source routing level = 6) */
#define ZB_APS_CONST_SAFE_APSSEC_PAYLOAD_SIZE       (ZB_NWK_CONST_MAX_PAYLOAD_SIZE /* 108 */ - \
                                                     ZB_NWK_CONST_SECURITY_OVERHEAD /* 18 */ - \
                                                     4U /* source router header */ - \
                                                     /* was using ZB_NWK_CONST_MAX_SOURCE_ROUTE */ \
                                                     (2U * ZB_NWK_CONST_DEFAULT_SOURCE_ROUTE) /* 12 */ - \
                                                     ZB_APS_CONST_MIN_HEADER_OVERHEAD /* 8 */ - \
                                                     ZB_APS_CONST_SECURITY_OVERHEAD /* 9 */) /* = 57 */

/* "Assuming fragmentation is used there can be 256 such blocks
 * comprising a single maximum sized ASDU."
 * ZB_APS_CONST_MAX_PAYLOAD_SIZE:               20,992 bytes
 * ZB_APS_CONST_SAFE_NWKSEC_PAYLOAD_SIZE:       16,896 bytes
 * ZB_APS_CONST_SAFE_APSSEC_PAYLOAD_SIZE:       14,592 bytes */
#define ZB_APS_CONST_MAX_ASDU_LENGTH                (256U * ZB_APS_CONST_MAX_PAYLOAD_SIZE)

/* apscMaxFrameRetries */
#define ZB_APS_CONST_MAX_FRAME_RETRIES              3U

#define ZB_APS_CONST_MAX_WINDOW_SIZE                8U

/* apscJoinerTLVsUnfragmentedMaxSize */
#define ZB_APS_CONST_JOINER_TLVS_UNFRAG_MAX_SIZE    ZB_JOINER_TLVS_MAX_SIZE

/* A set of feature flags pertaining to the APS Key-Pair security material
 * denoting the peer’s support for specific APS security features. e.g,
 *
 *  1. Bit  0: APS Frame counter synchronisation supported(ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT)
 *  2. Bits 1 - 7: Reserved.
 */
#define ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT       0x01U /* Bit 0 */
#define ZB_APS_SEC_CAPABILITY_RESERVED              0xfeU /* Bits 1 - 7 */

/* Endpoint Definitions */
#define ZB_ENDPOINT_MIN                             0x00U /*   0 */
#define ZB_ENDPOINT_ZDO                             0x00U /*   0 */
#define ZB_ENDPOINT_FINDBIND_MIN                    0x01U /*   1 */
#define ZB_ENDPOINT_FINDBIND_MAX                    0xf0U /* 240 */
#define ZB_ENDPOINT_CBKE_DEFAULT                    ZB_ENDPOINT_FINDBIND_MAX
/* Endpoints 241 to 254 are assigned by the Zigbee Alliance */
#define ZB_ENDPOINT_GREENPOWER                      0xf2U /* 242 */
#define ZB_ENDPOINT_MAX                             0xfeU /* 254 */
#define ZB_ENDPOINT_BCAST                           0xffU /* 255 */

/* Internal endpoints used for special stack functions */
#define ZB_ENDPOINT_INTERNAL                        0x0100U
#define ZB_ENDPOINT_INTERPAN                        (ZB_ENDPOINT_INTERNAL + 0U)
#define ZB_ENDPOINT_GROUP                           (ZB_ENDPOINT_INTERNAL + 1U)

/* Global Commissioning EPID (See ZCL 7 Spec section 13.2.4.1 Global Commissioning EPID)
 * 00-50-C2-77-10-00-00-00 */
#define ZB_EPID_GLOBAL_COMMISSIONING                0x0050c27710000000ULL

/** APS Command Frame IDs */
enum ZbApsCmdIdT {
    /* ZB_APS_CMD_SKKE_1 = 0x01, deprecated as of R21 */
    /* ZB_APS_CMD_SKKE_2 = 0x02, deprecated as of R21 */
    /* ZB_APS_CMD_SKKE_3 = 0x03, deprecated as of R21 */
    /* ZB_APS_CMD_SKKE_4 = 0x04, deprecated as of R21 */
    ZB_APS_CMD_TRANSPORT_KEY = 0x05, /**< Transport Key */
    ZB_APS_CMD_UPDATE_DEVICE = 0x06, /**< Update Device */
    ZB_APS_CMD_REMOVE_DEVICE = 0x07, /**< Remove Device */
    ZB_APS_CMD_REQUEST_KEY = 0x08, /**< Request Key */
    ZB_APS_CMD_SWITCH_KEY = 0x09, /**< Switch Key */
    /* ZB_APS_CMD_EA_INIT_CHLNG = 0x0a, deprecated as of R21 */
    /* ZB_APS_CMD_EA_RESP_CHLNG = 0x0b, deprecated as of R21 */
    /* ZB_APS_CMD_EA_INIT_DATA = 0x0c, deprecated as of R21 */
    /* ZB_APS_CMD_EA_RESP_DATA = 0x0d, deprecated as of R21 */
    ZB_APS_CMD_TUNNEL = 0x0e, /**< Tunnel */
    ZB_APS_CMD_VERIFY_KEY = 0x0f, /**< Verify Key */
    ZB_APS_CMD_CONFIRM_KEY = 0x10, /**< Confirm Key */
#if (CONFIG_ZB_REV >= 23)
    ZB_APS_CMD_RELAY_DOWNSTREAM = 0x11, /**< Relay Downstream */
    ZB_APS_CMD_RELAY_UPSTREAM = 0x12 /**< Relay Upstream */
#endif
};

/*---------------------------------------------------------------
 * APSDE
 *---------------------------------------------------------------
 */
/** APSDE and Interpan Addressing Modes */
enum ZbApsAddrModeT {
    ZB_APSDE_ADDRMODE_NOTPRESENT = 0, /**< DstAddress and DstEndpoint not present */
    ZB_APSDE_ADDRMODE_GROUP, /**< 16-bit group address for DstAddress; DstEndpoint not present */
    ZB_APSDE_ADDRMODE_SHORT, /**< 16-bit address for DstAddress and DstEndpoint present */
    ZB_APSDE_ADDRMODE_EXT, /**< 64-bit extended address for DstAddress and DstEndpoint present */
    ZB_APSDE_ADDRMODE_IPGROUP /**< InterPAN */
};

#if (CONFIG_ZB_REV >= 23)
/** APS relay information data structure */
struct ZbApsRelayInfoT {
    bool relayMsg; /**< If true, APS packet shall be relayed. */
    uint64_t relayExtAddr;
    /**< Destination EUI64 for downstream, source EUI64 in case of upstream relay command. */
    uint64_t relayDstAddr;
    /**< APS relay command destination address. Address of intermediate router (multi-hop) or
     * unauthorized joiner (single-hop) for downstream. Address of intermediate router (multi-hop)
     * or TC (single-hop) for upstream. */
};

#ifdef CONFIG_ZB_DIAGNOSTICS
struct ZbApsStatTableT {
    uint16_t aps_tx_ucast_success;
    /**< The total number of successful APS unicast messages. APS messages without APS Acks SHALL be
     * considered successfully sent when the MAC ACK from the next hop is received.
     * Same as, ZCL_DIAG_SVR_ATTR_APS_TX_UCAST_SUCCESS. */
    uint16_t aps_tx_ucast_retry;
    /**< The total number of APS retries that have been recorded.
     * Same as, ZCL_DIAG_SVR_ATTR_APS_TX_UCAST_RETRY. */
    uint16_t aps_tx_ucast_fail;
    /**< The total number of APS unicast messages that are
     * considered failed. APS unicast messages without APS Acks shall be considered failed when
     * the MAC ACK from the next hop is not received after all MAC and NWK layer retries. APS
     * unicast messages with APS Acks shall be considered failed when the APS ACK is not received
     * for the message after all APS layer retries.
     * Same as, ZCL_DIAG_SVR_ATTR_APS_TX_UCAST_FAIL. */
    uint16_t nwk_fc_failure;
    /**< The total number of received messages dropped due to a frame counter failure at the
     * network security layer.
     * Same as, ZCL_DIAG_SVR_ATTR_NWK_FC_FAILURE. */
    uint16_t aps_fc_failure;
    /**< The total number of received messages dropped due to a frame counter failure at the
     * APS security layer.
     * Same as, ZCL_DIAG_SVR_ATTR_APS_FC_FAILURE. */
    uint16_t aps_unauthorized_key;
    /**< The total number of received messages dropped at the APS security layer because the key
     * is not authorized.
     * Same as, ZCL_DIAG_SVR_ATTR_APS_UNAUTH_KEY. */
    uint16_t nwk_decrypt_failures;
    /**< This is the total number of decryption failures at the NWK security layer.
     * Same as, ZCL_DIAG_SVR_ATTR_NWK_DECRYPT_FAILS. */
    uint16_t aps_decrypt_failures;
    /**< This is the total number of decryption failures at the APS security layer.
     * Same as, ZCL_DIAG_SVR_ATTR_APS_DECRYPT_FAILS. */
#if 0 /* EXEGIN - Not supported */
    uint16_t packet_buf_allocate_failures;
    /**< This is the total number of failures by the stack due to a lack of memory buffers.
     * Same as, ZCL_DIAG_SVR_ATTR_PACKET_BUF_ALLOC_FAILS. */
#endif
    uint16_t phy_to_mac_queue_lim_reached;
    /**< This is the total number of failures by the stack to transfer a message from the PHY
     * layer to the MAC layer.
     * Same as, ZCL_DIAG_SVR_ATTR_PHY_MAC_QUEUE_LIM. */
    uint16_t packet_validate_drop_count;
    /**< This is the total number of packets dropped due to invalid formatting.
     * Same as, ZCL_DIAG_SVR_ATTR_PACKET_VAL_DROP_COUNT. */
    uint32_t mac_tx_ucast;
    /**< The total number of successful mac unicast transmissions.
     * Same as, ZCL_DIAG_SVR_ATTR_MAC_TX_UCAST. */
    uint16_t mac_tx_ucast_retry;
    /**< The total number of retries at the MAC layer for unicast messages. This includes retries
     * within an MCPS transaction and not just the final MCPS result.
     * Same as, ZCL_DIAG_SVR_ATTR_MAC_TX_UCAST_RETRY. */
    uint16_t mac_tx_ucast_fail;
    /**< The total number of MAC unicast failures. This includes failures within an MCPS transaction
     * and not just the final MCPS result.
     * Same as, ZCL_DIAG_SVR_ATTR_MAC_TX_UCAST_FAIL.*/
};
#endif

#endif

/** APS address information data structure */
struct ZbApsAddrT {
    enum ZbApsAddrModeT mode; /**< Address mode (e.g. short, group, extended) */

    uint16_t endpoint;
    /**< Destination endpoint. If set to ZB_ENDPOINT_INTERPAN, then packet is
     * sent as an InterPAN packet */

    uint16_t panId;
    /**< Destination PAN Id. This is for InterPAN packets, when the
     * endpoint == ZB_ENDPOINT_INTERPAN */

    uint16_t nwkAddr;
    /**< Destination network address when mode == ZB_APSDE_ADDRMODE_SHORT,
     * ZB_APSDE_ADDRMODE_GROUP or ZB_APSDE_ADDRMODE_IPGROUP */

    uint64_t extAddr; /**< Destination extended address when mode == ZB_APSDE_ADDRMODE_EXT */

#if (CONFIG_ZB_REV >= 23)
    uint16_t nwkBcastAddr;
    /**< nwkBcastAddr - This indicates the broadcast address used for groupcast messages
     * (DstAddrMode = 0x01). Valid range: 0xFFFC - 0xFFFF */
#endif
};

/** Helper struct to send using binding */
extern const struct ZbApsAddrT *ZbApsAddrBinding; /**< Pointer to APS address binding */

/* Helpter to configure the loopback destination */
static inline void
zb_aps_dst_loopback(struct ZigBeeT *zb, struct ZbApsAddrT *dst, uint8_t endpoint)
{
    dst->mode = ZB_APSDE_ADDRMODE_EXT;
    dst->extAddr = ZbExtendedAddress(zb);
    dst->endpoint = endpoint;
}

/*
 * @name APSDE.DATA.request (TxOptions)
 * APSDE Transmit Options
 */
/*@{*/
/* TxOptions (Security enabled transmission). If set, use payload security */
#define ZB_APSDE_DATAREQ_TXOPTIONS_SECURITY         0x0001U
/* TxOptions (Use NWK key). If set and ZB_APSDE_DATAREQ_TXOPTIONS_SECURITY is set,
 * use NWK security only.
 * If not set and ZB_APSDE_DATAREQ_TXOPTIONS_SECURITY is set, use APS and NWK security. */
/* Developer note: this flag used to mean that the APS payload would be separately
 * encrypted with the NWK key. However, since all NWK payloads are encrypted, this
 * process is a waste of time. */
#define ZB_APSDE_DATAREQ_TXOPTIONS_NWKKEY           0x0002U
/* TxOptions (Acknowledged transmission) */
#define ZB_APSDE_DATAREQ_TXOPTIONS_ACK              0x0004U
/* TxOptions (Fragmentation permitted) */
#define ZB_APSDE_DATAREQ_TXOPTIONS_FRAG             0x0008U
/* TxOptions (Include extended nonce in APS security frame)
 * Note, this will be ignored if ZB_APSDE_DATAREQ_TXOPTIONS_NWKKEY is set. */
#define ZB_APSDE_DATAREQ_TXOPTIONS_NONCE            0x0010U
/* TxOptions (ASDU is an array of struct ZbApsBufT structures)
 * [Exegin Custom] When the VECTOR option is set, the ASDU points instead
 * to an array of struct ZbApsBufT structures that point to fragments of the
 * message to assemble into one ASDU, and the ASDU length is the number of
 * buffer structures. This is used for scatter-gather mode API calls to
 * reduce heap activity. */
#define ZB_APSDE_DATAREQ_TXOPTIONS_VECTOR           0x0100U
/* TxOptions (UseAlias)
 * [Exegin Custom] If set, request alias usage by NWK layer for the current frame.
 * This is used in place of the separate useAlias parameter defined in the spec. */
#define ZB_APSDE_DATAREQ_TXOPTIONS_ALIAS            0x0200U
/*@}*/

/**
 * Buffer descriptor for vectored/scatter-gather API.
 * Used when ZB_APSDE_DATAREQ_TXOPTIONS_VECTOR TX Options bit is set.
 */
struct ZbApsBufT {
    const uint8_t *data; /**< Data */
    unsigned int len; /**< Length */
};

/**
 * APSDE-DATA.request data structure
 */
struct ZbApsdeDataReqT {
    struct ZbApsAddrT dst;
    /**< DstAddress - DstEndpoint Destination address information,
     * including address mode, address and endpoint */
    uint16_t profileId; /**< ProfileId - ProfileId The profile for which this frame is intended */
    uint16_t clusterId; /**< ClusterId - The object for which this frame is intended */
    uint16_t srcEndpt; /**< SrcEndpoint - The source endpoint */
    const void *asdu; /**< ASDU - The set of octets comprising the ASDU to be transferred */
    uint16_t asduLength; /**< ASDULength - The number of octets comprising the ASDU */
    uint32_t asduHandle; /**< An optional handle ID to use in order to match up with the APSDE-DATA.confirm */
    uint16_t txOptions; /**< TxOptions -Transmit options bitmask (e.g. ZB_APSDE_DATAREQ_TXOPTIONS_SECURITY) */
    bool discoverRoute;
    /**< discoverRoute - If you perform route discovery separately using ZbNlmeRouteDiscReq(),
     * then you can set discoverRoute to zero, decreasing the length of time
     * an APS data request may take if there is a problem sending the packet
     * to the target */
    uint8_t radius; /**< Radius - Network radius. If 0, default value is used */
    uint16_t aliasAddr; /**< AliasSrcAddr - Requires ZB_APSDE_DATAREQ_TXOPTIONS_ALIAS to be enabled */
    uint8_t aliasSeqnum; /**< AliasSeqNumb - Requires ZB_APSDE_DATAREQ_TXOPTIONS_ALIAS to be enabled */
#if (CONFIG_ZB_REV >= 23)
    struct ZbApsRelayInfoT relayInfo; /**< Contains required information to relay the APS packet. */
#endif
};

/**
 * APSDE-DATA.confirm data structure
 */
struct ZbApsdeDataConfT {
    struct ZbApsAddrT dst; /**< DstAddrMode - Destination address information of the APSDE-DATA.request */
    uint8_t srcEndpt; /**< SrcEndpoint - Source endpoint of the APSDE-DATA.request */
    uint32_t asduHandle; /**< The optional handle ID from the APSDE-DATA.request */
    enum ZbStatusCodeT status; /**< Zigbee Status Code */
};

/**
 * APSDE-DATA.indication data structure.
 * These messages are received from the stack after setting up the proper message
 * filter using ZbApsFilterEndpointAdd or ZbApsFilterClusterAdd.
 */
struct ZbApsdeDataIndT {
    struct ZbApsAddrT dst; /**< DstAddress - Destination address information of the incoming APS message */
    struct ZbApsAddrT src; /**< SrcAddress - Source address information of the incoming APS message */
    uint16_t profileId; /**< ProfileId - The profile for which this frame is intended */
    uint16_t clusterId; /**< ClusterId - The object for which this frame is intended */
    uint8_t *asdu; /**< asdu - The set of octets comprising the ASDU that was received */
    uint16_t asduLength; /**< asduLength - The number of octets comprising the ASDU */

    enum ZbStatusCodeT securityStatus;
    /**< SecurityStatus - The security level used to encrypt the incoming frame. One of:
     * ZB_APS_STATUS_UNSECURED (no decryption necessary),
     * ZB_APS_STATUS_SECURED_NWK_KEY (decrypted with the Network Key),
     * ZB_APS_STATUS_SECURED_LINK_KEY, (decrypted with a Link Key) */

    uint8_t linkQuality;
    /**< LinkQuality - The incoming Link Quality value, or set to 0 if not supported by
     * lower layers */

    int8_t rssi;
    /**< The incoming RSSI value, or set to PHY_RSSI_INVALID (-128) if not
     * supported by lower layers */

    uint16_t linkAddr; /**< Exegin Addon for Inter-PAN portability */

#if (CONFIG_ZB_REV >= 23)
    struct ZbApsRelayInfoT relayInfo; /**< Contains required information to relay the APS packet. */
#endif
};

/**
 * Send an APSDE-DATA.request.
 * @param zb Zigbee instance
 * @param req APSDE-DATA.request data structure
 * @param callback Application callback to call for APSDE-DATA.confirm. May be set to NULL
 * @param arg Application callback argument, which will be passed to callback()
 * @return ZCL_STATUS_SUCCESS If the packet was queued, or other ZclStatusCodeT value on error
 */
enum ZbStatusCodeT ZB_WARN_UNUSED ZbApsdeDataReqCallback(struct ZigBeeT *zb, struct ZbApsdeDataReqT *req,
    void (*callback)(struct ZbApsdeDataConfT *conf, void *arg), void *arg);

/*---------------------------------------------------------------
 * APSME
 *---------------------------------------------------------------
 */
/** APS IB Attributes */
enum ZbApsmeIbAttrIdT {
    /* ZB_APS_IB_ID_ADDRESS_MAP = 0xc0, Removed in ZigBee 2007 */
    ZB_APS_IB_ID_BINDING_TABLE = 0xc1,
    /**< apsBindingTable (type: struct ZbApsmeBindT, reset: yes, persist: yes) */
    ZB_APS_IB_ID_DESIGNATED_COORD = 0xc2,
    /**< apsDesignatedCoordinator (type: uint8_t, reset: yes, persist: yes) */
    ZB_APS_IB_ID_CHANNEL_MASK = 0xc3,
    /**< apsChannelMaskList. Converted to a list in R22
     * (type: struct ZbChannelListT, reset: yes, persist: yes) */
    ZB_APS_IB_ID_USE_EPID = 0xc4,
    /**< apsUseExtendedPANID (type: uint64_t, reset: yes, persist: no) */
    ZB_APS_IB_ID_GROUP_TABLE = 0xc5,
    /**< apsGroupTable (type: struct ZbApsmeGroupT, reset: yes, persist: yes) */
    /* Removed -- 0xc6 (ZB_APS_IB_ID_NONMEMBER_RADIUS) */
    /* Removed -- 0xc7 (ZB_APS_IB_ID_PERMISSIONS_CONFIG) */
    ZB_APS_IB_ID_USE_INSECURE_JOIN = 0xc8,
    /**< apsUseInsecureJoin (type: uint8_t, reset: yes, persist: yes) */
    ZB_APS_IB_ID_INTERFRAME_DELAY = 0xc9,
    /**< apsInterframeDelay (type: uint8_t, reset: no, persist: no) */
    ZB_APS_IB_ID_LAST_CHANNEL_ENERGY = 0xca,
    /**< apsLastChannelEnergy (type: uint8_t, reset: yes, persist: no) */
    ZB_APS_IB_ID_LAST_CHANNEL_FAILRATE = 0xcb,
    /**< apsLastChannelFailureRate (type: uint8_t, reset: yes, persist: no) */
    ZB_APS_IB_ID_CHANNEL_TIMER = 0xcc,
    /**< apsChannelTimer (type: ZbUptimeT, reset: yes, persist: no) */
    ZB_APS_IB_ID_MAX_WINDOW_SIZE = 0xcd,
    /**< apsMaxWindow Size (type: uint8_t, reset: no, persist: no) */
    /* Removed -- 0xce (ZB_APS_IB_ID_PARENT_ANNOUNCE_TIMER) */
    ZB_APS_IB_ID_ZDO_RESTRICTED_MODE = 0xcf,
    /**< R23 (type: uint8_t, reset: yes, persist: no) */
#if (CONFIG_ZB_REV >= 23)
    ZB_APS_IB_ID_STAT_TABLE = 0xd0,
    /**< R23 (type: uint8_t, reset: no, persist: no) */
#endif

    /*** Security attributes ***/
    ZB_APS_IB_ID_DEVICE_KEY_PAIR_SET = 0xaa,
    /**< apsDeviceKeyPairSet (type: struct ZbApsmeKeyPairT, reset: yes, persist: yes) */
    ZB_APS_IB_ID_TRUST_CENTER_ADDRESS = 0xab,
    /**< apsTrustCenterAddress (type: uint64_t, reset: yes, persist: yes) */
    ZB_APS_IB_ID_SECURITY_TIMEOUT_PERIOD = 0xac,
    /**< apsSecurityTimeOutPeriod, milliseconds
     * (type: uint16_t, reset: no, persist: no) */

    ZB_APS_IB_ID_TRUST_CENTER_POLICY = 0xad,
    /**< trustCenterPolicies. Trust center policy table bitmask
     * Represents the following AIBs:
     * allowJoins = 0xad,
     * requireInstallCodesOrPresetPassphrase = 0xaf,
     * updateTrustCenterLinkKeysRequired = 0xb3,
     * allowRejoinsWithWellKnownKey = 0xb6,
     * allowTrustCenterLinkKeyRequests = 0xb7,
     * networkKeyUpdateMethod = 0xba,
     * allowApplicationKeyRequests = 0xbb,
     * allowRemoteTcPolicyChange = 0xbd,
     * allowVirtualDevices = 0xbe
     * (type: uint32_t, enum ZbApsmePolicyT, reset: no, persist: no) */

    /* Reserved 0xae */
    ZB_APS_IB_ID_SUPPORTED_KEY_NEGO_METHODS = 0xaf,
    /**< apsSupportedKeyNegotiationMethods (R23)
     * (type: uint8_t, reset: no, persist: no) */
    /* Removed -- 0xb0 (type: uint8_t) apsChallengePeriodTimeoutSeconds (R23) */
    /* Removed -- 0xb1 (type: uint8_t) apsChallengePeriodRemainingSeconds (R23) */
    ZB_APS_IB_ID_CHALLENGE_VALUE = 0xb2,
    /**< apsChallengeValue (R23) (type: uint64_t, reset: no, persist: no) */
    ZB_APS_IB_ID_CHALLENGE_TARGET_EUI64 = 0xb3,
    /**< apsChallengeTargetEui64 (R23) (type: uint64_t, reset: no, persist: no) */
    ZB_APS_IB_ID_DEVICE_INTERVIEW_TIMEOUT_PERIOD = 0xb4,
    /**< apsDeviceInterviewTimeoutPeriod (R23), seconds
     * (type: uint8_t, reset: no, persist: no).
     * NOTE: On the Coordinator, the ZSDK stack uses apsSecurityTimeOutPeriod
     * (ZB_APS_IB_ID_SECURITY_TIMEOUT_PERIOD) instead of this APS IB
     * for device interview timeout. The joining device undergoing Device Interview
     * will use this APS IB to refresh its Interview Timeout upon each received
     * APS Downstream Relay */

    /* Exegin extensions (0x0500 to 0x05ff reserved for custom AIBs) */
    ZB_APS_IB_ID_SCAN_COUNT = 0x0500,
    /**< ZDO join parameter. (type: uint8_t, reset: no, persist: yes) */
    ZB_APS_IB_ID_LEAVE_REMOVE_CHILDREN = 0x0501,
    /**< ZDO leave parameter (type: uint8_t, reset: yes, persist: yes) */
    ZB_APS_IB_ID_PRECONFIGURED_LINK_KEY = 0x0502,
    /**< apsPreconfiguredLinkKey. Preconfigured Trust Center Link Key.
     * (type: array of uint8_t of size ZB_SEC_KEYSIZE, reset: yes, persist: yes) */
    ZB_APS_IB_ID_DISTRIBUTED_GLOBAL_KEY = 0x0503,
    /**< apsDistributedGlobalKey (type: array of uint8_t of size ZB_SEC_KEYSIZE,
     * reset: yes, persist: yes) */
    ZB_APS_IB_ID_KEY_UPDATE_PERIOD = 0x0504,
    /**< KeyUpdatePeriod. From the trust center policy table.
     * (type: uint32_t, reset: yes, persist: no) */
    ZB_APS_IB_ID_MANUFACTURER_ID = 0x0505,
    /**< Manufacturer ID (type: uint16_t, reset: no, persist: no) */
    ZB_APS_IB_ID_SEND_PKT_COOLDOWN = 0x0506,
    /**< Send packet cooldown in milliseconds
     * (type: uint16_t, reset: no, persist: no) */
    ZB_APS_IB_ID_BIND_ADDR_RESOLVE_PERIOD = 0x0507,
    /**< Bind address resolve period in seconds, 0 = disabled
     * (type: uint16_t, reset: no, persist: no) */
    ZB_APS_IB_ID_FRAGMENTATION_THRESH = 0x0508,
    /**< apsFragmentationThresh. Fragmentation Threshold
     * (type: uint8_t, reset: no, persist: no) */
    ZB_APS_IB_ID_SUPPORTED_PSK_SECRETS = 0x0509,
    /**< apsSupportedPreSharedSecrets (R23)
     * (type: uint8_t, reset: no, persist: no) */
    ZB_APS_IB_ID_MAX_IN_QUEUED_PACKETS = 0x050a,
    /**< Maximum number of incoming packets the APS is allowed to queue.
     * Default is 0, which means there's no limit, other than available memory.
     * A SED may want to set this value between 2 to 4 so it doesn't get overwhelmed with
     * requests during its wake cycle. (type: uint16_t, reset: no, persist: no) */
    ZB_APS_IB_ID_SUSPEND_ZCL_APSDE_DATA_REQ = 0x050b,
    /**< apsSuspendZclApsdeDataReq. When set to true transmission of ASPDE-DATA.requests
     * from ZCL is suspended and will return error right away.
     * (type: uint8_t, reset: yes, persist: yes) */

    ZB_APS_IB_ID_MAX = 0x05ff
};

/** APSME-BIND.request */
struct ZbApsmeBindReqT {
    uint64_t srcExtAddr; /**< SrcAddr */
    uint8_t srcEndpt; /**< SrcEndpoint */
    uint16_t clusterId; /**< ClusterId */
    /* dst.panId not used, dst.nwkAddr is only for the group address,
     * and dst.endpoint only used if mode == ZB_APSDE_ADDRMODE_EXT */
    struct ZbApsAddrT dst; /**< APS address information data structure */
};

/** APSME-BIND.confirm */
struct ZbApsmeBindConfT {
    enum ZbStatusCodeT status; /**< Status */
    uint64_t srcExtAddr; /**< SrcAddr */
    uint8_t srcEndpt; /**< SrcEndpoint */
    uint16_t clusterId; /**< ClusterId */
    /* dst.panId not used, dst.nwkAddr is only for the group address,
     * and dst.endpoint only used if mode == ZB_APSDE_ADDRMODE_EXT */
    struct ZbApsAddrT dst; /**< APS address information data structure */
};

/** APSME-UNBIND.request */
struct ZbApsmeUnbindReqT {
    uint64_t srcExtAddr; /**< SrcAddr */
    uint8_t srcEndpt; /**< SrcEndpoint */
    uint16_t clusterId; /**< ClusterId */
    /* dst.panId not used, dst.nwkAddr is only for the group address,
     * and dst.endpoint only used if mode == ZB_APSDE_ADDRMODE_EXT */
    struct ZbApsAddrT dst; /**< APS address information data structure */
};

/** APSME-UNBIND.confirm */
struct ZbApsmeUnbindConfT {
    enum ZbStatusCodeT status; /**< Status */
    uint64_t srcExtAddr; /**< SrcAddr */
    uint8_t srcEndpt; /**< SrcEndpoint */
    uint16_t clusterId; /**< ClusterId */
    /* dst.panId not used, dst.nwkAddr is only for the group address,
     * and dst.endpoint only used if mode == ZB_APSDE_ADDRMODE_EXT */
    struct ZbApsAddrT dst; /**< APS address information data structure */
};

/** APSME-ADD-GROUP.request */
struct ZbApsmeAddGroupReqT {
    uint16_t groupAddr; /**< GroupAddress */
    uint8_t endpt; /**< Endpoint */
};

/** APSME-ADD-GROUP.confirm */
struct ZbApsmeAddGroupConfT {
    enum ZbStatusCodeT status; /**< Status */
    uint16_t groupAddr; /**< GroupAddress */
    uint8_t endpt; /**< Endpoint */
};

/** APSME-REMOVE-GROUP.request */
struct ZbApsmeRemoveGroupReqT {
    uint16_t groupAddr; /**< GroupAddress */
    uint8_t endpt; /**< Endpoint */
};

/** APSME-REMOVE-GROUP.confirm */
struct ZbApsmeRemoveGroupConfT {
    enum ZbStatusCodeT status; /**< Status */
    uint16_t groupAddr; /**< GroupAddress */
    uint8_t endpt; /**< Endpoint */
};

/** APSME-REMOVE-ALL-GROUPS.request */
struct ZbApsmeRemoveAllGroupsReqT {
    uint8_t endpt; /**< Endpoint */
};

/** APSME-REMOVE-ALL-GROUPS.confirm */
struct ZbApsmeRemoveAllGroupsConfT {
    enum ZbStatusCodeT status; /**< Status */
    uint8_t endpt; /**< Endpoint */
};

/** APSME-ADD-ENDPOINT.request - Exegin Custom */
struct ZbApsmeAddEndpointReqT {
    /* Application Information */
    uint8_t endpoint; /**< Endpoint */
    uint16_t profileId; /**< Profile Id */
    uint16_t deviceId; /**< Device Id */
    uint8_t version; /**< Version */
    uint8_t inputClusterCount; /**< Supported Server Clusters */
    const uint16_t *inputClusterList; /**< Pointer to the input cluster list */
    uint8_t outputClusterCount; /* Supported Client Clusters */
    const uint16_t *outputClusterList; /**< Pointer to the output cluster list */
    uint16_t bdbCommissioningGroupID; /**< e.g. DEFAULT_EP_BDB_COMMISSION_GRP_ID; */
};

/** APSME-ADD-ENDPOINT.confirm - Exegin Custom */
struct ZbApsmeAddEndpointConfT {
    enum ZbStatusCodeT status; /**< Status */
};

/** APSME-REMOVE-ENDPOINT.request - Exegin Custom */
struct ZbApsmeRemoveEndpointReqT {
    uint8_t endpoint; /**< Endpoint */
};

/** APSME-REMOVE-ENDPOINT.confirm - Exegin Custom */
struct ZbApsmeRemoveEndpointConfT {
    enum ZbStatusCodeT status; /**< Status */
};

/** APS Binding Table entry */
struct ZbApsmeBindT {
    /* Source */
    uint64_t srcExtAddr; /**< SrcAddr - if zero, entry is invalid */
    uint8_t srcEndpt; /**< SrcEndpoint */
    /* Cluster */
    uint16_t clusterId; /**< ClusterId */
    /* Destination */
    /* dst.panId not used, dst.nwkAddr is only for the group address,
     * and dst.endpoint only used if mode == ZB_APSDE_ADDRMODE_EXT */
    struct ZbApsAddrT dst; /**< APS address information data structure */
};

/** APS Group ID Table entry */
struct ZbApsmeGroupT {
    uint16_t groupAddr; /**< GroupAddress */
    uint8_t endpoint; /**< Endpoint */
};

/**
 * Add an entry to the stack's binding table.
 * The size of the binding table is determined in the tableSizes parameter to ZbInit().
 * The binding table is maintained by the stack.
 * @param zb Zigbee stack instance
 * @param bindReqPtr APSME-BIND.request
 * @param bindConfPtr
 * @param APSME-BIND.confirm
 * @return Returns void
 */
void ZbApsmeBindReq(struct ZigBeeT *zb, struct ZbApsmeBindReqT *bindReqPtr, struct ZbApsmeBindConfT *bindConfPtr);

/**
 * Remove an entry from the binding table.
 * @param zb Zigbee stack instance
 * @param unbindReqPtr APSME-UNBIND.request
 * @param unbindConfPtr APSME-UNBIND.confirm
 * @return Returns void
 */
void ZbApsmeUnbindReq(struct ZigBeeT *zb, struct ZbApsmeUnbindReqT *unbindReqPtr, struct ZbApsmeUnbindConfT *unbindConfPtr);

/**
 * Remove all entries from the binding table.
 * @param zb Zigbee stack instance
 * @return Returns void
 */
void ZbApsUnbindAllReq(struct ZigBeeT *zb);

/**
 * Returns true if there's a binding entry in the Binding Table that matches the
 * local device as the source address, and a matching source endpoint and cluster Id.
 * @param zb Zigbee stack instance
 * @param endpoint Source endpoint
 * @param clusterId Cluster Id
 * @return Returns true if binding exists, false otherwise.
 */
bool ZbApsBindSrcExists(struct ZigBeeT *zb, uint8_t endpoint, uint16_t clusterId);

/**
 * Add an entry to the group table.
 * @param zb Zigbee stack instance
 * @param r APSME-ADD-GROUP.request
 * @param c APSME-ADD-GROUP.confirm
 * @return Returns void
 */
void ZbApsmeAddGroupReq(struct ZigBeeT *zb, struct ZbApsmeAddGroupReqT *r, struct ZbApsmeAddGroupConfT *c);

/**
 * Remove an entry from the group table
 * @param zb Zigbee stack instance
 * @param r APSME-REMOVE-GROUP.request
 * @param c APSME-REMOVE-GROUP.confirm
 * @return Returns void
 */
void ZbApsmeRemoveGroupReq(struct ZigBeeT *zb, struct ZbApsmeRemoveGroupReqT *r, struct ZbApsmeRemoveGroupConfT *c);

/**
 * Remove all entries from the group table.
 * @param zb Zigbee stack instance
 * @param r APSME-REMOVE-ALL-GROUPS.request
 * @param c APSME-REMOVE-ALL-GROUPS.confirm
 * @return Returns void
 */
void ZbApsmeRemoveAllGroupsReq(struct ZigBeeT *zb, struct ZbApsmeRemoveAllGroupsReqT *r, struct ZbApsmeRemoveAllGroupsConfT *c);

/**
 * Retrieve the number of free entries in the group table.
 * @param zb Zigbee stack instance
 * @return Returns number of free entries in the group table
 */
uint8_t ZbApsGroupsGetCapacity(struct ZigBeeT *zb);

/**
 * Retrieve all group addresses on this endpoint.
 * @param zb Zigbee stack instance
 * @param endpoint endpoint
 * @param group_list (OUT) list of groups on this endpoint
 * @param max_len Maximum number of groups to be returned
 * @return Returns number of group addresses
 */
uint8_t ZbApsGroupsGetMembership(struct ZigBeeT *zb, uint8_t endpoint, uint16_t *group_list,
    uint8_t max_len);

/**
 * Register an endpoint with the ZigBee stack.
 * Typically called during initialization.
 * Should be safe to call from an init function.
 * @param zb Zigbee stack instance
 * @param r APSME-ADD-ENDPOINT.request
 * @param c APSME-ADD-ENDPOINT.confirm
 * @return Returns void
 */
void ZbApsmeAddEndpoint(struct ZigBeeT *zb, struct ZbApsmeAddEndpointReqT *r, struct ZbApsmeAddEndpointConfT *c);

/**
 * Unregister and remove an endpoint from the APS endpoint table.
 * Typically called when terminating an application.
 * @param zb Zigbee stack instance
 * @param r APSME-REMOVE-ENDPOINT.request
 * @param c APSME-REMOVE-ENDPOINT.confirm
 * @return Returns void
 */
void ZbApsmeRemoveEndpoint(struct ZigBeeT *zb, struct ZbApsmeRemoveEndpointReqT *r, struct ZbApsmeRemoveEndpointConfT *c);

/**
 * Add a cluster ID to the input cluster list of an existing endpoint.
 * @param zb Zigbee stack instance
 * @param endpoint endpoint
 * @param cluster_id ID of cluster to be added
 * @param is_input true if input cluster, false if output cluster
 * @return Returns true on success, false otherwise
 */
bool ZbApsmeEndpointClusterListAppend(struct ZigBeeT *zb, uint8_t endpoint,
    uint16_t cluster_id, bool is_input);

/**
 * Remove a cluster from an endpoint’s cluster list.
 * @param zb Zigbee stack instance
 * @param endpoint endpoint
 * @param cluster_id ID of cluster to be removed
 * @param is_input true if input cluster, false if output cluster
 * @return Returns true on success, false otherwise
 */
bool ZbApsmeEndpointClusterListRemove(struct ZigBeeT *zb, uint8_t endpoint,
    uint16_t cluster_id, bool is_input);

/**
 * Determine if an endpoint currently exists.
 * @param zb Zigbee stack instance
 * @param endpoint endpoint
 * @return Returns true if endpoint is found, false otherwise
 */
bool ZbApsEndpointExists(struct ZigBeeT *zb, uint8_t endpoint);
/* Get the Profile ID for this endpoint */

/**
 * Retrieve the profile ID of an endpoint.
 * @param zb Zigbee stack instance
 * @param endpoint endpoint
 * @return Returns profile ID, or ZCL_PROFILE_WILDCARD (0xffff) on error
 */
uint16_t ZbApsEndpointProfile(struct ZigBeeT *zb, uint8_t endpoint);

/*---------------------------------------------------------------
 * APSME - Security
 *---------------------------------------------------------------
 */
/** Device status values for APSME-UPDATE-DEVICE.request and indication */
enum ZbApsmeDeviceStatusT {
    ZB_APSME_DEV_STD_SECURE_REJOIN = 0x00U, /**< Standard device secured rejoin */
    ZB_APSME_DEV_STD_INSECURE_JOIN = 0x01U, /**< Standard device unsecured join */
    ZB_APSME_DEV_LEFT = 0x02U, /**< Device left */
    ZB_APSME_DEV_STD_INSECURE_REJOIN = 0x03U /**< Standard device trust center rejoin */
        /* 0x04 - 0xff reserved */
};

/*---------------------------------------------------------------
 * Key attributes set in the device key pair set (bitmask)
 * Verified keys are the default.
 * Warning, the bitmask used here does not match the ZigBee Spec
 * (R21: Table 4.29) */

/* Unique Link Key (e.g. Install Code Generated Key) */
#define ZB_APSME_KEY_ATTR_VERIFIED          0x00U

/* Shared key (value stored in apsPreconfiguredLinkKey) */
/* Global Link Key */
#define ZB_APSME_KEY_ATTR_SHARED            0x01U

/* An unverified TCLK derived key. We should continue to use
 * apsPreconfiguredLinkKey until it gets verified by a
 * APSME-VERIFY-KEY.indication */
#define ZB_APSME_KEY_ATTR_UNVERIFIED        0x02U

/* ZCL KE/CBKE derived key (Unique Link Key) */
#define ZB_APSME_KEY_ATTR_CBKE              0x04U

/* TCLK update derived key. Set when we receive a APSME-REQUEST-KEY.indication
 * with key-type set to TCLK. ZB_APSME_KEY_ATTR_UNVERIFIED is set at the
 * same time */
#define ZB_APSME_KEY_ATTR_TCLK_DERIVED      0x08U

/* Distributed Security Global Key (value stored in apsDistributedGlobalKey) */
/* Global Link Key */
#define ZB_APSME_KEY_ATTR_DISTRIBUTED       0x10U

/* Trust center link key derived using Dynamic Link key negotiation. */
#define ZB_APSME_KEY_ATTR_DLK               0x20U

/* Trust center link key which can only be used provisionally to allow
 * a device to establish/renegotiate a new trust center link key.
 *
 * KeyAttribute field for all the KeyPairTable entries on the new trust
 * center shall be set to ZB_APSME_KEY_ATTR_PROVISIONAL on TCSO, forcing
 * other devices to update the trust center link key with the new TC on
 * trust center rejoin using the mutually supported mechanism of choice
 * (e.g, TCLK, DLK or CBKE). Zigbee Direct also uses provisional link keys
 * in case of OOB join, these keys shall be updated once the join is complete
 * and connection to ZC is available. */
#define ZB_APSME_KEY_ATTR_PROVISIONAL       0x40U
/*-------------------------------------------------------------*/

/* See R22 section 4.7.3 Trust Center Policy Values */
/** Trust Center Policy Flags (ZB_APS_IB_ID_TRUST_CENTER_POLICY) */
enum ZbApsmePolicyT {
    ZB_APSME_POLICY_ALLOW_JOIN = 0x00000001, /**< allowJoins */
    ZB_APSME_POLICY_WHITELIST = 0x00000002, /**< useWhiteList */ /* deprecated with R23  */
    ZB_APSME_POLICY_IC_MASK = 0x0000000C, /**< allowInstallCodes */ /* requireInstallCodesOrPresetPassphrase */
    ZB_APSME_POLICY_IC_NOT_SUPPORTED = 0x00000000, /**< 0x00 - Do not support Install Codes Or Preset Passphrase */
    ZB_APSME_POLICY_IC_SUPPORTED = 0x00000004, /**< 0x01 - Support but do not require Install Codes Or Preset Passphrase */
    ZB_APSME_POLICY_IC_REQUIRED = 0x00000008, /**< 0x02 - Require the use of Install Codes Or Preset Passphrase) */
    ZB_APSME_POLICY_TCLK_UPDATE_REQUIRED = 0x00000010, /**< updateTrustCenterLinkKeysRequired */
    /* allowRejoinsWithWellKnownKey - "This value indicates if the trust center allows rejoins using
     * well known or default keys. A setting of FALSE means rejoins are only allowed with trust center
     * link keys where the KeyAttributes of the apsDeviceKeyPairSet entry indicates VERIFIED_KEY." */
    ZB_APSME_POLICY_ALLOW_REJOIN = 0x00000020, /**< allowRejoins */
    ZB_APSME_POLICY_TC_KEY_REQ_MASK = 0x000000C0, /**< allowTrustCenterLinkKeyRequests */
    ZB_APSME_POLICY_TC_KEY_REQ_ANY = 0x00000040, /**< 0x01 - Any device may request */
    ZB_APSME_POLICY_TC_KEY_REQ_PROV = 0x00000080, /* 0x02 - Provisional */

#if 0 /* not used and has no effect in stack */
      /* networkKeyUpdateMethod */
    ZB_APSME_POLICY_NWK_KEY_UNICAST = 0x00000100,
#endif

    ZB_APSME_POLICY_APP_KEY_REQ_MASK = 0x00000C00, /**< allowApplicationKeyRequests */
    ZB_APSME_POLICY_APP_KEY_REQ_NEVER = ZB_APSME_POLICY_IC_NOT_SUPPORTED, /**< 0x00 - Never */
    ZB_APSME_POLICY_APP_KEY_REQ_ANY = 0x00000400, /**< 0x01 - Any */
    ZB_APSME_POLICY_APP_KEY_REQ_PROV = 0x00000800, /**< 0x02 - Provisional, requires "applicationKeyRequestList" to be implemented */
    ZB_APSME_POLICY_TC_POLICY_CHANGE = 0x00001000, /**< allowRemoteTcPolicyChange */
    ZB_APSME_POLICY_ALLOW_VIRTUAL_DEVICES = 0x00002000, /**< allowVirtualDevices */

    /* For certification testing only */
    /* Authenticate using dummy keys only (preconfigured NWK key in use) */
    ZB_APSME_POLICY_DUMMY_KEY = 0x10000000
};

/** APSME-TRANSPORT-KEY.request */
struct ZbApsmeTransportKeyReqT {
    struct ZbApsAddrT dst; /**< APS address information data structure */
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
    union {
        struct {
            uint64_t parentAddr; /**< ParentAddress */
            uint8_t key[ZB_SEC_KEYSIZE]; /**< Key */
            uint8_t capabilities; /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT. */
        } trustKey; /**< Trust Center Link Key */
        struct {
            uint8_t keySeqNumber; /**< KeySeqNumber */
            uint8_t key[ZB_SEC_KEYSIZE]; /**< NetworkKey */
            bool useParent; /**< UseParent */
            uint64_t parentAddr; /**< ParentAddress */
        } nwkKey; /**< Network Key */
        struct {
            uint64_t partnerAddr; /**< PartnerAddress */
            bool initiator; /**< Initiator */
            uint8_t key[ZB_SEC_KEYSIZE]; /**< Key */
            uint8_t capabilities; /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT. */
        } linkKey; /**< Application Link Key */
    } keyinfo; /**< TransportKeyData */
};

/** APSME-TRANSPORT-KEY.indication */
struct ZbApsmeTransKeyIndT {
    uint64_t srcExtAddr; /**< SrcAddress */
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
    union {
        struct {
            uint8_t key[ZB_SEC_KEYSIZE]; /**< Key */
            bool capabilities_valid; /**< True, if a valid Link key and features TLV found. */
            uint8_t capabilities;
            /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT.
             * Valid only if 'capabilities_valid' is true. */
        } trustKey; /**< Trust Center Link Key */
        struct {
            uint8_t keySeqNumber; /**< KeySeqNumber */
            uint8_t key[ZB_SEC_KEYSIZE]; /**< Key */
        } nwkKey; /**< Network Key */
        struct {
            uint64_t partnerAddr; /**< PartnerAddress */
            bool initiator; /**< Initiator */ /* initiator field is missing from spec */
            uint8_t key[ZB_SEC_KEYSIZE]; /**< Key */
            bool capabilities_valid; /**< True, if a valid Link key and features TLV found. */
            uint8_t capabilities;
            /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT.
             * Valid only if 'capabilities_valid' is true. */
        } linkKey; /**< Application Link Key */
    } keyinfo; /**< TransportKeyData */
    enum ZbSecEncryptT encryptKeyType; /* Key used to encrypt the incoming command */
};

/** APSME-UPDATE-DEVICE.request */
struct ZbApsmeUpdateDeviceReqT {
    uint64_t dstExtAddr; /**< DestAddress */
    uint64_t devExtAddr; /**< DeviceAddress */
    enum ZbApsmeDeviceStatusT status; /**< Status - Device status values */
    uint16_t devShortAddr; /**< DeviceShortAddress */
#if (CONFIG_ZB_REV >= 23)
    struct ZbJoinerTLVsT joinerTLVs;
    /**< TLVs of the joining device as relayed during Network Commissioning */
#endif
};

/** APSME-UPDATE-DEVICE.indication */
struct ZbApsmeUpdateDeviceIndT {
    uint64_t srcExtAddr; /**< SrcAddress */
    uint64_t devExtAddr; /**< DeviceAddress */
    uint16_t devShortAddr; /**< DeviceShortAddress */
    enum ZbApsmeDeviceStatusT status; /**< Status - Device status values */
    enum ZbSecEncryptT encryptKeyType; /* key used to encrypt the incoming command */
#if (CONFIG_ZB_REV >= 23)
    struct ZbJoinerTLVsT joinerTLVs; /* (R23+) */
    /**< TLVs of the joining device as relayed during Network Commissioning */
#endif
};

/** APSME-REMOVE-DEVICE.request */
struct ZbApsmeRemoveDeviceReqT {
    uint64_t dstExtAddr; /**< ParentAddress */
    uint64_t targetAddr; /**< TargetAddress */
};

/** APSME-REMOVE-DEVICE.indication */
struct ZbApsmeRemoveDeviceIndT {
    uint64_t srcExtAddr; /**< SrcAddress */
    uint64_t targetAddr; /**< TargetAddress */
    enum ZbSecEncryptT encryptKeyType; /* Key used to encrypt the incoming command */
};

/* R22 Table 4-19 RequestKeyType Values */
/* This table is slightly different than the values from enum ZbSecKeyTypeT, which all the other commands use */
/** RequestKeyType Values */
enum ZbApsRequestKeyTypeT {
    ZB_APS_REQKEY_KEYTYPE_APP_LINK = 0x02, /**< Application Link Key */
    ZB_APS_REQKEY_KEYTYPE_TC_LINK = 0x04 /**< Trust Center Link Key */
};

/** APSME-REQUEST-KEY.request */
struct ZbApsmeRequestKeyReqT {
    uint64_t dstExtAddr; /**< DestAddress */
    enum ZbApsRequestKeyTypeT keyType; /**< RequestKeyType */
    uint64_t partnerAddr; /**< PartnerAddress - Only used with application keys */
};

/** APSME-REQUEST-KEY.indication */
struct ZbApsmeRequestKeyIndT {
    uint64_t srcExtAddr; /**< SrcAddress */
    enum ZbApsRequestKeyTypeT keyType; /**< RequestKeyType */
    uint64_t partnerAddr; /**< PartnerAddress */
    enum ZbSecEncryptT encryptKeyType; /* Key used to encrypt the incoming command */
};

/** APSME-SWITCH-KEY.request */
struct ZbApsmeSwitchKeyReqT {
    /*
     * Under normal stack operation, destination address mode must be
     * ZB_APSDE_ADDRMODE_EXT. If dstAddrMode == ZB_APSDE_ADDRMODE_EXT
     * and dstExtAddr == 0, the switch key command will be sent to the
     * 0xffff broadcast address.
     *
     * For ZigBee Pro testing, we need to have finer control over the
     * broadcast address.  For test 14.24, we need to be able to
     * specify 0xffff as well as 0xfffd (rx-on only).
     */
    struct ZbApsAddrT dst; /**< APS address information data structure */
    uint8_t keySeqNum; /**< KeySeqNumber */
};

/** APSME-SWITCH-KEY.indication */
struct ZbApsmeSwitchKeyIndT {
    uint64_t srcExtAddr; /**< SrcAddress */
    uint8_t keySeqNum; /**< KeySeqNumber */
    enum ZbSecEncryptT encryptKeyType; /* Key used to encrypt the incoming command */
};

/** APSME-VERIFY-KEY.request */
struct ZbApsmeVerifyKeyReqT {
    uint64_t dstExtAddr; /**< DestAddress */
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
#if (CONFIG_ZB_REV >= 23)
    struct ZbApsRelayInfoT relayInfo; /**< Contains information required to relay the APS packet. */
#endif
};

/** APSME-VERIFY-KEY.indication */
struct ZbApsmeVerifyKeyIndT {
    uint64_t srcExtAddr; /**< SrcAddress */
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
    uint8_t hash[ZB_SEC_KEYSIZE]; /**< ReceivedInitiatorHashValue */
    enum ZbSecEncryptT encryptKeyType; /* Key used to encrypt the incoming command */
#if (CONFIG_ZB_REV >= 23)
    struct ZbApsRelayInfoT relayInfo; /**< Contains information required to relay the APS packet. */
#endif
};

/** APSME-CONFIRM-KEY.request */
struct ZbApsmeConfirmKeyReqT {
    enum ZbStatusCodeT status; /**< Status */
    uint64_t dstExtAddr; /**< DestAddress */
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
#if (CONFIG_ZB_REV >= 23)
    struct ZbApsRelayInfoT relayInfo; /**< Contains information required to relay the APS packet. */
#endif
};

/** APSME-CONFIRM-KEY.indication */
struct ZbApsmeConfirmKeyIndT {
    enum ZbStatusCodeT status; /**< Status */
    uint64_t srcExtAddr; /**< SrcAddress */
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
    enum ZbSecEncryptT encryptKeyType; /* Key used to encrypt the incoming command */
#if (CONFIG_ZB_REV >= 23)
    struct ZbApsRelayInfoT relayInfo; /**< Contains information required to relay the APS packet. */
#endif
};

#if (CONFIG_ZB_REV >= 23)
/** Initial join authentication method used with DLK. */
enum ZbApsInitialJoinAuthMethodT {
    ZB_APS_INITIAL_JOIN_AUTH_NONE = 0U,
    /**< Initial join authentication - none. */
    ZB_APS_INITIAL_JOIN_AUTH_INSTALL_CODE_KEY = 1U,
    /**< Initial join authentication - install code key. */
    ZB_APS_INITIAL_JOIN_AUTH_ANON_KEY_NEGO = 2U,
    /**< Initial join authentication - anonymous key negotiation. */
    ZB_APS_INITIAL_JOIN_AUTH_KEY_NEGO_WITH_AUTH = 3U
        /**< Initial join authentication - authentication key negotiation. */
};

/** Post join key update method. */
enum ZbApsPostJoinKeyUpdateMethodT {
    ZB_APS_POST_JOIN_KEY_UPDATE_NONE = 0U,
    /**< Post join key update - none. */
    ZB_APS_POST_JOIN_KEY_UPDATE_REQUEST_KEY = 1U,
    /**< Post join key update - request key. */
    ZB_APS_POST_JOIN_KEY_UPDATE_UNAUTH_DLK = 2U,
    /**< Post join key update - anonymous DLK. */
    ZB_APS_POST_JOIN_KEY_UPDATE_AUTH_DLK = 3U,
    /**< Post join key update - authentication DLK. */
    ZB_APS_POST_JOIN_KEY_UPDATE_CBKE = 4U
        /**< Post join key update - CBKE. */
};

/* Dynamic Link Key negotiation state. */
enum ZbApsKeyNegoStateT {
    ZB_APS_KEY_NEGO_STATE_NONE = 0U,
    /**< APS Key negotiation state none. */
    ZB_APS_KEY_NEGO_STATE_START = 1U,
    /**< APS Key negotiation state start. */
    ZB_APS_KEY_NEGO_STATE_COMPLETE = 2U
        /**< APS Key negotiation state complete. */
};

/* Dynamic Link Key negotiation state. */
enum ZbApsPreSharedKeyTypeT {
    ZB_APS_PRE_SHARED_KEY_TYPE_INVALID = 0U,
    /**< APS pre-shared key type invalid. */
    ZB_APS_PRE_SHARED_KEY_TYPE_IC_KEY = 1U,
    /**< APS pre-shared key type install code derived link key. */
    ZB_APS_PRE_SHARED_KEY_TYPE_PASSCODE = 2U
        /**< APS pre-shared key type variable length passcode. */
};
#endif

/** APSME-ADD-KEY.request - Exegin Custom */
struct ZbApsmeAddKeyReqT {
    enum ZbSecKeyTypeT keyType;
    /**< Key type e.g, ZB_SEC_KEYTYPE_STANDARD_NWK. */
    uint8_t key[ZB_SEC_KEYSIZE];
    /**< Input Key. */
    uint8_t keyAttribute;
    /**< Key attribute e.g, ZB_APSME_KEY_ATTR_VERIFIED */
    uint8_t keySeqNumber;
    /**< Sequence number of the input key. */
    uint64_t partnerAddr;
    /**< Partner address of the key added to APS KeyPair table. */
    uint32_t outgoingCounter;
    /* Outgoing frame counter, for link keys only. */
    uint32_t incomingCounter;
    /* Incoming frame counter, for link keys only. */
#if (CONFIG_ZB_REV >= 23)
    enum ZbApsInitialJoinAuthMethodT joinAuthMethod;
    /* Initial join authentication method. (R23+) */
    enum ZbApsPostJoinKeyUpdateMethodT keyUpdateMethod;
    /**< Post join key update method. (R23+) */
    enum ZbSelKeyNegoMethodT selKeyNegoMethod;
    /**< Selected key negotiation method. (R23+) */
    enum ZbApsKeyNegoStateT keyNegoState;
    /**< APS key negotiation state. (R23+) */
    enum ZbApsPreSharedKeyTypeT preSharedKeyType;
    /**< APS pre-shared key type. (R23+) */
    uint8_t passphrase[ZB_SEC_PASSPHRASE_SIZE];
    /**< Passphrase to use for authentication DLK. (R23+) */
    bool passphraseUpdateAllowed;
    /**< APS passphrase update allowed. (R23+) */
    bool verifiedFrameCounter;
    /**< Indicates whether the incoming frame counter value has been verified through
     * a challenge response. Frame counters are implicitly verified after join, i.e,
     * TCLK/DLK etc. However, after reboot FC shall be verified using ZDO Security_Challenge_req/rsp
     * (R23+) */
    uint8_t capabilities;
    /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT. */
#endif
};

/** APSME-ADD-KEY.confirm - Exegin Custom */
struct ZbApsmeAddKeyConfT {
    enum ZbStatusCodeT status; /**< Status */
};

/*STRUCTURE:-----------------------------------------------------
 *  NAME        struct ZbApsmeGetKeyReqT
 *  DESC        Exegin Custom
 *  PARAMS
 *      keyType         ;
 *      keySeqNumber    ; Only used with ZB_SEC_KEYTYPE_STANDARD_NWK
 *                        The active network key's sequence number can be retrieved from
 *                        the NIB attribute ZB_NWK_NIB_ID_ActiveKeySeqNumber.
 *      partnerAddr     ;
 *---------------------------------------------------------------
 */

/** APSME-GET-KEY.request - Exegin Custom */
struct ZbApsmeGetKeyReqT {
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
    uint8_t keySeqNumber; /**< KeySeqNumber */
    uint64_t partnerAddr; /**< PartnerAddress */
};

/* APSME-GET-KEY.confirm - Exegin Custom */
struct ZbApsmeGetKeyConfT {
    enum ZbStatusCodeT status; /**< Status */
    uint8_t key[ZB_SEC_KEYSIZE]; /**< Key */
    uint32_t outgoingCounter; /**< outgoingCounter */
    uint32_t incomingCounter; /**< incomingCounter */
    uint8_t apsKeyAttribute; /**< apsKeyAttribute - Only valid if req.keyType != ZB_SEC_KEYTYPE_STANDARD_NWK */
#if (CONFIG_ZB_REV >= 23)
    enum ZbApsInitialJoinAuthMethodT joinAuthMethod;
    /**< Initial join authentication method. (R23+) */
    enum ZbApsPostJoinKeyUpdateMethodT keyUpdateMethod;
    /**< Post join key update method. */
    enum ZbSelKeyNegoMethodT selKeyNegoMethod;
    /**< Selected key negotiation method. (R23+) */
    enum ZbApsPreSharedKeyTypeT preSharedKeyType;
    /**< APS pre-shared key type. (R23+) */
    uint8_t passphrase[ZB_SEC_PASSPHRASE_SIZE];
    /**< Passphrase to use for authentication DLK. (R23+) */
    bool verifiedFrameCounter;
    /**< Indicates whether the incoming frame counter value has been verified through
     * a challenge response.. (R23+) */
    uint8_t capabilities;
    /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT. */
#endif
};

/** APSME-REMOVE-KEY.request - Exegin Custom */
struct ZbApsmeRemoveKeyReqT {
    enum ZbSecKeyTypeT keyType; /**< StandardKeyType */
    uint64_t partnerAddr; /**< PartnerAddress */
};

/** APSME-REMOVE-KEY.confirm - Exegin Custom */
struct ZbApsmeRemoveKeyConfT {
    enum ZbStatusCodeT status; /**< Status */
};

#if (CONFIG_ZB_REV >= 23)
/* APSME-KEY-NEGOTIATION.request (R23) */
struct ZbApsmeKeyNegoReqT {
    enum ZbSelKeyNegoMethodT requestedKeyNegoMethod;
    /**< Selected/Requested key negotiation method. */
    enum ZbSelPreSharedSecretT selPreSharedSecret;
    /**< Selected Pre-Shared secret. */
    uint64_t partnerLongAddr;
    /**< This is the EUI64 of the partner that key negotiation is being performed. */
    bool relayCommand;
    /**< This indicates whether or not the request should be relayed through another router. */
    uint64_t relayLongAddr;
    /**< Extended address of intermediate relay device. */
};

/** APSME-KEY-NEGOTIATION.Confirm */
struct ZbApsmeKeyNegoConfirmT {
    enum ZbStatusCodeT status;
    /**< ZDO status. */
    uint8_t partnerPubPoint[ZB_DLK_CURVE25519_PUB_POINT_LEN];
    /**< Partner public point data */
    uint64_t partnerLongAddr;
    /**< Partner extended address. */
    bool relayCommand;
    /**< This indicates whether or not the response was relayed through another router. */
    uint64_t relayLongAddr;
    /**< Extended address of intermediate relay device. */
};

/* APSME-KEY-NEGOTIATION.indication (R23) */
struct ZbApsmeKeyNegoIndT {
    uint64_t partnerLongAddr;
    /**< Partner extended address. */
    uint8_t partnerPubPoint[ZB_ECDHE_C25519_PUBLIC_KEY_SIZE];
    /**< Partner public point data */
    uint8_t seqnum;
    /**< ZDO sequence number. */
    bool relayCommand;
    /**< This indicates whether or not the response should be relayed through another router. */
    uint64_t relayLongAddr;
    /**< Extended address of intermediate relay device. */
};

/* APSME-SEC-CHALLENGE.request (R23 - Exegin add-on) */
struct ZbApsmeSecChallengeReqT {
    uint16_t devShortAddr;
    /**< Device short address. */
    uint64_t devExtAddr;
    /**< Extended address of partner device to perform APS Frame counter synchronization. */
};

/* APSME-SEC-CHALLENGE.indication (R23 - Exegin add-on) */
struct ZbApsmeSecChallengeIndT {
    uint16_t devShortAddr;
    /**< Device short address. */
    uint64_t devExtAddr;
    /**< Extended address of partner device to perform APS Frame counter synchronization. */
};
#endif

/* APS Key/Pair Descriptor - used with ZB_APS_IB_ID_DEVICE_KEY_PAIR_SET */
struct ZbApsmeKeyPairT {
    uint64_t deviceAddress;
    /**< Extended device address. */
    uint8_t linkKey[ZB_SEC_KEYSIZE];
    /**< APS link key. */
    uint32_t outgoingFrameCounter;
    /**< APS outgoing frame counter. */
    uint32_t incomingFrameCounter;
    /**< APS incoming frame counter. */
    uint32_t persistOutFrameCounter;
    /**< Persisted value of APS outgoing frame counter. */
    uint32_t persistInFrameCounter;
    /**< Persisted value of APS incoming frame counter. */
    uint8_t keyAttribute;
    /**< APS Key attribute e.g, ZB_APSME_KEY_ATTR_VERIFIED */
    ZbUptimeT cooldown;
    /**< APS frame counter cooldown period. */
#if (CONFIG_ZB_REV >= 23)
    enum ZbApsInitialJoinAuthMethodT joinAuthMethod;
    /**< Initial join authentication method. (R23+) */
    enum ZbApsPostJoinKeyUpdateMethodT keyUpdateMethod;
    /**< Post join key update method. */
    enum ZbSelKeyNegoMethodT selKeyNegoMethod;
    /**< Selected key negotiation method. (R23+) */
    enum ZbSelPreSharedSecretT selPreSharedSecret;
    /**< Selected pre-Shared secret. (R23+) */
    enum ZbApsKeyNegoStateT keyNegoState;
    /**< APS key negotiation state. (R23+) */
    enum ZbApsPreSharedKeyTypeT preSharedKeyType;
    /**< APS pre-shared key type. (R23+) */
    uint8_t passphrase[ZB_SEC_PASSPHRASE_SIZE];
    /**< Passphrase to use for authentication DLK. (R23+) */
    uint16_t keyTimeout;
    /**< APS key timeout duration. Default, 0xFFFF - key does not expire. (R23+) */
    bool passphraseUpdateAllowed;
    /**< APS passphrase update allowed. (R23+) */
    bool verifiedFrameCounter;
    /**< Indicates whether the incoming frame counter value has been verified through
     * a challenge response.. (R23+) */
    uint32_t challengeFrameCounter;
    /**< The AES-CCM-128 outgoing frame counter used to generate the MIC using
     * the special nonce and AES-128 key for frame counter synchronization */
    uint8_t capabilities;
    /**< Link key features and capabilities e.g, ZB_APS_SEC_CAPABILITY_FC_SYNC_SUPPORT. */
#endif
};

/**
 * Perform an APSME-TRANSPORT-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-TRANSPORT-KEY.request
 * @return Returns void
 */
void ZbApsmeTransportKeyReq(struct ZigBeeT *zb, struct ZbApsmeTransportKeyReqT *req);

/**
 * Perform an APSME-UPDATE-DEVICE.request.
 * @param zb Zigbee stack instance
 * @param req APSME-UPDATE-DEVICE.request
 * @return Returns security key used to send Update Device
 */
enum ZbSecHdrKeyIdT ZbApsmeUpdateDeviceReq(struct ZigBeeT *zb, struct ZbApsmeUpdateDeviceReqT *req);

/**
 * Perform an APSME-REMOVE-DEVICE.request.
 * @param zb Zigbee stack instance
 * @param req APSME-REMOVE-DEVICE.request
 * @return Returns void
 */
void ZbApsmeRemoveDeviceReq(struct ZigBeeT *zb, struct ZbApsmeRemoveDeviceReqT *req);

/**
 * Perform an APSME-REQUEST-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-REQUEST-KEY.request
 * @return ZCL_STATUS_SUCCESS if successful, or other ZclStatusCodeT value on error
 */
enum ZbStatusCodeT ZbApsmeRequestKeyReq(struct ZigBeeT *zb, struct ZbApsmeRequestKeyReqT *req);

/**
 * Perform an APSME-SWITCH-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-SWITCH-KEY.request
 * @return Returns void
 */
void ZbApsmeSwitchKeyReq(struct ZigBeeT *zb, struct ZbApsmeSwitchKeyReqT *req);

/**
 * Perform an APSME-VERIFY-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-VERIFY-KEY.request
 * @return Returns void
 */
void ZbApsmeVerifyKeyReq(struct ZigBeeT *zb, struct ZbApsmeVerifyKeyReqT *req);

/**
 * Perform an APSME-CONFIRM-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-CONFIRM-KEY.request
 * @return Returns void
 */
void ZbApsmeConfirmKeyReq(struct ZigBeeT *zb, struct ZbApsmeConfirmKeyReqT *req,
    void (*callback)(struct ZbApsdeDataConfT *conf, void *arg), void *arg);

/**
 * Perform an APSME-ADD-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-ADD-KEY.request
 * @param conf APSME-ADD-KEY.confirm
 * @return Returns void
 */
void ZbApsmeAddKeyReq(struct ZigBeeT *zb, struct ZbApsmeAddKeyReqT *req,
    struct ZbApsmeAddKeyConfT *conf);
/* For ZbApsmeGetKeyReq, key types ZB_SEC_KEYTYPE_TC_LINK and ZB_SEC_KEYTYPE_APP_LINK are treated
 * the same when searching, so you can use either to get the link key for the requested EUI. */

/**
 * Perform an APSME-GET-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-GET-KEY.request
 * @param conf APSME-GET-KEY.confirm
 * @return Returns void
 */
void ZbApsmeGetKeyReq(struct ZigBeeT *zb, struct ZbApsmeGetKeyReqT *req,
    struct ZbApsmeGetKeyConfT *conf);

/**
 * Perform an APSME-REMOVE-KEY.request.
 * @param zb Zigbee stack instance
 * @param req APSME-REMOVE-KEY.request
 * @param conf APSME-REMOVE-KEY.confirm
 * @return Returns void
 */
void ZbApsmeRemoveKeyReq(struct ZigBeeT *zb, struct ZbApsmeRemoveKeyReqT *req,
    struct ZbApsmeRemoveKeyConfT *conf);

#if (CONFIG_ZB_REV >= 23)
/* APSME-KEY-NEGOTIATION.request */
enum ZbStatusCodeT ZbApsmeKeyNegoRequest(struct ZigBeeT *zb, struct ZbApsmeKeyNegoReqT *req,
    void (*callback)(enum ZbStatusCodeT status, void *cb_arg), void *arg);
enum ZbStatusCodeT ZbApsmeKeyNegoIndRsp(struct ZigBeeT *zb, struct ZbApsmeKeyNegoIndT *ind);

/* APSME-SEC-CHALLENGE.request */
/**
 * Perform an APSME-SEC-CHALLENGE.request.
 * @param zb Zigbee stack instance
 * @param req APSME-SEC-CHALLENGE.request
 * @return Returns enum ZbStatusCodeT.
 */
enum ZbStatusCodeT ZbApsmeSecChallengeRequest(struct ZigBeeT *zb,
    struct ZbApsmeSecChallengeReqT *req);
#endif

/*---------------------------------------------------------------
 * Filter API
 *---------------------------------------------------------------
 */
/**
 * Create an APSDE-DATA.indication filter for a specific endpoint, with no specific cluster
 * being filtered. For any incoming APS data packets that match this filter, the provided
 * 'callback' function will be called. Filter is freed by calling ZbApsFilterEndpointFree.
 * @param zb Zigbee instance
 * @param endpoint Endpoint Id to match with incoming packets
 * @param profileId Profile Id to match with incoming packets
 * @param callback APSDE-DATA.indication callback if the filter matches the incoming packet.
 * @param arg Application callback argument, which will be passed to callback()
 * @return Filter pointer (handle)
 */
struct ZbApsFilterT * ZbApsFilterEndpointAdd(struct ZigBeeT *zb, uint8_t endpoint, uint16_t profileId,
    enum zb_msg_filter_rc (*callback)(struct ZbApsdeDataIndT *dataInd, void *cb_arg), void *arg);

/**
 * Create an APSDE-DATA.indication filter for a specific endpoint and cluster Id.
 * being filtered. For any incoming APS data packets that match this filter, the provided
 * 'callback' function will be called. Filter is freed by calling ZbApsFilterEndpointFree.
 * @param zb Zigbee instance
 * @param endpoint Endpoint Id to match with incoming packets
 * @param clusterId Cluster Id to match with incoming packets
 * @param profileId Profile Id to match with incoming packets
 * @param callback APSDE-DATA.indication callback if the filter matches the incoming packet
 * @param arg Application callback argument, which will be passed to callback()
 * @return Filter pointer (handle)
 */
struct ZbApsFilterT * ZbApsFilterClusterAdd(struct ZigBeeT *zb, uint8_t endpoint,
    uint16_t clusterId, uint16_t profileId,
    enum zb_msg_filter_rc (*callback)(struct ZbApsdeDataIndT *dataInd, void *cb_arg), void *arg);

/**
 * Remove and free an APS indication filter.
 * @param zb Zigbee instance
 * @param filter Filter handle to remove and free
 * @return Returns void
 */
void ZbApsFilterEndpointFree(struct ZigBeeT *zb, struct ZbApsFilterT *filter);

/*---------------------------------------------------------------
 * APSME-GET.request / APSME-SET.request
 *---------------------------------------------------------------
 */
/* ZbApsGet and ZbApsSet return the confirm status byte (SUCCESS == 0x00) */
#define ZbApsGet(_zb_, _id_, _ptr_, _sz_) ZbApsGetIndex(_zb_, _id_, _ptr_, _sz_, 0)
#define ZbApsSet(_zb_, _id_, _ptr_, _sz_) ZbApsSetIndex(_zb_, _id_, _ptr_, _sz_, 0)

/**
 * Performs an APSME-GET.request. Retrieve the value of the attribute
 * corresponding to the supplied index.
 * @param zb Zigbee stack instance
 * @param attrId Attribute Id
 * @param attrPtr Attribute pointer
 * @param attrSz attribute size
 * @return ZCL_STATUS_SUCCESS if successful, or other ZclStatusCodeT value on error
 */
enum ZbStatusCodeT ZbApsGetIndex(struct ZigBeeT *zb, enum ZbApsmeIbAttrIdT attrId,
    void *attrPtr, unsigned int attrSz, unsigned int attrIndex);

/**
 * Performs an APSME-SET.request. Set the value of the attribute
 * corresponding to the supplied index.
 * @param zb Zigbee stack instance
 * @param attrId Attribute Id
 * @param attrPtr Attribute pointer
 * @param attrSz attribute size
 * @return ZCL_STATUS_SUCCESS if successful, or other ZclStatusCodeT value on error
 */
enum ZbStatusCodeT ZbApsSetIndex(struct ZigBeeT *zb, enum ZbApsmeIbAttrIdT attrId,
    const void *attrPtr, unsigned int attrSz, unsigned int attrIndex);

/*---------------------------------------------------------------
 * Helper Functions
 *---------------------------------------------------------------
 */
/**
 * Check if the local device is a member of a specified group.
 * @param zb Zigbee stack instance
 * @param groupAddr Group address
 * @param endpoint Endpoint of interest, or ZB_ENDPOINT_BCAST to determine if any endpoint is a member of the group
 * @return Returns true if device is a member, false otherwise
 */
bool ZbApsGroupIsMember(struct ZigBeeT *zb, uint16_t groupAddr, uint8_t endpoint);

/**
 * Check if a link key exists in the AIB.
 * @param zb Zigbee stack instance
 * @param Partner address
 * @return Returns true if key exists, false otherwise
 */
bool ZbApsLinkKeyExists(struct ZigBeeT *zb, uint64_t partner);

/**
 * Look up an APS key pair descriptor from the apsDeviceKeyPairSet AIB attribute/key table.
 * @param zb Zigbee stack instance
 * @param key (OUT) key pair descriptor
 * @param addr Partner addresses
 * @param idx (OUT) index value into Device Key Pair Set Table for the APS key returned, if successful
 * @return Returns key pair on success, or NULL if no such entry was found
 */
struct ZbApsmeKeyPairT * ZbApsLookupKey(struct ZigBeeT *zb, struct ZbApsmeKeyPairT *key,
    uint64_t addr, unsigned int *idx);

/**
 * Check if an address is set to broadcast.
 * @param addr Address to check
 * @return Returns true if address is set to broadcast, false otherwise
 */
bool ZbApsAddrIsBcast(const struct ZbApsAddrT *addr);

/**
 * Check if an address is that of the provided Zigbee stack structure.
 * @param zb Zigbee stack instance
 * @param addr Address to check
 * @return Returns true if address is local, false otherwise.
 */
bool ZbApsAddrIsLocal(struct ZigBeeT *zb, const struct ZbApsAddrT *addr);

/**
 * Check if an incoming command has the appropriate security level.
 * @param zb Zigbee stack instance
 * @param cmdId Command Id
 * @param srcExtAddr Source extended address
 * @param encryptKeyType Key type
 * @return Returns true if the command is allowed, false otherwise
 */
bool ZbApsCommandSecurityCheck(struct ZigBeeT *zb, enum ZbApsCmdIdT cmdId, uint64_t srcExtAddr, enum ZbSecEncryptT encryptKeyType);

/*
 * Helpers for certification testing (TP/PRO/BV-43 and TP/PRO/BV-44)
 * - For Internal use Only
 * - Controls GU behaviour
 */

/*
 *
 * @param zb Zigbee stack instance
 * @param blockNum
 * @return
 */
bool ZbApsFragDropTxAdd(struct ZigBeeT *zb, uint8_t blockNum);

/*
 *
 * @param zb Zigbee stack instance
 * @return Returns void
 */
void ZbApsFragDropTxClear(struct ZigBeeT *zb);

#endif /* ZIGBEE_APS_H */
