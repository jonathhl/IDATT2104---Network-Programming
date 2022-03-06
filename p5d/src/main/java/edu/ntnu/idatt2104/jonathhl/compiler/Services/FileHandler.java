package edu.ntnu.idatt2104.jonathhl.compiler.Services;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import org.springframework.stereotype.Service;

@Service
public class FileHandler {
    public void writeToFile(File file, String input) throws IOException {
        String[] separate = input.split("\"\\r?\\n|\\r");

        try(OutputStream os = new FileOutputStream(file);
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(os))) {
            for (String s : separate) {
                pw.write(s + "\n");
            }
        }
    }
}