/*
 * CaesarCipherClient is the client for calling the CaesarCipher server after prompting for the rotation number 
 *	and any number of lines of text.
 * 
 * Written by: Ethan Clark (elc3)
 * CS 232 - Project6
 * Date: May 3, 2017
 */

import java.util.Scanner;

public class CaesarCipherClient {
	
	public static void main(String[] args) {
		System.out.println("Welcome to Ethan's CasesarCipherClient!");
		System.out.println("Please enter the rotation offset integer (1..25): ");

		Scanner getInput = new Scanner(System.in);
		int rotation = getInput.nextInt();

		System.out.println("User entered integer: " + rotation);

	}
}
