package com.gp.androidnative;

import android.util.Log;

import java.util.ArrayList;

public class JniUtils {

    public static final String LOGO = "gp888";

    static {
        System.loadLibrary("native-lib");
    }

    public native String stringFromJNI();


    public native String testCallMethod();  //非静态

    public native String testNewJavaDate();

    public static native String testStaticCallMethod();//静态

    public static native String testStaticCallStaticMethod();//静态

    public String describe(){
        return LOGO + "非静态方法";
    }

    public static String staticDescribe(){
        return LOGO + "静态方法";
    }

    public Father father = new Child();
    public native String testCallFatherMethod(); //调用父类toString方法
    public native String testCallChildMethod(); // 调用子类toString方法







    private String name = "Java";

    public void callbackForJni(String fromNative) {
        Log.d("ZLiZH", "callbackForJni---jni string from native" + fromNative);
    }

    public native int square(int num);
    public native float square(float num);
    public native double square(double num);
    public native String greetings(String username);
    public native int[][] getTwoArray(int dimon);
    public native void nativeSetName();
    public native void doCallback();
    public native User nativeGetUser();
    public native void printUserInfoAtNative(User user);
    public native User changeUserInfo(User user);
    public native ArrayList<User> nativeGetUserList(int num);

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
