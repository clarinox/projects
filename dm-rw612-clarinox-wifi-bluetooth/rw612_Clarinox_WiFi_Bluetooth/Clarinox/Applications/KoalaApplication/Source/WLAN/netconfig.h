/**

  */

#ifndef __NETCONFIG_H
#define __NETCONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Static IP Address definition ***********************************************/
#define IP_ADDR0 10//172//172// 192
#define IP_ADDR1  0//16//16// 168
#define IP_ADDR2  0//0//1
#define IP_ADDR3  3
   
/* NETMASK definition *********************************************************/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255//0//255
#define NETMASK_ADDR3   0

/* Gateway Address definition *************************************************/
#define GW_ADDR0  10//172//172//192
#define GW_ADDR1  0//16//16//168
#define GW_ADDR2  0//0//0//1
#define GW_ADDR3  1//100//0//1
 
#define DHCP_START_ADDR0   10
#define DHCP_START_ADDR1   0
#define DHCP_START_ADDR2   0
#define DHCP_START_ADDR3   4

#ifdef __cplusplus
}
#endif

#endif /* __NETCONFIG_H */


/*****END OF FILE****/

