package com.example.hellojni;

public class HelloJni {
    static {
        System.loadLibrary("hello-jni");
    }

    public static native String stringFromJni();

    public static native byte[] getBytesFromJni(byte[] myBytes);
}
