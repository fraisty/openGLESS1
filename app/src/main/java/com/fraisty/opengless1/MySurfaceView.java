package com.fraisty.opengless1;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import com.fraisty.opengless1.esNativeRender;


import androidx.annotation.NonNull;

public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    private esNativeRender nativeRender;
    public MySurfaceView(Context context,AttributeSet attrs){
        super(context,attrs);
        getHolder().addCallback(this);
        nativeRender = new esNativeRender();
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
        nativeRender.onCreate(holder.getSurface());
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {

        nativeRender.onChange(width,height);
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {
        nativeRender.onDestory();
    }
}
