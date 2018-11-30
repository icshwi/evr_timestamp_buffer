TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = esschic
# esschic.dbd will be created and installed
DBD += esschic.dbd

# esschic.dbd will be made up from these files:
esschic_DBD += base.dbd

# Include dbd files from all support applications:
#esschic_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#esschic_LIBS += xxx

# esschic_registerRecordDeviceDriver.cpp derives from esschic.dbd
esschic_SRCS += esschic_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
esschic_SRCS_DEFAULT += esschicMain.cpp
esschic_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#esschic_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
esschic_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

