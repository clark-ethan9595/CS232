/*
 * CaesarCipherClient is the client for calling the CaesarCipher server after prompting for the rotation number
 *	and any number of lines of text
 *
 * Written by: Ethan Clark (elc3)
 * CS 232 - Project6
 * Date: May 11, 2017
 */

import java.util.Scanner;
import java.net.Socket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;

public class CaesarCipherClient {

	public static void main(String[] args) throws IOException {

		// Get the portNumber and the server name from the argument list
		Integer portNumber;
		String server_name = args[0];

		try {
			portNumber = Integer.parseInt(args[1]);
		} catch (NumberFormatException ex) {
			System.out.println("Second argument must be a valid port number!");
			return;
		}


		// Welcome the user and prompt for an integer offset value
		System.out.println("Welcome to Ethan's CasesarCipherClient!\n");

		System.out.println("Please enter the rotation offset integer (1..25): ");

		// Read in the integer value from the user
		Scanner getInput = new Scanner(System.in);
		Integer rotation = getInput.nextInt();

		// Create the necessary server sockets and connections to the CeaserCipherServer
		Socket serverSocket = new Socket(server_name, portNumber);
		OutputStream os = serverSocket.getOutputStream();
		PrintWriter out = new PrintWriter(os, true);

		// Write the integer offset to the CaesarCipherServer
		out.append(rotation.toString());
		out.append("\n");
		out.flush();

		// Read in the returned offset integer value from the CaesarCipherServer
		BufferedReader input = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
		String outputLine = input.readLine();
		System.out.println("Server returned integer of: " + outputLine + "\n");

		/*
		 * Continually prompt for the user to enter text
		 * Send the text to the CaesarCipherServer to be encrypted
		 * Read back the encrypted text and display to the user
		 *
		 * If the user enters "quit", quit the application
		 */
		String returned;
		while (true) {
			System.out.println("Please enter the text to be encrypted: ");
			String text = getInput.nextLine();

			if (text.equals("quit")) {
				System.out.println("\nThanks for using the CaeserCipher!\n");
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
