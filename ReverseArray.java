import java.util.ArrayList;
import java.util.Scanner;
public class ReverseArray{
	public static ArrayList total = new ArrayList();
	public static Scanner reader = new Scanner(System.in);
	public static void main(String[] args){
	reader();
	reverser();
	for(int i=0;i<total.size();i++){
	System.out.println(total.get(i));
	}	
	}
	public static void reader(){
		int input;
		while(true){
			input = reader.nextInt();
			if(input == -1)
				break;
			else 
				total.add(input);
		}
	}
	public static void reverser(){
		ArrayList temp = new ArrayList();
		for(int i=0;i<total.size();i++){
			temp.add(total.get(total.size()-i-1));
		}	
		total = temp;
	}
}

