#include "main.h"
#include "cmsis_os.h"

#define StartSettingsAddres 0x08007C00


void flash_write(uint32_t address,uint32_t data);
void FLASH_WriteSettings(settings_t params, uint32_t pageAdr);
void Flash_ReadParams(settings_t *params, uint32_t adr);


void flash_lock(void);
void flash_unlock(void);
void flash_erase_page(uint32_t address);
uint8_t flash_ready(void);