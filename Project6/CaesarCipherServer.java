/*
 * CaesarCipherServer implements the server side of taking a string and caeser cipher encrypting it.
 * Gets called by a client application.
 *
 * Written by: Ethan Clark
 * Project 6 - CS 232
 * Date: May 15, 2017
 */

import java.util.Scanner;
import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class CaesarCipherServer {

	public static void main(String[] args) throws Exception {

		// Check that there was one argument from the user
		if (args.length != 1) {
            System.err.println("Usage: java server <port number>");
            System.exit(1);
        }

        // Get the port number from the user
		int portNumber = Integer.parseInt(args[0]);
		System.out.println("Server started on port " + portNumber);

		// Create a forever loop variable to wait for new connections to the server
		Boolean listening = true;

		// Try connecting server to the given port number...
		try (ServerSocket serverSocket = new ServerSocket(portNumber)) { 

			// Continuously wait for new connections to the server and spawn off new threads
            while (listening) {
	            new CaesarCipherMultiThread(serverSocket.accept()).start();
	        }

	    // If the server is unable to use the given port number...
	    } catch (IOException e) {
            System.err.println("Could not listen on port " + portNumber);
            System.exit(-1);
        }
    }
}

// Class that implements a new spawned off thread for the server
class CaesarCipherMultiThread extends Thread {

	// Instance variable for the client socket connection
	private Socket clientSocket = null;
	private String ipAddress;

	// Assign the connection from the main class to the spawned off thread class
	// Also display date, time, and IP Address of connected client
	public CaesarCipherMultiThread(Socket socket) {
		this.clientSocket = socket;
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		ipAddress = this.clientSocket.getRemoteSocketAddress().toString();
		System.out.println("New connection to " + ipAddress + " at " + dateFormat.format(date));
	}

	// Run the forever loop, prompting for user input and encrypting the input
	public void run() {

		try (   PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		) {
			// Boolean to know if the user has already entered a rotation value
			Boolean integer = true;
			Integer rotation = 0;
			String inputline;
	
			// While the server can read in input from the client
			while ((inputline = in.readLine()) != null) {

				// If user just connected, they need to give a rotation value
				if (integer) {
					rotation = Integer.parseInt(inputline);
					out.append(rotation.toString());
					out.append("\n");
					out.flush();
					integer = false;
					continue;
				}

				// Call caesarCipher function to encrypt the given text
				out.append(caesarCipher(rotation, inputline));
				out.append("\n");
				out.flush();
			}

			// Once the client quits, close connection to client and stop running thread
			System.out.println("Closing connection to client " + ipAddress);
			out.close();
			in.close();
			clientSocket.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}


	// caesarCipher function to encrypt text based on a rotation value
	//		Making sure to loop back around to the beginning of the alphabet if the rotation brings to the end of the alphanet
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