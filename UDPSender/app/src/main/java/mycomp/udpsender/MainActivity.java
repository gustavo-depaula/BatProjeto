package mycomp.udpsender;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.app.AlertDialog;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import io.github.controlwear.virtual.joystick.android.JoystickView;

public class MainActivity extends AppCompatActivity {

    public EditText ipTxt;
    public EditText portTxt;
    public Button updateBt;
    public Switch sendSw;

    public String ip = "192.168.0.17";
    public int port = 55056;
    public boolean sendSwitchState;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTitle("BatControle");
        super.onCreate(savedInstanceState);

        getSupportActionBar().setLogo(R.drawable.ic_launcher);
        getSupportActionBar().setDisplayUseLogoEnabled(true);

        setContentView(R.layout.activity_main);

        this.ipTxt = (EditText) findViewById(R.id.ip_txt);
        this.portTxt = (EditText) findViewById(R.id.port_txt);
        this.updateBt = (Button) findViewById(R.id.updateButton);
        this.sendSw = (Switch) findViewById(R.id.sendSwitch);

        this.beginApp();
    }

    void beginApp() {
        this.ipTxt.setText(this.ip);
        this.portTxt.setText(Integer.toString(this.port));

        updateBt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                MainActivity.this.updateValues();
                AlertDialog.Builder alert = new AlertDialog.Builder(MainActivity.this);
                alert.setTitle("Done!").setMessage("Changes has been updated.");
                alert.show();
            }
        });
        sendSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean value) {
                MainActivity.this.sendSwitchState = value;
                if(value)
                    MainActivity.this.updateBt.setEnabled(false);
                else
                    MainActivity.this.updateBt.setEnabled(true);
            }
        });

        JoystickView joystick = (JoystickView) findViewById(R.id.joystick);

        joystick.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                if(MainActivity.this.sendSwitchState) {
                    float str = (float)strength / 100;
                    float motorLeft=0, motorRight=0;
                    char forw_backw = 'n';

                    if (angle >= 0 && angle < 90) {
                        motorLeft = 1;
                        motorRight = ((float)angle / 90);
                        forw_backw = 'f';
                    }
                    else if(angle == 90){
                        motorLeft = 1;
                        motorRight = 1;
                        forw_backw = 'f';
                    }
                    else if(angle>90 && angle<=180){
                        motorLeft = ((float)(angle-90)/-90)+1;
                        motorRight = 1;
                        forw_backw = 'f';
                    }
                    else if(angle>180 && angle<270){
                        motorLeft = ((float)(angle-180)/90);
                        motorRight = 1;
                        forw_backw = 'b';
                    }
                    else if(angle == 270){
                        motorLeft = 1;
                        motorRight = 1;
                        forw_backw = 'b';
                    }
                    else if(angle>270 && angle<360){
                        motorLeft = 1;
                        motorRight = ((float)(angle-270)/-90)+1;
                        forw_backw = 'b';
                    }
                    motorLeft *= str * 255;
                    motorRight *= str * 255;
                    final String msg = Integer.toString((int)motorLeft) + ';' + Integer.toString((int)motorRight) + ';' + forw_backw;

                    final int port = MainActivity.this.port;
                    final String ip = MainActivity.this.ip;

                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            DatagramSocket udpSocket  = null;
                            try {
                                udpSocket = new DatagramSocket(port);
                                InetAddress serverAddr = InetAddress.getByName(ip);
                                byte[] buf = msg.getBytes();
                                DatagramPacket packet = new DatagramPacket(buf, buf.length, serverAddr, port);
                                udpSocket.send(packet);
                            } catch (IOException e) {} finally {
                                if (udpSocket != null)
                                    udpSocket.close();
                            }
                        }
                    }).start();
                }
            }
        });
    }
    void updateValues(){
        this.ip = this.ipTxt.getText().toString();
        this.port = Integer.parseInt(this.portTxt.getText().toString());
    }
}