package com.user.relativistickinematics;

import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {

    double c = 299.792458; // speed of light mm/ns
    double mass = 938.272046;
    String Sym = "1H";
    double Sp = 0;
    double Sn = 0;
    double BEA = 0;
    double KE = 0;
    double momt = 0;
    double Gamma = 1;
    double beta = 0;
    double length = 1000;
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

    EditText mass_dis;
    EditText Sym_dis;
    EditText BEA_dis;
    EditText Sp_dis;
    EditText Sn_dis;
    EditText Z_dis;
    EditText A_dis;
    EditText KE_dis;
    EditText momt_dis;
    EditText Gamma_dis;
    EditText beta_dis;
    EditText length_dis;
    EditText tof_dis;
    EditText Brho_dis;

    boolean editedName = false;

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

        mass_dis = (EditText) findViewById(R.id.mass_text);
        Sp_dis = (EditText) findViewById(R.id.Sp_text);
        Sn_dis = (EditText) findViewById(R.id.Sn_text);
        Sym_dis = (EditText) findViewById(R.id.Sym_text);
        BEA_dis = (EditText) findViewById(R.id.BEA_text);
        Z_dis = (EditText) findViewById(R.id.Z_text);
        A_dis = (EditText) findViewById(R.id.A_text);
        KE_dis = (EditText) findViewById(R.id.ke_text);
        momt_dis = (EditText) findViewById(R.id.momt_text);
        Gamma_dis = (EditText) findViewById(R.id.gamma_text);
        beta_dis = (EditText) findViewById(R.id.beta_text);
        length_dis = (EditText) findViewById(R.id.length_text);
        tof_dis = (EditText) findViewById(R.id.tof_text);
        Brho_dis = (EditText) findViewById(R.id.Brho_text);

        mass_dis.setText("" + mass);
        BEA_dis.setText(""+ BEA);
        Sp_dis.setText("" + Sp);
        Sn_dis.setText("" + Sn);
        Sym_dis.setText(""+Sym);
        Z_dis.setText("" + Z);
        A_dis.setText("" + A);
        KE_dis.setText("" + KE);
        momt_dis.setText("" + momt);
        Gamma_dis.setText("" + Gamma);
        beta_dis.setText("" + beta);
        tof_dis.setText("" + tof);
        length_dis.setText("" + length);
        Brho_dis.setText("" + Brho);



        Sym_dis.setOnEditorActionListener(new TextView.OnEditorActionListener(){

            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event){
                if( actionId == EditorInfo.IME_ACTION_DONE ||
                        actionId == EditorInfo.IME_ACTION_SEND ||
                        actionId == EditorInfo.IME_ACTION_NONE ||
                        actionId == EditorInfo.IME_ACTION_NEXT ||
                        event.getKeyCode() == KeyEvent.KEYCODE_ENTER){

                    Log.i("Reed", "================== edited.");
                    editedName = true;

                    return true;
                }

                editedName = false;
                return false;
            }

        });

        mass_Cal.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if( editedName == false) {
                    Z = Integer.parseInt(Z_dis.getText().toString());
                    A = Integer.parseInt(A_dis.getText().toString());
                    Log.i("Read","A = "+Integer.toString(A)+", Z = "+Integer.toString(Z)) ;
                    mass = FindMassByBEA(A, Z);
                    mass_dis.setText("" + mass);
                }else{
                    String name = Sym_dis.getText().toString();
                    mass = FindMassByName(name);
                    mass_dis.setText("" + mass);

                    Z_dis.setText("" + Z);
                    A_dis.setText("" + A);
                }
                Sym_dis.setText("" + Sym);

                BEA_dis.setText(""+BEA);
                Sp = FindSp(0,A,Z);
                Sp_dis.setText("" + Sp);

                Sn = FindSp(1,A,Z);
                Sn_dis.setText("" + Sn);

                editedName = false;

            }
        });

        ke_Cal.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Z = Integer.parseInt(Z_dis.getText().toString());
                A = Integer.parseInt(A_dis.getText().toString());
                length = Double.parseDouble(length_dis.getText().toString());
                mass = FindMassByBEA(A,Z);
                Sp = FindSp(0,A,Z);
                Sn = FindSp(1,A,Z);

                KE = Double.parseDouble(KE_dis.getText().toString()) * A;

                Gamma = (KE + mass) / mass;
                beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
                momt = mass * Gamma * beta;
                tof = length / (beta * c);
                Brho = mass * Gamma * beta / c / Z;

                mass_dis.setText("" + mass);
                Sp_dis.setText("" + Sp);
                Sn_dis.setText("" + Sn);
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
                Z = Integer.parseInt(Z_dis.getText().toString());
                A = Integer.parseInt(A_dis.getText().toString());
                length = Double.parseDouble(length_dis.getText().toString());
                mass = FindMassByBEA(A,Z);
                Sp = FindSp(0,A,Z);
                Sn = FindSp(1,A,Z);

                momt = Double.parseDouble(momt_dis.getText().toString());

                KE = (Math.sqrt(Math.pow(mass,2)+Math.pow(momt,2)) - mass)/A;
                Gamma = (KE + mass) / mass;
                beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
                momt = mass * Gamma * beta;
                tof = length / (beta * c);
                Brho = mass * Gamma * beta / c / Z;

                mass_dis.setText("" + mass);
                Sp_dis.setText("" + Sp);
                Sn_dis.setText("" + Sn);
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
                Z = Integer.parseInt(Z_dis.getText().toString());
                A = Integer.parseInt(A_dis.getText().toString());
                length = Double.parseDouble(length_dis.getText().toString());
                mass = FindMassByBEA(A,Z);
                Sp = FindSp(0,A,Z);
                Sn = FindSp(1,A,Z);

                Gamma = Double.parseDouble(Gamma_dis.getText().toString());

                KE = (Gamma - 1) * mass / A;
                beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
                momt = mass * Gamma * beta;
                tof = length / (beta * c);
                Brho = mass * Gamma * beta / c / Z;

                mass_dis.setText("" + mass);
                Sp_dis.setText("" + Sp);
                Sn_dis.setText("" + Sn);
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
                Z = Integer.parseInt(Z_dis.getText().toString());
                A = Integer.parseInt(A_dis.getText().toString());
                length = Double.parseDouble(length_dis.getText().toString());
                mass = FindMassByBEA(A,Z);
                Sp = FindSp(0,A,Z);
                Sn = FindSp(1,A,Z);

                beta = Double.parseDouble(beta_dis.getText().toString());

                Gamma = 1 / Math.pow(1 - Math.pow(beta, 2), 0.5);
                KE = (Gamma - 1) * mass / A;
                momt = mass * Gamma * beta;
                tof = length / (beta * c);
                Brho = mass * Gamma * beta / c / Z;

                mass_dis.setText("" + mass);
                Sp_dis.setText("" + Sp);
                Sn_dis.setText("" + Sn);
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
                Z = Integer.parseInt(Z_dis.getText().toString());
                A = Integer.parseInt(A_dis.getText().toString());
                length = Double.parseDouble(length_dis.getText().toString());
                mass = FindMassByBEA(A,Z);
                Sp = FindSp(0,A,Z);
                Sn = FindSp(1,A,Z);

                tof = Double.parseDouble(tof_dis.getText().toString());

                beta = length / (tof * c);
                Gamma = 1 / Math.pow(1 - Math.pow(beta, 2), 0.5);
                momt = mass * Gamma * beta;
                KE = (Gamma - 1) * mass / A;
                Brho = mass * Gamma * beta / c  / Z;

                mass_dis.setText("" + mass);
                Sp_dis.setText("" + Sp);
                Sn_dis.setText("" + Sn);
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
                Z = Integer.parseInt(Z_dis.getText().toString());
                A = Integer.parseInt(A_dis.getText().toString());
                length = Double.parseDouble(length_dis.getText().toString());
                mass = FindMassByBEA(A,Z);
                Sp = FindSp(0,A,Z);
                Sn = FindSp(1,A,Z);

                Brho = Double.parseDouble(Brho_dis.getText().toString());

                Gamma = Math.pow(Math.pow(Brho * Z  * c / mass, 2) + 1,0.5);
                KE = (Gamma - 1) * mass / A;
                beta = Math.pow((1 - 1 / Math.pow(Gamma, 2)), 0.5);
                momt = mass * Gamma * beta;
                tof = length / (beta * c);

                //	ShowResult(mass, KE, momt, Gamma, beta, tof, Brho);

                mass_dis.setText("" + mass);
                Sp_dis.setText("" + Sp);
                Sn_dis.setText("" + Sn);
                KE_dis.setText("" + KE);
                momt_dis.setText("" + momt);
                Gamma_dis.setText("" + Gamma);
                beta_dis.setText("" + beta);
                tof_dis.setText("" + tof);

            }
        });
    }

    private  double FindMassByName(String name){

        int A_tmp, Z_tmp, numLine = 1;

        double mp = 938.272046;
        double mn = 939.565378;

        AssetManager assetManager = getAssets();
        BufferedReader reader = null;

        int numLineStart = 40;
        int numLineEnd = 3392;
        int flag = 0;

        try {
            InputStream massData = assetManager.open("mass12.txt");
            reader = new BufferedReader(new InputStreamReader(massData));
            String text = null;
            //     Log.i("Read","flag = " + Integer.toString(flag)+", numLine = " + Integer.toString(numLine));
            // repeat until all lines is read
            while ((text = reader.readLine()) != null && flag == 0) {
                if(numLine >= numLineStart && numLine <=numLineEnd){
                    //	Log.i("Read","numLine ="+Integer.toString(numLine)) ;
                    //	Log.i("Read",text.toString()) ;
                    //	Log.i("Read","A_tmp string = " + text.substring(15, 19)) ;
                    //	Log.i("Read","Z_tmp string = " + text.substring(10, 14)) ;
                    String Name_tmp = text.substring(20,22);
                    // need to delete space
                    Name_tmp = Name_tmp.replace(" ", "");
                    A_tmp = Integer.parseInt(text.substring(15, 19).replaceAll("\\s",""));
                    Z_tmp = Integer.parseInt(text.substring(10, 14).replaceAll("\\s",""));

                    //Log.i("Read", name + " | Name = " + Name_tmp + ", A_tmp ="+Integer.toString(A_tmp)+", Z_tmp = "+Integer.toString(Z_tmp)) ;

                    if( Name_tmp.equals(name)){
                        //Log.i("Read","mDefect string = " + text.substring(54, 65)) ;
                        BEA = Double.parseDouble(text.substring(54, 65).replaceAll("#","").replaceAll("\\s",""))/1000.;
                        Log.i("Read","mDefect per A ="+Double.toString(BEA)) ;
                        A = A_tmp;
                        Z = Z_tmp;
                        mass = Z*mp + (A-Z)*mn - A*BEA;
                        Sym = A + Name_tmp;
                        //Log.i("Read","mass ="+Double.toString(mass)) ;
                        flag = 1;
                        break;
                    }else {
                        Log.i("Read", name + " != " + Name_tmp) ;
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
            BEA = -404;
            Sym = "non";
        }

        return mass;

    }

    private double FindMassByBEA(int a,int z){
        //	Log.i("Read","a ="+Integer.toString(a)+", z = "+Integer.toString(z)) ;
        int A_tmp, Z_tmp, numLine=1;

        double mp = 938.272046;
        double mn = 939.565378;

        int flag = 0;
        AssetManager assetManager = getAssets();
        BufferedReader reader = null;

        int numLineStart = 40;
        int numLineEnd = 3392;

        if ( a >= 50 && a <  100){
            numLineStart = 454;
        }else if (a >= 100 && a < 150){
            numLineStart = 1100;
        }else if (a >= 150 && a < 200){
            numLineStart = 1899;
        }else if (a >= 200){
            numLineStart = 2622;
        }
        Log.i("Read","numLineStart = "+Integer.toString(numLineStart)) ;

        try {
            InputStream massData = assetManager.open("mass12.txt");
            reader = new BufferedReader(new InputStreamReader(massData));
            String text = null;
            //     Log.i("Read","flag = " + Integer.toString(flag)+", numLine = " + Integer.toString(numLine));
            // repeat until all lines is read
            while ((text = reader.readLine()) != null && flag == 0) {
                if(numLine >= numLineStart && numLine <=numLineEnd){
                    //	Log.i("Read","numLine ="+Integer.toString(numLine)) ;
                    //	Log.i("Read",text.toString()) ;
                    //	Log.i("Read","A_tmp string = " + text.substring(15, 19)) ;
                    //	Log.i("Read","Z_tmp string = " + text.substring(10, 14)) ;
                    A_tmp = Integer.parseInt(text.substring(15, 19).replaceAll("\\s",""));
                    Z_tmp = Integer.parseInt(text.substring(10, 14).replaceAll("\\s",""));
                    //	Log.i("Read","A_tmp ="+Integer.toString(A_tmp)+", Z_tmp = "+Integer.toString(Z_tmp)) ;
                    if(A_tmp == a && Z_tmp == z){
                        //Log.i("Read","mDefect string = " + text.substring(54, 65)) ;
                        BEA = Double.parseDouble(text.substring(54, 65).replaceAll("#","").replaceAll("\\s",""))/1000.;
                        Log.i("Read","mDefect per A ="+Double.toString(BEA)) ;
                        mass = z*mp + (a-z)*mn - a*BEA;
                        Sym = A + text.substring(20,22);
                        //Log.i("Read","mass ="+Double.toString(mass)) ;
                        flag = 1;
                    }else if (A_tmp > a){
                        Log.i("Read","A_temp > a = "+Integer.toString(A_tmp)+". Stop search.") ;
                        break;
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
            BEA = -404;
            Sym = "non";
        }

        return mass;
    }


    private double FindSp(int id, int a,int z){

        if (a == 1 ){
            return 0;
        }

        double mass3 = 0;
        double massRes = 0;

        if ( id == 0){
            mass3 = 938.272046; // proton
            massRes = FindMassByBEA(a-1, z-1);
        }else if (id == 1){
            mass3 = 939.565378; // neutron
            massRes = FindMassByBEA(a-1, z);
        }

        double mass1 = FindMassByBEA(a, z);
        Log.i("Read","id = "+id+", massRes = "+Double.toString(massRes)) ;

        if (mass1 != -404 && massRes != -404){
            return massRes + mass3 - mass1;
        }else{
            return -404;
        }

    }
}
