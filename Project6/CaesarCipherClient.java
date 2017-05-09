/*
 * CaesarCipherClient is the client for calling the CaesarCipher server after prompting for the rotation number
 *	and any number of lines of text.
 *
 * Written by: Ethan Clark (elc3)
 * CS 232 - Project6
 * Date: May 3, 2017
 */

import java.util.Scanner;
import java.net.Socket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class CaesarCipherClient {

	public static void main(String[] args) throws IOException {

		Integer portNumber = Integer.parseInt(args[1]);
		String server_name = args[0];

		System.out.println("Welcome to Ethan's CasesarCipherClient!\n");

		System.out.println("Please enter the rotation offset integer (1..25): ");

		Scanner getInput = new Scanner(System.in);
		Integer rotation = getInput.nextInt();

		Socket serverSocket = new Socket(server_name, portNumber);
		PrintWriter out = new PrintWriter(serverSocket.getOutputStream(), true);
		BufferedReader input = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));

		out.append(rotation.toString());
		out.append("\n");

		String outputLine;
		outputLine = input.readLine();

		System.out.println("Server returned integer of: " + outputLine + "\n");

		String returned;

		while (true) {
			System.out.println("Please enter the text to be encrypted: ");
			String text = getInput.nextLine();

			if (text.equals("q")) {
				System.out.println("Thanks for using the CaeserCipher!\n");
				break;
			}

			out.append(text);
			out.append("\n");
			out.flush();

			returned = input.readLine();

			System.out.println("Returned text is: " + returned);
		}

	}
}
