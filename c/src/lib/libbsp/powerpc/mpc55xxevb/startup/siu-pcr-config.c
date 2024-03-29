/**
 * @file
 *
 * @ingroup mpc55xx
 *
 * @brief MPC55XX SIU PCR configuration.
 */

/*
 * Copyright (c) 2008-2011 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 * $Id: siu-pcr-config.c,v 1.1 2011/08/31 16:03:10 sh Exp $
 */

#include <bsp/mpc55xx-config.h>
#include <bsp/start.h>
#include <bsp.h>

const BSP_START_TEXT_SECTION mpc55xx_siu_pcr_config_entry
mpc55xx_siu_pcr_config [] = {
#if defined(MPC55XX_BOARD_GWLCFM)
  {  0,16,{.B.PA = 1,           .B.WPE = 0}}, /* PA[ 0..15] analog input */
  { 16, 4,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PB[ 0.. 4] LED/CAN_STBN out */
  { 20, 2,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PB[ 5.. 6] CAN_ERR/USBFLGC in*/
  { 22, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PB[ 7    ] FR_A_EN out */
  { 23, 4,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PB[ 8..10] IRQ/FR_A_ERR/USB_RDYin */
  { 27, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PB[11..11] FR_STBN out */

  { 32, 2,{.B.PA = 2,.B.OBE = 1,.B.WPE = 0}}, /* PC[ 0.. 1] FR_A_TX/TXEN out */
  { 34, 1,{.B.PA = 2,.B.IBE = 1,.B.WPE = 0}}, /* PC[ 2.. 2] FR_A_RX in */
  { 35, 2,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PC[ 3.. 4] INIT_ERR/ISB_IRQ in */
  { 37, 2,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PC[ 5.. 6] PWRO1/2_ON out */
  { 39, 1,{.B.PA = 2,.B.IBE = 1,.B.WPE = 0}}, /* PC[ 7.. 7] FR_B_RX in */
  { 40, 2,{.B.PA = 2,.B.OBE = 1,.B.WPE = 0}}, /* PC[ 8.. 9] FR_B_TX/TXEN out */
  { 42, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PC[10    ] FR_B_EN out */
  { 43, 1,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PC[11    ] FOR_STATUS in */
  { 44, 1,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PC[12    ] FR_B_ERRN  in */
  { 45, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PC[13    ] HS_CAN_STBN out */
  { 46, 1,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PC[14    ] HS_CAN_ERR in */
  { 47, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PC[15    ] HS_CAN_EN out */

  { 48, 1,{.B.PA = 1,.B.OBE = 1,.B.WPE = 0}}, /* PD[ 0    ] HS_CAN_TX out */
  { 49, 1,{.B.PA = 1,.B.IBE = 1,.B.WPE = 0}}, /* PD[ 1    ] HS_CAN_RX in  */
  { 50, 2,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PD[ 2.. 3] PWRO1/2_OC in */
  { 52, 1,{.B.PA = 1,.B.OBE = 1,.B.WPE = 0}}, /* PD[ 4    ] LS_CAN_TX out */
  { 53, 1,{.B.PA = 1,.B.IBE = 1,.B.WPE = 0}}, /* PD[ 5    ] LS_CAN_RX in  */
  { 54, 1,{.B.PA = 1,.B.OBE = 1,.B.WPE = 0}}, /* PD[ 6    ] HS_CAN_TX out */
  { 55, 1,{.B.PA = 1,.B.IBE = 1,.B.WPE = 0}}, /* PD[ 7    ] HS_CAN_RX in  */
  { 56, 1,{.B.PA = 2,.B.IBE = 1,.B.OBE = 1,.B.WPE = 0}}, 
  /* PD[ 8    ] I2C_SCL in/out */
  { 57, 1,{.B.PA = 2,.B.IBE = 1,.B.OBE = 1,.B.WPE = 0}}, 
  /* PD[ 9    ] I2C_SDA in/out */
  
  { 58, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PD[10] LS_CAN_EN     out*/
  { 59, 3,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, 
  /* PD[11..13] PWO1_OC, MOCO_INT in */
  
  { 62, 4,{.B.PA = 0,.B.IBE = 1,.B.WPE = 0}}, /* PD[14..15] USB_FLGA/B    in */

  { 64, 5,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PE[ 0.. 4] LED_EXT1-5.   out*/
  { 70, 1,{.B.PA = 1,.B.SRC = 3,.B.WPE = 0}}, /* PE[ 6.. 6] CLKOUT        out*/

  { 80, 1,{.B.PA = 1,.B.SRC = 1,.B.WPE = 0}}, /* PF[ 0.. 0] RD_WR         out*/
  { 81, 1,{.B.PA = 0,.B.SRC = 0,.B.WPE = 0}}, /* PF[ 1.. 1] (nc)          in */
  { 82, 8,{.B.PA = 2,.B.SRC = 1,.B.WPE = 0}}, /* PF[ 2..11] ADDR[8..15]   out*/
  { 90, 2,{.B.PA = 1,.B.SRC = 1,.B.WPE = 0}}, /* PF[ 2..11] CS[0..1]      out*/
  { 92, 1,{.B.PA = 3,.B.SRC = 3,.B.WPE = 0}}, /* PF[    12] ALE           out*/
  { 93, 3,{.B.PA = 1,.B.SRC = 1,.B.WPE = 0}}, /* PF[13..15] OE/WE         out*/

  { 96,16,{.B.PA = 1,.B.SRC = 1,.B.WPE = 0}}, /* PG[ 0..15] AD16..31   in/out*/

  {113, 1,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PH[ 1.. 1] RES_MOSTComp  out*/
  {114, 1,{.B.PA = 3,.B.OBE = 1,.B.WPE = 0}}, /* PH[ 2.. 2] CS3_MOSTComp  out*/
  {115, 1,{.B.PA = 3,.B.OBE = 1,.B.WPE = 0}}, /* PH[ 3.. 3] CS2_ETH       out*/
  {116, 2,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}}, /* PH[ 4.. 5] FR/HC_TERM    out*/
  {118, 1,{.B.PA = 2,.B.OBE = 1,.B.WPE = 0}}, /* PH[ 6.. 6] LIN_Tx        out*/
  {119, 1,{.B.PA = 2,.B.IBE = 1,.B.WPE = 0}}, /* PH[ 7.. 7] LIN_Rx        in */
  {120, 4,{.B.PA = 0,.B.OBE = 1,.B.WPE = 0}} /* PH[ 8..11] LIN_SLP,RST   out*/
#elif defined(MPC55XX_BOARD_PHYCORE_MPC5554)
  {  0, 4,{.B.PA = 1,          .B.DSC = 1,.B.WPE=1,.B.WPS=1}}, /* !CS  [0:3]    */
  {  4,24,{.B.PA = 1,          .B.DSC = 1                  }}, /* ADDR [8 : 31] */
  { 28,32,{.B.PA = 1,          .B.DSC = 1                  }}, /* DATA [0 : 31] */
  { 60, 4,{.B.PA = 1,          .B.DSC = 1,                 }}, /* TSIZ[0:1], RD_!WR, BDIP */
  { 64, 6,{.B.PA = 1,          .B.DSC = 1,.B.WPE=1,.B.WPS=1}}, /* RD_!WR, BDIP, !WE, !OE, !TS */
  { 89, 4,{.B.PA = 1                                       }}, /* ESCI_A and ESCI_B        */
  {229, 4,{          .B.OBE= 1,.B.DSC = 1                  }} /* CLKOUT */
#elif defined(MPC55XX_BOARD_MPC5566EVB)
  {  0, 1,{.B.PA = 1,.B.DSC = 1,.B.WPE=1,.B.WPS=1}}, /* !CS  [0]      */
  {  3, 1,{.B.PA = 1,.B.DSC = 1,.B.WPE=1,.B.WPS=1}}, /* !CS  [3]      */
  {  4,24,{.B.PA = 1,.B.DSC = 1                  }}, /* ADDR [8 : 31] */
  { 28,16,{.B.PA = 1,.B.DSC = 1                  }}, /* DATA [0 : 15] */
  { 62, 8,{.B.PA = 1,.B.DSC = 1,.B.WPE=1,.B.WPS=1}}, /* RD_!WR, BDIP, 
							!WE, !OE, !TS */
  { 89, 2,{.B.PA = 1                             }} /* ESCI_B        */
#elif defined(MPC55XX_BOARD_MPC5674FEVB)
  {  89,  2, { .B = { .PA = 1 } } }, /* ESCI_A */
  { 256,  1, { .B = { .PA = 1, .DSC = 1 } } }, /* D_CS0 */
  { 257,  1, { .B = { .PA = 2, .DSC = 1 } } }, /* D_ADD_DAT31 */
  { 259,  4, { .B = { .PA = 1, .DSC = 1 } } }, /* D_ADD12 .. D_ADD15 */
  { 263, 15, { .B = { .PA = 2, .DSC = 1 } } }, /* D_ADD_DAT16 .. D_ADD_DAT30 */
  { 278, 16, { .B = { .PA = 1, .DSC = 1 } } }, /* D_ADD_DAT0 .. D_ADD_DAT15 */
  { 294,  6, { .B = { .PA = 1, .DSC = 1 } } }, /* D_RD_WR, D_WE0, D_WE1, D_OE, D_TS, D_ALE */
  { 302,  6, { .B = { .PA = 1, .DSC = 1 } } } /* D_BDIP, D_WE2, D_WE3, D_ADD9 .. D_ADD11 */
#endif
};

const BSP_START_TEXT_SECTION size_t mpc55xx_siu_pcr_config_count [] = {
  sizeof(mpc55xx_siu_pcr_config) / sizeof(mpc55xx_siu_pcr_config [0])
};
