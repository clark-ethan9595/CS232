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
		System.out.println("Welcome to Ethan's CasesarCipherClient!");

		Integer portNumber = Integer.parseInt(args[1]);
		String server_name = args[0];

		Socket serverSocket = new Socket(server_name, portNumber);

		PrintWriter out = new PrintWriter(serverSocket.getOutputStream(), true);

		System.out.println("Please enter the rotation offset integer (1..25): ");

		Scanner getInput = new Scanner(System.in);
		Integer rotation = getInput.nextInt();

		out.append(rotation.toString());
		out.append("\n");

		BufferedReader input = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
		String outputLine;

		outputLine = input.readLine();

		System.out.println("Server returned integer of: " + outputLine);

	}
}
