package com.example.relativistickinematics;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import android.content.res.AssetManager;
import android.util.Log;

import android.os.Bundle;
import android.app.Activity;
//import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends Activity {

	double mp = 938.27203; // mass of proton
	double c = 0.299792458; // speed of light m/ns
	double mass;
	double KE = 0;
	double momt = 0;
	double Gamma = 1;
	double beta = 0;
	double length = 1;
	double tof = 1000000;
	double Brho = 0;
	int Z = 1; // number of unit charge of particle
	int A = 1; // number of unit charge of particle
	Button mass_Cal;
	Button ke_Cal;
	Button momt_Cal;
	Button gamma_Cal;
	Button beta_Cal;
	Button tof_Cal;
	Button Brho_Cal;
	// Button isotopes;
	EditText mass_dis;
	EditText Z_dis;
	EditText A_dis;
	EditText KE_dis;
	EditText momt_dis;
	EditText Gamma_dis;
	EditText beta_dis;
	EditText length_dis;
	EditText tof_dis;
	EditText Brho_dis;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		mass_Cal =(Button) findViewById(R.id.mass_view);
		ke_Cal = (Button) findViewById(R.id.ke_but);
		momt_Cal = (Button) findViewById(R.id.momt_but);
		gamma_Cal = (Button) findViewById(R.id.gamma_but);
		beta_Cal = (Button) findViewById(R.id.beta_but);
		tof_Cal = (Button) findViewById(R.id.tof_but);
		Brho_Cal = (Button) findViewById(R.id.Brho_but);
		// isotopes = (Button) findViewById(R.id.isotopes_but );

		mass_dis = (EditText) findViewById(R.id.mass_text);
		Z_dis = (EditText) findViewById(R.id.Z_text);
		A_dis = (EditText) findViewById(R.id.A_text);
		KE_dis = (EditText) findViewById(R.id.ke_text);
		momt_dis = (EditText) findViewById(R.id.momt_text);
		Gamma_dis = (EditText) findViewById(R.id.gamma_text);
		beta_dis = (EditText) findViewById(R.id.beta_text);
		length_dis = (EditText) findViewById(R.id.length_text);
		tof_dis = (EditText) findViewById(R.id.tof_text);
		Brho_dis = (EditText) findViewById(R.id.Brho_text);

		mass_dis.setText("" + mp);
		Z_dis.setText("" + Z);
		A_dis.setText("" + A);
		KE_dis.setText("" + KE);
		momt_dis.setText("" + momt);
		Gamma_dis.setText("" + Gamma);
		beta_dis.setText("" + beta);
		tof_dis.setText("" + tof);
		length_dis.setText("" + length);
		Brho_dis.setText("" + Brho);
		
		
		mass_Cal.setOnClickListener(new View.OnClickListener() { 
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				Log.i("Read","A = "+Integer.toString(A)+", Z = "+Integer.toString(Z)) ;
				
				mass = FindMass(A,Z);
				mass_dis.setText("" + mass);
				
			}
		});
		
		ke_Cal.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				length = Double.parseDouble(length_dis.getText().toString());
				mass = FindMass(A,Z);
				
				KE = Double.parseDouble(KE_dis.getText().toString()) * A;

				Gamma = (KE + mass) / mass;
				beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
				momt = mass * Gamma * beta;
				tof = length / (beta * c);
				Brho = mass * Gamma * beta / c / 1000 / Z;

				mass_dis.setText("" + mass);
				momt_dis.setText("" + momt);
				Gamma_dis.setText("" + Gamma);
				beta_dis.setText("" + beta);
				tof_dis.setText("" + tof);
				Brho_dis.setText("" + Brho);

			}
		});
		
		momt_Cal.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				length = Double.parseDouble(length_dis.getText().toString());
				mass = FindMass(A,Z);
				
				momt = Double.parseDouble(momt_dis.getText().toString());

				KE = (Math.sqrt(Math.pow(mass,2)+Math.pow(momt,2)) - mass)/A;
				Gamma = (KE + mass) / mass;
				beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
				momt = mass * Gamma * beta;
				tof = length / (beta * c);
				Brho = mass * Gamma * beta / c / 1000 / Z;

				mass_dis.setText("" + mass);
				KE_dis.setText("" + KE);
				Gamma_dis.setText("" + Gamma);
				beta_dis.setText("" + beta);
				tof_dis.setText("" + tof);
				Brho_dis.setText("" + Brho);

			}
		});

		gamma_Cal.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				length = Double.parseDouble(length_dis.getText().toString());
				mass = FindMass(A,Z);
				
				Gamma = Double.parseDouble(Gamma_dis.getText().toString());

				KE = (Gamma - 1) * mass / A;
				beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
				momt = mass * Gamma * beta;
				tof = length / (beta * c);
				Brho = mass * Gamma * beta / c / 1000 / Z;

				mass_dis.setText("" + mass);
				KE_dis.setText("" + KE);
				momt_dis.setText("" + momt);
				beta_dis.setText("" + beta);
				tof_dis.setText("" + tof);
				Brho_dis.setText("" + Brho);

			}
		});

		beta_Cal.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				length = Double.parseDouble(length_dis.getText().toString());
				mass = FindMass(A,Z);
				
				beta = Double.parseDouble(beta_dis.getText().toString());

				Gamma = 1 / Math.pow(1 - Math.pow(beta, 2), 0.5);
				KE = (Gamma - 1) * mass / A;
				momt = mass * Gamma * beta;
				tof = length / (beta * c);
				Brho = mass * Gamma * beta / c / 1000 / Z;

				mass_dis.setText("" + mass);
				KE_dis.setText("" + KE);
				momt_dis.setText("" + momt);
				Gamma_dis.setText("" + Gamma);
				tof_dis.setText("" + tof);
				Brho_dis.setText("" + Brho);

			}
		});

		tof_Cal.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				length = Double.parseDouble(length_dis.getText().toString());
				mass = FindMass(A,Z);
				
				tof = Double.parseDouble(tof_dis.getText().toString());

				beta = length / (tof * c);
				Gamma = 1 / Math.pow(1 - Math.pow(beta, 2), 0.5);
				momt = mass * Gamma * beta;
				KE = (Gamma - 1) * mass / A;
				Brho = mass * Gamma * beta / c / 1000 / Z;

				mass_dis.setText("" + mass);
				KE_dis.setText("" + KE);
				momt_dis.setText("" + momt);
				Gamma_dis.setText("" + Gamma);
				beta_dis.setText("" + beta);
				Brho_dis.setText("" + Brho);

			}
		});

		Brho_Cal.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Z = Integer.parseInt(Z_dis.getText().toString());
				A = Integer.parseInt(A_dis.getText().toString());
				length = Double.parseDouble(length_dis.getText().toString());
				mass = FindMass(A,Z);
				
				Brho = Double.parseDouble(Brho_dis.getText().toString());

				Gamma = Math.pow(Math.pow(Brho * Z * 1000 * c / mass, 2) + 1,0.5);
				KE = (Gamma - 1) * mass / A;
				beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
				momt = mass * Gamma * beta;
				tof = length / (beta * c);

				mass_dis.setText("" + mass);
				KE_dis.setText("" + KE);
				momt_dis.setText("" + momt);
				Gamma_dis.setText("" + Gamma);
				beta_dis.setText("" + beta);
				tof_dis.setText("" + tof);

			}
		});

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	

	private double FindMass(int a,int b){
	//	Log.i("Read","a ="+Integer.toString(a)+", b = "+Integer.toString(b)) ;
		int A_tmp, Z_tmp, numLine=1;
		double m1_tmp, m2_tmp;
		
		double amu = 931.494; 
					
		int flag = 0;
		AssetManager assetManager = getAssets();
		BufferedReader reader = null;
		
        try {
			InputStream massData = assetManager.open("mass03.txt");
        	reader = new BufferedReader(new InputStreamReader(massData));
            String text = null;
       //     Log.i("Read","flag = " + Integer.toString(flag)+", numLine = " + Integer.toString(numLine));
            // repeat until all lines is read
            while ((text = reader.readLine()) != null && flag == 0) {
            	if(numLine >= 40 && numLine <3128){
            	//	Log.i("Read","numLine ="+Integer.toString(numLine)) ;
            	//	Log.i("Read",text.toString()) ;
            	//	Log.i("Read","A_tmp string = " + text.substring(15, 19)) ;
            	//	Log.i("Read","Z_tmp string = " + text.substring(10, 14)) ;
            		A_tmp = Integer.parseInt(text.substring(15, 19).replaceAll("\\s",""));
            		Z_tmp = Integer.parseInt(text.substring(10, 14).replaceAll("\\s",""));
            	//	Log.i("Read","A_tmp ="+Integer.toString(A_tmp)+", Z_tmp = "+Integer.toString(Z_tmp)) ;
            		if(A_tmp == a && Z_tmp == b){
            	//		Log.i("Read","m1_tmp string = " + text.substring(96, 99)) ;
	            //		Log.i("Read","m2_tmp string = " + text.substring(99, 112)) ;
            			m1_tmp = Double.parseDouble(text.substring(96, 99).replaceAll("\\s",""));
            			m2_tmp = Double.parseDouble(text.substring(99, 112).replaceAll("\\s","").replaceAll("[#]",""));
            	//		Log.i("Read","m1_tmp ="+Double.toString(m1_tmp)+", m2_tmp = "+Double.toString(m2_tmp)) ;
            			mass = (m1_tmp+m2_tmp/1e6)*amu;
            	//		Log.i("Read","mass ="+Double.toString(mass)) ;
            			flag = 1;
            		}
     
            	}
            	numLine ++;
            }
        } catch (IOException e) {
            e.printStackTrace();
            Log.i("Error",e.toString()) ;
            mass = -3;
        } finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        
        if (flag ==0){
        	mass = -404;
        }
		
		return mass;
	}

	
}

