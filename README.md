# WavToMp3


1. add maven

```groovy
maven { url "https://raw.githubusercontent.com/onehupo/WavToMp3/main/repo/"}
```

2.add implementation and so
```groovy
implementation "dev.hupo.converter:wav2mp3:1.0.0"
```

so from folder 
`converter/src/main/jniLibs`

3.converterFile

```java
val config = Mp3ConverterConfig()
config.setInputFile(wavPath)
config.setOutputFile(mp3Path)
WavToMp3Converter.setListener {
  Log.d("WavToMp3", "progress: $it")
}
WavToMp3Converter.convert(config)
```
