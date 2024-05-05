package Prac2;
import java.util.Scanner;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
public class md5 {
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter a string:");
        String input=sc.next();
        String md5Hash=calculateMD5(input);
        System.out.println("The MD5 hash is:"+md5Hash);
        sc.close();
    }
    public static String calculateMD5(String input)
    {
        try{
            MessageDigest md=MessageDigest.getInstance("MD5");
            md.update(input.getBytes());
            byte[] bytes=md.digest();
            StringBuilder sb=new StringBuilder();
            for(byte b:bytes)
            {
                sb.append(Integer.toString((b&0xff)+0x100,16).substring(1));
            }
            return sb.toString();
        }
        catch(NoSuchAlgorithmException e){
           throw new RuntimeException(e);
        }
    }
}
