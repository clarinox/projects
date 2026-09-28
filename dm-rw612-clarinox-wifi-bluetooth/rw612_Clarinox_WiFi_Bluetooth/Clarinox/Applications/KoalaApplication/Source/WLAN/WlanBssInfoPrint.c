/*********************************************************************************
*
* Project             Wlan Sample Application
* File                WlanBssInfoPrint.c
* Description         Wlan BSS Information Display
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/


#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "ConsoleUIEngine.h"
#include "ClarinoxWlan.h"
#include "Wlan.Api.h"
#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
#include "Wlan.ClxMesh.Api.h"
#endif
#include "Wlan.Config.h"
#include "WiFiApp.h"


#define ITEM_TITLE_COLOR                                Gray
#define SUBITEM_TITLE_COLOR                             Peach
#define ITEM_VALUE_COLOR                                Khaki

#define BASE_IEEE802_11_CHANNEL_SPACING                 5   /* MHZ; two adjacent channels n and (n + 1) are 5 MHz apart */
#define PRIMARY_CHANNEL_BADNWIDTH                       20  /* MHZ */
#define HT_SECONDARY_CHANNEL_BADNWIDTH                  20  /* MHZ */


#define ITEM_TITLE_SSID                                         itemTitles[0]
#define ITEM_TITLE_BSSID                                        itemTitles[1]
#define ITEM_TITLE_PRIMARY_CHANNEL                              itemTitles[2]
#define ITEM_TITLE_SIGNAL_POWER_LEVEL                           itemTitles[3]
#define ITEM_TITLE_SUPPORTED_AUTH_SUITES                        itemTitles[4]
#define ITEM_TITLE_SUPPORTED_CIPHER_SUITES                      itemTitles[5]
#define ITEM_TITLE_HT_CHANNEL_BW                                itemTitles[6]
#define ITEM_TITLE_SUPPORTED_HT_RATES                           itemTitles[7]
#define ITEM_TITLE_SUPPORTED_VHT_CHANNEL_BW                     itemTitles[8]
#define ITEM_TITLE_SUPPORTED_VHT_RX_RATES                       itemTitles[9]
#define ITEM_TITLE_SUPPORTED_VHT_TX_RATES                       itemTitles[10]
#define ITEM_TITLE_PROTECTED_MGMT_FRAMES                        itemTitles[11]
#define ITEM_TITLE_CLARINOX_MESH_NODE_INFORMATION               itemTitles[12]
#define ITEM_TITLE_SUPPORTED_HE_CHANNEL_BW                      itemTitles[13]


#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
#define ITEM_MESH_SUBITEM_TITLE_MESH_ID                         meshsubitemTitles[0]
#define ITEM_MESH_SUBITEM_TITLE_AL_MAC_ADDRESS                  meshsubitemTitles[1]
#define ITEM_MESH_SUBITEM_TITLE_DOWNLINK_INFORMATION            meshsubitemTitles[2]
#define ITEM_MESH_SUBITEM_TITLE_MAX_NUM_OF_CLIENTS              meshsubitemTitles[3]
#define ITEM_MESH_SUBITEM_TITLE_CURRENT_NUM_OF_CLIENTS          meshsubitemTitles[4]
#define ITEM_MESH_SUBITEM_TITLE_MAX_TX_SUPPORTED_RATE           meshsubitemTitles[5]
#define ITEM_MESH_SUBITEM_TITLE_MAX_RX_SUPPORTED_RATE           meshsubitemTitles[6]
#define ITEM_MESH_SUBITEM_TITLE_OPERATING_CHANNEL               meshsubitemTitles[7]
#define ITEM_MESH_SUBITEM_TITLE_UPLINK_CONNECTION_INFORMATION   meshsubitemTitles[8]
#define ITEM_MESH_SUBITEM_TITLE_PARENT_AL_MAC_ADDRESS           meshsubitemTitles[9]
#define ITEM_MESH_SUBITEM_TITLE_PARENT_BSSID                    meshsubitemTitles[10]
#define ITEM_MESH_SUBITEM_TITLE_HOPS_TO_ROOT_NODE               meshsubitemTitles[11]
#define ITEM_MESH_SUBITEM_TITLE_DOWNLINK_PACKET_STATISTICS      meshsubitemTitles[12]
#define ITEM_MESH_SUBITEM_TITLE_UPLINK_PACKET_STATISTICS        meshsubitemTitles[13]
#define ITEM_MESH_SUBITEM_TITLE_MEASUREMENT_PERIOD              meshsubitemTitles[14]
#define ITEM_MESH_SUBITEM_TITLE_TX_PACKET_ERRORS                meshsubitemTitles[15]
#define ITEM_MESH_SUBITEM_TITLE_TRANSMITTED_PACKETS             meshsubitemTitles[16]
#define ITEM_MESH_SUBITEM_TITLE_RX_PACKET_ERRORS                meshsubitemTitles[17]
#define ITEM_MESH_SUBITEM_TITLE_PACKETS_RECEIVED                meshsubitemTitles[18]
#define ITEM_MESH_SUBITEM_TITLE_AVERAGE_RSSI                    meshsubitemTitles[19]
#endif /* #if defined(CLARINOX_WLAN_MESH_SUPPORTED) */


static const s1* itemTitles[] =
{
    "SSID",
    "BSSID                          ",
    "Primary Channel                ",
    "Signal Power Level             ",
    "Supported Auth Suites          ",
    "Supported Cipher Suites        ",
    "HT Channel BW                  ",
    "Supported HT Rates             ",
    "Supported VHT Channel BW       ",
    "Supported VHT RX Rates         ",
    "Supported VHT TX Rates         ",
    "Protected Mgmt Frames          ",
    "ClarinoxMesh Node Information  ",
    "Supported HE Channel Width     "
};


#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
static const s1* meshsubitemTitles[] =
{
    "MeshID                         ",
    "AL MacAddress                  ",
    "Downlink Information",
    "Maximum Number of Clients      ",
    "Current Number of Clients      ",
    "Maximum TX Supported Rate      ",
    "Maximum RX Supported Rate      ",
    "Operating Channel              ",
    "Uplink Connection Information",
    "Parent AL MacAddress           ",
    "Parent BSSID                   ",
    "Number of Hops to Root Node    ",
    "Downlink Packet Statistics",
    "Uplink Packet Statistics",
    "Measurement Period             ",
    "TX Packet Errors               ",
    "Transmitted Packets            ",
    "RX Packet Errors               ",
    "Packets Received               ",
    "Average RSSI                   "
};
#endif /* #if defined(CLARINOX_WLAN_MESH_SUPPORTED) */



typedef struct HtMcsGroupStruct
{
    u1 firstIndex;
    u1 lastIndex;
} HtMcsGroup;


#define SET_ITEM_VALUE_COLOR    CLX_TE_SET_COLOR(ITEM_VALUE_COLOR)



static void printItemTitle(const s1* title)
{
    CLX_TE_SET_COLOR(ITEM_TITLE_COLOR);
    clxConsoleUIEngineText("\t%s : ", title);
    CLX_TE_RESET_COLOR;
}

#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
static void printSubitemTitle(const s1* title, u1 depth)
{
    CLX_TE_SET_COLOR(SUBITEM_TITLE_COLOR);

    /* One TAB for the parent item: */
    while (depth-- != 0)
    {
        clxConsoleUIEngineText("\t");
    }

    clxConsoleUIEngineText("%s : ", title);

    CLX_TE_RESET_COLOR;
}

static void printIndentedString(const s1* strBeforeTabs, const s1* strAfterTabs, s1 numOfTabs)
{
    if (strBeforeTabs)
    {
        clxConsoleUIEngineText("%s", strBeforeTabs);
    }

    while (numOfTabs-- > 0)
    {
        clxConsoleUIEngineText("\t");
    }

    if (strAfterTabs)
    {
        clxConsoleUIEngineText("%s", strAfterTabs);
    }
}
#endif


static const s1* separator(boolean firstItem)
{
    return (firstItem) ? "" : ", ";
}

static HtMcsGroup findNextSupportedHtMcsGroup(ClxWlanHTInfo* htInfo, const HtMcsGroup* lastGroup)
{
    HtMcsGroup ret = { lastGroup ? (lastGroup->lastIndex + 1) : 0, 0 };

    /* First, lets find the first MCS index: */
    while (ret.firstIndex <= CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX)
    {
        if (CLX_WLAN_HT_RX_MCS_BIT(*htInfo, ret.firstIndex))
        {
            break;
        }

        ++ret.firstIndex;
    }

    ret.lastIndex = ret.firstIndex;

    /* First, lets find the last MCS index: */
    while (ret.lastIndex < CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX)
    {
        if (CLX_WLAN_HT_RX_MCS_BIT(*htInfo, (ret.lastIndex + 1)) == 0)
        {
            break;
        }

        ++ret.lastIndex;
    }

    return ret;
}

static void printSupportedHtMcsGroups(ClxWlanHTInfo* htInfo)
{
    HtMcsGroup  htMcsGroup = { 0, 0 };
    HtMcsGroup* lastHtMcsGroup = NULL;

    boolean firstItem = TRUE;

    printItemTitle(ITEM_TITLE_SUPPORTED_HT_RATES);

    SET_ITEM_VALUE_COLOR;
    while (1)
    {
        htMcsGroup = findNextSupportedHtMcsGroup(htInfo, lastHtMcsGroup);

        if ((htMcsGroup.firstIndex <= CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX) &&
            (htMcsGroup.lastIndex <= CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX))
        {
            if (htMcsGroup.firstIndex == htMcsGroup.lastIndex)
            {
                clxConsoleUIEngineText("%sMCS%u", separator(firstItem), htMcsGroup.firstIndex);
            }
            else
            {
                clxConsoleUIEngineText("%sMCS%u-MCS%u", separator(firstItem), htMcsGroup.firstIndex, htMcsGroup.lastIndex);
            }

            lastHtMcsGroup = &htMcsGroup;
        }
        else
        {
            break;
        }

        firstItem = FALSE;
    }
    CLX_TE_RESET_COLOR;

    clxConsoleUIEngineText("\n");
}

static void printSupportedVHtMcs(u2 map)
{
    boolean firstItem = TRUE;

    for (u4 i = 1; i <= CLX_WLAN_VHT_MAX_NUMBER_OF_SPATIAL_STREAMS; i++)
    {
        ClxWlanVHTSupportedMCS mcs = _CLX_WLAN_GET_VHT_SUPPORTED_MCS_PER_NSS_(map, i);

        switch (mcs)
        {
        case ClxWlanVHTSupportedMCS_0_7:
            clxConsoleUIEngineText("%sMCS0-MCS7[NSS%u]", separator(firstItem), i);
            break;
        case ClxWlanVHTSupportedMCS_0_8:
            clxConsoleUIEngineText("%sMCS0-MCS8[NSS%u]", separator(firstItem), i);
            break;
        case ClxWlanVHTSupportedMCS_0_9:
            clxConsoleUIEngineText("%sMCS0-MCS9[NSS%u]", separator(firstItem), i);
            break;
        default:
            break;
        }

        firstItem = FALSE;
    }

    clxConsoleUIEngineText("\n");
}

static void printSupportedAuthSuites(u4 value)
{
    boolean firstItem = TRUE;

    printItemTitle(ITEM_TITLE_SUPPORTED_AUTH_SUITES);
     
    SET_ITEM_VALUE_COLOR;
    if (value & (u4)ClxAuthTypeOpenSystem)
    {
        clxConsoleUIEngineText("%sOpenSystem", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxAuthTypePresharedKey)
    {
        clxConsoleUIEngineText("%sPSK", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxAuthTypeIEEE802_1x)
    {
        clxConsoleUIEngineText("%sIEEE802.1x", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxAuthTypeSAE)
    {
        clxConsoleUIEngineText("%sSAE", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxAuthTypeOWE)
    {
        clxConsoleUIEngineText("%sOWE", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxAuthTypePSK_SHA256)
    {
        clxConsoleUIEngineText("%sPSK_SHA256", separator(firstItem));
        firstItem = FALSE;
    }
#if defined(CLX_IEEE802_11_R_SUPPORTED)
    if (value & ClxAuthTypeIEEE802_1x_FT)
    {
        clxConsoleUIEngineText("%sIEEE802.1x_FT", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & ClxAuthTypeIEEE802_1x_FT_SHA384)
    {
        clxConsoleUIEngineText("%sIEEE802.1x_FT_SHA384", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & ClxAuthTypePSK_FT)
    {
        clxConsoleUIEngineText("%sPSK_FT", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & ClxAuthTypeSAE_FT)
    {
        clxConsoleUIEngineText("%sSAE_FT", separator(firstItem));
        firstItem = FALSE;
    }
#endif

    CLX_TE_RESET_COLOR;

    clxConsoleUIEngineText("\n");
}

static void printSupportedCipherSuites(u4 value)
{
    if (value == 0)
    {
        return;
    }

    boolean firstItem = TRUE;

    printItemTitle(ITEM_TITLE_SUPPORTED_CIPHER_SUITES);

    SET_ITEM_VALUE_COLOR;
    if (value & (u4)ClxEncProtoWEP40)
    {
        clxConsoleUIEngineText("%sWEP40", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProtoWEP104)
    {
        clxConsoleUIEngineText("%sWEP104", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProtoTKIP)
    {
        clxConsoleUIEngineText("%sTKIP", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProtoAES_CCMP)
    {
        clxConsoleUIEngineText("%sCCMP", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_Proprietary)
    {
        clxConsoleUIEngineText("%sProprietary", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_CCMP_256)
    {
        clxConsoleUIEngineText("%sCCMP_256", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_BIP_CMAC_128)
    {
        clxConsoleUIEngineText("%sBIP_CMAC_128", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_GCMP_128)
    {
        clxConsoleUIEngineText("%sGCMP_128", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_GCMP_256)
    {
        clxConsoleUIEngineText("%sGCMP_256", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_BIP_GMAC_128)
    {
        clxConsoleUIEngineText("%sBIP_GMAC_128", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_BIP_GMAC_256)
    {
        clxConsoleUIEngineText("%sBIP_GMAC_256", separator(firstItem));
        firstItem = FALSE;
    }
    if (value & (u4)ClxEncProto_BIP_CMAC_256)
    {
        clxConsoleUIEngineText("%sBIP_CMAC_256", separator(firstItem));
        firstItem = FALSE;
    }
    CLX_TE_RESET_COLOR;

    clxConsoleUIEngineText("\n");
}


#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
void clxWlanPrintDetailedMeshPacketStatistics(const ClxWlanMeshPacketStatsTLV* tlv, boolean downlink)
{
    if (downlink)
    {
        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_DOWNLINK_PACKET_STATISTICS, 1);
    }
    else
    {
        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_UPLINK_PACKET_STATISTICS, 1);
    }

    {
        CLX_TE_SET_COLOR(SkyBlue); printIndentedString("\n", "{\n", 2);

        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MEASUREMENT_PERIOD, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u Seconds\n", tlv->measurementTime / 1000); CLX_TE_RESET_COLOR;
        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_TX_PACKET_ERRORS, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", tlv->txPacketErrors); CLX_TE_RESET_COLOR;
        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_TRANSMITTED_PACKETS, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", tlv->transmittedPackets); CLX_TE_RESET_COLOR;
        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_RX_PACKET_ERRORS, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", tlv->rxPacketErrors); CLX_TE_RESET_COLOR;
        printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_PACKETS_RECEIVED, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", tlv->packetsReceived); CLX_TE_RESET_COLOR;

        CLX_TE_SET_COLOR(SkyBlue); printIndentedString(NULL, "}\n", 2);
    }
}

void clxWlanPrintDetailedMeshInfo(const ClxWlanMeshIE* meshIE)
{
    ClxWlanMeshNodeInfo meshNodeInfo;

    if (clxWlanMeshDecodeMeshBssIE(meshIE, &meshNodeInfo))
    {
        printItemTitle(ITEM_TITLE_CLARINOX_MESH_NODE_INFORMATION);

        CLX_TE_SET_COLOR(SkyBlue); printIndentedString("\n", "{\n", 1);

        if (meshNodeInfo.meshID.base.initialized)
        {
            printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MESH_ID, 1); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%s\n", meshNodeInfo.meshID.field.value); CLX_TE_RESET_COLOR;
        }

        if (meshNodeInfo.alMacAddress.base.initialized)
        {
            printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_AL_MAC_ADDRESS, 1);

            SET_ITEM_VALUE_COLOR;
            clxConsoleUIEngineText("%02X:%02X:%02X:%02X:%02X:%02X\n",
                meshNodeInfo.alMacAddress.field[0],
                meshNodeInfo.alMacAddress.field[1],
                meshNodeInfo.alMacAddress.field[2],
                meshNodeInfo.alMacAddress.field[3],
                meshNodeInfo.alMacAddress.field[4],
                meshNodeInfo.alMacAddress.field[5]);
            CLX_TE_RESET_COLOR;
        }

        if (meshNodeInfo.downlinkInfo.base.initialized)
        {
            clxConsoleUIEngineText("\n");
            printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_DOWNLINK_INFORMATION, 1);

            {
                CLX_TE_SET_COLOR(SkyBlue); printIndentedString("\n", "{\n", 2);

                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MAX_NUM_OF_CLIENTS, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", meshNodeInfo.downlinkInfo.maxNumberOfClients); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_CURRENT_NUM_OF_CLIENTS, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", meshNodeInfo.downlinkInfo.currentNumberOfClients); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MAX_TX_SUPPORTED_RATE, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u Mbps\n", meshNodeInfo.downlinkInfo.maxTxSupportedRate); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MAX_RX_SUPPORTED_RATE, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u Mbps\n", meshNodeInfo.downlinkInfo.maxRxSupportedRate); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_OPERATING_CHANNEL, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", meshNodeInfo.downlinkInfo.channel.channelNo); CLX_TE_RESET_COLOR;

                CLX_TE_SET_COLOR(SkyBlue); printIndentedString(NULL, "}\n", 2);
            }
        }

        if (meshNodeInfo.uplinkConnectionInfo.base.initialized)
        {
            clxConsoleUIEngineText("\n");
            printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_UPLINK_CONNECTION_INFORMATION, 1);

            {
                CLX_TE_SET_COLOR(SkyBlue); printIndentedString("\n", "{\n", 2);

                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_PARENT_AL_MAC_ADDRESS, 2);

                SET_ITEM_VALUE_COLOR;
                clxConsoleUIEngineText("%02X:%02X:%02X:%02X:%02X:%02X\n",
                    meshNodeInfo.uplinkConnectionInfo.parentALMacAddress[0],
                    meshNodeInfo.uplinkConnectionInfo.parentALMacAddress[1],
                    meshNodeInfo.uplinkConnectionInfo.parentALMacAddress[2],
                    meshNodeInfo.uplinkConnectionInfo.parentALMacAddress[3],
                    meshNodeInfo.uplinkConnectionInfo.parentALMacAddress[4],
                    meshNodeInfo.uplinkConnectionInfo.parentALMacAddress[5]);
                CLX_TE_RESET_COLOR;


                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_PARENT_BSSID, 2);

                SET_ITEM_VALUE_COLOR;
                clxConsoleUIEngineText("%02X:%02X:%02X:%02X:%02X:%02X\n",
                    meshNodeInfo.uplinkConnectionInfo.parentBSSID[0],
                    meshNodeInfo.uplinkConnectionInfo.parentBSSID[1],
                    meshNodeInfo.uplinkConnectionInfo.parentBSSID[2],
                    meshNodeInfo.uplinkConnectionInfo.parentBSSID[3],
                    meshNodeInfo.uplinkConnectionInfo.parentBSSID[4],
                    meshNodeInfo.uplinkConnectionInfo.parentBSSID[5]);
                CLX_TE_RESET_COLOR;


                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_HOPS_TO_ROOT_NODE, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", meshNodeInfo.uplinkConnectionInfo.hopsToRoot); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MAX_TX_SUPPORTED_RATE, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u Mbps\n", meshNodeInfo.uplinkConnectionInfo.maxTxSupportedRate); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_MAX_RX_SUPPORTED_RATE, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u Mbps\n", meshNodeInfo.uplinkConnectionInfo.maxRxSupportedRate); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_AVERAGE_RSSI, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%d dBm\n", (s4)meshNodeInfo.uplinkConnectionInfo.rssi); CLX_TE_RESET_COLOR;
                printSubitemTitle(ITEM_MESH_SUBITEM_TITLE_OPERATING_CHANNEL, 2); SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u\n", meshNodeInfo.uplinkConnectionInfo.channel.channelNo); CLX_TE_RESET_COLOR;

                CLX_TE_SET_COLOR(SkyBlue); printIndentedString(NULL, "}\n", 2);
            }
        }

        if (meshNodeInfo.downlinkPacketStats.base.initialized)
        {
            clxConsoleUIEngineText("\n");
            clxWlanPrintDetailedMeshPacketStatistics(&meshNodeInfo.downlinkPacketStats, TRUE);
        }

        if (meshNodeInfo.uplinkPacketStats.base.initialized)
        {
            clxConsoleUIEngineText("\n");
            clxWlanPrintDetailedMeshPacketStatistics(&meshNodeInfo.uplinkPacketStats, FALSE);
        }

        CLX_TE_SET_COLOR(SkyBlue); printIndentedString(NULL, "}\n", 1);
    }
}
#endif /* #if defined(CLARINOX_WLAN_MESH_SUPPORTED) */



/*******************************************************************************************************************************
* 
*                                                       clxWlanPrintDetailedBssInfo
*
* Prints out the BSS information in details.
*
*******************************************************************************************************************************/
void clxWlanPrintDetailedBssInfo(ClxBSSInfo* bss, u4 index)
{
    bss->ssid.value[bss->ssid.len] = '\0';
 
    CLX_TE_SET_COLOR(Yellow);  clxConsoleUIEngineText("\n%u. ", index);
    CLX_TE_SET_COLOR(SkyBlue); clxConsoleUIEngineText("%s : ", ITEM_TITLE_SSID);
    CLX_TE_SET_COLOR(Brown);   clxConsoleUIEngineText("%s\n", (bss->ssid.len > 0) ? (s1*)bss->ssid.value : "<Wildcard SSID>");
    CLX_TE_SET_COLOR(SkyBlue); clxConsoleUIEngineText("{\n");

    CLX_TE_RESET_COLOR;

    printItemTitle(ITEM_TITLE_BSSID);

    SET_ITEM_VALUE_COLOR;
    clxConsoleUIEngineText("%02X:%02X:%02X:%02X:%02X:%02X\n",
        bss->bssid[0],
        bss->bssid[1],
        bss->bssid[2],
        bss->bssid[3],
        bss->bssid[4],
        bss->bssid[5]);
    CLX_TE_RESET_COLOR;

    printItemTitle(ITEM_TITLE_PRIMARY_CHANNEL);     SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%u (%s)\n", (u4)bss->channel, ((bss->band == ClxWlanFreqBand5GHz) ? "5 GHz" : "2.4 GHz")); CLX_TE_RESET_COLOR;
    printItemTitle(ITEM_TITLE_SIGNAL_POWER_LEVEL);  SET_ITEM_VALUE_COLOR; clxConsoleUIEngineText("%d dBm\n", (s4)bss->rssi); CLX_TE_RESET_COLOR;

    printSupportedAuthSuites(bss->authType);
    printSupportedCipherSuites(bss->encProtocol);

    if (bss->capabilities & CLX_WLAN_CAPABILITY_HT_SUPPORTED)
    {
        printItemTitle(ITEM_TITLE_HT_CHANNEL_BW);

        SET_ITEM_VALUE_COLOR;
        switch (bss->htInfo.bss.channelBW)
        {
        case ClxWlanChannelBandwidth_20:    
            clxConsoleUIEngineText("20 MHz\n");
            break;
        case ClxWlanChannelBandwidth_40_Below:
            clxConsoleUIEngineText("40 MHz (Secondary Channel : %u)\n", (u4)bss->channel - (HT_SECONDARY_CHANNEL_BADNWIDTH / BASE_IEEE802_11_CHANNEL_SPACING));
            break;
        case ClxWlanChannelBandwidth_40_Above:
            clxConsoleUIEngineText("40 MHz (Secondary Channel : %u)\n", (u4)bss->channel + (HT_SECONDARY_CHANNEL_BADNWIDTH / BASE_IEEE802_11_CHANNEL_SPACING));
            break;
        default:
            clxConsoleUIEngineText("N/A\n");
            break;
        }
        CLX_TE_RESET_COLOR;

        printSupportedHtMcsGroups(&bss->htInfo);
    }

    if (bss->capabilities & CLX_WLAN_CAPABILITY_VHT_SUPPORTED)
    {
        printItemTitle(ITEM_TITLE_SUPPORTED_VHT_CHANNEL_BW);

        SET_ITEM_VALUE_COLOR;
        switch (bss->vhtInfo.bss.channelBW)
        {
        case ClxWlanChannelBandwidth_20:
            clxConsoleUIEngineText("20 MHz\n");
            break;
        case ClxWlanChannelBandwidth_40_Below:
        case ClxWlanChannelBandwidth_40_Above:
            clxConsoleUIEngineText("40 MHz (Center Channel : %u)\n", bss->vhtInfo.bss.channel0);
            break;
        case ClxWlanChannelBandwidth_80:   
            clxConsoleUIEngineText("80 MHz (Center Channel : %u)\n", bss->vhtInfo.bss.channel0);
            break;
        case ClxWlanChannelBandwidth_160:  
            clxConsoleUIEngineText("160 MHz (Center Channel : %u)\n", bss->vhtInfo.bss.channel0);
            break;
        case ClxWlanChannelBandwidth_80_80:
            clxConsoleUIEngineText("80+80 MHz (Center Channels : %u and %u)\n", bss->vhtInfo.bss.channel0, bss->vhtInfo.bss.channel1);
            break;
        default:
            clxConsoleUIEngineText("N/A\n");
            break;
        }
        CLX_TE_RESET_COLOR;

        printItemTitle(ITEM_TITLE_SUPPORTED_VHT_RX_RATES); SET_ITEM_VALUE_COLOR; printSupportedVHtMcs(bss->vhtInfo.rxMcsSet); CLX_TE_RESET_COLOR;
        printItemTitle(ITEM_TITLE_SUPPORTED_VHT_TX_RATES); SET_ITEM_VALUE_COLOR; printSupportedVHtMcs(bss->vhtInfo.txMcsSet); CLX_TE_RESET_COLOR;
    }

    if (bss->capabilities & CLX_WLAN_CAPABILITY_HE_SUPPORTED)
    {
        printItemTitle(ITEM_TITLE_SUPPORTED_HE_CHANNEL_BW);

        SET_ITEM_VALUE_COLOR;
        switch (bss->heInfo.supportedBW)
        {
        case ClxWlanHESupportedBandwidth_40_2_4G:
            clxConsoleUIEngineText("20 MHz and 40 MHz channels in 2.4 GHz band\n");
            break;
        case ClxWlanHESupportedBandwidth_80:
            clxConsoleUIEngineText("20, 40, and 80 MHz channels in 5 GHz / 6 GHz bands\n");
            break;
        case ClxWlanHESupportedBandwidth_160:
            clxConsoleUIEngineText("Contiguous 160 MHz channels\n");
            break;
        case ClxWlanHESupportedBandwidth_80_80:
            clxConsoleUIEngineText("Non-contiguous 80+80 MHz channels\n");
            break;
        default:
            clxConsoleUIEngineText("N/A\n");
            break;
        }
        CLX_TE_RESET_COLOR;
    }

    printItemTitle(ITEM_TITLE_PROTECTED_MGMT_FRAMES);

    SET_ITEM_VALUE_COLOR;
    switch (bss->pmf)
    {
    case ClxWlanPmfPolicy_Disabled:
        clxConsoleUIEngineText("Not Supported\n");
        break;
    case ClxWlanPmfPolicy_Capable:
        clxConsoleUIEngineText("Supported\n");
        break;
    case ClxWlanPmfPolicy_Required:
        clxConsoleUIEngineText("Supported, Required\n");
        break;
    default:
        clxConsoleUIEngineText("?\n");
        break;
    }
    CLX_TE_RESET_COLOR;

#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
    if (bss->meshBssIE)
    {
        clxWlanPrintDetailedMeshInfo(bss->meshBssIE);
    }
#endif

    CLX_TE_SET_COLOR(SkyBlue); clxConsoleUIEngineText("}\n");

    CLX_TE_RESET_COLOR;
}

