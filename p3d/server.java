package p3d;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class server {
  public static void main(String[] args) throws IOException {
    final int PORTNR = 3333;
  ServerSocket serverSocket = new ServerSocket(PORTNR);

  System.out.println("Server started...");
  System.out.println("Waiting for connections..");
  
  while(true) {
    Socket clientSocket = serverSocket.accept();
    Thread t = new Thread() {
      public void run() {
        try (
          PrintWriter writer = new PrintWriter(clientSocket.getOutputStream(), true);
          Scanner input = new Scanner(clientSocket.getInputStream());
        ) {
          while(input.hasNextLine()) {
            String in = input.nextLine();
            if(in.equalsIgnoreCase(null)) {
              break;
            } else {
              System.out.println("A client wrote: " + in);
              int r = 0;
              String[] result = in.split("(?=[+-])|(?<=[+-])");
              if(result[1].equals("+")) {
                r += Integer.parseInt(result[0]) + Integer.parseInt(result[2]);
              } else if (result[1].equals("-")) {
                r += Integer.parseInt(result[0]) - Integer.parseInt(result[2]);
              }
              writer.println(r);
            }
          }
        } catch (IOException e) {
           e.printStackTrace();
          }
        }
      };
      t.start();
    } 
  }
}