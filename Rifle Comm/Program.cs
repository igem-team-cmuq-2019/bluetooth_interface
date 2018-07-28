using System;
using System.IO.Ports;
using System.Threading;

public class Rifle_Connect
{
    static bool _continue;
    static SerialPort _serialPort;
    static bool _notFailed = true;

    public static void Main()
    {
        Console.WriteLine("\n\n");
        Console.WriteLine("      Serial Connection to Rifle ");
        Console.WriteLine("\n  ----------------------------------\n");
        Console.WriteLine("      type quit to exit.\n");
        string message;
        StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
        Thread readThread = new Thread(Read);

        _serialPort = new SerialPort
        {
            ReadTimeout = 500,
            WriteTimeout = 500
        };


        foreach (string s in SerialPort.GetPortNames())
        {
            Console.WriteLine("\n   >Trying {0}.", s);
            Console.WriteLine("   Connecting...\n");
            _serialPort.PortName = s;
            try
            {
                _serialPort.Open();
            }
            catch (System.IO.IOException)
            {
                Console.WriteLine("   Trying another port...");
            }
            catch (System.InvalidOperationException)
            {
                Console.WriteLine("   Port is closed. Trying another port...");
            }
            catch (TimeoutException)
            {
                Console.WriteLine("   Connection timed Out. Trying another port...");

            }
            if (_serialPort.IsOpen) { break; }
            

        }

        if (_serialPort.IsOpen == false)
        {
            Console.WriteLine("   None of the Ports are available.");
            Console.WriteLine("   Press Ctrl+C to quit.");
        }
        else
        {
            try
            {
                _serialPort.WriteLine("\n");
            }
            catch (TimeoutException)
            {
                _notFailed = false;
                

            }
            //Console.WriteLine(_serialPort.ReadExisting());
        }

        if (_notFailed)
        {
            _continue = true;
            Console.WriteLine("   Connected.");
            readThread.Start();

        }

        while (_continue)
        {
            message = Console.ReadLine();

            if (stringComparer.Equals("quit", message))
            {
                _continue = false;
            }
        }

        try
        {
            readThread.Join();
        }
        catch (System.Threading.ThreadStateException)
        {
            Console.WriteLine("   Connection failed, press return to exit.");

        }
        _serialPort.Close();
        Console.ReadLine();
    }

    public static void Read()
    {
        while (_continue)
        {
            try
            {
                string message = _serialPort.ReadLine();
                Console.WriteLine("   " + message);
            }
            catch (TimeoutException)
            {

            }

        }
    }

    public static string SetPortName(string defaultPortName)
    {
        string portName;

        Console.WriteLine("   Available Ports:");
        

        Console.Write("   COM port({0}): ", defaultPortName);
        portName = Console.ReadLine();

        if (portName == "")
        {
            portName = defaultPortName;
        }
        return portName;
    }
}