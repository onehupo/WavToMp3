package dev.hupo.converter;

import java.io.Serializable;

public class Mp3ConverterConfig implements Serializable {
    private int inputSampleRate = 16000; // 输入采样率，默认为 16000 Hz
    private int channels = 1; // 声道数，默认为 2

    private int bRate = 128; // 比特率，默认为 128 kbps

    private int outputSampleRate = 16000; // 输出采样率，默认为 16000 Hz

    private String inputFile = "";

    private String outputFile = "";

    public int getInputSampleRate() {
        return inputSampleRate;
    }

    public void setInputSampleRate(int inputSampleRate) {
        this.inputSampleRate = inputSampleRate;
    }

    public int getChannels() {
        return channels;
    }

    public void setChannels(int channels) {
        this.channels = channels;
    }

    public int getbRate() {
        return bRate;
    }

    public void setbRate(int bRate) {
        this.bRate = bRate;
    }

    public int getOutputSampleRate() {
        return outputSampleRate;
    }

    public void setOutputSampleRate(int outputSampleRate) {
        this.outputSampleRate = outputSampleRate;
    }

    public String getInputFile() {
        return inputFile;
    }

    public void setInputFile(String inputFile) {
        this.inputFile = inputFile;
    }

    public String getOutputFile() {
        return outputFile;
    }

    public void setOutputFile(String outputFile) {
        this.outputFile = outputFile;
    }
}
