package com.example.jnitestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.example.hellojni.HelloJni;
import com.example.myjnitest.MyJniTest;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.e("xtxt","so test = " + HelloJni.stringFromJni());
        Log.e("xtxt","jni test = " + MyJniTest.jniFirstTestFun("123"));

        Log.e("xtxt","des test = " + Util.byte2HexStr(MyJniTest.tripleDesEncrypt(Util.hexString2Bytes(
                        "1234567890"),Util.hexString2Bytes("1234567890"))));
    }
}