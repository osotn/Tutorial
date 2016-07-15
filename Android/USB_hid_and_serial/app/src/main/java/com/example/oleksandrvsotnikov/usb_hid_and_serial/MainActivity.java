package com.example.oleksandrvsotnikov.usb_hid_and_serial;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.TextView;
import com.example.oleksandrvsotnikov.usb_hid_and_serial.R;


public class MainActivity extends Activity {

    private Button btnCheck;
    private TextView textInfo, debugInfo, dataInfo;
    public String debug_string = "", data_string = "", can_string = "";
    private UsbDevice device;
    private UsbManager manager;
    private UsbDeviceConnection connection;
    private boolean alive = false;
    private  int iACMIntef = 0;
    private Timer timer;

    protected class RemindTask extends TimerTask {
        @Override
        public void run() {
            mHandler.obtainMessage(1).sendToTarget();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btnCheck = (Button) findViewById(R.id.check);
        textInfo = (TextView) findViewById(R.id.info);
        debugInfo = (TextView) findViewById(R.id.debug);
        dataInfo = (TextView) findViewById(R.id.data);
        btnCheck.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                textInfo.setText("");

                if (alive)
                {
                    alive = false;
                    return;
                }

                alive = true;

                checkInfo();

                if (connection == null || iACMIntef == -1)
                {
                    alive = false;
                    return;
                }

                new CommUsbThread();
            }
        });


        timer = new Timer();
        timer.schedule(new RemindTask(), 0, 5 * 1000);


        // SERVER
        //serverThread = new Thread(new ServerThread());
        //serverThread.start();
        //new Thread(new ClientThread()).start();
    }

    public byte camera_mode = 0;

    public void onCheckboxClicked(View view) {
        // Is the view now checked?
        boolean checked = ((CheckBox) view).isChecked();

        // Check which checkbox was clicked
        switch(view.getId()) {
            case R.id.checkbox_1:
                if (checked)
                    camera_mode |= 0x01;
                else
                    camera_mode &= ~0x01;
                break;
            case R.id.checkbox_2:
                if (checked)
                    camera_mode |= 0x02;
                else
                    camera_mode &= ~0x02;
                break;
        }
    }

    private void checkInfo() {
        manager = (UsbManager) getSystemService(Context.USB_SERVICE);

        HashMap<String , UsbDevice> deviceList = manager.getDeviceList();
        Iterator<UsbDevice> deviceIterator = deviceList.values().iterator();
        String s = "14:00 ";
        while (deviceIterator.hasNext()) {

            UsbDevice iDevice = deviceIterator.next();

            s += "DeviceID: " + iDevice.getDeviceId() + " "
                    + "DeviceName: " + iDevice.getDeviceName() + " "
                    + "DeviceClass: " + iDevice.getDeviceClass() + " - "
                    + "DeviceSubClass: " + iDevice.getDeviceSubclass() + " "
                    + "VendorID: " + iDevice.getVendorId() + " "
                    + "ProductID: " + iDevice.getProductId() + " ";

            if (((iDevice.getVendorId() == 1317) && (iDevice.getProductId() == 42156)) ||
                    ((iDevice.getVendorId() == 9025) && (iDevice.getProductId() == 67)) )
            {
                s += " !!! SELECTED !!!!";
                device = iDevice;
            }
        }

        connection = manager.openDevice(device);


        if (connection == null)
        {
            s += "!!! Connection == null" + "\n";
        }
        else
        {
            int iACMIntef_local = -1;

            // Debug info.
            //s += "Interfaces number: " + device.getInterfaceCount() + "\n";

            for (int i=0; i < device.getInterfaceCount(); i++)
            {
                UsbInterface intf = device.getInterface(i);
                s += "\n" + i + ". Interface: Class= " + intf.getInterfaceClass() + " ";
                s += "     EP Nums: " + intf.getEndpointCount() + " ";

                if (intf.getInterfaceClass() == 10)
                {
                    if (iACMIntef_local == -1) {
                        iACMIntef_local = i;

                        //s += " selected interface: " + iACMIntef_local + "\n";
                    }
                }
            }

            iACMIntef = iACMIntef_local;

            if (connection.claimInterface(device.getInterface(iACMIntef), true))
            {
                int res1 = connection.controlTransfer(0x21, 34, 0, 0, null, 0, 0);
                int res2 = connection.controlTransfer(0x21, 32, 0, 0,
                        new byte[] { (byte) 0x00, (byte) 0xC2, 0x01, 0x00, 0x00, 0x00, 0x08 }, 7, 0);
            }
            else
            {
                s += "Fail claimInterface" + "\n";
            }

            if (connection.claimInterface(device.getInterface(iACMIntef + 2), true))
            {
                int res1 = connection.controlTransfer(0x21, 34, 0, 0, null, 0, 0);
                int res2 = connection.controlTransfer(0x21, 32, 0, 0,
                        new byte[] { (byte) 0x00, (byte) 0xC2, 0x01, 0x00, 0x00, 0x00, 0x08 }, 7, 0);
            }
            else
            {
                s += "Fail claimInterface" + "\n";
            }

        }

        textInfo.setText(s);
    }


    private class CommUsbThread implements Runnable {
        public CommUsbThread() {
            new Thread(this).start();
        }

        @Override
        public void run() {
            if (device == null) return;


            if (device.getInterfaceCount() == 0) return;


            UsbEndpoint epIN = null;
            UsbEndpoint epOut = null;

            UsbInterface usbInterface = device.getInterface(iACMIntef);

            for (int i = 0; i < usbInterface.getEndpointCount(); i++) {
                if (usbInterface.getEndpoint(i).getType() == UsbConstants.USB_ENDPOINT_XFER_BULK) {
                    if (usbInterface.getEndpoint(i).getDirection() == UsbConstants.USB_DIR_IN) {
                        epIN = usbInterface.getEndpoint(i);
                    }
                    else if (usbInterface.getEndpoint(i).getDirection() == UsbConstants.USB_DIR_OUT) {
                        epOut = usbInterface.getEndpoint(i);
                    }
                }
            }

            UsbInterface usbInterface2 = device.getInterface(iACMIntef + 2);
            UsbEndpoint epIN2 = null;

            if (usbInterface2 == null) {

                debug_string += "Fail to getInterface: " + (iACMIntef + 2) + "\n";
                mHandler.obtainMessage(1).sendToTarget();
            }
            else {

                debug_string += "CAN getInterface: " + (iACMIntef + 2) + "\n";
                debug_string += "nEPs: " + usbInterface2.getEndpointCount() + "\n";


                for (int i = 0; i < usbInterface2.getEndpointCount(); i++) {
                    if (usbInterface2.getEndpoint(i).getType() == UsbConstants.USB_ENDPOINT_XFER_BULK) {
                        if (usbInterface2.getEndpoint(i).getDirection() == UsbConstants.USB_DIR_IN) {
                            debug_string += "Find EpIN2 \n";
                            epIN2 = usbInterface2.getEndpoint(i);
                        }
                    }
                }

                if (epIN2 == null)
                {
                    debug_string += "No IN endpoind \n";

                }

                mHandler.obtainMessage(1).sendToTarget();
            }

            byte camera_mode_copy = 8;
            int nSend = 0;

            while(alive) {
                byte[] bt = null;
                int cnt = -1;

                if (epIN != null) {
                    bt = new byte[epIN.getMaxPacketSize()];
                    cnt = connection.bulkTransfer(epIN, bt, epIN.getMaxPacketSize(), 10);

                    if (cnt >= 0) {

                        byte [] bt_data = Arrays.copyOfRange(bt, 0, cnt);
                        data_string += String.format("btn: (%d) 0x%02x ", cnt, bt_data[0]);
                        mHandler.obtainMessage(1).sendToTarget();
                    }
                }

                if (epIN2 != null) {
                    bt = new byte[epIN.getMaxPacketSize()];
                    cnt = connection.bulkTransfer(epIN2, bt, epIN.getMaxPacketSize(), 10);

                    if (cnt >= 0) {

                        byte[] bt_data = Arrays.copyOfRange(bt, 0, cnt);

                        // SERVER
                        //try {
                        //    PrintWriter out = new PrintWriter(new BufferedWriter(
                        //            new OutputStreamWriter(socket.getOutputStream())), true);
                        //    out.println(new String(bt_data));
                        //} catch (UnknownHostException e) {
                        //    e.printStackTrace();
                        //} catch (IOException e) {
                        //    e.printStackTrace();
                        //} catch (Exception e) {
                        //    e.printStackTrace();
                        //}
                        //debug_string += "ToServer: "  + nSend + "(" + cnt + ") ";

                        can_string += new String(bt_data);
                        mHandler.obtainMessage(1).sendToTarget();
                        //nSend++;
                    }
                }

                if (epOut != null) {

                    if ( (camera_mode_copy == -1) || (camera_mode_copy != camera_mode) )
                    {
                        camera_mode_copy = camera_mode;

                        int n = connection.bulkTransfer(epOut,
                                new byte[] {(byte)(camera_mode_copy | 0x04)}, 1, 0);

                        debug_string += "Send: = " +
                                String.format("0x%02x ", camera_mode_copy) +
                                " result = " + n + "\n";
                        mHandler.obtainMessage(1).sendToTarget();
                    }
                }
            }
            connection.close();
        }
    }

    protected Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            String debug_s = "Time: " + System.currentTimeMillis() + "\n";

            if (debug_string.length() > 50) {
                debug_string = "... " + debug_string.substring(debug_string.length()-40, debug_string.length());
            }

            debug_s += debug_string;
            debugInfo.setText(debug_s);


            String data_s = "ArduinoButtons:\n";

            if (data_string.length() > 100) {
                data_string = "... " + data_string.substring(data_string.length()-50, data_string.length());
            }
            data_s += data_string + "\nCAN data:\n";

            if (can_string.length() > 700) {
                can_string = "... " + can_string.substring(can_string.length()-600, can_string.length());
            }
            data_s += can_string;

            dataInfo.setText(data_s);
        }
    };

    // TEST SERVER

    private ServerSocket serverSocket;
    Thread serverThread = null;
    public static final int SERVERPORT = 6001;

    class ServerThread implements Runnable {
        public void run() {
            Socket socket = null;
            try {
                serverSocket = new ServerSocket(SERVERPORT);
            } catch (IOException e) {
                e.printStackTrace();
            }
            while (!Thread.currentThread().isInterrupted()) {
                try {
                    socket = serverSocket.accept();

                    CommunicationThread commThread = new CommunicationThread(socket);
                    new Thread(commThread).start();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class CommunicationThread implements Runnable {
        private Socket clientSocket;
        private BufferedReader input;
        public CommunicationThread(Socket clientSocket) {
            this.clientSocket = clientSocket;
            try {
                this.input = new BufferedReader(new InputStreamReader(this.clientSocket.getInputStream()));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private int cnt = 0;

        public void run() {
            while (!Thread.currentThread().isInterrupted()) {
                try {
                    String read = input.readLine();

                    can_string += "<SRV:" + cnt + "(" + read.length() + ")>" + read;
                    mHandler.obtainMessage(1).sendToTarget();

                    cnt++;

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private Socket socket;
    private static final String SERVER_IP = "localhost";//"127.0.0.1"; // "10.0.2.2."

    class ClientThread implements Runnable {
        @Override
        public void run() {
            try {
                debug_string += "server IP: " + SERVER_IP + " \n";
                mHandler.obtainMessage(1).sendToTarget();

                InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
                socket = new Socket(serverAddr, SERVERPORT);
            } catch (UnknownHostException e1) {
                e1.printStackTrace();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}