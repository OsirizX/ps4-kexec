#ifndef ACPI_CAPS_H
#define ACPI_CAPS_H

//See http://arbor.mindshare.com/arbor/refview?pane=index

#define  PCI_CAP_ID_PM		0x01	/* Power Management */
#define  PCI_CAP_ID_AGP		0x02	/* Accelerated Graphics Port */
#define  PCI_CAP_ID_VPD		0x03	/* Vital Product Data */
#define  PCI_CAP_ID_SLOTID	0x04	/* Slot Identification */
#define  PCI_CAP_ID_MSI		0x05	/* Message Signalled Interrupts */
#define  PCI_CAP_ID_CHSWP	0x06	/* CompactPCI HotSwap */
#define  PCI_CAP_ID_PCIX	0x07	/* PCI-X */
#define  PCI_CAP_ID_HT		0x08	/* HyperTransport */
#define  PCI_CAP_ID_VNDR	0x09	/* Vendor specific */
#define  PCI_CAP_ID_DBG		0x0A	/* Debug port */
#define  PCI_CAP_ID_CCRC	0x0B	/* CompactPCI Central Resource Control */
#define  PCI_CAP_ID_SHPC 	0x0C	/* PCI Standard Hot-Plug Controller */
#define  PCI_CAP_ID_SSVID	0x0D	/* Bridge subsystem vendor/device ID */
#define  PCI_CAP_ID_AGP3	0x0E	/* AGP Target PCI-PCI bridge */
#define  PCI_CAP_ID_EXP 	0x10	/* PCI Express */
#define  PCI_CAP_ID_MSIX	0x11	/* MSI-X */
#define  PCI_CAP_ID_AF		0x13	/* PCI Advanced Features */
#define  PCI_CAP_ID_IOMMU	0x0F	/* Secure Device capability IOMMU 48882_IOMMU.pdf, page 175 */

#define UCHAR u8
#define USHORT u16
#define ULONG u32
#define PACKED __attribute__((packed))
typedef struct PACKED _PCI_CAPABILITIES_HEADER {
    UCHAR CapabilityID;
  	UCHAR Next;
} PCI_CAPABILITIES_HEADER, *PPCI_CAPABILITIES_HEADER;

typedef struct __attribute__((packed)) _PCI_PMC {
  UCHAR              Version  :3;
  UCHAR              PMEClock  :1;
  UCHAR              Rsvd1  :1;
  UCHAR              DeviceSpecificInitialization  :1;
  UCHAR              Rsvd2  :2;
  struct __attribute__((packed)) _PM_SUPPORT {
    UCHAR Rsvd2  :1;
    UCHAR D1  :1;
    UCHAR D2  :1;
    UCHAR PMED0  :1;
    UCHAR PMED1  :1;
    UCHAR PMED2  :1;
    UCHAR PMED3Hot  :1;
    UCHAR PMED3Cold  :1;
  } Support;
} PCI_PMC, *PPCI_PMC;

typedef struct __attribute__((packed)) _PCI_PMCSR {
  USHORT PowerState  :2;
  USHORT Rsvd1  :6;
  USHORT PMEEnable  :1;
  USHORT DataSelect  :4;
  USHORT DataScale  :2;
  USHORT PMEStatus  :1;
} PCI_PMCSR, *PPCI_PMCSR;

typedef struct __attribute__((packed)) _PCI_PMCSR_BSE {
  UCHAR Rsvd1;
  UCHAR D3HotSupportsStopClock;
  UCHAR BusPowerClockControlEnabled;
} PCI_PMCSR_BSE, *PPCI_PMCSR_BSE;

typedef struct PACKED _PCI_PM_CAPABILITY {
  PCI_CAPABILITIES_HEADER Header;
  union {
    PCI_PMC Capabilities;
    USHORT  AsUSHORT;
  } PMC;
  union {
    PCI_PMCSR ControlStatus;
    USHORT    AsUSHORT;
  } PMCSR;
  union {
    PCI_PMCSR_BSE BridgeSupport;
    UCHAR         AsUCHAR;
  } PMCSR_BSE;
  UCHAR                   Data;
} PCI_PM_CAPABILITY, *PPCI_PM_CAPABILITY;

typedef struct PACKED _PCI_MSI_CAPABILITY {
  PCI_CAPABILITIES_HEADER Header;
  u16 msiEnable : 1, multipleMessageCapable : 3, multipleMessageEnable : 3, address64Capable : 1, reserved0 : 8;
  u32 lowerAddress : 30, reserved1 : 2;
  union {
  	struct {
  		u32 upperAddress;
  		u32 messageData64 : 16, reservedData64 : 16;
  		u32 mask64;
  	};
  	struct {
  		u32 messageData32 : 16, reservedData32 : 16;
  		u32 mask32;
  	};
  };
} PCI_MSI_CAPABILITY, *PPCI_MSI_CAPABILITY;

//PCI Express
typedef union PACKED _PCI_EXPRESS_CAPABILITIES_REGISTER {
  struct {
    USHORT CapabilityVersion  :4;
    USHORT DeviceType  :4;
    USHORT SlotImplemented  :1;
    USHORT InterruptMessageNumber  :5;
    USHORT Rsvd  :2;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_CAPABILITIES_REGISTER, *PPCI_EXPRESS_CAPABILITIES_REGISTER;

typedef union PACKED _PCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER {
  struct {
    ULONG MaxPayloadSizeSupported  :3;
    ULONG PhantomFunctionsSupported  :2;
    ULONG ExtendedTagSupported  :1;
    ULONG L0sAcceptableLatency  :3;
    ULONG L1AcceptableLatency  :3;
    ULONG Undefined  :3;
    ULONG RoleBasedErrorReporting  :1;
    ULONG Rsvd1  :2;
    ULONG CapturedSlotPowerLimit  :8;
    ULONG CapturedSlotPowerLimitScale  :2;
	ULONG FunctionLevelReset : 1;
    ULONG Rsvd2  :3;
  };
  ULONG  AsULONG;
} PCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER, *PPCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER;

typedef union PACKED _PCI_EXPRESS_DEVICE_CONTROL_REGISTER {
  struct {
    USHORT CorrectableErrorEnable  :1;
    USHORT NonFatalErrorEnable  :1;
    USHORT FatalErrorEnable  :1;
    USHORT UnsupportedRequestErrorEnable  :1;
    USHORT EnableRelaxedOrder  :1;
    USHORT MaxPayloadSize  :3;
    USHORT ExtendedTagEnable  :1;
    USHORT PhantomFunctionsEnable  :1;
    USHORT AuxPowerEnable  :1;
    USHORT NoSnoopEnable  :1;
    USHORT MaxReadRequestSize  :3;
    USHORT BridgeConfigRetryEnable  :1;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_DEVICE_CONTROL_REGISTER, *PPCI_EXPRESS_DEVICE_CONTROL_REGISTER;

typedef union PACKED _PCI_EXPRESS_DEVICE_STATUS_REGISTER {
  struct {
    USHORT CorrectableErrorDetected  :1;
    USHORT NonFatalErrorDetected  :1;
    USHORT FatalErrorDetected  :1;
    USHORT UnsupportedRequestDetected  :1;
    USHORT AuxPowerDetected  :1;
    USHORT TransactionsPending  :1;
    USHORT Rsvd  :10;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_DEVICE_STATUS_REGISTER, *PPCI_EXPRESS_DEVICE_STATUS_REGISTER;

typedef union PACKED _PCI_EXPRESS_LINK_CAPABILITIES_REGISTER {
  struct {
    ULONG MaximumLinkSpeed  :4;
    ULONG MaximumLinkWidth  :6;
    ULONG ActiveStatePMSupport  :2;
    ULONG L0sExitLatency  :3;
    ULONG L1ExitLatency  :3;
    ULONG ClockPowerManagement  :1;
    ULONG SurpriseDownErrorReportingCapable  :1;
    ULONG DataLinkLayerActiveReportingCapable  :1;
    ULONG Rsvd  :3;
    ULONG PortNumber  :8;
  };
  ULONG  AsULONG;
} PCI_EXPRESS_LINK_CAPABILITIES_REGISTER, *PPCI_EXPRESS_LINK_CAPABILITIES_REGISTER;

typedef union PACKED _PCI_EXPRESS_LINK_CONTROL_REGISTER {
  struct {
    USHORT ActiveStatePMControl  :2;
    USHORT Rsvd1  :1;
    USHORT ReadCompletionBoundary  :1;
    USHORT LinkDisable  :1;
    USHORT RetrainLink  :1;
    USHORT CommonClockConfig  :1;
    USHORT ExtendedSynch  :1;
    USHORT EnableClockPowerManagement  :1;
    USHORT Rsvd2  :7;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_LINK_CONTROL_REGISTER, *PPCI_EXPRESS_LINK_CONTROL_REGISTER;

typedef union PACKED _PCI_EXPRESS_LINK_STATUS_REGISTER {
  struct {
    USHORT LinkSpeed  :4;
    USHORT LinkWidth  :6;
    USHORT Undefined  :1;
    USHORT LinkTraining  :1;
    USHORT SlotClockConfig  :1;
    USHORT DataLinkLayerActive  :1;
    USHORT LinkBandwidthManagementStatus  :1;
	USHORT LinkAutonomousBandwidthStatus  :1;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_LINK_STATUS_REGISTER, *PPCI_EXPRESS_LINK_STATUS_REGISTER;

typedef union PACKED _PCI_EXPRESS_SLOT_CAPABILITIES_REGISTER {
  struct {
    ULONG AttentionButtonPresent  :1;
    ULONG PowerControllerPresent  :1;
    ULONG MRLSensorPresent  :1;
    ULONG AttentionIndicatorPresent  :1;
    ULONG PowerIndicatorPresent  :1;
    ULONG HotPlugSurprise  :1;
    ULONG HotPlugCapable  :1;
    ULONG SlotPowerLimit  :8;
    ULONG SlotPowerLimitScale  :2;
    ULONG ElectromechanicalLockPresent  :1;
    ULONG NoCommandCompletedSupport  :1;
    ULONG PhysicalSlotNumber  :13;
  };
  ULONG  AsULONG;
} PCI_EXPRESS_SLOT_CAPABILITIES_REGISTER, *PPCI_EXPRESS_SLOT_CAPABILITIES_REGISTER;

typedef union PACKED _PCI_EXPRESS_SLOT_CONTROL_REGISTER {
  struct {
    USHORT AttentionButtonEnable  :1;
    USHORT PowerFaultDetectEnable  :1;
    USHORT MRLSensorEnable;
    USHORT PresenceDetectEnable  :1;
    USHORT CommandCompletedEnable  :1;
    USHORT HotPlugInterruptEnable  :1;
    USHORT AttentionIndicatorControl  :2;
    USHORT PowerIndicatorControl  :2;
    USHORT PowerControllerControl  :1;
    USHORT ElectromechanicalLockControl  :1;
    USHORT DataLinkStateChangeEnable  :1;
    USHORT Rsvd  :3;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_SLOT_CONTROL_REGISTER, *PPCI_EXPRESS_SLOT_CONTROL_REGISTER;

typedef union PACKED _PCI_EXPRESS_SLOT_STATUS_REGISTER {
  struct {
    USHORT AttentionButtonPressed  :1;
    USHORT PowerFaultDetected  :1;
    USHORT MRLSensorChanged  :1;
    USHORT PresenceDetectChanged  :1;
    USHORT CommandCompleted  :1;
    USHORT MRLSensorState  :1;
    USHORT PresenceDetectState  :1;
    USHORT ElectromechanicalLockEngaged  :1;
    USHORT DataLinkStateChanged  :1;
    USHORT Rsvd  :7;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_SLOT_STATUS_REGISTER, *PPCI_EXPRESS_SLOT_STATUS_REGISTER;

typedef union PACKED _PCI_EXPRESS_ROOT_CONTROL_REGISTER {
  struct {
    USHORT CorrectableSerrEnable  :1;
    USHORT NonFatalSerrEnable  :1;
    USHORT FatalSerrEnable  :1;
    USHORT PMEInterruptEnable  :1;
    USHORT CRSSoftwareVisibilityEnable  :1;
    USHORT Rsvd  :11;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_ROOT_CONTROL_REGISTER, *PPCI_EXPRESS_ROOT_CONTROL_REGISTER;

typedef union PACKED _PCI_EXPRESS_ROOT_CAPABILITIES_REGISTER {
  struct {
    USHORT CRSSoftwareVisibility  :1;
    USHORT Rsvd  :15;
  };
  USHORT AsUSHORT;
} PCI_EXPRESS_ROOT_CAPABILITIES_REGISTER, *PPCI_EXPRESS_ROOT_CAPABILITIES_REGISTER;

typedef union PACKED _PCI_EXPRESS_ROOT_STATUS_REGISTER {
  struct {
    ULONG PMERequestorId  :16;
    ULONG PMEStatus  :1;
    ULONG PMEPending  :1;
    ULONG Rsvd  :14;
  };
  ULONG  AsULONG;
} PCI_EXPRESS_ROOT_STATUS_REGISTER, *PPCI_EXPRESS_ROOT_STATUS_REGISTER;

typedef struct PACKED _PCI_EXPRESS_CAPABILITY {
  PCI_CAPABILITIES_HEADER                  Header;
  PCI_EXPRESS_CAPABILITIES_REGISTER        ExpressCapabilities;
  PCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER DeviceCapabilities;
  PCI_EXPRESS_DEVICE_CONTROL_REGISTER      DeviceControl;
  PCI_EXPRESS_DEVICE_STATUS_REGISTER       DeviceStatus;
  PCI_EXPRESS_LINK_CAPABILITIES_REGISTER   LinkCapabilities;
  PCI_EXPRESS_LINK_CONTROL_REGISTER        LinkControl;
  PCI_EXPRESS_LINK_STATUS_REGISTER         LinkStatus;
  PCI_EXPRESS_SLOT_CAPABILITIES_REGISTER   SlotCapabilities;
  PCI_EXPRESS_SLOT_CONTROL_REGISTER        SlotControl;
  PCI_EXPRESS_SLOT_STATUS_REGISTER         SlotStatus;
  PCI_EXPRESS_ROOT_CONTROL_REGISTER        RootControl;
  PCI_EXPRESS_ROOT_CAPABILITIES_REGISTER   RootCapabilities;
  PCI_EXPRESS_ROOT_STATUS_REGISTER         RootStatus;
} PCI_EXPRESS_CAPABILITY, *PPCI_EXPRESS_CAPABILITY;

//IOMMU capability
typedef struct PACKED _PCI_IOMMU_CAPABILITY { //page 174
  PCI_CAPABILITIES_HEADER Header;
  /*offset=02h*/u16 CapType : 3, CapRev : 5, IotlbSup : 1, HtTunnel : 1, NpCache : 1, EFRSup : 1, CapExt : 1, reserved0 : 3;
  /*offset=04h*/union {
  	u32 enable: 1; //When Enable is written with a 1, all RW capability registers defined in Section 3.2 [IOMMU Base Capability Block Registers] are locked until the next system reset.
  	u32 BaseAddressLowRegister;
  };
  u32 BaseAddressHigh;	
  /*offset=0Ch, shadowed later*/union {
	struct { u32 UnitID : 5 /*deprecated and maybe 0*/,reserved : 2, RngValid : 1, BusNumber : 16, FirstDevice : 8, LastDevice : 8; } RANGE_REGISTER; //Although the register contents are valid, software is encouraged to use I/O topology information as defined in Chapter 5, "I/O Virtualization ACPI Table". 0b = Software must use I/O topology information.
	u32 RangeRegister;
  };
  /*offset 10h, shadowed later*/union {
	struct { u32 MsiNum: 5 /* 0 FOR MSI Event Log*/, GVAsize : 3, PAsize : 7, VAsize : 7, HtAtsResv : 1, reserved2 : 4, MsiNumPPR : 5; } MISC_INFO_REGISTER0; /* MsiNumPPR must be zero when PPRSup = 0. For MSI 0 */
	u32 MiscellaneousInformationRegister0;
  };
  /*offset 14h, shadowed later*/union {
	  struct { u32 MsiNumGA : 5 /*valid if CapExt=1 */, reserved3 : 27; } MISC_INFO_REGISTER1;
	  u32 MiscellaneousInformationRegister1;
  };
} PCI_IOMMU_CAPABILITY, *PPCI_IOMMU_CAPABILITY;

typedef struct PACKED _PCI_IOMMU_MMIO_CONTROL { //page 180
  union {
	struct { u64 Size : 9, reserved : 3, DevTabBase : 40/*4K aligned*/, reserved0 : 12; };
	u64 DeviceTableSegmentBaseAddressRegister0; //others are below.
  };
  union {
  	struct { u64 reserved1: 12, ComBase : 40 /*4K aligned*/, reserved2 : 4, ComLen : 4, reserved3 : 4; };
  	u64 CommandBufferBaseAddressRegister;
  };
  union {
  	struct { u64 reserved4 : 12, EventBase : 40/*4K aligned*/, reserved5 : 4, EventLen : 4, reserved6 : 4; };
  	u64 EventLogBaseAddressRegister;
  };
  union {
	struct { u64 IommuEn : 1, HtTunEn : 1/*see HtTunnel*/, 
		EventLogEn : 1, EventIntEn : 1, 
		ComWaitIntEn : 1, InvTimeOut : 3, 
		PassPW : 1, ResPassPW: 1, 
		Coherent : 1, Isoc : 1, CmdBufEn : 1, PPRLogEn : 1/*ignored when PPRSup=0*/, PprIntEn : 1, PPREn : 1/*writes ignored when PPRSup=0*/, 
		GTEn : 1, GAEn : 1, CRW : 4, 
		SmiFEn : 1/*ignored if SmiFSup=0*/, SlfWBdis : 1, SmiFLogEn : 1,
		GAMEn : 3, GALogEn : 1, GAIntEn : 1, 
		DualPprLogEn : 2, DualEventLogEn : 2,
		DevTblSegEn : 3, 
		PrivAbrtEn : 2, PprAutoRspEn : 1, MarcEn : 1, BlkStopMrkEn : 1, PprAutoRspAon : 1,
		DomainIDPNE : 1, reserved : 20; } CONTROL_REGISTER;
	u64 ControlRegister;
  };
  /*Offset 0020h*/u64 ExEn : 1, Allow : 1, ExclusionRangeBaseAddress : 40/*4k aligned*/, reserved7 : 12;
  u64 reserved8 : 12, ExclusionRangeLimit : 40, reserved9 : 12;
  /*Offset 0030h*/union {
	struct { u64 PreFSup : 1, PPRSup : 1, reserved0 : 1, NXSup : 1, GTSup : 1, reserved3 : 1, IASup : 1, GASup : 1, HESup : 1, PCSup : 1, 
		HATS : 2, GATS : 2, GLXSup : 2, SmiFSup : 2, SmiFRC : 3, GAMSup : 3, DualPprLogSup : 2, reserved4 : 2, DualEventLogSup : 2, reserved5 : 2, PASmax : 5; } EXTENDED_FEATURE_REGISTER;
    u64 ExtendedFeatureRegister;
  };
  u64 PPRLogBaseAddressRegister;
  u64 HardwareEventUpperRegister;
  u64 HardwareEventLowerRegister;
  /*Offset 0060h*/u64 SMIFilterRegisters[16];
  /*Offset 00E0h*/u64 GuestVirtualAPICLogBaseAddressRegister;
  u64 GuestVirtualAPICLogTailAddressRegister;
  u64 PPRLogBBaseAddressRegister;
  u64 EventLogBBaseAddressRegister;
  /*Offset 00100h*/u64 DeviceTableSegmentBaseAddressRegisters[7];
  /*Offset 00138h*/u64 DeviceSpecificFeatureExtensionRegister;
  u64 DeviceSpecificControlExtensionRegister;
  u64 DeviceSpecificStatusExtensionRegister;
  //MSI
  /*Offset 00150h*/u32 MSIVectorRegister0Shadow;
  u32 MSIVectorRegister1Shadow;
  u32 MSICapabilityHeaderRegisterShadow;
  u32 MSIAddressLowRegister;
  u32 MSIAddressHighRegister;
  u32 MSIDataRegister : 16, reservedData : 16;
  /*Offset 00168h*/union {
	struct { u32 MsiMapCapId : 8/*=08h*/, reserved10: 8, MsiMapEn : 1, MsiMapFixd : 1, reserved11 : 9, MsiMapCapType : 5/*=15h*/; } MAPPING_CAPABILITY_HEADER_REGISTER;
	u32 MSIMappingCapabilityHeaderRegister;
  };
  /*Offset 0016Ch*/u32 PerformanceOptimizationControlRegister;
  //TODO:
} PCI_IOMMU_MMIO_CONTROL, *PPCI_IOMMU_MMIO_CONTROL;

typedef struct PACKED _PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER { //https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/wdm/ns-wdm-_pci_express_enhanced_capability_header
  USHORT CapabilityID;
  USHORT Version  :4, Next  :12;
} PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER, *PPCI_EXPRESS_ENHANCED_CAPABILITY_HEADER;

typedef struct PACKED _PCI_EXPRESS_RCRB_CAPABILITY {
  PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;
  u32 VendorId : 16, DeviceId : 16;
  u32 CRSSoftwareVisibility : 1, reserved0 : 31;
  u32 CRSSoftwareEnable : 1, reserved1 : 31;
  u32 reserved2;
} PCI_EXPRESS_RCRB_CAPABILITY, *PPCI_EXPRESS_RCRB_CAPABILITY;

typedef struct PACKED _PCI_EXPRESS_DEVSERIAL_CAPABILITY {
  PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;
  u32 DeviceSerialLow;
  u32 DeviceSerialHigh;
} PCI_EXPRESS_DEVSERIAL_CAPABILITY, *PPCI_EXPRESS_DEVSERIAL_CAPABILITY;

#endif
