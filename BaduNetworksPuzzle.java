import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class BaduNetworksPuzzle {

	public static void main(String[] args) throws IOException {
		String hostname = args[0];
		int port = 80;

	    Socket socket = null;
	    PrintWriter writer = null;
	    BufferedReader reader = null;

        socket = new Socket(hostname, port);
        writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
        writer.println("GET / HTTP/1.0");
        writer.println("Host: " + hostname);
        writer.println("Accept: */*");
        writer.println("User-Agent: Java"); 
        writer.println(""); 
        writer.flush();

        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        String line;
        while((line = reader.readLine()) != null) {
            if (line.isEmpty()) break;
            System.out.println(line);
        } 
        if (reader != null) { reader.close(); }
        if (writer != null) { writer.close(); }
        if (socket != null) { socket.close(); }
	}
}

// ALTERNATE SOLUTION 

// 		   String hostname = "stackoverflow.com";
//         int port = 80;

//         Socket socket = null;
//         PrintWriter writer = null;
//         BufferedReader reader = null;

//         try {
//             socket = new Socket(hostname, port);
//             writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
//             writer.println("GET / HTTP/1.0");
//             writer.println("Host: " + hostname);
//             writer.println("Accept: */*");
//             writer.println("User-Agent: Java"); // Be honest.
//             writer.println(""); // Important, else the server will expect that there's more into the request.
//             writer.flush();

//             reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//             for (String line; (line = reader.readLine()) != null;) {
//                 if (line.isEmpty()) break; // Stop when headers are completed. We're not interested in all the HTML.
//                 System.out.println(line);
//             }
//         } finally {
//             if (reader != null) try { reader.close(); } catch (IOException logOrIgnore) {} 
//             if (writer != null) { writer.close(); }
//             if (socket != null) try { socket.close(); } catch (IOException logOrIgnore) {} 
//         }



