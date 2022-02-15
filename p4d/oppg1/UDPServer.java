package oppg1;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPServer {
    
    public static void main(String[] args) throws IOException {

        int PORTNR = 3333;
        DatagramSocket socket = new DatagramSocket(PORTNR);
        byte[] buffer = null;

        DatagramPacket DpReceive = null;
        DatagramPacket DpSend = null;

        while(true) {
            buffer = new byte[65535];

            DpReceive = new DatagramPacket(buffer, buffer.length);
            socket.receive(DpReceive);

            String input = new String(buffer, 0, buffer.length);
            input = input.trim();
            System.out.println("Equation received: " + input);

            if(input.equals("")) {
                System.out.println("Client exiting...");

                break;
            }

            int result;

            // Splitting up string into parts using regex
            String[] equation = input.split("(?=[+-/*])|(?<=[+-/*])");
            
            int part1 = Integer.parseInt(equation[0]);
            String operator = equation[1];
            int part2 = Integer.parseInt(equation[2]);

            if(operator.equals("+")) {
                result = part1 + part2;
            } else if(operator.equals("-")) {
                result = part1 - part2;
            } else if(operator.equals("*")) {
                result = part1 * part2;
            } else {
                result = part1 / part2;
            }

            String res = Integer.toString(result);
            System.out.println("Result is: " + res);
            System.out.println("Sending result to client...");

            buffer = res.getBytes();

            int port = DpReceive.getPort();

            DpSend = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), port);
            socket.send(DpSend);
        }
        socket.close();
    }
}
