// # BSP SD DiskIO
// ## Description
// Functions for handling DiskIO via SDMMC
//
// These are usually configured through the FatFS driver/interface,
// and won't need to be accessed directly often.
//
#pragma once
#ifndef DSY_BSP_SD_DISKIO_H
#define DSY_BSP_SD_DISKIO_H
#include <stdint.h>

// ## DataStructures
// 
// This struct is identical to the struct provided as "HAL_SD_CardInfoTypeDef"
// I'm using this to allow users to link to the fatfs middleware without having to then link in the entire HAL to their project.
// ~~~~
typedef struct
{
    uint32_t CardType; /*!< Specifies the card Type                         */

    uint32_t
        CardVersion; /*!< Specifies the card version                      */

    uint32_t Class; /*!< Specifies the class of the card class           */

    uint32_t RelCardAdd; /*!< Specifies the Relative Card Address            */

    uint32_t BlockNbr; /*!< Specifies the Card Capacity in blocks           */

    uint32_t BlockSize; /*!< Specifies one block size in bytes               */

    uint32_t
        LogBlockNbr; /*!< Specifies the Card logical Capacity in blocks   */

    uint32_t
        LogBlockSize; /*!< Specifies logical block size in bytes           */

    uint32_t CardSpeed; /*!< Specifies the card Speed                        */

} DSY_SD_CardInfoTypeDef;
// ~~~~

// ## SD Related Defines
// ~~~~
#define BSP_SD_CardInfo DSY_SD_CardInfoTypeDef
#define MSD_OK ((uint8_t)0x00)
#define MSD_ERROR ((uint8_t)0x01)
#define MSD_ERROR_SD_NOT_PRESENT ((uint8_t)0x02)
#define SD_TRANSFER_OK ((uint8_t)0x00)
#define SD_TRANSFER_BUSY ((uint8_t)0x01)
#define SD_PRESENT ((uint8_t)0x01)
#define SD_NOT_PRESENT ((uint8_t)0x00)
#define SD_DATATIMEOUT ((uint32_t)100000000)
// ~~~~

// Functions internal for diskIO
// ~~~~
uint8_t BSP_SD_Init(void);
uint8_t BSP_SD_ITConfig(void);
uint8_t BSP_SD_ReadBlocks(uint32_t *pData,
                          uint32_t  ReadAddr,
                          uint32_t  NumOfBlocks,
                          uint32_t  Timeout);
uint8_t BSP_SD_WriteBlocks(uint32_t *pData,
                           uint32_t  WriteAddr,
                           uint32_t  NumOfBlocks,
                           uint32_t  Timeout);
uint8_t
        BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData,
                               uint32_t  WriteAddr,
                               uint32_t  NumOfBlocks);
uint8_t BSP_SD_Erase(uint32_t StartAddr, uint32_t EndAddr);
uint8_t BSP_SD_GetCardState(void);
void    BSP_SD_GetCardInfo(BSP_SD_CardInfo *CardInfo);
uint8_t BSP_SD_IsDetected(void);
// ~~~~

// These functions can be modified in case the current settings (e.g. DMA stream)
//   need to be changed for specific application needs
// ~~~~
void BSP_SD_AbortCallback(void);
void BSP_SD_WriteCpltCallback(void);
void BSP_SD_ReadCpltCallback(void);
// ~~~~

#endif
