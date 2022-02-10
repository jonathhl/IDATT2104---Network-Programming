package p3d;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class webServer {
    
    public static void main(String[] args) throws IOException {
        final int PORTNR = 8080;

        ServerSocket server = new ServerSocket(PORTNR);
        Socket connection = server.accept();
        PrintWriter writer = new PrintWriter(connection.getOutputStream(), true);
        String output = "HTTP/2 200 OK \n" +
                        "Content-type: text/html; charset=utf-8 \n" +
                        "\n\n" +
                        "<html> <body>" +
                        "<h1> Heisann! Du er nå tilkoblet. </h1>" +
                        "<p>Header fra klient er</p>" +
                        "<ul>" +
                        "<li> HTTP/2 200 OK \n" +
                        "Content-type: text/html; charset=utf-8 </li>" +
                        "</ul>" +
                        "</body></html>";
        writer.println(output);
        writer.close();
        connection.close();
    }
}