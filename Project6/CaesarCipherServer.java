/*
 * CaesarCipherServer implements the server side of taking a string and caeser cipher encrypting it.
 * Gets called by a client application.
 *
 * Written by: Ethan Clark
 * Project 6 - CS 232
 * Date: May 7, 2017
 */

import java.util.Scanner;
import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class CaesarCipherServer {

	public static void main(String[] args) throws Exception {

		int portNumber = Integer.parseInt(args[0]);
		ServerSocket my_socket = new ServerSocket(portNumber);

		while (true) {
			Socket clientSocket = my_socket.accept();
			PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

			String string;
			Integer rotation;

			while ((string = in.readLine()) != null) {

				try {
					rotation = Integer.parseInt(string);
					out.append(rotation.toString());
					out.append("\n");
					out.flush();
				} catch (NumberFormatException ne) {
					out.append("Rotation number must be an integer 1 - 25!");
					out.flush();
					break;
				}

				out.append(caesarCipher(rotation, string));
				out.append("\n");
				out.flush();
			}

			out.close();
			in.close();
			clientSocket.close();
		
		}
	}

	private static String caesarCipher(Integer rotation, String string) {

		String tempString = "";
		Integer length = string.length();

		for (Integer x = 0; x < length; x++) {
			char c = (char)(string.charAt(x) + rotation);
			if (c > 'z') {
				tempString += (char)(string.charAt(x) - (26-rotation));
			} else {
				tempString += (char)(string.charAt(x) + rotation);
			}
		}
		return tempString;
	}

}