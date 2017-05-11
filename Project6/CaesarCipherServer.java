/*
 * CaesarCipherServer implements the server side of taking a string and caeser cipher encrypting it.
 * Gets called by a client application.
 *
 * Written by: Ethan Clark
 * Project 6 - CS 232
 * Date: May 11, 2017
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
		System.out.println("Server started on port " + portNumber);
		boolean listening = true;

		try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
			while (listening) {
				new CaesarCipherMultiThread(serverSocket.accept()).start();
			}
		} catch (IOException e) {
			System.err.println("Could not listen on port " + portNumber);
			Systemexit(-1);
		}
	}

	public class CaesarCipherMultiThread extends Thread {
		private Socket socket = null;

		public CaesarCipherMultiThread(Socket socket) {
			super("CaesarCipherMultiThread");
			this.socket = socket;
		}

		public void run() {
			Integer rotation = 0;
			try (
				PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
				BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			) {
				String string;
				while ((s = in.readLine()) != null) {
					rotation = Integer.parseInt(s);
					out.append(rotation.toString());
					out.append("\n");
					out.flush();
					out.append(caesarCipher(rotation, string));
					out.append("\n");
					out.flush();
				}

				out.close();
				in.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
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