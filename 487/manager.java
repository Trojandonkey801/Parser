import java.net.*;
import java.io.*;  
import java.util.*;
public class manager{
	ArrayList<Integer> agents = new ArrayList<Integer>();
	public void receive_input() {
		try{
			String serverIP = ("127.0.0.1");
			Socket clientSocket = new Socket(serverIP, 1234); 
			DataInputStream inStream  = new DataInputStream(clientSocket.getInputStream());
			DataOutputStream outStream = new DataOutputStream(clientSocket.getOutputStream());
			DatagramSocket dSocket = new DatagramSocket(80);
			byte[] buf = new byte[80];
			byte[] temp = new byte[80];
			DatagramPacket dPacket = new DatagramPacket(buf,buf.length);
			dSocket.receive(dPacket);
		}catch(IOException e){
			System.out.println(e);
		}
		finally{
		}
	
	class agents{
		public class agents(int ID, int startup, int interval, String IP, lkjkj){
		}
	}
}
