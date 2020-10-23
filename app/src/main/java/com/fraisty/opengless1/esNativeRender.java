package com.fraisty.opengless1;

public class esNativeRender {

    static {
        System.loadLibrary("nativelib-render");
    }

    public native static String NativeJniTest(String tstr);


}
