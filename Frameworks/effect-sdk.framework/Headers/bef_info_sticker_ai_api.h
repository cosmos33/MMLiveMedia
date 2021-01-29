//
// Created by bytedance game on 2018/9/28.
//

#ifndef bef_info_sticker_ai_api_h
#define bef_info_sticker_ai_api_h

#include "bef_effect_ai_public_define.h"
#include "bef_info_sticker_ai_public_define.h"
#include <stdbool.h>
//
// 信息化贴纸坐标系:
//
//                                (0，1)
//       Screen or DrawBoard    ^ X 轴
//      (-1.0, 1.0) ------------|-------------    (1, 1)
//                 |            |            |
//                 |            |            |
//                 |            |            |
//                 |            |            |
//                 |            |            |
//         (0, -1) |            | 原点 (0,0)  |
//                 |--------------------------> y (1, 0)
//                 |            |            |
//                 |            |            |
//                 |            |            |
//                 |            |            |
//                 |            |            |
//                 |            |            |
//         (-1,-1) |            |            |    (1,-1)
//                 -------------|-------------
//                               (0, 1)
//
// 信息化贴纸每个贴纸的坐标 (x, y）使用同 OpenGL 一样的归一化坐标值描述，
// 具体的真实像素坐标根据 Screen 或 DrawBoard 的具体 size 决定.
// 而 screen size 根据 set_width_height 接口设定.
// 例如：
// screen size 为 720 * 1280
// 某款贴纸 M 的坐标为 (1.0， 0.5), 则 M 在屏幕上的真实像素笛卡尔坐标为 (360.0, 320.0)
// 使用归一化坐标的优势：
// 当 screen size 变化时贴纸的坐标也会相对于 screen 进行变化，从而自然适配.

//----------------------------------------------------------------------------

// 关于  info_sticker_api 的 return 值
// type 为 bef_effect_result_t, 为 0 表示操作 success, 不为 0 则错误，具体数字有对应的错误码.

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_check_license(JNIEnv* env, jobject context, bef_info_sticker_ai_director handle, const char *licensePath);
#else
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_check_license(bef_info_sticker_ai_director handle, const char *licensePath);
#endif

/**
 * @brief 创建信息化贴纸 handle, 可选择内部使用的 gles version, 2.0 or 3.0. 渲染线程调用.
 * @param outHandlePtr handle, manage infoSticker 上下文
 * @param width 画布宽, 单位：像素
 * @param height 画布像素高, 单位：像素
 * @param type bef_render_api_gles20 使用 es2.0, bef_render_api_gles30 使用 es3.0 渲染
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_director_create_with_context(bef_info_sticker_ai_director *outHandlePtr,
                                                                              unsigned int width,
                                                                              unsigned int height,
                                                                              bef_ai_render_api_type type);

/**
 * @brief 初始化信息化贴纸画布 宽, 高. 渲染线程调用.
 * @param width  画布宽，单位：像素
 * @param height 画布高，单位：像素
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_width_height(bef_info_sticker_ai_director handle,
                                                                  unsigned int width,
                                                                  unsigned int height);

/* @brief 创建模型下发函数指针，内部算法通过该指针找到对应模型文件.
 * @param handle        信息化贴纸 handle
 * @param strModelDir   模型下发根目录
 * @return              函数指针，用于找对应的模型文件
*/
BEF_SDK_API bef_ai_resource_finder bef_info_sticker_ai_create_file_resource_finder(bef_info_sticker_ai_director handle, const char *strModelDir);


/** @brief 设置模型下发函数指针, 内部算法通过该指针找到对应模型文件.
 *  注意：若不调用该接口，则无法启用任何算法.
 *  @param handle 信息化贴纸 handle
 *  @param finder 模型下发函数指针, 值同 bef_effect_init 传入的 finder
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_resource_finder(bef_info_sticker_ai_director handle, bef_ai_resource_finder finder);


/**
 * @brief 释放信息化贴纸 handle 内存. 渲染线程调用.
 * @param handle 信息化贴纸 handle
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_director_destory(bef_info_sticker_ai_director handle);

/**
 * @brief 信息化贴纸时间戳驱动接口. 渲染线程调用.
 * @param handle 信息化贴纸 handle
 * @param srcTexture 输入纹理 gles id
 * @param dstTexture 输出纹理 gles id
 * @param timeStamp 时间戳，单位：秒
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_process_texture(bef_info_sticker_ai_director handle,
                                                                 bef_InfoSticker_ai_texture *srcTexture,
                                                                 unsigned int dstTexture,
                                                                 double timeStamp);

/**
 * @brief 功能同 bef_info_sticker_ai_process_texture. 下游目前使用 bef_info_sticker_ai_process_texture 接口. 渲染线程调用.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_seek_frame(bef_info_sticker_ai_director handle,
                                                            bef_InfoSticker_ai_texture *srcTexture,
                                                            unsigned int dstTexture,
                                                            double timeStamp);

/**
 * @brief 添加贴纸, 渲染线程调用
 * @param handle 信息化贴纸 handle
 * @param stickerPath 资源路径
 * @param outStickerName 输出贴纸对应的唯一标识名
 * @param parmsNum 额外参数个数
 * 后面变参数传类型 const char *, 如 0: 时间 UTC: "123123123", 1: 温度 : "37"
 * 变参会按顺序传入 sticker 资源包中，具体参数 根据客户端 rd 跟贴纸生产 rd 约定的 协议来确定传什么.
 *
 * ps:
 * 传单张 png 时，变参可用 4 个动态参数: left, right, bottom, top.
 * left, right, bottom, top 描述 png 在屏幕上所显示的矩形区域.
 * 坐标使用信息化贴纸归一化坐标系.
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_sticker_dynamic_params(bef_info_sticker_ai_director handle,
                                            const char *stickerPath,
                                            bef_info_sticker_ai_handle *outStickerName,
                                            int paramsNum,
                                            ...);

/**
 * @brief 添加贴纸, 功能同 bef_info_sticker_ai_add_sticker_dynamic_params. 渲染线程调用.
 * @param handle 信息化贴纸 handle
 * @param stickerPath 资源路径
 * @param outStickerName 输出贴纸对应的唯一标识名
 * @param parmsNum 额外参数个数
 * 后面变参数传类型 const char *, 如 0: 时间 UTC: "123123123", 1: 温度 : "37"
 * 变参会按顺序传入 sticker 资源包中，具体参数 根据客户端 rd 跟贴纸生产 rd 约定的 协议来确定传什么.
 *
 * ps:
 * 传单张 png 时，变参可用 4 个动态参数: left, right, bottom, top.
 * left, right, bottom, top 描述 png 在屏幕上所显示的矩形区域.
 * 坐标使用信息化贴纸归一化坐标系.
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_sticker(bef_info_sticker_ai_director
                             handle, const char *stickerPath,
                             bef_info_sticker_ai_handle *outStickerName,
                             bef_InfoSticker_ai_info *info);

/**
 * @brief 添加图像贴纸, 描述参数为 textureId 和 归一化 AABB 包围盒.
 * @param textureWidth  纹理宽度, 单位：像素
 * @param textureHeight 纹理高度, 单位：像素
 * @param in_box 为 (-1 ~ 1) 归一化坐标，可描述 texture 归一化的 pos, width, height
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_sticker_by_textureid_with_box(
                         bef_info_sticker_ai_director handle,
                         unsigned int stickerTextureId,
                         int textureWidth,
                         int textureHeight,
                         bef_ai_BoundingBox_2d in_box,
                         bef_info_sticker_ai_handle *outStickerName);

/// 旧接口，弃用，暂时保留，保证编译通过，后会删掉.
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_sticker_by_textureid(
                                          bef_info_sticker_ai_director handle,
                                          unsigned int stickerTextureId,
                                          int width,
                                          int height,
                                          bef_info_sticker_ai_handle *outStickerName);


/**
 * @brief 添加单张图形贴纸, 传递 rgba buffer, 对应的 sticker 以 view 宽为准, 按 720 px 设计分辨率缩放. 渲染线程调用.
 * @param stickerRgbaBuf 4 字节纹理数据
 * @param textureWidth   纹理像素宽度
 * @param textureHeight  纹理像素高度
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_sticker_by_rgba(
                                     bef_info_sticker_ai_director handle,
                                     const void *stickerRgbaBuf,
                                     int textureWidth,
                                     int textureHeight,
                                     bef_info_sticker_ai_handle *outStickerName);

/**
 * @brief 添加单张图像贴纸, 参数格式为 rgba buff. 对应的 sticker 适配以归一化坐标适配. 渲染线程调用.
 * @param textureWidth  纹理宽度, 单位：像素
 * @param textureHeight 纹理像素高度, 单位：像素
 * @param in_box 为 (-1 ~ 1) 归一化坐标，可描述 texture 归一化的 pos, width, height
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_sticker_by_rgba_with_box(
                        bef_info_sticker_ai_director handle,
                        const void *stickerRgbaBuf,
                        int textureWidth,
                        int textureHeight,
                        bef_ai_BoundingBox_2d in_box,
                        bef_info_sticker_ai_handle *outStickerName);

/**
 * @brief 移除贴纸. 也会释放 sticker 对应的 CPU 和 GPU 资源. 渲染线程调用.
 * @param handle 信息化贴纸 handle
 * @param stickerName 贴纸对应的唯一标识名
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_remove_sticker(bef_info_sticker_ai_director handle,
                                                                bef_info_sticker_ai_handle stickerName);


/// 编辑环境宏
#define OPERATION_CONTEXT_PREVIEW     "preview"

/// 合成环境宏
#define OPERATION_CONTEXT_COMPOSITION "composition"

/**
 * @brief 设置运行环境. 有些动画只有在编辑环境给用户交互时显示, 而合成时不显示.
 * @param OPERATION_CONTEXT_PREVIEW 编辑环境
 * @param OPERATION_CONTEXT_COMPOSITION 合成环境
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_operation_context(bef_info_sticker_ai_director handle, const char * context);

/**
 * @brief 判断贴纸是否是动画. 业务接口.
 * 场景是用户给一张图片添加贴纸时，若有至少一张贴纸是带动画的, 则合成时作为视频合成, 若没有一张贴纸带动画，则作为图片合成.
 * @param handle 信息化贴 handle.
 * @param infoStickerName 贴纸唯一标识名.
 * @param isAnimation 是否有动画.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_is_animation(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              bool* isAnimation);

BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_pause_all_animation(bef_info_sticker_ai_director handle, bool pause);

/**
 * @brief 设置贴纸的 旋转角度, 绕位置中心旋转.
 * @param infoStickerName 贴纸唯一标识名.
 * @@param angle 贴纸旋转角度，单位：角度. 正值逆时针，负值顺时针.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_rotation(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              float angle);
/**
 * @brief 获取贴纸的 旋转角度.
 * @param infoStickerName 贴纸唯一标识名.
 * @param *angle 输出的角度
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_rotation(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              float *angle);

/**
 * @brief 设置贴纸相对现有尺寸的缩放尺寸, 假设当前 sticker scaleX 为 2.0, 传入 scaleX 为 2.0, 则实际 scaleX 为 2.0 * 2.0 = 4.0.
 * @param scaleX X 方向相对缩放值
 * @param scaleY Y 方向相对缩放值
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_scale(bef_info_sticker_ai_director handle,
                                                       bef_info_sticker_ai_handle infoStickerName,
                                                       float scaleX,
                                                       float scaleY);

/**
 * @brief 设置贴纸绝对缩放尺寸, 假设当前 sticker scaleX 为 2.0, 传入 scaleX 为 3.0, 则实际 scaleX 为 3.0.
 * @param scaleX X 方向绝对缩放值
 * @param scaleY Y 方向绝对缩放值
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_scale(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           float scaleX,
                                                           float scaleY);
/**
 * @brief 获取 sticker 绝对缩放尺寸.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_scale(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           float *x,
                                                           float *y);

/**
 * @brief 设置贴纸坐标位置, 采用信息化贴纸归一化坐标（坐标说明见 api 抬头）
 * 信息化贴纸位置坐标系为：以屏幕中心点为原点 (0, 0), x 向右正, y 向上为正, x, y 范围为 -1.0 ~ 1.0. （同 OpenGL 坐标）
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸唯一标识名
 * @param x x 轴坐标, 值范围 -1.0 ~ 1.0
 * @param y y 轴坐标，值范围 -1.0 ~ 1.0
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_position(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              float x,
                                                              float y);
/**
 * @brief 获取贴纸坐标位置.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_position(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              float *x,
                                                              float *y);

/**
 * @brief 镜像翻转贴纸，支持 水平 或 垂直 翻转.
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸唯一标识名
 * @param flipX 是否水平翻转, true 为翻转，false 为不翻转，即默认方向
 * @param flipY 是否垂直翻转，true 为翻转，false 为不翻转，即默认方向
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_flip(bef_info_sticker_ai_director handle,
                                                          bef_info_sticker_ai_handle infoStickerName,
                                                          bool flipX,
                                                          bool flipY);

/**
 * @brief 获取贴纸翻转值.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_flip(bef_info_sticker_ai_director handle,
                                                          bef_info_sticker_ai_handle infoStickerName,
                                                          bool *flipX,
                                                          bool *flipY);

/**
 * @brief 设置贴纸在同一层 layer 中的绘制顺序，order 越大, 显示越上, order >= 0.
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸唯一标识名
 * @param order 贴纸的顺序, >= 0, 不要为负值.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_order_in_layer(bef_info_sticker_ai_director handle,
                                                                    bef_info_sticker_ai_handle infoStickerName,
                                                                    unsigned int order);

/**
 * @brief 获取贴纸的所在 layer 中的 order.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_order_in_layer(bef_info_sticker_ai_director handle,
                                                                    bef_info_sticker_ai_handle infoStickerName,
                                                                    unsigned int *order);

/**
 * @brief 设置贴纸在到某个 layer(图层), 通常用于对贴纸做分组 (比如背景和ui分组), layer 越大显示越上. layer >= 0.
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸唯一标识名
 * @param layer 贴纸的层级, >= 0.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_layer(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           unsigned int layer);

/**
 * @brief 获取贴纸 layer 层级.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_layer(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           unsigned int *layer);

/**
 * @brief 设置贴纸透明度,
 * @infoStickerName 贴纸唯一标识名
 * @alpha 透明度, 0.0 ~ 1.0 范围, 为 0 全透明不显示，为 1 完全显示
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_alpha(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           float alpha);

/**
 * @brief 获取贴纸透明度.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_alpha(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           float *alpha);

/**
  * @brief 获取贴纸 本地坐标系显示区域，显示区域为 AABB 包围盒, 使用 bef_ai_BoundingBox_2d 描述.
  * 场景：客户端通过该区域判断是否点用户选中贴纸.
  * @param infoStickerName 贴纸唯一标识名
  * @param out_box 返回贴纸进行 ‘平移，缩放，旋转’ 变换后的 AABB 包围盒，表示坐标为 -1 ~ 1 归一化坐标.
  */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_local_boundingbox(bef_info_sticker_ai_director handle,
                                                                       bef_info_sticker_ai_handle infoStickerName,
                                                                       bef_ai_BoundingBox_2d *out_box);

/**
  * @brief 获取贴纸 本地坐标系显示区域，显示区域为 AABB 包围盒, 使用 bef_ai_BoundingBox_2d 描述.
  * 但该包围盒只包含缩放变换, 不包含 旋转，移动变换.
  * 场景：客户端通过该区域判断是否点用户选中贴纸. 目前业务使用该接口.
  * @param infoStickerName 贴纸唯一标识名
  * @param out_box 返回贴纸仅仅进行 ‘缩放’ 变换后的 AABB 包围盒，四个顶点表示坐标为 信息化贴纸 的归一化坐标系.
  */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_local_boundingbox_with_scale(bef_info_sticker_ai_director handle,
                                                                                  bef_info_sticker_ai_handle infoStickerName,
                                                                                  bef_ai_BoundingBox_2d *out_box);


/**
 * @brief 获取贴纸 世界坐标系显示区域. 其余同 bef_info_sticker_ai_get_local_boundingbox.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_world_boundingbox(bef_info_sticker_ai_director handle,
                                                                       bef_info_sticker_ai_handle infoStickerName,
                                                                       bef_ai_BoundingBox_2d *out_box);

/**
 * @brief 设置贴纸是否隐藏. 与设置 alpha 为 0 不同, 若隐藏, 内部会对该贴纸停止调用 OpenGLES 绘制命令.
 * @param flag true 为显示，false 为隐藏，隐藏时不释放内存.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_visible(bef_info_sticker_ai_director handle,
                                                             bef_info_sticker_ai_handle infoStickerName,
                                                             bool flag);
/**
 * @brief 获取贴纸是否隐藏.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_visible(bef_info_sticker_ai_director handle,
                                                             bef_info_sticker_ai_handle infoStickerName,
                                                             bool *flag);

/**
 * @brief 设置贴纸开始播放动画时间.
 * 例如, 0 ~ 15 秒视频, 设置开始播放时间为 3 秒，则贴纸动画在第 3 秒开始播放. 否则会从第 0 秒开始播放.
 * @param stickerName 贴纸唯一标识名
 * @param timeStamp 开始播放的时间, 单位：秒
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_entrance_time(bef_info_sticker_ai_director handle,
                                                                   bef_info_sticker_ai_handle stickerName,
                                                                   float timeStamp);

// 画笔 api

BEF_SDK_API bef_effect_result_t  bef_info_ai_begin_2d_brush(bef_info_sticker_ai_director handle);

BEF_SDK_API bef_effect_result_t  bef_info_ai_end_2d_brush(bef_info_sticker_ai_director handle);

BEF_SDK_API bef_effect_result_t  get_info_ai_brush_buf_size(bef_info_sticker_ai_director handle,
                                                         int* bufSize,
                                                         int* width,
                                                         int* height);

BEF_SDK_API bef_effect_result_t  get_info_ai_brush_buf_content(bef_info_sticker_ai_director handle,
                                                            void* pBuf,
                                                            int bufSize);

/**
 设置画笔粗细

 @param handle 信息化贴纸handle
 @param size 画笔粗细。归一化坐标，以分辨率宽度为基准。
 @return 是否成功
 */
BEF_SDK_API bef_effect_result_t  bef_info_ai_set_2d_brush_size(bef_info_sticker_ai_director handle, float size);

// 设置画笔颜色
BEF_SDK_API bef_effect_result_t  bef_info_ai_set_2d_brush_color(bef_info_sticker_ai_director handle, float r, float g, float b, float a);

BEF_SDK_API bef_effect_result_t  bef_info_ai_undo_2d_brush_stroke(bef_info_sticker_ai_director handle);

BEF_SDK_API int  bef_info_ai_get_2d_brush_stroke_count(bef_info_sticker_ai_director handle);

BEF_SDK_API bef_effect_result_t bef_info_ai_sticker_ai_set_2d_brush_canvas_alpha(bef_info_sticker_ai_director handle, float alpha);


// animation
/**
 设置动画

 @param handle              信息化贴纸handle
 @param infoStickerName     信息化贴纸Name
 @param animId              动画id
 @param inTime              动画入场时间(s)
 @param stillTime           动画持续时间(s)（不包括入出场时间）
 @param outTime             动画出场时间(s)
 @return 是否成功
 */

/**
    动画id：5 位int 用ABCDE表示:
    A = 0  表示   无动画;
    A = 1  表示   非循环动画;
    A = 2  表示   循环动画;

    BC 表示   出场动画类型
    DE 表示   入场动画类型
        动画类型：0  -->  无动画
                1  -->  alpha
                2  -->  放大
                3  -->  缩小
                4  -->  右移
                5  -->  左移
                6  -->  下移
                7  -->  上移
                8  -->  摇晃
                9  -->  旋转
                10 -->  闪烁
                11 -->  心跳
                12 -->  跳动

    例如：
        1.
        animId = 10101  inTime = 1.0f  stillTime = 2.0f  outTime = 1.0f
        非循环动画，入场alpha动画持续1s，停顿2s，出场alpha动画持续1s。

        2.
        animId = 20008  inTime = 2.0f  stillTime = 3.0f  outTime = 0.0f
        循环动画，摇晃2s，停顿3s，再摇晃2s，停顿3s...

        3.
        animId = 0  inTime = 0.0f  stillTime = 0.0f  outTime = 0.0f
        无动画

*/

BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_anim(
        bef_info_sticker_ai_director handle,
        bef_info_sticker_ai_handle infoStickerName,
        int animId,
        float inTime,
        float stillTime,
        float outTime);

/**
 * @brief 设置动画
 * @param startTime             动画开始播放的时间(s)
 * 其他参数，参考bef_info_sticker_ai_set_anim
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_anim_with_start_time(
        bef_info_sticker_ai_director handle,
        bef_info_sticker_ai_handle infoStickerName,
        int animId,
        float inTime,
        float stillTime,
        float outTime,
        float startTime);

/**
  * @brief 设置动画是否用绝对时间更新.
  * @param handle              信息化贴纸handle
  * @param infoStickerName     信息化贴纸Name
  * @param selfUpdate          是否用绝对时间更新动
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_anim_absolute_update(
        bef_info_sticker_ai_director handle,
        bef_info_sticker_ai_handle infoStickerName,
        bool absoluteUpdate);

// 信息化贴纸 - Pin api

/**
 * @brief 开始 pin 操作，设置初始参数：指定要 pin 的贴纸，对应的起始时间、结束时间.
 * @param handle 信息化贴纸 handle
 * @param param pin 算法参数
 * @param debugCode 算法处理码，0 可以跟踪，其他值表示有可能会跟乱，不管 debugCode
 * 是什么值，只要该接口不返回 BEF_RESULT_FAIL 就可以进行后续跟踪操作
 * @return BEF_RESULT_SUC Pin 初始成功, BEF_RESULT_FAIL Pin 初始失败，不要进行后续操作
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_begin_pin(bef_info_sticker_ai_director handle,
                                                           bef_InfoSticker_ai_pin_param *param,
                                                           int *debugCode);

/**
 * @brief 算法处理纹理唯一接口, 其他接口需要收敛到此接口. Pin 算法使用该接口 seek.
 * @param handle          信息化贴纸 handle
 * @param srcTextures     输入检测的纹理，传入数组. 可以是多个, 每个纹理的宽高可以
 * @param size            输入检测的纹理个
 * @param param           算法处理的额外
 * @return 返回 BEF_RESULT_SUC 表示该帧处理成功，BEF_RESULT_FAIL 表示该帧处理失败
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_algorithm_textures_with_param(bef_info_sticker_ai_director handle,
                                                                               bef_InfoSticker_ai_texture *srcTextures,
                                                                               unsigned int size,
                                                                               bef_InfoSticker_ai_algorithm_param *param);

/**
 * @brief 结束 pin 操作, 调用该接口说明表示不将再传帧进入, sticker 的 bef_InfoSticker_ai_pin_state 状态由
 * PINNING 转换为 PINNED.
 * @param handle 信息化贴纸 handle
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_end_pin(bef_info_sticker_ai_director handle);

/**
 * @brief 对指定贴纸取消 pin, 清空对应的算法内存数据，贴纸 bef_InfoSticker_ai_pin_state 状态由 PINNED 转换为 NONE;
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸唯一标识名
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_cancel_pin(bef_info_sticker_ai_director handle,
                                                            bef_info_sticker_ai_handle infoStickerName);

/// 设置 pin 数据恢复模式.
typedef enum bef_InfoSticker_ai_pin_restore_mode {
    bef_InfoSticker_ai_PIN_RESTORE_ORIGIN = 0,            // pin 算法数据按原始   viewSize 适配
    bef_InfoSticker_ai_PIN_RESTORE_NORMALIZED = 1,         // pin 算法数据按归一化适配
    bef_InfoSticker_ai_PIN_RESTORE_CROP_NORMALIZED = 2,     // pin 算法按裁剪归一化适配
}bef_InfoSticker_ai_pin_restore_mode;

/**
 * @brief 设置信息化恢复模式，默认值是 bef_InfoSticker_ai_pin_restore_mode::bef_InfoSticker_ai_PIN_RESTORE_ORIGIN
 * @param mode 目前有两种模式，解释入下：
 * bef_InfoSticker_ai_PIN_RESTORE_ORIGIN：
 * 当 pin 贴纸的画布 size 是 A * B 时。在新画布上 C * D 上 恢复时，
 * pin 的 x,y 坐标数据（坐标点以画布中心点为原点）仍然按 A * B 来计算，不受画布 size 变化影响.
 *
 * bef_InfoSticker_ai_PIN_RESTORE_NORMALIZED：
 * 当 pin 贴纸的画布 size 是 A * B 时。在新画布上 C * D 上，
 * pin 的 x,y 坐标数据（坐标点以画布中心点为原点）按 C * D 相对于 A * B 的缩放（即归一化）值来计算，会受画布 size 变化影响.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_pin_restore_mode(bef_info_sticker_ai_director handle,
                                                                      bef_InfoSticker_ai_pin_restore_mode mode);

/**
 * @brief 对贴纸传入 pin 已保存的算法数据. (草稿箱恢复时使用).
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸的 handle
 * @param data 算法数据, byte buffer, protobuf 协议, 中间可能含有 /0, 不要用 string 去读写.
 * @param size data size
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_pin_data(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              const void *data,
                                                              int size);

/**
 * @breif 获取 sticker 对应的 pin 状态.
 * @param handle 信息化贴纸 handle
 * @param infoStickerNaame 贴纸唯一标识名
 * @param state 输出 sticker 状态
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_pin_state(bef_info_sticker_ai_director handle,
                                                               bef_info_sticker_ai_handle infoStickerName,
                                                               bef_InfoSticker_ai_pin_state *state);

/**
 * @brief 如果是上下 或 左右 有黑边的视频，需要告诉视频相关信息, 比如内容的 size.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_crop_content_info(bef_info_sticker_ai_director handle,
                                                                       bef_info_sticker_ai_handle infoStickerName,
                                                                       bef_InfoSticker_ai_crop_content_info *info);

/**
 * @brief 调用该接口获取 pin 算法序列化数据，客户端可将改字符串写入文件中，从 (草稿箱恢复时) 传入文件即可将算法数据设置给 sticker.
 * @param handle 信息化贴纸 handle
 * @param infoStickerName 贴纸唯一表示名
 * @param data 外部记得不用后释放，算法数据，byte buffer, protobuf 协议, 中间可能含有 /0, 不要用 string 去读写.
 * @param size 获取 data size.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_pin_data(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              void **data,
                                                              int *size);


// 歌词贴纸相关 api

/**
 * @brief 设置字幕文本信息，json 字符串，如为 "歌词贴纸 feature"，传入 歌词的 json 协议即可.
 * @param handle 信息化贴纸句柄
 * @param infoStickerName 对应的歌词贴纸 name
 * @param content json 文件内容，以歌词为例：需包含 “曲名”，“歌手名”，及 歌词内容 和 对应时间信息 等相关信息；
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_srt_info(bef_info_sticker_ai_director handle,
                                                  bef_info_sticker_ai_handle infoStickerName,
                                                  const char *content);

/**
 * @brief 设置字体册文件路径.
 * @param handle 信息化贴纸句柄
 * @param infoStickerName 对应的歌词贴纸 name
 * @param path 字体文件路径，支持 .ttf .otf 等格式
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_font_path(bef_info_sticker_ai_director handle,
                                                   bef_info_sticker_ai_handle infoStickerName,
                                                   const char *path);

/**
 * @brief 设置字体册文件资源包路径.
 * @param handle 信息化贴纸句柄
 * @param infoStickerName 对应的歌词贴纸 name
 * @param dir 字体文件所在资源包路径，内含 一个 config.json, 一个 font.json，一个 字体册文件
 * font.json 指定字体册在资源包内所在的相对目录，包括文件名
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_font_dir(bef_info_sticker_ai_director handle,
                                                              bef_info_sticker_ai_handle infoStickerName,
                                                              const char *fontDir);


/**
 * @brief 获取字体册文件路径.
 * @param handle 信息化贴纸句柄
 * @param infoStickerName 对应的歌词贴纸 name
 * @param outPath 字体文件路径
 * @param size 字符 size，caller 建议分配 1000 保证足够大.
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_font_path(bef_info_sticker_ai_director handle,
                                                               bef_info_sticker_ai_handle infoStickerName,
                                                               char *outPath, const int size);

/**
 * @brief 设置当前歌词播放的绝对时间戳，紧接在 bef_info_sticker_ai_process_texture 前调用.
 * @param handle 信息化贴纸句柄
 * @param timestamp 歌词当前播放的绝对时间戳，单位：秒
 * @param startTime 裁剪歌词的起始时间，单位：秒
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_music_timestamp(bef_info_sticker_ai_director handle,
                                                         double timestamp,
                                                         double startTime);

/**
 * @brief 设置当前歌词播放的绝对时间戳，紧接在 bef_info_sticker_ai_process_texture 前调用，传入有效性 bool 值
 * @param handle 信息化贴纸句柄
 * @param timestamp 歌词当前播放的绝对时间戳，单位：秒
 * @param startTime 裁剪歌词的起始时间，单位：秒
 * @param isValid 当前时间戳是否有效，判断当前是有需要显示歌词
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_valid_music_timestamp(bef_info_sticker_ai_director handle,
                                                         double timestamp,
                                                         double startTime,
                                                         bool isValid);

/**
 * @brief  目前用于设置 "歌词贴纸" 显示颜色值
 * @param handle 信息化贴纸句柄
 * @param infoStickerName 对应的贴纸 name
 * @param color r, g, b, a 颜色值，范围 0.0 ~ 1.0
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_color(bef_info_sticker_ai_director handle,
                                               bef_info_sticker_ai_handle infoStickerName,
                                               bef_InfoSticker_ai_color color);

/**
 * @breif 获取颜色值.
 * @param handle 信息化贴纸句柄
 * @param infoStickerName 对应的贴纸 name
 * @param color r, g, b, a 颜色值，范围 0.0 ~ 1.0
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_get_color(bef_info_sticker_ai_director handle,
                                                           bef_info_sticker_ai_handle infoStickerName,
                                                           bef_InfoSticker_ai_color *color);

/**
 * @brief 歌词贴纸接口，编辑状态设置；解决用户旋转、缩放、平移（左对齐贴纸）贴纸的过程中，
 * 歌词长度不断变换而需要重新设置旋转中心点的问题；用户开始做 编辑操作（旋转，缩放，平移） 或 结束编辑操作（旋转，缩放，平移） 时调用
 * @param state 为 true 表示用户正在编辑，为 false 表示用户结束编辑
 */
BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_set_manipulate_state(bef_info_sticker_ai_director handle,
                                                          bef_info_sticker_ai_handle infoStickerName,
                                                          bool state);


/**
 * @brief 歌词贴纸接口，解决对齐偏移问题.
 * @param handle 信息化贴纸句柄
 * @param offsetX 输出偏移量 X 坐标
 * @param offsetY 输出偏移量 Y 坐标
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_get_offset(bef_info_sticker_ai_director handle, bef_info_sticker_ai_handle stickerName, float *offsetX, float *offsetY);



// Amazing Engine new api

BEF_SDK_API bef_effect_result_t bef_info_sticker_ai_director_create_with_context_amazing(
    bef_info_sticker_ai_director *outHandlePtr,
    unsigned int
    width, unsigned int height,
    bef_ai_render_api_type type,
    bool useAmazing);

/** 必须设置
 * @brief 渲染线程
 * @param start_time    元素timeline起始时间 (s)
 * @param end_time      元素timeline结束时间 (s)
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_set_sticker_time(bef_info_sticker_ai_director handle,
                                  bef_info_sticker_ai_handle sticker_handle,
                                  double start_time,
                                  double end_time);

/**
 * @brief 渲染线程，添加一个文字信息化贴纸
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_text_sticker(bef_info_sticker_ai_director handle, bef_info_sticker_ai_handle *sticker_handle);

/**
 * @brief 渲染线程，添加一个表情信息化贴纸
 * @param utf8code 对应表情的utf8编码
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_add_emoji(bef_info_sticker_ai_director handle, bef_info_sticker_ai_handle *sticker_handle, const char* utf8code);

/**
 * @brief 渲染线程
 * @param json  文字样式，形状，特效等
 *
 *
 enum class TextAlign
 {
 LEFT = 0,
 CENTER = 1,
 RIGHT = 2,
 UP = 3,
 DOWN = 4
 };
 fontSize: pt
 lineMaxWidth: 一行最大的宽度，超过自动换行，>0屏幕宽度的百分比，<0不限制
 color: rgba, [0, 1]
 outlineWidth: [0, 1]
 shadowSmoothing/shadowOffset/outlineWidth/charSpacing/innerPadding: 相对字高度
 {
 "version" : "1",
 "text": "content",
 "fontSize": 48,
 "alignType": 0,
 "textColor": [1, 0, 0, 1],
 "background": true,
 "backgroundColor": [1, 1, 1, 1],
 "shadow": true,
 "shadowColor": [0, 1, 0, 1],
 "shadowSmoothing": 1.0,
 "shadowOffset": [0.02, -0.02],
 "outline": true,
 "outlineWidth": 0.3,
 "outlineColor": [0, 0, 1, 1],
 "charSpacing": 0,
 "innerPadding" 0,
 "lineMaxWidth": -1,
 "fontPath": "",
 "fallbackFontPath": "",
 "effectPath": "/path",
 "shapePath": "/path"
 }
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_set_text_params(bef_info_sticker_ai_director handle, bef_info_sticker_ai_handle sticker_handle, const char* json);

/**
 * @brief 渲染线程
 * @param type        动画类型 1:入场 2:出场 3:循环
 * @param anim_path   动画路径，为空时取消动画
 * @param duration    动画持续时间
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_set_anim_new(bef_info_sticker_ai_director handle,
                              bef_info_sticker_ai_handle sticker_handle,
                              int type,
                              const char* anim_path,
                              double duration);


/**
 * @brief 渲染线程
 * @param type        动画类型 1:入场 2:出场 3:循环(一次循环的时长)
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_set_anim_duration(bef_info_sticker_ai_director handle,
                                   bef_info_sticker_ai_handle sticker_handle,
                                   int type,
                                   double duration);

/**
 * @brief 渲染线程
 * @param mode        预览模式 0:取消预览模式 1:预览入场动画 2:出场动画 3:循环动画 4.整个贴纸
 */
BEF_SDK_API bef_effect_result_t
bef_info_sticker_ai_set_sticker_preview_mode(bef_info_sticker_ai_director handle,
                                          bef_info_sticker_ai_handle sticker_handle,
                                          int mode);

#endif
