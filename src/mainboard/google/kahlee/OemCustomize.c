/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015-2016 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <chip.h>
#include <amdblocks/agesawrapper.h>
#include <boardid.h>
#include <gpio.h>
#include <console/console.h>
#include <soc/pci_devs.h>

#define DIMMS_PER_CHANNEL 1
#if DIMMS_PER_CHANNEL > MAX_DIMMS_PER_CH
#error "Too many DIMM sockets defined for the mainboard"
#endif

static const PSO_ENTRY DDR4PlatformMemoryConfiguration[] = {
	DRAM_TECHNOLOGY(ANY_SOCKET, DDR4_TECHNOLOGY),
	NUMBER_OF_DIMMS_SUPPORTED(ANY_SOCKET, ANY_CHANNEL, DIMMS_PER_CHANNEL),
	NUMBER_OF_CHANNELS_SUPPORTED(ANY_SOCKET, MAX_DRAM_CH),
	MOTHER_BOARD_LAYERS(LAYERS_6),
	MEMCLK_DIS_MAP(ANY_SOCKET, ANY_CHANNEL,
				0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00),
	CKE_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0xff, 0xff, 0xff, 0xff),
	ODT_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0xff, 0xff, 0xff, 0xff),
	CS_TRI_MAP(ANY_SOCKET, ANY_CHANNEL,
				0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00),
	PSO_END
};
/* Liara-specific 2T memory configuration */
static const PSO_ENTRY DDR4LiaraMemoryConfiguration[] = {
	DRAM_TECHNOLOGY(ANY_SOCKET, DDR4_TECHNOLOGY),
	NUMBER_OF_DIMMS_SUPPORTED(ANY_SOCKET, ANY_CHANNEL, DIMMS_PER_CHANNEL),
	NUMBER_OF_CHANNELS_SUPPORTED(ANY_SOCKET, MAX_DRAM_CH),
	MOTHER_BOARD_LAYERS(LAYERS_6),
	MEMCLK_DIS_MAP(ANY_SOCKET, ANY_CHANNEL,
				0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00),
	CKE_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0xff, 0xff, 0xff, 0xff),
	ODT_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0xff, 0xff, 0xff, 0xff),
	CS_TRI_MAP(ANY_SOCKET, ANY_CHANNEL,
				0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00),
	TBLDRV_CONFIG_TO_OVERRIDE(DIMMS_PER_CHANNEL, ANY_SPEED, VOLT_ANY_,
	ANY_),
	TBLDRV_CONFIG_ENTRY_SLOWACCMODE(1),
	PSO_END
};

void OemPostParams(AMD_POST_PARAMS *PostParams)
{
	if (IS_ENABLED(CONFIG_BOARD_GOOGLE_LIARA))
		PostParams->MemConfig.PlatformMemoryConfiguration =
			(PSO_ENTRY *)DDR4LiaraMemoryConfiguration;
	else
		PostParams->MemConfig.PlatformMemoryConfiguration =
			(PSO_ENTRY *)DDR4PlatformMemoryConfiguration;
	/*
	 * Bank interleaving is enabled by default in AGESA. However, from AMD's
	 * explanation, bank interleaving is really chip select interleave,
	 * requiring 2 chip select arriving to the DIMM (rank interleaving). As
	 * both kahlee and grunt are hardware limited to a single chip select
	 * arriving at the DIMM, interleave will not work. This causes AGESA to
	 * throw a warning. To avoid the warning, interleaving needs to be
	 * disabled.
	 */
	PostParams->MemConfig.EnableBankIntlv = FALSE;
}

void set_board_env_params(GNB_ENV_CONFIGURATION *params)
{
	const struct soc_amd_stoneyridge_config *cfg;
	const struct device *dev = dev_find_slot(0, GNB_DEVFN);
	if (!dev || !dev->chip_info) {
		printk(BIOS_WARNING, "Warning: Cannot find SoC devicetree config\n");
		return;
	}
	cfg = dev->chip_info;
	if (cfg->lvds_poseq_blon_to_varybl && cfg->lvds_poseq_varybl_to_blon) {
		/*
		 * GPIO 133 - Backlight enable (active low)
		 * Pass control of the backlight to the video BIOS
		 */
		gpio_set(GPIO_133, 0);
		printk(BIOS_INFO, "Change panel init timing\n");
		params->LvdsPowerOnSeqVaryBlToBlon =
			cfg->lvds_poseq_varybl_to_blon;
		params->LvdsPowerOnSeqBlonToVaryBl =
			cfg->lvds_poseq_blon_to_varybl;
		printk(BIOS_INFO, "LvdsPowerOnSeqVaryBlToBlon: %dms\n",
			(params->LvdsPowerOnSeqVaryBlToBlon)*4);
		printk(BIOS_INFO, "LvdsPowerOnSeqBlonToVaryBl: %dms\n",
			(params->LvdsPowerOnSeqBlonToVaryBl)*4);
	}
	params->EDPv1_4VSMode = EDP_VS_HIGH_VDIFF_MODE;
}
