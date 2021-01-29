//----------------------------------------------------------------------------

#ifndef EFFECT_SDK_INFOSTICKER_AI_PUBLIC_DEFINE_H
#define EFFECT_SDK_INFOSTICKER_AI_PUBLIC_DEFINE_H

/// 信息化贴纸 handle 类型
typedef unsigned long long bef_info_sticker_ai_director;

/// 每个信息化贴纸的唯一 标识符类型
typedef const char *bef_info_sticker_ai_handle;

/// 信息化贴纸矩形描述，每个属性范围 -1.0 ~ 1.0，四个属性描述了在屏幕上的一个矩形区域.
typedef struct bef_ai_BoundingBox_2d_t {
    float left;
    float top;
    float right;
    float bottom;
} bef_ai_BoundingBox_2d;

/// 最大信息化贴纸变参数量.
#define INFO_STICKER_MAX_PARAMS 10

/// 信息化贴纸变参结构体, 记得释放
typedef struct bef_InfoSticker_ai_info_t{
    const char *params[INFO_STICKER_MAX_PARAMS];
    int count ;
}bef_InfoSticker_ai_info;

/// 颜色值, 0.0f ~ 1.0f
typedef struct bef_InfoSticker_ai_color {
    float r; float g; float b; float a;
}bef_InfoSticker_ai_color;

/// 每帧输入算法参数
typedef struct bef_InfoSticker_ai_algorithm_param {
    unsigned long frameId; // 当前帧的id
    double timeStamp;      // 算法时间戳
} bef_InfoSticker_ai_algorithm_param;

/// 算法输入纹理定义, 被定义在 bef_info_sticker_ai_api.h 文件中. rgba
typedef struct bef_InfoSticker_ai_texture {
    unsigned int srcIndex;       // 纹理索引
    unsigned int width;          // 纹理宽
    unsigned int height;         // 纹理高
} bef_InfoSticker_ai_texture;

/// 纹理 buff 定义，被定义在 bef_info_sticker_ai_api.h 文件中. rgba
typedef struct bef_InfoSticker_ai_texture_buff {
    unsigned char *buff;      // 纹理 buff
    unsigned int width;       // 纹理宽
    unsigned int height;      // 纹理高
} bef_InfoSticker_ai_texture_buff;

/// Pin 算法参数
typedef struct bef_InfoSticker_ai_pin_param {
    bef_info_sticker_ai_handle infoStickerName; // 要跟踪的信息化贴纸
    double startTime; // 起始时间
    double endTime;   // 结束时间
    double pinTime;   // pin 那一帧所在的时间
    bef_InfoSticker_ai_texture_buff initBuff; // pin 跟踪的初始纹理 buff
}bef_InfoSticker_ai_pin_param;

/// Pin 查询状态，查询 sticker 是否被 Pin
typedef enum bef_InfoSticker_ai_pin_state {
        bef_InfoSticker_ai_NONE = 0,    // 没被 Pin
        bef_InfoSticker_ai_PINNING,     // 正在 Pin
        bef_InfoSticker_ai_PINNED,      // 已被 Pin
}bef_InfoSticker_ai_pin_state;

typedef struct bef_InfoSticker_ai_crop_content_info {
    int contentWidth;
    int contentHeight;
}bef_InfoSticker_ai_crop_content_info;

#endif // EFFECT_SDK_INFOSTICKER_AI_PUBLIC_DEFINE_H
