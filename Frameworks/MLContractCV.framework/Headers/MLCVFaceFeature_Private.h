//
//  MLCVFaceFeature_Private.h
//  MLContractCV
//
//  Created by Naichuan on 2021/1/25.
//

#import <Foundation/Foundation.h>
#import <vector>
//#import <effect-sdk/bef_effect_ai_face_detect.h>
#if !TARGET_IPHONE_SIMULATOR
#import "bef_effect_ai_face_detect.h"
#endif
#import <simd/simd.h>
#import <MomoCV/MMFaceFeature.h>
NS_ASSUME_NONNULL_BEGIN

struct MLFaceInternalMask {
    std::vector<uint8_t> mask;
    std::vector<float>   warp_mat;
    
    CGSize mask_size;
    float covered_rate;
};

struct MLCVFaceFeatureInternalRepresentation {        
     std::vector<float> bounds;//left top right bottom
    
    std::vector<float> landmarks96;
    std::vector<float> landmarks68;
    std::vector<float> landmarks87;
    std::vector<float> landmarks104;
    std::vector<float> landmarks106;
    std::vector<float> landmarks137;
    std::vector<float> landmarks222;
    
    std::vector<float> origin_landmarks96;
    std::vector<float> origin_landmarks68;
    std::vector<float> origin_landmarks87;
    std::vector<float> origin_landmarks104;
    std::vector<float> origin_landmarks106;
    std::vector<float> origin_landmarks137;
    std::vector<float> origin_landmarks222;
    
    std::vector<float> euler_angles;
    
    std::vector<int> skin_color_threshold;
    
    float face_rotate_degree;
    float left_eye_close_prob;
    float right_eye_close_prob;
    
    int tracking_id;
    
    // 每个人脸对应一个拉长的 3x3 矩阵，按行存储
    std::vector<float> camera_matrix;
    
    // 每个人脸对应一个拉长的 3x3 矩阵，
    std::vector<float> rotation_matrix;
    
    // 每个人脸对应一个拉长的 3 维向量，
    std::vector<float> rotation_vector;
    
    // 每个人脸对应一个拉长的 3 维向量，
    std::vector<float> translation_vector;
    
    // 每个人脸对应一个拉长的 3x4 矩阵，
    std::vector<float> projection_matrix;
    
    // 每个人脸对应一个拉长的 4x4 矩阵，
    std::vector<float> modelview_matrix;
    
    std::vector<float> projection_matrix_opengl;
    
    int expression;
    
    std::vector<float> facerig_feature;
    
    std::vector<uint8_t> feature;
    
    int quality;
    
    MLFaceInternalMask face_mask;
    MLFaceInternalMask mouth_mask;
    
    CGSize imageSize;
};

typedef MLCVFaceFeatureInternalRepresentation MMFaceFeatureInternalRepresentation;

#if !TARGET_IPHONE_SIMULATOR
extern MMFaceFeatureInternalRepresentation MMFaceFeatureInternalRepresentationMakeByByteDance(bef_ai_face_106 face, bef_ai_face_ext_info face_ext, size_t imageWidth, size_t imageHeight, float landmarkScale);


#endif
@interface MMFaceFeature (ByteDance)
- (instancetype)initWithInternelRepresentation:(MMFaceFeatureInternalRepresentation)internalRepresentation;
@end
NS_ASSUME_NONNULL_END
