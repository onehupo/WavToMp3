## WavToMp3

[README 中文版](./README_zh.md)

This Android library is based on the LAME library and provides functionality to convert WAV audio files to the MP3 format. 
LAME is an open-source audio encoding library that offers high-quality audio compression and encoding algorithms.
This library offers a simple yet powerful interface, allowing developers to easily convert WAV files to MP3 format,
enabling audio format conversion and compression in their applications. With this library, you can convert audio files to
MP3 format to reduce file size, saving bandwidth and storage space in network transfers or storage. Whether you're building an audio editing app, 
a media player, or any other application that requires audio conversion, this library can help you accomplish the task effortlessly.


<img src="./image/Screenshot.png" alt="Screenshot" width="432" height="936">


## Use

1. Add Maven repository to your build file (e.g., build.gradle).

```groovy
repositories {
    maven { url "https://raw.githubusercontent.com/onehupo/WavToMp3/main/repo/" }
}
```

2. Add the library's dependency to your build file.

```groovy
implementation "dev.hupo.converter:wav2mp3:1.0.0"
```

3. Copy the .so files to the jniLibs directory in your Android project.copy the .so files to the following path:

`converter/src/main/jniLibs`

4. Convert the WAV file using the following code snippet.

```kotlin
val config = Mp3ConverterConfig()
config.setInputFile(wavPath)
config.setOutputFile(mp3Path)
WavToMp3Converter.setListener {
  Log.d("WavToMp3", "progress: $it")
}
WavToMp3Converter.convert(config)
```

Mp3ConverterConfig contains the following configuration information:

| Field Name       | Type    | Default Value | Description                                   |
|------------------|---------|---------------|-----------------------------------------------|
| inputSampleRate  | Integer | 16000         | Sets the input audio sample rate (in Hz).      |
| channels         | Integer | 1             | Sets the number of channels in the input audio.|
| bRate            | Integer | 128           | Sets the output audio bit rate (in kbps).      |
| outputSampleRate | Integer | 16000         | Sets the output audio sample rate (in Hz).     |
| inputFile        | String  | Empty String  | Sets the path of the input file for conversion.|
| outputFile       | String  | Empty String  | Sets the path of the output file after conversion. |

If proguard is enabled in the project, it is necessary to configure the keep rules to prevent certain classes from being proguard.

```
-keep class dev.hupo.converter.** { *; }
```