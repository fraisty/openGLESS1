package com.fraisty.opengless1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.SurfaceView;
import android.widget.TextView;

import com.fraisty.opengless1.MySurfaceView;

public class MainActivity extends AppCompatActivity {

    private MySurfaceView mySurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //TextView mytextView = (TextView)findViewById(R.id.textview1);
        //String str = esNativeRender.NativeJniTest("Java!");
        //mytextView.setText(str);

        mySurfaceView =  findViewById(R.id.mysurfaceview);

    }
}









