//
// Created by Hille on 2023/1/4.
//

#include "my-jni-test.h"
#include "include/openssl/des.h"


#include <android/log.h>
#include <jni.h>
#include <malloc.h>
#include <string.h>

#define DES_ENCRYPT  1

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "Tag", __VA_ARGS__)

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "Tag", __VA_ARGS__)

JNIEXPORT jstring JNICALL
Java_com_example_myjnitest_MyJniTest_jniFirstTestFun(JNIEnv *env, jclass clazz, jstring name) {
    char *my_name;
    free(my_name);
    my_name = (*env)->GetStringUTFChars(env,name,0);
    char name_tail[10] = " from jni";
    name_tail[9] = 'I';
    my_name = strcat(my_name, name_tail);
    jstring ret_name = (* env)->NewStringUTF(env, my_name);
    (* env)->ReleaseStringUTFChars(env,name,my_name);
    return ret_name;

}

JNIEXPORT jbyteArray JNICALL
Java_com_example_myjnitest_MyJniTest_tripleDesEncrypt(JNIEnv *env, jclass clazz, jbyteArray data,
                                                      jbyteArray key) {
    jbyte *get_key = NULL;
    jbyte *get_in_data = NULL;
    int get_key_len = (* env)->GetArrayLength(env, key);
    int get_in_data_len = (* env)->GetArrayLength(env, data);
    get_key = (jbyte *) malloc(get_key_len * sizeof(jbyte));
    get_in_data = (jbyte *) malloc(get_in_data_len * sizeof(jbyte));
    memset(get_in_data, 0, get_in_data_len);
    (* env)->GetByteArrayRegion(env, key, 0, get_key_len, get_key);
    (* env)->GetByteArrayRegion(env, data, 0, get_in_data_len, get_in_data);
    char *get_in_data_str = NULL;
    get_in_data_str = (char *) malloc(sizeof(get_in_data) * 2 + 1);
    byte_to_hex_string(get_in_data, get_in_data_str);
    LOGE("get_in_data: %lu",sizeof(get_in_data));
    LOGE("get_in_data: %s",get_in_data_str);
    if(sizeof(get_key) < 24) {
        get_key = realloc(get_key, 24);
        memset((get_key + get_key_len), 0, 24 - get_key_len);
    }

//    if(sizeof(get_in_data) < 24) {
//        get_in_data = realloc(get_in_data, 24);
//        memset((get_in_data + get_in_data_len), 0, 24 - get_in_data_len);
//    }
    unsigned char in_data[8],out_data[8],k1[8],k2[8],k3[8];
    DES_key_schedule s1,s2,s3;

    memcpy(k1, get_key, 8);
    memcpy(k2, get_key + 8, 8);
    memcpy(k3 , get_key + 16, 8);

    memcpy(in_data, get_in_data, 8);

    DES_set_key_unchecked(k1, &s1);
    DES_set_key_unchecked(k2, &s2);
    DES_set_key_unchecked(k3, &s3);

    DES_ecb3_encrypt(in_data, out_data, &s1, &s2, &s3, DES_ENCRYPT);

    free(get_key);
    free(get_in_data);
    free(get_in_data_str);

    get_key = NULL;
    get_in_data = NULL;
    get_in_data_str = NULL;

    jbyteArray output_data = (* env)->NewByteArray(env, 8);

    (* env)->SetByteArrayRegion(env, output_data, 0, 8, (jbyte *)out_data);


    return output_data;



}
/**
 *
 * @param byte_data
 * @param str_data
 */
void byte_to_hex_string(char *byte_data, char *str_data) {
    int data_size = sizeof (byte_data);
    for(int i = 0, j = 0; i < data_size; i++,j++) {
        str_data[j] = ((byte_data[i] & 0xF0) >> 4 ) + 0x30;
        str_data[++j] = (byte_data[i] & 0x0F) + 0x30;
    }
    str_data[data_size * 2 - 1] = 0;
}