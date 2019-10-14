package com.example.kostas.firstnativeapp;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
public class FirstNative extends Activity{
    private static String LOGTAG = "FirstNative";
    protected GraphicsView graphicsView;
    @Override protected void onCreate(Bundle savedInstaceState){
        super.onCreate(savedInstaceState);
        Log.d(LOGTAG, "On Create Method Calling Native Lib");
        graphicsView = new GraphicsView(getApplication());
        setContentView(graphicsView);
//        NativeLibrary.init();
    }

    @Override protected void onPause(){
        super.onPause();
        graphicsView.onPause();
    }

    @Override protected  void onResume(){
        super.onResume();
        graphicsView.onResume();
    }
}
