LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= distance

LOCAL_SRC_FILES += distance.c

LOCAL_LDLIBS += -ldl -llog -latomic

include $(BUILD_SHARED_LIBRARY)
