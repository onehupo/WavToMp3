package dev.hupo.converter;

import java.lang.invoke.MutableCallSite;

public class WavToMp3Converter {

    private static OnProgressListener listener;

    static {
        System.loadLibrary("mp3lame");
    }
    public native static void convert(Mp3ConverterConfig config);

    public native static String getVersion();

    public native static long getProgress();

    public static void onProgress(long current){
        if (WavToMp3Converter.getListener()!= null) {
            WavToMp3Converter.getListener().onProgress(current);
        }
    }

    public static OnProgressListener getListener() {
        return listener;
    }

    public static void setListener(OnProgressListener listener) {
        WavToMp3Converter.listener = listener;
    }

    public static void destroy(){
        listener = null;
    }

    public interface OnProgressListener {
        void onProgress(long current);
    }
}
