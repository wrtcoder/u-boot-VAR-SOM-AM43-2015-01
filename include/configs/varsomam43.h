/*
 * am43xx_evm.h
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_AM43XX_EVM_H
#define __CONFIG_AM43XX_EVM_H

#define CONFIG_AM43XX

#define CONFIG_CMD_FAT
#define CONFIG_CMD_SAVEENV

#define CONFIG_BOARD_LATE_INIT
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_SYS_CACHELINE_SIZE       32
#define CONFIG_MAX_RAM_BANK_SIZE	(1024 << 20)	/* 1GB */
#define CONFIG_SYS_TIMERBASE		0x48040000	/* Use Timer2 */

#include <asm/arch/omap.h>

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		48000000

/* I2C Configuration */
#define CONFIG_CMD_EEPROM
#define CONFIG_ENV_EEPROM_IS_ON_I2C
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* Main EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2
#define CONFIG_SYS_I2C_MULTI_EEPROMS

/* Power */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_TPS65218
#define CONFIG_POWER_TPS62362

/* SPL defines. */
#define CONFIG_SPL_TEXT_BASE		0x40300350
#define CONFIG_SPL_MAX_SIZE		(220 << 10)	/* 220KB */
#define CONFIG_SYS_SPL_ARGS_ADDR	(CONFIG_SYS_SDRAM_BASE + \
					 (128 << 20))
#define CONFIG_SPL_POWER_SUPPORT
#define CONFIG_SPL_YMODEM_SUPPORT

/* Enabling L2 Cache */
#define CONFIG_SYS_L2_PL310
#define CONFIG_SYS_PL310_BASE	0x48242000
#define CONFIG_SYS_CACHELINE_SIZE	32

/*
 * Since SPL did pll and ddr initialization for us,
 * we don't need to do it twice.
 */
#if !defined(CONFIG_SPL_BUILD) && !defined(CONFIG_QSPI_BOOT)
#define CONFIG_SKIP_LOWLEVEL_INIT
#endif

/*
 * When building U-Boot such that there is no previous loader
 * we need to call board_early_init_f.  This is taken care of in
 * s_init when we have SPL used.
 */
#if !defined(CONFIG_SKIP_LOWLEVEL_INIT) && !defined(CONFIG_SPL)
#define CONFIG_BOARD_EARLY_INIT_F
#endif

/* Now bring in the rest of the common code. */
#include <configs/ti_armv7_common.h>

/* Always 64 KiB env size */
#define CONFIG_ENV_SIZE			(64 << 10)

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000	/* Base EVM has UART0 */

#define CONFIG_ENV_IS_IN_FAT
#define FAT_ENV_INTERFACE		"mmc"
#define FAT_ENV_DEVICE_AND_PART		"0:1"
#define FAT_ENV_FILE			"uboot.env"
#define CONFIG_FAT_WRITE

#define CONFIG_SPL_LDSCRIPT		"$(CPUDIR)/omap-common/u-boot-spl.lds"

/* SPL USB Support */
#define CONFIG_SPL_USB_SUPPORT
#define CONFIG_SPL_USB_HOST_SUPPORT
#define CONFIG_SYS_USB_FAT_BOOT_PARTITION		1

#define CONFIG_CMD_USB
#define CONFIG_USB_HOST
#define CONFIG_USB_XHCI
#define CONFIG_USB_XHCI_OMAP
#define CONFIG_USB_STORAGE
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 2

#define CONFIG_OMAP_USB_PHY
#define CONFIG_AM437X_USB2PHY2_HOST

#ifdef CONFIG_QSPI_BOOT
#define CONFIG_SYS_TEXT_BASE           0x30000000
#undef CONFIG_ENV_IS_IN_FAT
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_SPI_MAX_HZ           CONFIG_SF_DEFAULT_SPEED
#define CONFIG_ENV_SECT_SIZE           (64 << 10) /* 64 KB sectors */
#define CONFIG_ENV_OFFSET              0x110000
#define CONFIG_ENV_OFFSET_REDUND       0x120000
#ifdef MTDIDS_DEFAULT
#undef MTDIDS_DEFAULT
#endif
#ifdef MTDPARTS_DEFAULT
#undef MTDPARTS_DEFAULT
#endif
#define MTDPARTS_DEFAULT		"mtdparts=qspi.0:512k(QSPI.u-boot)," \
					"512k(QSPI.u-boot.backup)," \
					"512k(QSPI.u-boot-spl-os)," \
					"64k(QSPI.u-boot-env)," \
					"64k(QSPI.u-boot-env.backup)," \
					"8m(QSPI.kernel)," \
					"-(QSPI.file-system)"
#endif

/* SPI */
#undef CONFIG_OMAP3_SPI
#define CONFIG_TI_QSPI
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_MACRONIX
#define CONFIG_CMD_SF
#define CONFIG_CMD_SPI
#define CONFIG_TI_SPI_MMAP
#define CONFIG_SPI_FLASH_BAR
#define CONFIG_QSPI_SEL_GPIO                   48
#define CONFIG_SF_DEFAULT_SPEED                48000000
#define CONFIG_DEFAULT_SPI_MODE                SPI_MODE_3

/* Enhance our eMMC support / experience. */
#define CONFIG_CMD_GPT
#define CONFIG_EFI_PARTITION

#ifndef CONFIG_SPL_BUILD
#define CONFIG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	"fdtfile=var-som-am43.dtb\0" \
	"bootpart=0:2\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"console=ttyO0,115200n8\0" \
	"partitions=" \
		"uuid_disk=${uuid_gpt_disk};" \
		"name=rootfs,start=2MiB,size=-,uuid=${uuid_gpt_rootfs}\0" \
	"optargs=\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p2 rw\0" \
	"mmcrootfstype=ext4 rootwait\0" \
	"usbroot=/dev/sda2 rw\0" \
	"usbrootfstype=ext4 rootwait\0" \
	"usbdev=0\0" \
	"ramroot=/dev/ram0 rw\0" \
	"ramrootfstype=ext2\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"usbargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${usbroot} " \
		"rootfstype=${usbrootfstype}\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load ${devtype} ${devnum} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
	"ramargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${ramroot} " \
		"rootfstype=${ramrootfstype}\0" \
	"loadramdisk=load ${devtype} ${devnum} ${rdaddr} ramdisk.gz\0" \
	"loadimage=load ${devtype} ${bootpart} ${loadaddr} ${bootdir}/${bootfile}\0" \
	"loadfdt=load ${devtype} ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}\0" \
	"mmcboot=mmc dev ${mmcdev}; " \
		"setenv devnum ${mmcdev}; " \
		"setenv devtype mmc; " \
		"if mmc rescan; then " \
			"echo SD/MMC found on device ${devnum};" \
			"if run loadbootenv; then " \
				"echo Loaded environment from ${bootenv};" \
				"run importbootenv;" \
			"fi;" \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...;" \
				"run uenvcmd;" \
			"fi;" \
			"if run loadimage; then " \
				"run loadfdt; " \
				"echo Booting from mmc${mmcdev} ...; " \
				"run mmcargs; " \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"fi;" \
		"fi;\0" \
	"usbboot=" \
		"setenv devnum ${usbdev}; " \
		"setenv devtype usb; " \
		"usb start ${usbdev}; " \
		"if usb dev ${usbdev}; then " \
			"if run loadbootenv; then " \
				"echo Loaded environment from ${bootenv};" \
				"run importbootenv;" \
			"fi;" \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...;" \
				"run uenvcmd;" \
			"fi;" \
			"if run loadimage; then " \
				"run loadfdt; " \
				"echo Booting from usb ${usbdev}...; " \
				"run usbargs;" \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"fi;" \
		"fi\0" \
	"findfdt=setenv fdtfile var-som-am43.dtb;\0"\
	"netboot=echo Booting from network ...; setenv autoload no; dhcp; tftp ${loadaddr} ${bootfile}; tftp ${fdtaddr} ${fdtfile}; run netargs; bootz ${loadaddr} - ${fdtaddr} \0" 

#define CONFIG_BOOTCOMMAND \
	"run findfdt; " \
	"run mmcboot;" \
	"run usbboot;"

#endif

/* CPSW Ethernet */
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_MII
#define CONFIG_DRIVER_TI_CPSW
#define CONFIG_MII
#define CONFIG_BOOTP_DEFAULT
#define CONFIG_BOOTP_DNS
#define CONFIG_BOOTP_DNS2
#define CONFIG_BOOTP_SEND_HOSTNAME
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_NET_RETRY_COUNT		10
#define CONFIG_NET_MULTI
#define CONFIG_PHY_GIGE
#define CONFIG_PHYLIB

#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_NET_VCI_STRING	"AM43xx U-Boot SPL"

#define CONFIG_SPL_ETH_SUPPORT
#define CONFIG_SPL_NET_SUPPORT
#define CONFIG_SYS_RX_ETH_BUFFER	64

/* NAND support */
#ifdef CONFIG_NAND
/* NAND: device related configs */
#define CONFIG_SYS_NAND_PAGE_SIZE	4096
#define CONFIG_SYS_NAND_OOBSIZE		224
#define CONFIG_SYS_NAND_BLOCK_SIZE	(256*1024)
#define CONFIG_SYS_NAND_PAGE_COUNT	(CONFIG_SYS_NAND_BLOCK_SIZE / \
					 CONFIG_SYS_NAND_PAGE_SIZE)
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
/* NAND: driver related configs */
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_NAND_OMAP_ELM
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_NAND_OMAP_ECCSCHEME	OMAP_ECC_BCH16_CODE_HW
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS	{ 2, 3, 4, 5, 6, 7, 8, 9, \
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29, \
				30, 31, 32, 33, 34, 35, 36, 37, 38, 39, \
				40, 41, 42, 43, 44, 45, 46, 47, 48, 49, \
				50, 51, 52, 53, 54, 55, 56, 57, 58, 59, \
				60, 61, 62, 63, 64, 65, 66, 67, 68, 69, \
				70, 71, 72, 73, 74, 75, 76, 77, 78, 79, \
				80, 81, 82, 83, 84, 85, 86, 87, 88, 89, \
				90, 91, 92, 93, 94, 95, 96, 97, 98, 99, \
			100, 101, 102, 103, 104, 105, 106, 107, 108, 109, \
			110, 111, 112, 113, 114, 115, 116, 117, 118, 119, \
			120, 121, 122, 123, 124, 125, 126, 127, 128, 129, \
			130, 131, 132, 133, 134, 135, 136, 137, 138, 139, \
			140, 141, 142, 143, 144, 145, 146, 147, 148, 149, \
			150, 151, 152, 153, 154, 155, 156, 157, 158, 159, \
			160, 161, 162, 163, 164, 165, 166, 167, 168, 169, \
			170, 171, 172, 173, 174, 175, 176, 177, 178, 179, \
			180, 181, 182, 183, 184, 185, 186, 187, 188, 189, \
			190, 191, 192, 193, 194, 195, 196, 197, 198, 199, \
			200, 201, 202, 203, 204, 205, 206, 207, 208, 209, \
			}
#define CONFIG_SYS_NAND_ECCSIZE		512
#define CONFIG_SYS_NAND_ECCBYTES	26
#define MTDIDS_DEFAULT			"nand0=nand.0"
#define MTDPARTS_DEFAULT		"mtdparts=nand.0:" \
					"256k(NAND.SPL)," \
					"256k(NAND.SPL.backup1)," \
					"256k(NAND.SPL.backup2)," \
					"256k(NAND.SPL.backup3)," \
					"512k(NAND.u-boot-spl-os)," \
					"1m(NAND.u-boot)," \
					"256k(NAND.u-boot-env)," \
					"256k(NAND.u-boot-env.backup1)," \
					"7m(NAND.kernel)," \
					"-(NAND.rootfs)"
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x00180000
/* NAND: SPL related configs */
#ifdef CONFIG_SPL_NAND_SUPPORT
#define CONFIG_SPL_NAND_AM33XX_BCH
#endif
/* NAND: SPL falcon mode configs */
#ifdef CONFIG_SPL_OS_BOOT
#define CONFIG_CMD_SPL_NAND_OFS		0x00100000 /* os parameters */
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00300000 /* kernel offset */
#define CONFIG_CMD_SPL_WRITE_SIZE	CONFIG_SYS_NAND_BLOCK_SIZE
#endif
#endif /* !CONFIG_NAND */

#endif	/* __CONFIG_AM43XX_EVM_H */
