/** @file

Copyright (c) 2015, Intel Corporation. All rights reserved.<BR>

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of Intel Corporation nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

  This file is automatically generated. Please do NOT modify !!!

**/

#ifndef __FSPUPDVPD_H__
#define __FSPUPDVPD_H__

#pragma pack(push, 1)


#define MRC_MAX_RCOMP          3
#define MRC_MAX_RCOMP_TARGETS  5
#define MAX_CHANNELS_NUM       2
#define MAX_DIMMS_NUM          2

typedef struct {
  UINT16  RcompResistor[MRC_MAX_RCOMP];       ///< Offset 0: Reference RCOMP resistors on motherboard
  UINT16  RcompTarget[MRC_MAX_RCOMP_TARGETS]; ///< Offset 6: RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
} MEMORY_RCOMP;


typedef struct {
  UINT32 VendorDeviceId;     /* Vendor ID/Device ID */
  UINT16 SubSystemId;        /* SubSystem ID */
  UINT8  RevisionId;         /* Revision ID. 0xFF applies to all steppings */
  UINT8  FrontPanelSupport;  /* Front panel support (1=yes, 2=no) */
  UINT16 NumberOfRearJacks;  /* Number of Rear Jacks */
  UINT16 NumberOfFrontJacks; /* Number of Front Jacks */
} SA_HDA_HEADER;

typedef struct {
  UINT16 VendorId;          /* Codec Vendor ID */
  UINT16 DeviceId;          /* Codec Device ID */
  UINT8  RevisionId;        /* Revision ID of the codec. 0xFF matches any revision. */
  UINT8  SdiNo;             /* SDI number, 0xFF matches any SDI. */
  UINT16 DataDwords;        /* Number of data DWORDs pointed by the codec data buffer. */
  UINT32 Reserved;          /* Reserved for future use. Must be set to 0. */
} AZALIA_HEADER;

typedef struct {
  AZALIA_HEADER Header;     /* AZALIA PCH header */
  UINT32        *Data;      /* Pointer to the data buffer. Its length is specified in the header */
} AUDIO_AZALIA_VERB_TABLE;

///
/// Refer to the definition of PCH_INT_PIN
///
typedef enum {
  SiPchNoInt,        ///< No Interrupt Pin
  SiPchIntA,
  SiPchIntB,
  SiPchIntC,
  SiPchIntD
} SI_PCH_INT_PIN;
///
/// The PCH_DEVICE_INTERRUPT_CONFIG block describes interrupt pin, IRQ and interrupt mode for PCH device.
///
typedef struct {
  UINT8        Device;                  ///< Device number
  UINT8        Function;                ///< Device function
  UINT8        IntX;                    ///< Interrupt pin: INTA-INTD (see SI_PCH_INT_PIN)
  UINT8        Irq;                     ///< IRQ to be set for device.
} SI_PCH_DEVICE_INTERRUPT_CONFIG;

#define SI_PCH_MAX_DEVICE_INTERRUPT_CONFIG  64       ///< Number of all PCH devices

typedef struct {
  UINT8         DimmId;
  UINT32        SizeInMb;
  UINT16        MfgId;
  UINT8         ModulePartNum[20];/* Module part number for DDR3 is 18 bytes however for DRR4 20 bytes as per JEDEC Spec, so reserving 20 bytes */
} DIMM_INFO;

typedef struct {
  UINT8         ChannelId;
  UINT8         DimmCount;
  DIMM_INFO     DimmInfo[MAX_DIMMS_NUM];
} CHANNEL_INFO;

typedef struct {
  UINT8         Revision;
  UINT16        DataWidth;
  /** As defined in SMBIOS 3.0 spec
    Section 7.18.2 and Table 75
  **/
  UINT8         MemoryType;
  UINT16        MemoryFrequencyInMHz;
  /** As defined in SMBIOS 3.0 spec
    Section 7.17.3 and Table 72
  **/
  UINT8         ErrorCorrectionType;
  UINT8         ChannelCount;
  CHANNEL_INFO  ChannelInfo[MAX_CHANNELS_NUM];
} FSP_SMBIOS_MEMORY_INFO;



/** UPD data structure for FspMemoryInitApi
**/
typedef struct {

/** Offset 0x0020
**/
  UINT64                      Signature;

/** Offset 0x0028 - Revision
  Revision version of the MemoryInitUpd Region
**/
  UINT8                       Revision;

/** Offset 0x0029
**/
  UINT8                       UnusedUpdSpace0[7];

/** Offset 0x0030 - Platform Reserved Memory Size
  The minimum platform memory size required to pass control into DXE
  0x400000 : 0x400000
**/
  UINT64                      PlatformMemorySize;

/** Offset 0x0038 - Memory SPD Pointer Channel 0 Dimm 0
  Pointer to SPD data in Memory. Default: 0 for empty channel
**/
  UINT32                      MemorySpdPtr00;

/** Offset 0x003C - Memory SPD Pointer Channel 0 Dimm 1
  Pointer to SPD data in Memory. Default: 0 for empty channel
**/
  UINT32                      MemorySpdPtr01;

/** Offset 0x0040 - Memory SPD Pointer Channel 1 Dimm 0
  Pointer to SPD data in Memory. Default: 0 for empty channel
**/
  UINT32                      MemorySpdPtr10;

/** Offset 0x0044 - Memory SPD Pointer Channel 1 Dimm 1
  Pointer to SPD data in Memory. Default: 0 for empty channel
**/
  UINT32                      MemorySpdPtr11;

/** Offset 0x0048 - SPD Data Length
  Length of SPD Data
  0x100:256 Bytes, 0x200:512 Bytes
**/
  UINT16                      MemorySpdDataLen;

/** Offset 0x004A - Dq Byte Map CH0
  Dq byte mapping between CPU and DRAM, Channel 0: board-dependent
**/
  UINT8                       DqByteMapCh0[12];

/** Offset 0x0056 - Dq Byte Map CH1
  Dq byte mapping between CPU and DRAM, Channel 1: board-dependent
**/
  UINT8                       DqByteMapCh1[12];

/** Offset 0x0062 - Dqs Map CPU to DRAM CH 0
  Set Dqs mapping relationship between CPU and DRAM, Channel 0: board-dependent
**/
  UINT8                       DqsMapCpu2DramCh0[8];

/** Offset 0x006A - Dqs Map CPU to DRAM CH 1
  Set Dqs mapping relationship between CPU and DRAM, Channel 1: board-dependent
**/
  UINT8                       DqsMapCpu2DramCh1[8];

/** Offset 0x0072 - RcompResister settings
  Indicates  RcompReister settings: Board-dependent
**/
  UINT16                      RcompResistor[3];

/** Offset 0x0078 - RcompTarget settings
  RcompTarget settings: board-dependent
**/
  UINT16                      RcompTarget[5];

/** Offset 0x0082 - Dqs Pins Interleaved Setting
  Indicates DqPinsInterleaved setting: board-dependent
  $EN_DIS
**/
  UINT8                       DqPinsInterleaved;

/** Offset 0x0083 - VREF_CA
  CA Vref routing: board-dependent
  0:VREF_CA goes to both CH_A and CH_B, 1: VREF_CA to CH_A and VREF_DQ_A to CH_B, 2:VREF_CA to CH_A and VREF_DQ_B to CH_B
**/
  UINT8                       CaVrefConfig;

/** Offset 0x0084 - Smram Mask
  The SMM Regions AB-SEG and/or H-SEG reserved
  0: Neither, 1:AB-SEG, 2:H-SEG, 3: Both
**/
  UINT8                       SmramMask;

/** Offset 0x0085 - MRC Fast Boot
  Enables/Disable the MRC fast path thru the MRC
  $EN_DIS
**/
  UINT8                       MrcFastBoot;

/** Offset 0x0086
**/
  UINT16                      UnusedUpdSpace1;

/** Offset 0x0088 - Intel Enhanced Debug
  Intel Enhanced Debug (IED): 0=Disabled, 0x400000=Enabled and 4MB SMRAM occupied
  0 : Disable, 0x400000 : Enable
**/
  UINT32                      IedSize;

/** Offset 0x008C - Tseg Size
  Size of SMRAM memory reserved. 0x400000 for Release build and 0x1000000 for Debug build
  0x0400000:4MB, 0x01000000:16MB
**/
  UINT32                      TsegSize;

/** Offset 0x0090 - MMIO Size
  Size of memory address space reserved for MMIO (Memory Mapped I/O) in MB.
  0x0600 : 0x0600
**/
  UINT16                      MmioSize;

/** Offset 0x0092 - Probeless Trace
  Probeless Trace: 0=Disabled, 1=Enable. Enabling Probeless Trace will reserve 128MB. This also requires IED to be enabled.
  $EN_DIS
**/
  UINT8                       ProbelessTrace;

/** Offset 0x0093 - Enable LAN
  Enable/disable LAN controller.
  $EN_DIS
**/
  UINT8                       EnableLan;

/** Offset 0x0094
**/
  UINT16                      UnusedUpdSpace2;

/** Offset 0x0096 - Enable Trace Hub
  Enable/disable Trace Hub function.
  $EN_DIS
**/
  UINT8                       EnableTraceHub;

/** Offset 0x0097 - Enable PCIE RP
  Enable/disable PCIE Root Ports. 0: disable, 1: enable. One byte for each port, byte0 for port1, byte1 for port2, and so on.
**/
  UINT8                       PcieRpEnable[20];

/** Offset 0x00AB - Enable PCIE RP CLKREQ Support
  Enable/disable PCIE Root Port CLKREQ support. 0: disable, 1: enable. One byte for each port, byte0 for port1, byte1 for port2, and so on.
**/
  UINT8                       PcieRpClkReqSupport[20];

/** Offset 0x00BF - Configure CLKREQ Number
  Configure Root Port CLKREQ Number if CLKREQ is supported. Each value in arrary can be between 0-6. One byte for each port, byte0 for port1, byte1 for port2, and so on.
**/
  UINT8                       PcieRpClkReqNumber[20];

/** Offset 0x00D3 - Internal Graphics Pre-allocated Memory
  Size of memory preallocated for internal graphics.
  0x00:0 MB, 0x01:32 MB, 0x02:64 MB, 0x03:128 MB, 0x04:256 MB,  0x05:512 MB
**/
  UINT8                       IgdDvmt50PreAlloc;

/** Offset 0x00D4 - Internal Graphics
  Enable/disable internal graphics.
  $EN_DIS
**/
  UINT8                       InternalGfx;

/** Offset 0x00D5 - Aperture Size
  Select the Aperture Size.
  0:128 MB, 1:256 MB, 2:512 MB
**/
  UINT8                       ApertureSize;

/** Offset 0x00D6 - SA GV
  System Agent dynamic frequency support and when enabled memory will be training at two different frequencies. Only effects ULX/ULT CPUs. 0=Disabled, 1=FixedLow, 2=FixedHigh, and 3=Enabled.
  0:Disabled, 1:FixedLow, 2:FixedHigh, 3:Enabled
**/
  UINT8                       SaGv;

/** Offset 0x00D7 - Rank Margin Tool
  Enable/disable Rank Margin Tool.
  $EN_DIS
**/
  UINT8                       RMT;

/** Offset 0x00D8 - DDR Frequency Limit
  Maximum Memory Frequency Selections in Mhz. Options are 1067, 1333, 1600, 1867, 2133, 2400 and 0 for Auto.
  1067:1067, 1333:1333, 1600:1600, 1867:1867, 2133:2133, 2400:2400, 0:Auto
**/
  UINT16                      DdrFreqLimit;

/** Offset 0x00DA - Board Type
  MrcBoardType, Options are 0=Mobile/Mobile Halo, 1=Desktop/DT Halo, 5=ULT/ULX/Mobile Halo, 7=UP Server
  0:Mobile/Mobile Halo, 1:Desktop/DT Halo, 5:ULT/ULX/Mobile Halo, 7:UP Server
**/
  UINT8                       UserBd;

/** Offset 0x00DB
**/
  UINT8                       UnusedUpdSpace3[105];

/** Offset 0x0144 - MMA Test Content Pointer
  Pointer to MMA Test Content in Memory
**/
  UINT32                      MmaTestContentPtr;

/** Offset 0x0148 - MMA Test Content Size
  Size of MMA Test Content in Memory
**/
  UINT32                      MmaTestContentSize;

/** Offset 0x014C - MMA Test Config Pointer
  Pointer to MMA Test Config in Memory
**/
  UINT32                      MmaTestConfigPtr;

/** Offset 0x0150 - MMA Test Config Size
  Size of MMA Test Config in Memory
**/
  UINT32                      MmaTestConfigSize;

/** Offset 0x0154 - Enable CIO2 Controller
  Enable/disable SKYCAM CIO2 Controller.
  $EN_DIS
**/
  UINT8                       Cio2Enable;

/** Offset 0x0155
**/
  UINT8                       ReservedMemoryInitUpd[171];
} MEMORY_INIT_UPD;

/** UPD data structure for FspSiliconInitApi
**/
typedef struct {

/** Offset 0x0200
**/
  UINT64                      Signature;

/** Offset 0x0208 - Revision
  Revision version of the SiliconInitUpd Region
**/
  UINT8                       Revision;

/** Offset 0x0209
**/
  UINT8                       UnusedUpdSpace4[7];

/** Offset 0x0210 - Logo Pointer
  Points to PEI Display Logo Image
  0 : 0
**/
  UINT32                      LogoPtr;

/** Offset 0x0214 - Logo Size
  Size of PEI Display Logo Image
  0 : 0
**/
  UINT32                      LogoSize;

/** Offset 0x0218 - Graphics Configuration Ptr
  Points to VBT
  0 : 0
**/
  UINT32                      GraphicsConfigPtr;

/** Offset 0x021C - Enable Device 4
  Enable/disable Device 4
  $EN_DIS
**/
  UINT8                       Device4Enable;

/** Offset 0x021D - Enable Azalia
  Enable/disable Azalia controller.
  $EN_DIS
**/
  UINT8                       EnableAzalia;

/** Offset 0x021E - Enable HD Audio DSP
  Enable/disable HD Audio DSP feature.
  $EN_DIS
**/
  UINT8                       DspEnable;

/** Offset 0x021F - Select HDAudio IoBuffer Ownership
  Indicates the ownership of the I/O buffer between Intel HD Audio link vs I2S0 / I2S port. 0: Intel HD-Audio link owns all the I/O buffers. 1: Intel HD-Audio link owns 4 of the I/O buffers for 1 HD-Audio codec connection, and I2S1 port owns 4 of the I/O buffers for 1 I2S codec connection. 2: Reserved. 3: I2S0 and I2S1 ports own all the I/O buffers.
  0:HD-A Link, 1:Shared HD-A Link and I2S Port, 3:I2S Ports
**/
  UINT8                       IoBufferOwnership;

/** Offset 0x0220
**/
  UINT8                       UnusedUpdSpace5;

/** Offset 0x0221 - Enable eMMC Controller
  Enable/disable eMMC Controller.
  $EN_DIS
**/
  UINT8                       ScsEmmcEnabled;

/** Offset 0x0222 - Enable eMMC HS400 Mode
  Enable eMMC HS400 Mode.
  $EN_DIS
**/
  UINT8                       ScsEmmcHs400Enabled;

/** Offset 0x0223 - Enable SdCard Controller
  Enable/disable SD Card Controller.
  $EN_DIS
**/
  UINT8                       ScsSdCardEnabled;

/** Offset 0x0224 - Enable ISH Controller
  Enable/disable ISH Controller.
  $EN_DIS
**/
  UINT8                       IshEnable;

/** Offset 0x0225 - Show SPI controller
  Enable/disable to show SPI controller.
  $EN_DIS
**/
  UINT8                       ShowSpiController;

/** Offset 0x0226 - HSIO HECI Messaging
  Enable/Disable. 0: Disable, prevent the HSIO version check and HSIO init messages from being sent, 1: enable
  $EN_DIS
**/
  UINT8                       HsioMessaging;

/** Offset 0x0227 - HECI3 state
  The HECI3 state from Mbp for reference in S3 path or when MbpHob is not installed. 0: disable, 1: enable
  $EN_DIS
**/
  UINT8                       Heci3Enabled;

/** Offset 0x0228 - MicrocodeRegionBase
  Memory Base of Microcode Updates
**/
  UINT32                      MicrocodeRegionBase;

/** Offset 0x022C - MicrocodeRegionSize
  Size of Microcode Updates
**/
  UINT32                      MicrocodeRegionSize;

/** Offset 0x0230 - Turbo Mode
  Enable/Disable Turbo mode. 0: disable, 1: enable
  $EN_DIS
**/
  UINT8                       TurboMode;

/** Offset 0x0231 - Enable SATA SALP Support
  Enable/disable SATA Aggressive Link Power Management.
  $EN_DIS
**/
  UINT8                       SataSalpSupport;

/** Offset 0x0232 - Enable SATA ports
  Enable/disable SATA ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.
**/
  UINT8                       SataPortsEnable[8];

/** Offset 0x023A - Enable SATA DEVSLP Feature
  Enable/disable SATA DEVSLP per port. 0 is disable, 1 is enable. One byte for each port, byte0 for port0, byte1 for port1, and so on.
**/
  UINT8                       SataPortsDevSlp[8];

/** Offset 0x0242 - Enable USB2 ports
  Enable/disable per USB2 ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.
**/
  UINT8                       PortUsb20Enable[16];

/** Offset 0x0252 - Enable USB3 ports
  Enable/disable per USB3 ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.
**/
  UINT8                       PortUsb30Enable[10];

/** Offset 0x025C - Enable xDCI controller
  Enable/disable to xDCI controller.
  $EN_DIS
**/
  UINT8                       XdciEnable;

/** Offset 0x025D - Enable XHCI SSIC Eanble
  Enable/disable XHCI SSIC port.
  $EN_DIS
**/
  UINT8                       SsicPortEnable;

/** Offset 0x025E - Enable SMBus
  Enable/disable SMBus controller.
  $EN_DIS
**/
  UINT8                       SmbusEnable;

/** Offset 0x025F - Enable SerialIo Device Mode
  0:Disabled, 1:ACPI Mode, 2:PCI Mode, 3:Hidden mode, 4:Legacy UART mode - Enable/disable SerialIo I2C0,I2C1,I2C2,I2C3,I2C4,I2C5,SPI0,SPI1,UART0,UART1,UART2 device mode respectively. One byte for each controller, byte0 for I2C0, byte1 for I2C1, and so on.
**/
  UINT8                       SerialIoDevMode[11];

/** Offset 0x026A - Address of PCH_DEVICE_INTERRUPT_CONFIG table.
  The address of the table of PCH_DEVICE_INTERRUPT_CONFIG.
**/
  UINT32                      DevIntConfigPtr;

/** Offset 0x026E - Number of DevIntConfig Entry
  Number of Device Interrupt Configuration Entry. If this is not zero, the DevIntConfigPtr must not be NULL.
**/
  UINT8                       NumOfDevIntConfig;

/** Offset 0x026F - PIRQx to IRQx Map Config
  PIRQx to IRQx mapping. The valid value is 0x00 to 0x0F for each. First byte is for PIRQA, second byte is for PIRQB, and so on. The setting is only available in Legacy 8259 PCI mode.
**/
  UINT8                       PxRcConfig[8];

/** Offset 0x0277 - Select GPIO IRQ Route
  GPIO IRQ Select. The valid value is 14 or 15.
  0 : 0xFF
**/
  UINT8                       GpioIrqRoute;

/** Offset 0x0278 - Select SciIrqSelect
  SCI IRQ Select. The valid value is 9, 10, 11, and 20, 21, 22, 23 for APIC only.
  0 : 0xFF
**/
  UINT8                       SciIrqSelect;

/** Offset 0x0279 - Select TcoIrqSelect
  TCO IRQ Select. The valid value is 9, 10, 11, 20, 21, 22, 23.
  0 : 0xFF
**/
  UINT8                       TcoIrqSelect;

/** Offset 0x027A - Enable/Disable Tco IRQ
  Enable/disable TCO IRQ
  $EN_DIS
**/
  UINT8                       TcoIrqEnable;

/** Offset 0x027B - AzaliaVerbTableNumEntries
  Number of Entries in Azalia Verb Table
**/
  UINT8                       AzaliaVerbTableNumEntries;

/** Offset 0x027C - AzaliaVerbTablePtr
  Pointer to Array of pointers to Codec Table.
**/
  UINT32                      AzaliaVerbTablePtr;

/** Offset 0x0280 - RTC CMOS RAM LOCK
  Enable RTC lower and upper 128 byte Lock bits to lock Bytes 38h-3Fh in the upper and and lower 128-byte bank of RTC RAM.
  $EN_DIS
**/
  UINT8                       RtcLock;

/** Offset 0x0281 - Enable SATA
  Enable/disable SATA controller.
  $EN_DIS
**/
  UINT8                       EnableSata;

/** Offset 0x0282 - SATA Mode
  Select SATA controller working mode.
  0:AHCI, 1:RAID
**/
  UINT8                       SataMode;

/** Offset 0x0283 - USB Per Port HS Preemphasis Bias
  USB Per Port HS Preemphasis Bias. 000b-0mV, 001b-11.25mV, 010b-16.9mV, 011b-28.15mV, 100b-28.15mV, 101b-39.35mV, 110b-45mV, 111b-56.3mV. One byte for each port.
**/
  UINT8                       Usb2AfePetxiset[16];

/** Offset 0x0293 - USB Per Port HS Transmitter Bias
  USB Per Port HS Transmitter Bias. 000b-0mV, 001b-11.25mV, 010b-16.9mV, 011b-28.15mV, 100b-28.15mV, 101b-39.35mV, 110b-45mV, 111b-56.3mV, One byte for each port.
**/
  UINT8                       Usb2AfeTxiset[16];

/** Offset 0x02A3 - USB Per Port HS Transmitter Emphasis
  USB Per Port HS Transmitter Emphasis. 00b - Emphasis OFF, 01b - De-emphasis ON, 10b - Pre-emphasis ON, 11b - Pre-emphasis & De-emphasis ON. One byte for each port.
**/
  UINT8                       Usb2AfePredeemp[16];

/** Offset 0x02B3 - USB Per Port Half Bit Pre-emphasis
  USB Per Port Half Bit Pre-emphasis. 1b - half-bit pre-emphasis, 0b - full-bit pre-emphasis. One byte for each port.
**/
  UINT8                       Usb2AfePehalfbit[16];

/** Offset 0x02C3 - Enable the write to USB 3.0 TX Output -3.5dB De-Emphasis Adjustment
  Enable the write to USB 3.0 TX Output -3.5dB De-Emphasis Adjustment. Each value in arrary can be between 0-1. One byte for each port.
**/
  UINT8                       Usb3HsioTxDeEmphEnable[10];

/** Offset 0x02CD - USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting
  USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting, HSIO_TX_DWORD5[21:16], <b>Default = 29h</b> (approximately -3.5dB De-Emphasis). One byte for each port.
**/
  UINT8                       Usb3HsioTxDeEmph[10];

/** Offset 0x02D7 - Enable the write to USB 3.0 TX Output Downscale Amplitude Adjustment
  Enable the write to USB 3.0 TX Output Downscale Amplitude Adjustment, Each value in arrary can be between 0-1. One byte for each port.
**/
  UINT8                       Usb3HsioTxDownscaleAmpEnable[10];

/** Offset 0x02E1 - USB 3.0 TX Output Downscale Amplitude Adjustment
  USB 3.0 TX Output Downscale Amplitude Adjustment, HSIO_TX_DWORD8[21:16], <b>Default = 00h</b>. One byte for each port.
**/
  UINT8                       Usb3HsioTxDownscaleAmp[10];

/** Offset 0x02EB
**/
  UINT8                       ReservedSiliconInitUpd[271];
} SILICON_INIT_UPD;

#define FSP_UPD_SIGNATURE                0x244450554C4B5324        /* '$SKLUPD$' */
#define FSP_MEMORY_INIT_UPD_SIGNATURE    0x244450554D454D24        /* '$MEMUPD$' */
#define FSP_SILICON_INIT_UPD_SIGNATURE   0x244450555F495324        /* '$SI_UPD$' */

/** UPD data structure. The UPD_DATA_REGION may contain some reserved or unused fields in the data structure. These fields are required to use the default values provided in the FSP binary. Intel always recommends copying the whole UPD_DATA_REGION from the flash to a local structure in the stack before overriding any field.
**/
typedef struct {

/** Offset 0x0000
**/
  UINT64                      Signature;

/** Offset 0x0008 - This field is not an option and is a Revision of the UPD_DATA_REGION. It can be used by the boot loader to validate the UPD region. If the value in this field is changed for an FSP release, the boot loader should not assume the same layout for the UPD_DATA_REGION data structure. Instead it should use the new FspUpdVpd.h from the FSP release package.
  Size of SMRAM memory reserved. 0x400000 for Release build and 0x1000000 for Debug build
**/
  UINT8                       Revision;

/** Offset 0x0009
**/
  UINT8                       ReservedUpd0[7];

/** Offset 0x0010 - MemoryInitUpdOffset
  This field contains the offset of the MemoryInitUpd structure relative to UPD_DATA_REGION
**/
  UINT32                      MemoryInitUpdOffset;

/** Offset 0x0014 - SiliconInitUpdOffset
  This field contains the offset of the SiliconInitUpd structure relative to UPD_DATA_REGION
**/
  UINT32                      SiliconInitUpdOffset;

/** Offset 0x0018
**/
  UINT64                      ReservedUpd1;

/** Offset 0x0020
**/
  MEMORY_INIT_UPD             MemoryInitUpd;

/** Offset 0x0200
**/
  SILICON_INIT_UPD            SiliconInitUpd;

/** Offset 0x03FA - RegionTerminator
  This field is not an option and is a termination field at the end of the data structure. This field is will have a value 0x55AA indicating the end of UPD data.The boot loader should never override this field.
**/
  UINT16                      RegionTerminator;
} UPD_DATA_REGION;

#define FSP_IMAGE_ID    0x245053464C4B5324        /* '$SKLFSP$' */
#define FSP_IMAGE_REV   0x01070000

/** VPD data structure
**/
typedef struct {

/** Offset 0x0000
**/
  UINT64                      PcdVpdRegionSign;

/** Offset 0x0008 - PcdImageRevision
  This field is not an option and is a revision ID for the FSP release. It can be used by the boot loader to validate the VPD/UPD region. If the value in this field is changed for an FSP release, the boot loader should not assume the same layout for the UPD_DATA_REGION/VPD_DATA_REGION data structure. Instead it should use the new FspUpdVpd.h from the FSP release package.  This should match the ImageRevision in FSP_INFO_HEADER.
**/
  UINT32                      PcdImageRevision;

/** Offset 0x000C - PcdUpdRegionOffset
  This field is not an option and contains the offset of the UPD data region within the FSP release image. The boot loader can use it to find the location of UPD_DATA_REGION.
**/
  UINT32                      PcdUpdRegionOffset;

/** Offset 0x0010
**/
  UINT8                       UnusedVpdSpace0[32];

/** Offset 0x0030 - PcdSerialIoUartDebugEnable
  Enable SerialIo Uart debug library with/without initializing SerialIo Uart device in FSP.
  0:Disable, 1:Enable and Initialize, 2:Enable without Initializing
**/
  UINT8                       PcdSerialIoUartDebugEnable;

/** Offset 0x0031 - PcdSerialIoUartNumber
  Select SerialIo Uart Controller for debug.
  0:SerialIoUart0, 1:SerialIoUart1, 2:SerialIoUart2
**/
  UINT8                       PcdSerialIoUartNumber;

/** Offset 0x0032
**/
  UINT32                      PcdSerialIoUartInputClock;
} VPD_DATA_REGION;

#pragma pack(pop)

#endif
