TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = evr-timestamp-buffer
# evr-timestamp-buffer.dbd will be created and installed
DBD += evr-timestamp-buffer.dbd

# evr-timestamp-buffer.dbd will be made up from these files:
evr-timestamp-buffer_DBD += base.dbd

# Include dbd files from all support applications:
#evr-timestamp-buffer_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#evr-timestamp-buffer_LIBS += xxx

# evr-timestamp-buffer_registerRecordDeviceDriver.cpp derives from evr-timestamp-buffer.dbd
evr-timestamp-buffer_SRCS += evr-timestamp-buffer_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
evr-timestamp-buffer_SRCS_DEFAULT += evr-timestamp-bufferMain.cpp
evr-timestamp-buffer_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#evr-timestamp-buffer_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
evr-timestamp-buffer_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

