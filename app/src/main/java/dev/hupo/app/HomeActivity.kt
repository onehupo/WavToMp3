package dev.hupo.app

import android.app.Activity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.TextView
import dev.hupo.converter.Mp3ConverterConfig
import dev.hupo.converter.WavToMp3Converter
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream
import java.io.OutputStream


class HomeActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_home)

        val wavPath = filesDir.path + File.separator + "test.wav"
        val mp3Path = filesDir.path + File.separator + "test.mp3"


        val files = findViewById<TextView>(R.id.file)
        files.text = "convert\n${wavPath}\nto\n${mp3Path}"
        val version = findViewById<TextView>(R.id.version)
        version.text = WavToMp3Converter.getVersion()
        val button = findViewById<Button>(R.id.button)
        button.setOnClickListener {

            val file = File(wavPath)
            if (!file.exists()) {
                val inputStream: InputStream = assets.open("test.wav")
                val outFile: File = file

                val outputStream: OutputStream = FileOutputStream(outFile)
                val buffer = ByteArray(1024)
                var length: Int
                while (inputStream.read(buffer).also { length = it } > 0) {
                    outputStream.write(buffer, 0, length)
                }

                outputStream.flush()
                outputStream.close()
                inputStream.close()
            }

            val config = Mp3ConverterConfig()
            config.setInputFile(wavPath)
            config.setOutputFile(mp3Path)
            WavToMp3Converter.setListener {
//                Log.d("liangruiDebug", "onCreate: $it")
            }
            WavToMp3Converter.convert(config)
        }

    }
}

