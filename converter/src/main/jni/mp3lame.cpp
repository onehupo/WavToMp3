#include "stdio.h"
#include "string.h"
#include "jni.h"
#include "libmp3lame/lame.h"
#include "android/log.h"
#include <jni.h>
#include <jni.h>
#include <jni.h>
#include <jni.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "libmp3lame", __VA_ARGS__)
#define LOG_DEBUG false

jlong currentProgress = 0;

extern "C"
JNIEXPORT void JNICALL
Java_dev_hupo_converter_WavToMp3Converter_convert(JNIEnv
* env,
jclass clazz, jobject
config) {
    // 解析传入的java对象的field
    jclass cls = env->GetObjectClass(config);
    jfieldID inputSampleRateFieldID = env->GetFieldID(cls, "inputSampleRate", "I");
    jfieldID channelsFieldID = env->GetFieldID(cls, "channels", "I");
    jfieldID bRateFieldID = env->GetFieldID(cls, "bRate", "I");
    jfieldID outputSampleRateFieldID = env->GetFieldID(cls, "outputSampleRate", "I");
    jfieldID inputFileFieldID = env->GetFieldID(cls, "inputFile", "Ljava/lang/String;");
    jfieldID outputFileFieldID = env->GetFieldID(cls, "outputFile", "Ljava/lang/String;");

    // 在 JNI 中创建一个 Java 类引用
    // jclass javaClass = env->FindClass("dev/hupo/WavToMp3Converter");
    // 获取 Java 方法的方法 ID
    jmethodID javaMethod = env->GetStaticMethodID(clazz, "onProgress", "(J)V");

    // 解析传入的值
    jint inputSampleRate = env->GetIntField(config, inputSampleRateFieldID);
    jint channels = env->GetIntField(config, channelsFieldID);
    jint bRate = env->GetIntField(config, bRateFieldID);
    jint outputSampleRate = env->GetIntField(config, outputSampleRateFieldID);
    auto inputFile = (jstring)env->GetObjectField(config, inputFileFieldID);
    auto outputFile = (jstring)env->GetObjectField(config, outputFileFieldID);

    // 获取input的值
    const char *cInput = env->GetStringUTFChars(inputFile, 0);
    const char *cMp3 = env->GetStringUTFChars(outputFile, 0);
    FILE *wavFile = fopen(cInput, "rb");    // 打开 WAV 文件
    FILE *mp3File = fopen(cMp3, "wb");    // 创建 MP3 文件

    const int PCM_SIZE = 8192;
    const int MP3_SIZE = 8192;
    const int WAV_HEADER = 44;

    short int pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];

    // 初始化 LAME 编码器
    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, inputSampleRate);    // 输入采样率，默认为 44100 Hz
    lame_set_num_channels(lame, channels);    // 声道数，默认为 2
    lame_set_brate(lame, bRate);    // 比特率，默认为 128 kbps
    if (channels == 1) {
        lame_set_mode(lame, MONO);    // 声道模式，默认为立体声
    } else {
        lame_set_mode(lame, STEREO);    // 声道模式，默认为立体声
    }
    lame_set_out_samplerate(lame, outputSampleRate);

    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    // 忽略wav头文件的尺寸，头文件保存了wav的比特率等信息
    fseek(wavFile, WAV_HEADER, 0);

    env->CallStaticVoidMethod(clazz, javaMethod, (jlong)44);

    int read, write;
    long total = 0; // the bytes of reading input file

    currentProgress = 0;
    do {
        // 从 WAV 文件中读取 PCM 数据
        read = fread(pcm_buffer, sizeof(short int), PCM_SIZE, wavFile);
        total +=  read * sizeof(short int)*2;
        currentProgress = total;

        // 调用java的代码实现进度的监控
        env->CallStaticVoidMethod(clazz, javaMethod, currentProgress);

        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        else
            // 编码 PCM 数据为 MP3
            write = lame_encode_buffer(lame, pcm_buffer, nullptr, read, mp3_buffer, MP3_SIZE);
            // TODO
            // 如果双通道可能需要使用 lame_encode_buffer_interleaved


        // 将编码后的 MP3 数据写入文件
        fwrite(mp3_buffer, write, 1, mp3File);
    } while (read != 0);

    // 清理和关闭
    lame_close(lame);
    fclose(wavFile);
    fclose(mp3File);

    // 释放本地字符串
    env->ReleaseStringUTFChars((jstring)env->GetObjectField(config, inputFileFieldID), cInput);
    env->ReleaseStringUTFChars((jstring)env->GetObjectField(config, outputFileFieldID), cMp3);
}

extern "C"
JNIEXPORT jlong
JNICALL
Java_dev_hupo_converter_WavToMp3Converter_getProgress(JNIEnv * env, jclass clazz) {
    if (LOG_DEBUG)
        LOGD("lame version = %d", currentProgress);
    return currentProgress;
}

extern "C"
JNIEXPORT jstring
JNICALL
Java_dev_hupo_converter_WavToMp3Converter_getVersion(JNIEnv * env, jclass clazz) {
    if (LOG_DEBUG)
        LOGD("lame version = %s", get_lame_version());
    return env->NewStringUTF(get_lame_version());
}