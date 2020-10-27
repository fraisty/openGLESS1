package com.fraisty.opengless1;

import android.view.Surface;

public class esNativeRender {

    static {
        System.loadLibrary("nativelib-render");
    }

    //public native static String NativeJniTest(String tstr);

    public native static void onCreate(Surface surface);
    public native static void onChange(int w, int h);
    public native static void onDestory();

}
