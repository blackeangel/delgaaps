LOCAL_PATH := $(call my-dir)

#####################################################################################
#delgaaps
#####################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE := bin_delgaaps

LOCAL_C_INCLUDES :=

LOCAL_CXXFLAGS := -fexceptions -std=c++2a

LOCAL_LDFLAGS := -fPIE -static -ldl

LOCAL_SRC_FILES := \
	delgaaps.cpp

include $(BUILD_EXECUTABLE)

