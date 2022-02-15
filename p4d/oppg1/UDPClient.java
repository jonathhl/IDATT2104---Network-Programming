package oppg1;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class UDPClient {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int PORTNR = 3333;

        DatagramSocket socket = new DatagramSocket();

        InetAddress ip = InetAddress.getLocalHost();
        byte[] buffer = null;

        while(true) {
            System.out.print("Enter the equation in the format:");
            System.out.println("Operand - Operator - Operand");

            String input = sc.nextLine();
            buffer = new byte[65535];

            buffer = input.getBytes();

            DatagramPacket DpSend = new DatagramPacket(buffer, buffer.length, ip, PORTNR);

            socket.send(DpSend);

            if(input.equals("")) {
                break;
            }

            buffer = new byte[65535];

            DatagramPacket DpReceive = new DatagramPacket(buffer, buffer.length);
            socket.receive(DpReceive);

            System.out.println("Result = " + new String(buffer, 0, buffer.length));
        }
        sc.close();
        socket.close();
    }
}
