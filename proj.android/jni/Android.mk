LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

REALIZE_LIBRARY_FILES_H := /$(wildcard $(LOCAL_PATH)../../../Realize/*.h)

LOCAL_SRC_FILES := /$(SRC_FILES)

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   $(wildcard C:/cocos2d-x-3.0beta2/projects/FourCard/Classes/*.cpp) \
                   $(wildcard C:/cocos2d-x-3.0beta2/projects/Realize/RealizeClient/*.cpp)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../Realize/RealizeClient \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,extensions)