public class hello 
{

	//if a string has all unique characters
	public static boolean uniqueChar(String str) 
	{

		boolean[] array=new boolean[256];
		
		int length=str.length();
		for(int i=0; i<length; i++)
		{
			if(array[str.charAt(i)])	
				return false;	
			array[str.charAt(i)]=true;
		}
		return true;

		//additionally we could sort characters but it will be nlogn

	}


	// to reverse a C-Style String(dont touch last null character) //trick it inplace
	//in java we dont have sth like str.set(index, newchar) so doing in c++ is good with two pointer pointing to starting and ending of string
	public static void reverser(String stror)
	{

		StringBuilder str = new StringBuilder(stror); //this is extra space not good
		int first=0;
		int last=str.length()-2;
		
		for(;first<last;)
		{
			char tmp=str.charAt(first);

			str.setCharAt(first,str.charAt(last));
			str.setCharAt(last,tmp);

			first++;
			last--;
		}
		System.out.println(str);
	}



public static void removeDup(char[] str)
{
	int len=str.length;
	if(len<2)
		return;	
	boolean[] occurs=new boolean[256];
	for(int i=0; i<256; i++)
		occurs[i]=false;
	
	occurs[str[0]]=true;
	int end=1;
	for(int i=1; i<len; i++)
	{
		if(!occurs[str[i]])
		{
			occurs[str[i]]=true;
			str[end]=str[i];
			end++;
		}
	}
	str[end]=0;
	System.out.println(str);	
}


/*
	public static boolean checkAnagram(String str1, String str2)	
	{		// cinema, iceman
			return sort(str1)==sort(str2);
	}
*/

	public static void replaceSpaces(char[] str)
{
	//solution1
	String replaced="";
	int len=str.length;
	
	int numberofSpaces=0;
	for(int i=0; i<len; i++)
	{
		if(str[i]==' ')
		{
			replaced=replaced+"%20";
			numberofSpaces++;
		}
		else
		{
			replaced=replaced+str[i];
		}
	}
	System.out.println(replaced);
	//solution2
	//int newlength= numberofSpaces*2 +len;
	//str[newlength]='\0';

	/*for(int i=len-1; i>=0; i--)
	{
		if(str[i]==' ')
		{
			str[newlength-1]='0';
			str[newlength-2]='2';
			str[newlength-3]='%';
			newlength=newlength-3;
		}
		else
		{
			str[newlength-1]=str[i];
			newlength--;
		}
	}*/


	//System.out.println(str);
}



	public static int [][] rotate(int [][] input) 
	{
		//you cant do it inplace because dimensions will change

		int n =input.length;
		int m = input[0].length;
		int [][] output = new int [m][n];

		for (int i=0; i<n; i++)
			for (int j=0;j<m; j++)
				output [j][n-1-i] = input[i][j];
		return output;
	}


public static void makeZero(int [][] matrix)
{
	int n=matrix.length;
	int m=matrix[0].length;

	int[] r=new int[n];
	int[] c=new int[m];

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			if(matrix[i][j]==0)
			{
				r[i]=1;
				c[j]=1;
			}
		}
	}


	for (int i = 0; i < n; i++) 
	{ 
		for (int j = 0; j < m; j++) 
		{ 
			if ((r[i] == 1 || c[j] == 1)) 
			{ 	
				matrix[i][j] = 0;
 			} 
		} 
	} 
}
/*
public static boolean isRotation(String str1, String str2)
{
	if(str1.length != str2.length)
		return false;

	String s3=str1+str1;
	return isSubstring(s3,s2);
}
*/

    public static void main(String[] args) 
    {
        System.out.println("Hello");

        uniqueChar("hello");

        reverser("hello");
        char[] str={'h','e','l','l','o'};
        removeDup(str);
		
		char[] str2={'h',' ','e',' ',' ','l','l','o'};
        replaceSpaces(str2);







    }
    
}