package com.example.myjnitest;

public class MyJniTest {
    static {
        System.loadLibrary("my-jni-test");
    }

    public static native String jniFirstTestFun(String name);

    public static native byte[] tripleDesEncrypt(byte[] data, byte[] key);
}
