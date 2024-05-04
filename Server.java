package Prac1;
import java.util.Scanner;
import java.net.*;
import java.io.*;
public class Server {
    public static void main(String[] agrs)
    {
        Scanner sc=new Scanner(System.in);
        try{
        int port =8080;
        System.out.println("Enter Server Key(b):");
        int b=sc.nextInt();
        ServerSocket serverSocket= new ServerSocket(port);
        System.out.println("Waiting for client on port "+serverSocket.getLocalPort()+"...");
        Socket server=serverSocket.accept();
        System.out.println("Just connected to "+server.getRemoteSocketAddress());
        System.out.println("From Server :Private Key(b):"+b);
        DataInputStream in=new DataInputStream(server.getInputStream());
        double p=Double.parseDouble(in.readUTF());
        double q=Double.parseDouble(in.readUTF());
        double A=Double.parseDouble(in.readUTF());
        double B=(Math.pow(q,b)%p);
        DataOutputStream out=new DataOutputStream(server.getOutputStream());
        out.writeUTF(Double.toString(B));
        Double Skey=(Math.pow(A,b)%p);
        System.out.println("Secret key:"+Skey);
        server.close();
        serverSocket.close();

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        sc.close();
    }
}
