#ifndef BEF_EFFECT_AI_UTILS_H_
#define BEF_EFFECT_AI_UTILS_H_

#include <vector>
#include <string>
#include <chrono>

#ifdef __ANDROID__
#include<jni.h>
const char *getPackageName(JNIEnv *env, jobject context);
#endif

#ifdef __APPLE__
extern char *getBundleId();
#endif

const char* getAppId();

// @targetdir  out targetdir
// decode resouces to a temp dir, should del the temp after load resources
// @return the temp dir
//

void decodeBuffer(const char* buffer, long bufferlen, const char* key, char* outbuffer, long* outbuferLen, long bufferOffset = 0, bool addEnd = true);

#if 0
#define OUTPARAM
void decodeResource(const char* resourcedir, OUTPARAM char* targetdir, const char* key);
void copy_r_decode(const char* src_dir, const char* dst_dir, const char* decode_suffix, const char* key);
#endif

void r_decode(const char* src_dir, const char* decode_suffix, const char* key);

bool checkIsEncrypted(const std::string& filePath, unsigned char *buffer, long bufferLen, bool *should_encrypt, const std::vector<std::string>& suffixes, const std::string& encodeSign);

unsigned char *checkDecryptFile(unsigned char *buffer, long& length, std::string const& key, std::string const& encodeSign);

bool checkDecodeFile(const char* filepath, unsigned char* decodedBuffer, long*  decodedLen, std::string key, std::vector<std::string> suffixs, std::string encodeSign);

void r_del_decoded(const char* src_dir, const char* decode_suffix);

using Time = decltype(std::chrono::high_resolution_clock::now());

Time time();

double time_diff(Time t1, Time t2);

int reformat_license_error_code(int license_code);

#endif
