#include <jni.h>
#include <string>

#include "com_gp_androidnative_JniUtils.h"
#include <stdio.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_stringFromJNI(
        JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    char *str="String from native C";
    return env->NewStringUTF(hello.c_str());//str
}


//非静态方法传入的是当前类
extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_testCallMethod(JNIEnv *env, jobject instance) {
    jclass  jnibean_class = env->GetObjectClass(instance);                                   //因为是非静态的，所以要通过GetObjectClass获取对象
    jmethodID  nostatic_method = env->GetMethodID(jnibean_class, "describe", "()Ljava/lang/String;");// 通过GetMethod方法获取方法的methodId.

    jobject jobj = env->AllocObject(jnibean_class);                                         // 对jclass进行实例，相当于java中的new
    jstring pring = (jstring)(env)->CallObjectMethod(jobj, nostatic_method);                 // 类调用类中的方法

    char *print=(char*)(env)->GetStringUTFChars(pring, 0);                           // 转换格式输出。
    return env->NewStringUTF(print);
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_gp_androidnative_JniUtils_testNewJavaDate(JNIEnv *env, jobject instance) {
    jclass  class_date = env->FindClass("java/util/Date");//注意这里路径要换成/,不然会报illegal class name
    jmethodID  a_method = env->GetMethodID(class_date, "<init>", "()V");
    jobject  a_date_obj = env->NewObject(class_date, a_method);
    jmethodID  date_get_time = env->GetMethodID(class_date, "getTime","()J");
    jlong get_time = env->CallLongMethod(a_date_obj, date_get_time);
    return get_time;
}

//静态方法会直接传入jclass
extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_testStaticCallMethod(JNIEnv *env, jclass type) {
    jmethodID  a_method = env->GetMethodID(type,"describe", "()Ljava/lang/String;"); // 通过GetMethod方法获取方法的methodId.
    jobject jobj = env->AllocObject(type);                                          // 对jclass进行实例，相当于java中的new
    jstring pring= (jstring)(env)->CallObjectMethod(jobj,a_method);                 // 类调用类中的方法
    char *print=(char*)(env)->GetStringUTFChars(pring,0);                           // 转换格式输出。
    return env->NewStringUTF(print);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_testStaticCallStaticMethod(JNIEnv *env, jclass type) {
    jmethodID  a_method = env->GetStaticMethodID(type,"staticDescribe","()Ljava/lang/String;"); // 通过GetStaticMethodID方法获取方法的methodId.
    jstring pring= (jstring)(env)->CallStaticObjectMethod(type, a_method);                       // 类调用类中的方法
    char *print=(char*)(env)->GetStringUTFChars(pring,0);                                       // 转换格式输出。
    return env->NewStringUTF(print);
}



extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_testCallFatherMethod(JNIEnv *env, jobject instance) {
    jclass clazz = env -> GetObjectClass(instance);
    jfieldID  father_field = env -> GetFieldID(clazz,"father","Lcom/gp/androidnative/Father;");
    jobject  mFather = env -> GetObjectField(instance,father_field);
    jclass  clazz_father = env -> FindClass("com/gp/androidnative/Father");
    jmethodID  use_call_non_virtual = env -> GetMethodID(clazz_father,"toString","()Ljava/lang/String;");
    // 如果调用父类方法用CallNonvirtual***Method
    jstring  result = (jstring) env->CallNonvirtualObjectMethod(mFather,clazz_father,use_call_non_virtual);
    return result;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_testCallChildMethod(JNIEnv *env, jobject instance) {
    jclass clazz = env -> GetObjectClass(instance);
    jfieldID  father_field = env -> GetFieldID(clazz,"father","Lcom/gp/androidnative/Father;");
    jobject  mFather = env -> GetObjectField(instance,father_field);
    jclass  clazz_father = env -> FindClass("com/gp/androidnative/Father");
    jmethodID  use_call_non_virtual = env -> GetMethodID(clazz_father,"toString","()Ljava/lang/String;");
    // 如果调用子类方法用Call***Method
    jstring  result = (jstring) env->CallObjectMethod(mFather,use_call_non_virtual);
    return result;
}







extern "C" JNIEXPORT jint JNICALL
Java_com_gp_androidnative_JniUtils_square__I(JNIEnv *env, jobject obj, jint num) {
    return num * num;
}

extern "C" JNIEXPORT jfloat JNICALL
Java_com_gp_androidnative_JniUtils_square__F(JNIEnv *env, jobject obj, jfloat num) {
    return num * num;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_gp_androidnative_JniUtils_square__D(JNIEnv *env, jobject obj, jdouble num) {
    return num * num;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_gp_androidnative_JniUtils_greetings(JNIEnv *env, jobject obj, jstring jstr) {
    const char *str = env->GetStringUTFChars(jstr, NULL);
    if(str == NULL) {
        return NULL;
    }
    printf("%s\n", str);
    env->ReleaseStringUTFChars(jstr, str);
    const char *tmpStr = "I am from Jni";
    jstring resStr = env->NewStringUTF(tmpStr);
    return resStr;
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_gp_androidnative_JniUtils_getTwoArray(JNIEnv *env, jobject obj, jint dimion) {
    if(dimion > 10) {
        return NULL;
    }
    jclass intArrayClass = env->FindClass("[I");
    jobjectArray objectIntArray = env->NewObjectArray(dimion, intArrayClass, NULL);

    for (int i = 0; i < dimion; ++i) {
        jintArray intArray = env->NewIntArray(dimion);
        jint temp[10];
        for (int j = 0; j < dimion; ++j) {
            temp[j] = i + j;
        }
        env->SetIntArrayRegion(intArray, 0, dimion, temp);
        env->SetObjectArrayElement(objectIntArray, i, intArray);
        env->DeleteLocalRef(intArray);
    }

    return objectIntArray;
}

extern "C" JNIEXPORT void JNICALL
Java_com_gp_androidnative_JniUtils_nativeSetName(JNIEnv *env, jobject obj) {
    jclass clazz = env->GetObjectClass(obj);
    jfieldID nameFieldId = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
    if(nameFieldId == NULL) {
        printf("没有得到name的句柄Id \n");
    }

    jstring javaNameStr = (jstring) env->GetObjectField(obj, nameFieldId);
    const char *c_javaName = env->GetStringUTFChars(javaNameStr, NULL);
    printf("%s", c_javaName);
    printf("\n");
    env->ReleaseStringUTFChars(javaNameStr, c_javaName);

    const char *c_ptr_name = "setByNative";
    jstring cName = env->NewStringUTF(c_ptr_name);
    env->SetObjectField(obj, nameFieldId, cName);
}

extern "C" JNIEXPORT void JNICALL
Java_com_gp_androidnative_JniUtils_doCallback(JNIEnv *env, jobject obj) {
    jclass clazz = env->GetObjectClass(obj);
    jmethodID callbackMethodID = env->GetMethodID(clazz, "callbackForJni", "(Ljava/lang/String;)V");
    if(callbackMethodID == NULL) {
        printf("doCallback getMethodId is failed \n");
    }
    jstring navtive_desc = env->NewStringUTF("callback From Native");
    env->CallVoidMethod(obj, callbackMethodID, navtive_desc);
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_gp_androidnative_JniUtils_nativeGetUser(JNIEnv *env, jobject obj) {
    jclass userClazz = env->FindClass("com/gp/androidnative/User");
    jmethodID constructMID = env->GetMethodID(userClazz, "<init>", "(ILjava/lang/String;)V");
    jstring name = env->NewStringUTF("ZLOVE From Native");
    jobject userObj = env->NewObject(userClazz, constructMID, 11, name);
    return userObj;
}

extern "C" JNIEXPORT void JNICALL
Java_com_gp_androidnative_JniUtils_printUserInfoAtNative(JNIEnv *env, jobject obj, jobject userObj) {
    jclass userClazz = env->GetObjectClass(userObj);
    if(userClazz == NULL) {
        printf("GetObjectClass failed \n");
    }
    jfieldID ageFieldID = env->GetFieldID(userClazz, "age", "I");
    jfieldID nameFileID = env->GetFieldID(userClazz, "name", "Ljava/lang/String;");
    jint age = env->GetIntField(userObj, ageFieldID);
    jstring name = env->GetObjectField(userObj, nameFileID);
    const char *cname = env->GetStringUTFChars(name, NULL);
    printf("user age --- %d, user name --- %s", age, cname);
    env->ReleaseStringUTFChars(name, cname);
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_gp_androidnative_JniUtils_changeUserInfo(JNIEnv *env, jobject obj, jobject userObj) {
    jclass userClazz = env->GetObjectClass(userObj);
    if(userClazz == NULL) {
        printf("GetObjectClass failed \n");
    }
    jfieldID ageFieldID = env->GetFieldID(userClazz, "age", "I");
    jfieldID nameFileID = env->GetFieldID(userClazz, "name", "Ljava/lang/String;");
    jint age = env->GetIntField(userObj, ageFieldID);
    jstring name = env->GetObjectField(userObj, nameFileID);
    const char *c_name = env->GetStringUTFChars(name, NULL);
    printf("show user info age:%d name:%s", age, c_name);
    env->ReleaseStringUTFChars(name, c_name);

    const char *c_ptr_name = "ZLiZH";
    jstring cName = env->NewStringUTF(c_ptr_name);
    env->SetObjectField(userObj, nameFileID, cName);
    env->SetIntField(userObj, ageFieldID, 28);
    return userObj;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_gp_androidnative_JniUtils_nativeGetUserList(JNIEnv *env, jobject obj, jint size) {
    jclass listClass = env->FindClass("java/util/ArrayList");
    if(listClass == NULL) {
        printf("listClass is NULL \n");
    }
    jmethodID  list_construct = env->GetMethodID(listClass, "<init>", "()V");
    jobject listObj = env->NewObject(listClass, list_construct);
    jmethodID listAdd = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    jclass userClass = env->FindClass("com/gp/androidnative/User");
    jmethodID constructMID = env->GetMethodID(userClass, "<init>", "(ILjava/lang/String;)V");
    for (int i = 0; i < size; ++i) {
        jstring str = env->NewStringUTF("Native");
        jobject stu_obj = env->NewObject(userClass, constructMID, i, str);
        env->CallBooleanMethod(listObj, listAdd, stu_obj);
    }
    return listObj;
}
