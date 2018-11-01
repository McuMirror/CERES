#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../../Source/MDD File System/FSIO.c" ../../Source/NVMem.c ../../Source/USB/usb_msd_bootloader.c ../../Source/USB/usb_config.c ../../Source/USB/usb_host.c ../../Source/USB/usb_host_msd.c ../../Source/USB/usb_host_msd_scsi.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1382283020/FSIO.o ${OBJECTDIR}/_ext/1787047461/NVMem.o ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o ${OBJECTDIR}/_ext/313519312/usb_config.o ${OBJECTDIR}/_ext/313519312/usb_host.o ${OBJECTDIR}/_ext/313519312/usb_host_msd.o ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1382283020/FSIO.o.d ${OBJECTDIR}/_ext/1787047461/NVMem.o.d ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d ${OBJECTDIR}/_ext/313519312/usb_config.o.d ${OBJECTDIR}/_ext/313519312/usb_host.o.d ${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1382283020/FSIO.o ${OBJECTDIR}/_ext/1787047461/NVMem.o ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o ${OBJECTDIR}/_ext/313519312/usb_config.o ${OBJECTDIR}/_ext/313519312/usb_host.o ${OBJECTDIR}/_ext/313519312/usb_host_msd.o ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o

# Source Files
SOURCEFILES=../../Source/MDD File System/FSIO.c ../../Source/NVMem.c ../../Source/USB/usb_msd_bootloader.c ../../Source/USB/usb_config.c ../../Source/USB/usb_host.c ../../Source/USB/usb_host_msd.c ../../Source/USB/usb_host_msd_scsi.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="D:\Projets\CERES\SW\Bootloader\Source\BTL_32MX795F512L.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1382283020/FSIO.o: ../../Source/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1382283020" 
	@${RM} ${OBJECTDIR}/_ext/1382283020/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1382283020/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1382283020/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/1382283020/FSIO.o.d" -o ${OBJECTDIR}/_ext/1382283020/FSIO.o "../../Source/MDD File System/FSIO.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1787047461/NVMem.o: ../../Source/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/NVMem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/NVMem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" -o ${OBJECTDIR}/_ext/1787047461/NVMem.o ../../Source/NVMem.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o: ../../Source/USB/usb_msd_bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o ../../Source/USB/usb_msd_bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_config.o: ../../Source/USB/usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_config.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_config.o ../../Source/USB/usb_config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_host.o: ../../Source/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_host.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_host.o ../../Source/USB/usb_host.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_host_msd.o: ../../Source/USB/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_host_msd.o ../../Source/USB/usb_host_msd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o: ../../Source/USB/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o ../../Source/USB/usb_host_msd_scsi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1382283020/FSIO.o: ../../Source/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1382283020" 
	@${RM} ${OBJECTDIR}/_ext/1382283020/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1382283020/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1382283020/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/1382283020/FSIO.o.d" -o ${OBJECTDIR}/_ext/1382283020/FSIO.o "../../Source/MDD File System/FSIO.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1787047461/NVMem.o: ../../Source/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/NVMem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/NVMem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" -o ${OBJECTDIR}/_ext/1787047461/NVMem.o ../../Source/NVMem.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o: ../../Source/USB/usb_msd_bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_msd_bootloader.o ../../Source/USB/usb_msd_bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_config.o: ../../Source/USB/usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_config.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_config.o ../../Source/USB/usb_config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_host.o: ../../Source/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_host.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_host.o ../../Source/USB/usb_host.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_host_msd.o: ../../Source/USB/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_host_msd.o ../../Source/USB/usb_host_msd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o: ../../Source/USB/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313519312" 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -Os -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"../.." -I"../../include" -I"../../include/MDD File System" -I"../../include/HardwareProfile" -I"../../include/Usb/Stack" -I"../../include/FrameWork" -MMD -MF "${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/313519312/usb_host_msd_scsi.o ../../Source/USB/usb_host_msd_scsi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    D:/Projets/CERES/SW/Bootloader/Source/BTL_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_REAL_ICE=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,--defsym=_min_heap_size=512,--gc-sections
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   D:/Projets/CERES/SW/Bootloader/Source/BTL_32MX795F512L.ld ../../../MainBoard_v_1_3_8.X/dist/Release/production/MainBoard_v_1_3_8.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo "Creating unified hex file"
	@"C:/Program Files (x86)/Microchip/MPLABX/v5.05/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files (x86)/Microchip/MPLABX/v5.05/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/USB_MSD_Btl.X.${IMAGE_TYPE}.hex ../../../MainBoard_v_1_3_8.X/dist/Release/production/MainBoard_v_1_3_8.X.production.hex -odist/${CND_CONF}/production/USB_MSD_Btl.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd /D ../../../MainBoard_v_1_3_8.X && ${MAKE}  -f Makefile CONF=Release TYPE_IMAGE=DEBUG_RUN
else
	cd /D ../../../MainBoard_v_1_3_8.X && ${MAKE}  -f Makefile CONF=Release
endif


# Subprojects
.clean-subprojects:
	cd /D ../../../MainBoard_v_1_3_8.X && rm -rf "build/Release" "dist/Release"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif