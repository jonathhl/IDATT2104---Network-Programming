package p3d;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

class client {
  public static void main(String[] args) throws IOException {
    final String HOST = "localhost";
    final int PORTNR = 3333;
    System.out.println("Client started.");
    System.out.println("Press enter to exit.");
  
    try (
      Socket socket = new Socket(HOST, PORTNR);
      PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
      Scanner input = new Scanner(socket.getInputStream());
      Scanner s = new Scanner(System.in);
    ) {
      while(true) {
        System.out.println("Input: ");
        String in = s.nextLine();
        writer.println(in);
        if(in.equalsIgnoreCase("")) break;
        System.out.println("Echoed from server: " +  input.nextLine());
      }
    } 
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}