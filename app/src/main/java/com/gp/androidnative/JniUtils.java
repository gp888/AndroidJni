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

    public native long testNewJavaDate();

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

    //square：求int, float,double类型数值的平方
    public native int square(int num);
    public native float square(float num);
    public native double square(double num);

    //greetings：传一个字符串给C层，C层回传另一个字符串给Java层
    public native String greetings(String username);

    //getTwoArray：获取C层返回的一个二维数组
    public native int[][] getTwoArray(int dimon);

    //nativeSetName：C层改变Java层某个属性的值
    public native void nativeSetName();

    //doCallback：C层回调Java层方法
    public native void doCallback();
    public void callbackForJni(String fromNative) {
        Log.d("ZLiZH", "callbackForJni---jni string from native" + fromNative);
    }

    //nativeGetUser：C层生成Java层某个对象并返回
    public native User nativeGetUser();

    // printUserInfoAtNative：C层打印Java对象的属性值
    public native void printUserInfoAtNative(User user);

    //changeUserInfo：C层改变Java对象的属性值并返回
    public native User changeUserInfo(User user);

    //nativeGetUserList：C层构造Java对象列表并返回
    public native ArrayList<User> nativeGetUserList(int num);

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
