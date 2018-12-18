TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = evr_timestamp_buffer
# evr_timestamp_buffer.dbd will be created and installed
DBD += evr_timestamp_buffer.dbd

# evr_timestamp_buffer.dbd will be made up from these files:
evr_timestamp_buffer_DBD += base.dbd

# Include dbd files from all support applications:
#evr_timestamp_buffer_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#evr_timestamp_buffer_LIBS += xxx

# evr_timestamp_buffer_registerRecordDeviceDriver.cpp derives from evr_timestamp_buffer.dbd
evr_timestamp_buffer_SRCS += evr_timestamp_buffer_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
evr_timestamp_buffer_SRCS_DEFAULT += evr_timestamp_bufferMain.cpp
evr_timestamp_buffer_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#evr_timestamp_buffer_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
evr_timestamp_buffer_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

