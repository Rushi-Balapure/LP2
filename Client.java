package Prac1;
import java.util.Scanner;
import java.net.*;
import java.io.*;
public class Client {
    public static void main(String[] arge)
    {
        Scanner sc=new Scanner(System.in);
        try{
            String serverName="localhost";
            int port=8080;
            System.out.println("Enter P:");
            int p=sc.nextInt();
            System.out.println("Enter Q:");
            int q=sc.nextInt();
            System.out.println("Enter Client key(a):");
            int a=sc.nextInt();
            System.out.println("Connnecting to : "+serverName+" on port:"+port);
            Socket client=new Socket(serverName,port);
            System.out.println("Just Connected to:"+client.getRemoteSocketAddress());
            DataOutputStream out=new DataOutputStream(client.getOutputStream());
            out.writeUTF(Integer.toString(p));//send p
            out.writeUTF(Integer.toString(q));//send q
            double A=(Math.pow(q,a)%p);
            out.writeUTF(Double.toString(A));//send A

            System.out.println("from Client:Client's Public Key:"+A);
            DataInputStream in=new DataInputStream(client.getInputStream());
            double B=Double.parseDouble(in.readUTF());
            System.out.println("From Server:Server's Public Key:"+B);
            double Skey=(Math.pow(B,a)%p);
            System.out.println("Secret key for Encryption:"+Skey);
            client.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        sc.close();
    }
}
