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
ifeq "$(wildcard nbproject/Makefile-local-Release.mk)" "nbproject/Makefile-local-Release.mk"
include nbproject/Makefile-local-Release.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Release
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S D:/Projets/CERES/SW/FreeRTOS/Source/croutine.c D:/Projets/CERES/SW/FreeRTOS/Source/portable/MemMang/heap_4.c D:/Projets/CERES/SW/FreeRTOS/Source/list.c D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c D:/Projets/CERES/SW/FreeRTOS/Source/queue.c D:/Projets/CERES/SW/FreeRTOS/Source/tasks.c D:/Projets/CERES/SW/FreeRTOS/Source/timers.c MDB.c mdb_bv.c mdb_cg.c mdb_cl.c "../Microchip/TCPIP Stack/ARP.c" "../Microchip/TCPIP Stack/Announce.c" "../Microchip/TCPIP Stack/AutoIP.c" "../Microchip/TCPIP Stack/DHCP.c" "../Microchip/TCPIP Stack/DHCPs.c" "../Microchip/TCPIP Stack/DNS.c" "../Microchip/TCPIP Stack/DNSs.c" "../Microchip/TCPIP Stack/Delay.c" "../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c" "../Microchip/TCPIP Stack/ETHPIC32IntMac.c" "../Microchip/TCPIP Stack/HTTP2.c" "../Microchip/TCPIP Stack/Helpers.c" "../Microchip/TCPIP Stack/IP.c" "../Microchip/TCPIP Stack/MPFS2.c" "../Microchip/TCPIP Stack/NBNS.c" "../Microchip/TCPIP Stack/SMTP.c" "../Microchip/TCPIP Stack/StackTsk.c" "../Microchip/TCPIP Stack/TCP.c" "../Microchip/TCPIP Stack/Tick.c" "../Microchip/TCPIP Stack/UDP.c" "../Microchip/TCPIP Stack/DynDNS.c" "../Microchip/TCPIP Stack/SNTP.c" "../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c" usb_config.c usb_descriptors.c ../Microchip/USB/usb_device.c "../Microchip/USB/CDC Device Driver/usb_function_cdc.c" ../Microchip/USB/usb_host.c "../Microchip/USB/MSD Host Driver/usb_host_msd.c" "../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c" "../Microchip/MDD File System/FSIO.c" main.c HexKeyboard.c I2CE2PROML.c lcd4u.c UARTLib.C RS485.c satellites.c datetime.c CustomHTTPApp.c code.c exception.c password.c MPFSImg2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/971107649/port_asm.o ${OBJECTDIR}/_ext/1729257553/croutine.o ${OBJECTDIR}/_ext/1990890772/heap_4.o ${OBJECTDIR}/_ext/1729257553/list.o ${OBJECTDIR}/_ext/2099989927/port.o ${OBJECTDIR}/_ext/1729257553/queue.o ${OBJECTDIR}/_ext/1729257553/tasks.o ${OBJECTDIR}/_ext/1729257553/timers.o ${OBJECTDIR}/MDB.o ${OBJECTDIR}/mdb_bv.o ${OBJECTDIR}/mdb_cg.o ${OBJECTDIR}/mdb_cl.o ${OBJECTDIR}/_ext/867694782/ARP.o ${OBJECTDIR}/_ext/867694782/Announce.o ${OBJECTDIR}/_ext/867694782/AutoIP.o ${OBJECTDIR}/_ext/867694782/DHCP.o ${OBJECTDIR}/_ext/867694782/DHCPs.o ${OBJECTDIR}/_ext/867694782/DNS.o ${OBJECTDIR}/_ext/867694782/DNSs.o ${OBJECTDIR}/_ext/867694782/Delay.o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/867694782/HTTP2.o ${OBJECTDIR}/_ext/867694782/Helpers.o ${OBJECTDIR}/_ext/867694782/IP.o ${OBJECTDIR}/_ext/867694782/MPFS2.o ${OBJECTDIR}/_ext/867694782/NBNS.o ${OBJECTDIR}/_ext/867694782/SMTP.o ${OBJECTDIR}/_ext/867694782/StackTsk.o ${OBJECTDIR}/_ext/867694782/TCP.o ${OBJECTDIR}/_ext/867694782/Tick.o ${OBJECTDIR}/_ext/867694782/UDP.o ${OBJECTDIR}/_ext/867694782/DynDNS.o ${OBJECTDIR}/_ext/867694782/SNTP.o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o ${OBJECTDIR}/usb_config.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/_ext/343710134/usb_device.o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o ${OBJECTDIR}/_ext/343710134/usb_host.o ${OBJECTDIR}/_ext/131683717/usb_host_msd.o ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o ${OBJECTDIR}/_ext/2054364014/FSIO.o ${OBJECTDIR}/main.o ${OBJECTDIR}/HexKeyboard.o ${OBJECTDIR}/I2CE2PROML.o ${OBJECTDIR}/lcd4u.o ${OBJECTDIR}/UARTLib.o ${OBJECTDIR}/RS485.o ${OBJECTDIR}/satellites.o ${OBJECTDIR}/datetime.o ${OBJECTDIR}/CustomHTTPApp.o ${OBJECTDIR}/code.o ${OBJECTDIR}/exception.o ${OBJECTDIR}/password.o ${OBJECTDIR}/MPFSImg2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/971107649/port_asm.o.d ${OBJECTDIR}/_ext/1729257553/croutine.o.d ${OBJECTDIR}/_ext/1990890772/heap_4.o.d ${OBJECTDIR}/_ext/1729257553/list.o.d ${OBJECTDIR}/_ext/2099989927/port.o.d ${OBJECTDIR}/_ext/1729257553/queue.o.d ${OBJECTDIR}/_ext/1729257553/tasks.o.d ${OBJECTDIR}/_ext/1729257553/timers.o.d ${OBJECTDIR}/MDB.o.d ${OBJECTDIR}/mdb_bv.o.d ${OBJECTDIR}/mdb_cg.o.d ${OBJECTDIR}/mdb_cl.o.d ${OBJECTDIR}/_ext/867694782/ARP.o.d ${OBJECTDIR}/_ext/867694782/Announce.o.d ${OBJECTDIR}/_ext/867694782/AutoIP.o.d ${OBJECTDIR}/_ext/867694782/DHCP.o.d ${OBJECTDIR}/_ext/867694782/DHCPs.o.d ${OBJECTDIR}/_ext/867694782/DNS.o.d ${OBJECTDIR}/_ext/867694782/DNSs.o.d ${OBJECTDIR}/_ext/867694782/Delay.o.d ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d ${OBJECTDIR}/_ext/867694782/HTTP2.o.d ${OBJECTDIR}/_ext/867694782/Helpers.o.d ${OBJECTDIR}/_ext/867694782/IP.o.d ${OBJECTDIR}/_ext/867694782/MPFS2.o.d ${OBJECTDIR}/_ext/867694782/NBNS.o.d ${OBJECTDIR}/_ext/867694782/SMTP.o.d ${OBJECTDIR}/_ext/867694782/StackTsk.o.d ${OBJECTDIR}/_ext/867694782/TCP.o.d ${OBJECTDIR}/_ext/867694782/Tick.o.d ${OBJECTDIR}/_ext/867694782/UDP.o.d ${OBJECTDIR}/_ext/867694782/DynDNS.o.d ${OBJECTDIR}/_ext/867694782/SNTP.o.d ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d ${OBJECTDIR}/usb_config.o.d ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/_ext/343710134/usb_device.o.d ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d ${OBJECTDIR}/_ext/343710134/usb_host.o.d ${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d ${OBJECTDIR}/_ext/2054364014/FSIO.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/HexKeyboard.o.d ${OBJECTDIR}/I2CE2PROML.o.d ${OBJECTDIR}/lcd4u.o.d ${OBJECTDIR}/UARTLib.o.d ${OBJECTDIR}/RS485.o.d ${OBJECTDIR}/satellites.o.d ${OBJECTDIR}/datetime.o.d ${OBJECTDIR}/CustomHTTPApp.o.d ${OBJECTDIR}/code.o.d ${OBJECTDIR}/exception.o.d ${OBJECTDIR}/password.o.d ${OBJECTDIR}/MPFSImg2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/971107649/port_asm.o ${OBJECTDIR}/_ext/1729257553/croutine.o ${OBJECTDIR}/_ext/1990890772/heap_4.o ${OBJECTDIR}/_ext/1729257553/list.o ${OBJECTDIR}/_ext/2099989927/port.o ${OBJECTDIR}/_ext/1729257553/queue.o ${OBJECTDIR}/_ext/1729257553/tasks.o ${OBJECTDIR}/_ext/1729257553/timers.o ${OBJECTDIR}/MDB.o ${OBJECTDIR}/mdb_bv.o ${OBJECTDIR}/mdb_cg.o ${OBJECTDIR}/mdb_cl.o ${OBJECTDIR}/_ext/867694782/ARP.o ${OBJECTDIR}/_ext/867694782/Announce.o ${OBJECTDIR}/_ext/867694782/AutoIP.o ${OBJECTDIR}/_ext/867694782/DHCP.o ${OBJECTDIR}/_ext/867694782/DHCPs.o ${OBJECTDIR}/_ext/867694782/DNS.o ${OBJECTDIR}/_ext/867694782/DNSs.o ${OBJECTDIR}/_ext/867694782/Delay.o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/867694782/HTTP2.o ${OBJECTDIR}/_ext/867694782/Helpers.o ${OBJECTDIR}/_ext/867694782/IP.o ${OBJECTDIR}/_ext/867694782/MPFS2.o ${OBJECTDIR}/_ext/867694782/NBNS.o ${OBJECTDIR}/_ext/867694782/SMTP.o ${OBJECTDIR}/_ext/867694782/StackTsk.o ${OBJECTDIR}/_ext/867694782/TCP.o ${OBJECTDIR}/_ext/867694782/Tick.o ${OBJECTDIR}/_ext/867694782/UDP.o ${OBJECTDIR}/_ext/867694782/DynDNS.o ${OBJECTDIR}/_ext/867694782/SNTP.o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o ${OBJECTDIR}/usb_config.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/_ext/343710134/usb_device.o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o ${OBJECTDIR}/_ext/343710134/usb_host.o ${OBJECTDIR}/_ext/131683717/usb_host_msd.o ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o ${OBJECTDIR}/_ext/2054364014/FSIO.o ${OBJECTDIR}/main.o ${OBJECTDIR}/HexKeyboard.o ${OBJECTDIR}/I2CE2PROML.o ${OBJECTDIR}/lcd4u.o ${OBJECTDIR}/UARTLib.o ${OBJECTDIR}/RS485.o ${OBJECTDIR}/satellites.o ${OBJECTDIR}/datetime.o ${OBJECTDIR}/CustomHTTPApp.o ${OBJECTDIR}/code.o ${OBJECTDIR}/exception.o ${OBJECTDIR}/password.o ${OBJECTDIR}/MPFSImg2.o

# Source Files
SOURCEFILES=../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S D:/Projets/CERES/SW/FreeRTOS/Source/croutine.c D:/Projets/CERES/SW/FreeRTOS/Source/portable/MemMang/heap_4.c D:/Projets/CERES/SW/FreeRTOS/Source/list.c D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c D:/Projets/CERES/SW/FreeRTOS/Source/queue.c D:/Projets/CERES/SW/FreeRTOS/Source/tasks.c D:/Projets/CERES/SW/FreeRTOS/Source/timers.c MDB.c mdb_bv.c mdb_cg.c mdb_cl.c ../Microchip/TCPIP Stack/ARP.c ../Microchip/TCPIP Stack/Announce.c ../Microchip/TCPIP Stack/AutoIP.c ../Microchip/TCPIP Stack/DHCP.c ../Microchip/TCPIP Stack/DHCPs.c ../Microchip/TCPIP Stack/DNS.c ../Microchip/TCPIP Stack/DNSs.c ../Microchip/TCPIP Stack/Delay.c ../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c ../Microchip/TCPIP Stack/ETHPIC32IntMac.c ../Microchip/TCPIP Stack/HTTP2.c ../Microchip/TCPIP Stack/Helpers.c ../Microchip/TCPIP Stack/IP.c ../Microchip/TCPIP Stack/MPFS2.c ../Microchip/TCPIP Stack/NBNS.c ../Microchip/TCPIP Stack/SMTP.c ../Microchip/TCPIP Stack/StackTsk.c ../Microchip/TCPIP Stack/TCP.c ../Microchip/TCPIP Stack/Tick.c ../Microchip/TCPIP Stack/UDP.c ../Microchip/TCPIP Stack/DynDNS.c ../Microchip/TCPIP Stack/SNTP.c ../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c usb_config.c usb_descriptors.c ../Microchip/USB/usb_device.c ../Microchip/USB/CDC Device Driver/usb_function_cdc.c ../Microchip/USB/usb_host.c ../Microchip/USB/MSD Host Driver/usb_host_msd.c ../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c ../Microchip/MDD File System/FSIO.c main.c HexKeyboard.c I2CE2PROML.c lcd4u.c UARTLib.C RS485.c satellites.c datetime.c CustomHTTPApp.c code.c exception.c password.c MPFSImg2.c


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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/971107649/port_asm.o: ../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/971107649" 
	@${RM} ${OBJECTDIR}/_ext/971107649/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/971107649/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/971107649/port_asm.o.ok ${OBJECTDIR}/_ext/971107649/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/971107649/port_asm.o.d" "${OBJECTDIR}/_ext/971107649/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/971107649/port_asm.o.d"  -o ${OBJECTDIR}/_ext/971107649/port_asm.o ../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_Release=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/971107649/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1
	
else
${OBJECTDIR}/_ext/971107649/port_asm.o: ../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/971107649" 
	@${RM} ${OBJECTDIR}/_ext/971107649/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/971107649/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/971107649/port_asm.o.ok ${OBJECTDIR}/_ext/971107649/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/971107649/port_asm.o.d" "${OBJECTDIR}/_ext/971107649/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/971107649/port_asm.o.d"  -o ${OBJECTDIR}/_ext/971107649/port_asm.o ../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_Release=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/971107649/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1729257553/croutine.o: D:/Projets/CERES/SW/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/croutine.o.d" -o ${OBJECTDIR}/_ext/1729257553/croutine.o D:/Projets/CERES/SW/FreeRTOS/Source/croutine.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1990890772/heap_4.o: D:/Projets/CERES/SW/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1990890772" 
	@${RM} ${OBJECTDIR}/_ext/1990890772/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1990890772/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1990890772/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1990890772/heap_4.o.d" -o ${OBJECTDIR}/_ext/1990890772/heap_4.o D:/Projets/CERES/SW/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/list.o: D:/Projets/CERES/SW/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/list.o.d" -o ${OBJECTDIR}/_ext/1729257553/list.o D:/Projets/CERES/SW/FreeRTOS/Source/list.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2099989927/port.o: D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2099989927" 
	@${RM} ${OBJECTDIR}/_ext/2099989927/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/2099989927/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2099989927/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/2099989927/port.o.d" -o ${OBJECTDIR}/_ext/2099989927/port.o D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/queue.o: D:/Projets/CERES/SW/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/queue.o.d" -o ${OBJECTDIR}/_ext/1729257553/queue.o D:/Projets/CERES/SW/FreeRTOS/Source/queue.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/tasks.o: D:/Projets/CERES/SW/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/tasks.o.d" -o ${OBJECTDIR}/_ext/1729257553/tasks.o D:/Projets/CERES/SW/FreeRTOS/Source/tasks.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/timers.o: D:/Projets/CERES/SW/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/timers.o.d" -o ${OBJECTDIR}/_ext/1729257553/timers.o D:/Projets/CERES/SW/FreeRTOS/Source/timers.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/MDB.o: MDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MDB.o.d 
	@${RM} ${OBJECTDIR}/MDB.o 
	@${FIXDEPS} "${OBJECTDIR}/MDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/MDB.o.d" -o ${OBJECTDIR}/MDB.o MDB.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mdb_bv.o: mdb_bv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mdb_bv.o.d 
	@${RM} ${OBJECTDIR}/mdb_bv.o 
	@${FIXDEPS} "${OBJECTDIR}/mdb_bv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/mdb_bv.o.d" -o ${OBJECTDIR}/mdb_bv.o mdb_bv.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mdb_cg.o: mdb_cg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mdb_cg.o.d 
	@${RM} ${OBJECTDIR}/mdb_cg.o 
	@${FIXDEPS} "${OBJECTDIR}/mdb_cg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/mdb_cg.o.d" -o ${OBJECTDIR}/mdb_cg.o mdb_cg.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mdb_cl.o: mdb_cl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mdb_cl.o.d 
	@${RM} ${OBJECTDIR}/mdb_cl.o 
	@${FIXDEPS} "${OBJECTDIR}/mdb_cl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/mdb_cl.o.d" -o ${OBJECTDIR}/mdb_cl.o mdb_cl.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ARP.o: ../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ARP.o.d" -o ${OBJECTDIR}/_ext/867694782/ARP.o "../Microchip/TCPIP Stack/ARP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Announce.o: ../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Announce.o.d" -o ${OBJECTDIR}/_ext/867694782/Announce.o "../Microchip/TCPIP Stack/Announce.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/AutoIP.o: ../Microchip/TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/AutoIP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/AutoIP.o.d" -o ${OBJECTDIR}/_ext/867694782/AutoIP.o "../Microchip/TCPIP Stack/AutoIP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DHCP.o: ../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DHCP.o.d" -o ${OBJECTDIR}/_ext/867694782/DHCP.o "../Microchip/TCPIP Stack/DHCP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DHCPs.o: ../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DHCPs.o.d" -o ${OBJECTDIR}/_ext/867694782/DHCPs.o "../Microchip/TCPIP Stack/DHCPs.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DNS.o: ../Microchip/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DNS.o.d" -o ${OBJECTDIR}/_ext/867694782/DNS.o "../Microchip/TCPIP Stack/DNS.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DNSs.o: ../Microchip/TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNSs.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNSs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DNSs.o.d" -o ${OBJECTDIR}/_ext/867694782/DNSs.o "../Microchip/TCPIP Stack/DNSs.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Delay.o: ../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Delay.o.d" -o ${OBJECTDIR}/_ext/867694782/Delay.o "../Microchip/TCPIP Stack/Delay.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o: ../Microchip/TCPIP\ Stack/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o "../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o: ../Microchip/TCPIP\ Stack/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o "../Microchip/TCPIP Stack/ETHPIC32IntMac.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/HTTP2.o: ../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/HTTP2.o.d" -o ${OBJECTDIR}/_ext/867694782/HTTP2.o "../Microchip/TCPIP Stack/HTTP2.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Helpers.o: ../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Helpers.o.d" -o ${OBJECTDIR}/_ext/867694782/Helpers.o "../Microchip/TCPIP Stack/Helpers.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/IP.o: ../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/IP.o.d" -o ${OBJECTDIR}/_ext/867694782/IP.o "../Microchip/TCPIP Stack/IP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/MPFS2.o: ../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/MPFS2.o.d" -o ${OBJECTDIR}/_ext/867694782/MPFS2.o "../Microchip/TCPIP Stack/MPFS2.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/NBNS.o: ../Microchip/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/NBNS.o.d" -o ${OBJECTDIR}/_ext/867694782/NBNS.o "../Microchip/TCPIP Stack/NBNS.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/SMTP.o: ../Microchip/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/SMTP.o.d" -o ${OBJECTDIR}/_ext/867694782/SMTP.o "../Microchip/TCPIP Stack/SMTP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/StackTsk.o: ../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" -o ${OBJECTDIR}/_ext/867694782/StackTsk.o "../Microchip/TCPIP Stack/StackTsk.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/TCP.o: ../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/TCP.o.d" -o ${OBJECTDIR}/_ext/867694782/TCP.o "../Microchip/TCPIP Stack/TCP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Tick.o: ../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Tick.o.d" -o ${OBJECTDIR}/_ext/867694782/Tick.o "../Microchip/TCPIP Stack/Tick.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/UDP.o: ../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/UDP.o.d" -o ${OBJECTDIR}/_ext/867694782/UDP.o "../Microchip/TCPIP Stack/UDP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DynDNS.o: ../Microchip/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DynDNS.o.d" -o ${OBJECTDIR}/_ext/867694782/DynDNS.o "../Microchip/TCPIP Stack/DynDNS.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/SNTP.o: ../Microchip/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/SNTP.o.d" -o ${OBJECTDIR}/_ext/867694782/SNTP.o "../Microchip/TCPIP Stack/SNTP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o: ../Microchip/TCPIP\ Stack/ETHPIC32ExtPhyDP83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d" -o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o "../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_config.o: usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_config.o.d 
	@${RM} ${OBJECTDIR}/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/usb_config.o.d" -o ${OBJECTDIR}/usb_config.o usb_config.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/343710134/usb_device.o: ../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/343710134" 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_device.o.d" -o ${OBJECTDIR}/_ext/343710134/usb_device.o ../Microchip/USB/usb_device.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/131024517/usb_function_cdc.o: ../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131024517" 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o "../Microchip/USB/CDC Device Driver/usb_function_cdc.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/343710134/usb_host.o: ../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/343710134" 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_host.o.d" -o ${OBJECTDIR}/_ext/343710134/usb_host.o ../Microchip/USB/usb_host.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/131683717/usb_host_msd.o: ../Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131683717" 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/131683717/usb_host_msd.o "../Microchip/USB/MSD Host Driver/usb_host_msd.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o: ../Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131683717" 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o "../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2054364014/FSIO.o: ../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2054364014" 
	@${RM} ${OBJECTDIR}/_ext/2054364014/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/2054364014/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2054364014/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/2054364014/FSIO.o.d" -o ${OBJECTDIR}/_ext/2054364014/FSIO.o "../Microchip/MDD File System/FSIO.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HexKeyboard.o: HexKeyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HexKeyboard.o.d 
	@${RM} ${OBJECTDIR}/HexKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/HexKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/HexKeyboard.o.d" -o ${OBJECTDIR}/HexKeyboard.o HexKeyboard.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/I2CE2PROML.o: I2CE2PROML.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2CE2PROML.o.d 
	@${RM} ${OBJECTDIR}/I2CE2PROML.o 
	@${FIXDEPS} "${OBJECTDIR}/I2CE2PROML.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/I2CE2PROML.o.d" -o ${OBJECTDIR}/I2CE2PROML.o I2CE2PROML.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lcd4u.o: lcd4u.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd4u.o.d 
	@${RM} ${OBJECTDIR}/lcd4u.o 
	@${FIXDEPS} "${OBJECTDIR}/lcd4u.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/lcd4u.o.d" -o ${OBJECTDIR}/lcd4u.o lcd4u.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/UARTLib.o: UARTLib.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UARTLib.o.d 
	@${RM} ${OBJECTDIR}/UARTLib.o 
	@${FIXDEPS} "${OBJECTDIR}/UARTLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/UARTLib.o.d" -o ${OBJECTDIR}/UARTLib.o UARTLib.C    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/RS485.o: RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RS485.o.d 
	@${RM} ${OBJECTDIR}/RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/RS485.o.d" -o ${OBJECTDIR}/RS485.o RS485.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/satellites.o: satellites.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/satellites.o.d 
	@${RM} ${OBJECTDIR}/satellites.o 
	@${FIXDEPS} "${OBJECTDIR}/satellites.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/satellites.o.d" -o ${OBJECTDIR}/satellites.o satellites.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/datetime.o: datetime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/datetime.o.d 
	@${RM} ${OBJECTDIR}/datetime.o 
	@${FIXDEPS} "${OBJECTDIR}/datetime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/datetime.o.d" -o ${OBJECTDIR}/datetime.o datetime.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/CustomHTTPApp.o: CustomHTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CustomHTTPApp.o.d 
	@${RM} ${OBJECTDIR}/CustomHTTPApp.o 
	@${FIXDEPS} "${OBJECTDIR}/CustomHTTPApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/CustomHTTPApp.o.d" -o ${OBJECTDIR}/CustomHTTPApp.o CustomHTTPApp.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/code.o: code.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/code.o.d 
	@${RM} ${OBJECTDIR}/code.o 
	@${FIXDEPS} "${OBJECTDIR}/code.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/code.o.d" -o ${OBJECTDIR}/code.o code.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/exception.o: exception.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exception.o.d 
	@${RM} ${OBJECTDIR}/exception.o 
	@${FIXDEPS} "${OBJECTDIR}/exception.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/exception.o.d" -o ${OBJECTDIR}/exception.o exception.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/password.o: password.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/password.o.d 
	@${RM} ${OBJECTDIR}/password.o 
	@${FIXDEPS} "${OBJECTDIR}/password.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/password.o.d" -o ${OBJECTDIR}/password.o password.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/MPFSImg2.o: MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MPFSImg2.o.d 
	@${RM} ${OBJECTDIR}/MPFSImg2.o 
	@${FIXDEPS} "${OBJECTDIR}/MPFSImg2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/MPFSImg2.o.d" -o ${OBJECTDIR}/MPFSImg2.o MPFSImg2.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1729257553/croutine.o: D:/Projets/CERES/SW/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/croutine.o.d" -o ${OBJECTDIR}/_ext/1729257553/croutine.o D:/Projets/CERES/SW/FreeRTOS/Source/croutine.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1990890772/heap_4.o: D:/Projets/CERES/SW/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1990890772" 
	@${RM} ${OBJECTDIR}/_ext/1990890772/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1990890772/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1990890772/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1990890772/heap_4.o.d" -o ${OBJECTDIR}/_ext/1990890772/heap_4.o D:/Projets/CERES/SW/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/list.o: D:/Projets/CERES/SW/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/list.o.d" -o ${OBJECTDIR}/_ext/1729257553/list.o D:/Projets/CERES/SW/FreeRTOS/Source/list.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2099989927/port.o: D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2099989927" 
	@${RM} ${OBJECTDIR}/_ext/2099989927/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/2099989927/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2099989927/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/2099989927/port.o.d" -o ${OBJECTDIR}/_ext/2099989927/port.o D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/queue.o: D:/Projets/CERES/SW/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/queue.o.d" -o ${OBJECTDIR}/_ext/1729257553/queue.o D:/Projets/CERES/SW/FreeRTOS/Source/queue.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/tasks.o: D:/Projets/CERES/SW/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/tasks.o.d" -o ${OBJECTDIR}/_ext/1729257553/tasks.o D:/Projets/CERES/SW/FreeRTOS/Source/tasks.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1729257553/timers.o: D:/Projets/CERES/SW/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1729257553" 
	@${RM} ${OBJECTDIR}/_ext/1729257553/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1729257553/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1729257553/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/1729257553/timers.o.d" -o ${OBJECTDIR}/_ext/1729257553/timers.o D:/Projets/CERES/SW/FreeRTOS/Source/timers.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/MDB.o: MDB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MDB.o.d 
	@${RM} ${OBJECTDIR}/MDB.o 
	@${FIXDEPS} "${OBJECTDIR}/MDB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/MDB.o.d" -o ${OBJECTDIR}/MDB.o MDB.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mdb_bv.o: mdb_bv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mdb_bv.o.d 
	@${RM} ${OBJECTDIR}/mdb_bv.o 
	@${FIXDEPS} "${OBJECTDIR}/mdb_bv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/mdb_bv.o.d" -o ${OBJECTDIR}/mdb_bv.o mdb_bv.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mdb_cg.o: mdb_cg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mdb_cg.o.d 
	@${RM} ${OBJECTDIR}/mdb_cg.o 
	@${FIXDEPS} "${OBJECTDIR}/mdb_cg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/mdb_cg.o.d" -o ${OBJECTDIR}/mdb_cg.o mdb_cg.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mdb_cl.o: mdb_cl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mdb_cl.o.d 
	@${RM} ${OBJECTDIR}/mdb_cl.o 
	@${FIXDEPS} "${OBJECTDIR}/mdb_cl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/mdb_cl.o.d" -o ${OBJECTDIR}/mdb_cl.o mdb_cl.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ARP.o: ../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ARP.o.d" -o ${OBJECTDIR}/_ext/867694782/ARP.o "../Microchip/TCPIP Stack/ARP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Announce.o: ../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Announce.o.d" -o ${OBJECTDIR}/_ext/867694782/Announce.o "../Microchip/TCPIP Stack/Announce.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/AutoIP.o: ../Microchip/TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/AutoIP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/AutoIP.o.d" -o ${OBJECTDIR}/_ext/867694782/AutoIP.o "../Microchip/TCPIP Stack/AutoIP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DHCP.o: ../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DHCP.o.d" -o ${OBJECTDIR}/_ext/867694782/DHCP.o "../Microchip/TCPIP Stack/DHCP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DHCPs.o: ../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DHCPs.o.d" -o ${OBJECTDIR}/_ext/867694782/DHCPs.o "../Microchip/TCPIP Stack/DHCPs.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DNS.o: ../Microchip/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DNS.o.d" -o ${OBJECTDIR}/_ext/867694782/DNS.o "../Microchip/TCPIP Stack/DNS.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DNSs.o: ../Microchip/TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNSs.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DNSs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DNSs.o.d" -o ${OBJECTDIR}/_ext/867694782/DNSs.o "../Microchip/TCPIP Stack/DNSs.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Delay.o: ../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Delay.o.d" -o ${OBJECTDIR}/_ext/867694782/Delay.o "../Microchip/TCPIP Stack/Delay.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o: ../Microchip/TCPIP\ Stack/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhy.o "../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o: ../Microchip/TCPIP\ Stack/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/867694782/ETHPIC32IntMac.o "../Microchip/TCPIP Stack/ETHPIC32IntMac.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/HTTP2.o: ../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/HTTP2.o.d" -o ${OBJECTDIR}/_ext/867694782/HTTP2.o "../Microchip/TCPIP Stack/HTTP2.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Helpers.o: ../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Helpers.o.d" -o ${OBJECTDIR}/_ext/867694782/Helpers.o "../Microchip/TCPIP Stack/Helpers.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/IP.o: ../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/IP.o.d" -o ${OBJECTDIR}/_ext/867694782/IP.o "../Microchip/TCPIP Stack/IP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/MPFS2.o: ../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/MPFS2.o.d" -o ${OBJECTDIR}/_ext/867694782/MPFS2.o "../Microchip/TCPIP Stack/MPFS2.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/NBNS.o: ../Microchip/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/NBNS.o.d" -o ${OBJECTDIR}/_ext/867694782/NBNS.o "../Microchip/TCPIP Stack/NBNS.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/SMTP.o: ../Microchip/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/SMTP.o.d" -o ${OBJECTDIR}/_ext/867694782/SMTP.o "../Microchip/TCPIP Stack/SMTP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/StackTsk.o: ../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/StackTsk.o.d" -o ${OBJECTDIR}/_ext/867694782/StackTsk.o "../Microchip/TCPIP Stack/StackTsk.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/TCP.o: ../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/TCP.o.d" -o ${OBJECTDIR}/_ext/867694782/TCP.o "../Microchip/TCPIP Stack/TCP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/Tick.o: ../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/Tick.o.d" -o ${OBJECTDIR}/_ext/867694782/Tick.o "../Microchip/TCPIP Stack/Tick.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/UDP.o: ../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/UDP.o.d" -o ${OBJECTDIR}/_ext/867694782/UDP.o "../Microchip/TCPIP Stack/UDP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/DynDNS.o: ../Microchip/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/DynDNS.o.d" -o ${OBJECTDIR}/_ext/867694782/DynDNS.o "../Microchip/TCPIP Stack/DynDNS.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/SNTP.o: ../Microchip/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/SNTP.o.d" -o ${OBJECTDIR}/_ext/867694782/SNTP.o "../Microchip/TCPIP Stack/SNTP.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o: ../Microchip/TCPIP\ Stack/ETHPIC32ExtPhyDP83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/867694782" 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D__L_DEBUG -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o.d" -o ${OBJECTDIR}/_ext/867694782/ETHPIC32ExtPhyDP83848.o "../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_config.o: usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_config.o.d 
	@${RM} ${OBJECTDIR}/usb_config.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/usb_config.o.d" -o ${OBJECTDIR}/usb_config.o usb_config.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/343710134/usb_device.o: ../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/343710134" 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_device.o.d" -o ${OBJECTDIR}/_ext/343710134/usb_device.o ../Microchip/USB/usb_device.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/131024517/usb_function_cdc.o: ../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131024517" 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/131024517/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/131024517/usb_function_cdc.o "../Microchip/USB/CDC Device Driver/usb_function_cdc.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/343710134/usb_host.o: ../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/343710134" 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_host.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_host.o.d" -o ${OBJECTDIR}/_ext/343710134/usb_host.o ../Microchip/USB/usb_host.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/131683717/usb_host_msd.o: ../Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131683717" 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/131683717/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/131683717/usb_host_msd.o "../Microchip/USB/MSD Host Driver/usb_host_msd.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o: ../Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/131683717" 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/131683717/usb_host_msd_scsi.o "../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2054364014/FSIO.o: ../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2054364014" 
	@${RM} ${OBJECTDIR}/_ext/2054364014/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/2054364014/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2054364014/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/_ext/2054364014/FSIO.o.d" -o ${OBJECTDIR}/_ext/2054364014/FSIO.o "../Microchip/MDD File System/FSIO.c"    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HexKeyboard.o: HexKeyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HexKeyboard.o.d 
	@${RM} ${OBJECTDIR}/HexKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/HexKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/HexKeyboard.o.d" -o ${OBJECTDIR}/HexKeyboard.o HexKeyboard.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/I2CE2PROML.o: I2CE2PROML.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2CE2PROML.o.d 
	@${RM} ${OBJECTDIR}/I2CE2PROML.o 
	@${FIXDEPS} "${OBJECTDIR}/I2CE2PROML.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/I2CE2PROML.o.d" -o ${OBJECTDIR}/I2CE2PROML.o I2CE2PROML.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lcd4u.o: lcd4u.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd4u.o.d 
	@${RM} ${OBJECTDIR}/lcd4u.o 
	@${FIXDEPS} "${OBJECTDIR}/lcd4u.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/lcd4u.o.d" -o ${OBJECTDIR}/lcd4u.o lcd4u.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/UARTLib.o: UARTLib.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UARTLib.o.d 
	@${RM} ${OBJECTDIR}/UARTLib.o 
	@${FIXDEPS} "${OBJECTDIR}/UARTLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/UARTLib.o.d" -o ${OBJECTDIR}/UARTLib.o UARTLib.C    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/RS485.o: RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RS485.o.d 
	@${RM} ${OBJECTDIR}/RS485.o 
	@${FIXDEPS} "${OBJECTDIR}/RS485.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/RS485.o.d" -o ${OBJECTDIR}/RS485.o RS485.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/satellites.o: satellites.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/satellites.o.d 
	@${RM} ${OBJECTDIR}/satellites.o 
	@${FIXDEPS} "${OBJECTDIR}/satellites.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/satellites.o.d" -o ${OBJECTDIR}/satellites.o satellites.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/datetime.o: datetime.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/datetime.o.d 
	@${RM} ${OBJECTDIR}/datetime.o 
	@${FIXDEPS} "${OBJECTDIR}/datetime.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/datetime.o.d" -o ${OBJECTDIR}/datetime.o datetime.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/CustomHTTPApp.o: CustomHTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CustomHTTPApp.o.d 
	@${RM} ${OBJECTDIR}/CustomHTTPApp.o 
	@${FIXDEPS} "${OBJECTDIR}/CustomHTTPApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/CustomHTTPApp.o.d" -o ${OBJECTDIR}/CustomHTTPApp.o CustomHTTPApp.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/code.o: code.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/code.o.d 
	@${RM} ${OBJECTDIR}/code.o 
	@${FIXDEPS} "${OBJECTDIR}/code.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/code.o.d" -o ${OBJECTDIR}/code.o code.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/exception.o: exception.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exception.o.d 
	@${RM} ${OBJECTDIR}/exception.o 
	@${FIXDEPS} "${OBJECTDIR}/exception.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/exception.o.d" -o ${OBJECTDIR}/exception.o exception.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/password.o: password.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/password.o.d 
	@${RM} ${OBJECTDIR}/password.o 
	@${FIXDEPS} "${OBJECTDIR}/password.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/password.o.d" -o ${OBJECTDIR}/password.o password.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/MPFSImg2.o: MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MPFSImg2.o.d 
	@${RM} ${OBJECTDIR}/MPFSImg2.o 
	@${FIXDEPS} "${OBJECTDIR}/MPFSImg2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -D_SUPPRESS_PLIB_WARNING -DCFG_INCLUDE_PIC32_ETH_SK_ETH795 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -DTRANSPORT_LAYER_USB_HOST -DDEMO_BOARD_EXPLORER_16 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -I"." -I"../FreeRTOS/Source/include" -I"../FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../Microchip/Include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/include" -I"D:/Projets/CERES/SW/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"D:/Projets/CERES/SW/Microchip/Include" -MMD -MF "${OBJECTDIR}/MPFSImg2.o.d" -o ${OBJECTDIR}/MPFSImg2.o MPFSImg2.c    -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_REAL_ICE=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,--defsym=_min_heap_size=1024,--defsym=_min_stack_size=1024,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--defsym=_min_stack_size=1024,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MainBoard_v_1_2_19.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} -r dist/Release

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
