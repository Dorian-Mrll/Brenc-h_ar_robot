package com.example.controlrobot;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class HomeActivity extends AppCompatActivity {

    public FirebaseDatabase database = FirebaseDatabase.getInstance("https://esp32-31ba2-default-rtdb.europe-west1.firebasedatabase.app/");
    public DatabaseReference dr = database.getReference();
    final Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout_home);

        // Write a message to the database
        dr.child("Application").child("connection").setValue(false);
        dr.child("Application").child("start").setValue(false);
        dr.child("ESP32").child("WiFi").setValue(false);

        dr.child("Commandes").child("Bras").child("baisser_avant-bras").setValue(false);
        dr.child("Commandes").child("Bras").child("baisser_bras").setValue(false);
        dr.child("Commandes").child("Bras").child("lever_avant-bras").setValue(false);
        dr.child("Commandes").child("Bras").child("lever_bras").setValue(false);
        dr.child("Commandes").child("Bras").child("rotation_droite").setValue(false);
        dr.child("Commandes").child("Bras").child("rotation_gauche").setValue(false);
        dr.child("Commandes").child("Bras").child("tourne_droite").setValue(false);
        dr.child("Commandes").child("Bras").child("tourne_gauche").setValue(false);
        dr.child("Commandes").child("Pince").child("ferme").setValue(false);
        dr.child("Commandes").child("Pince").child("inclinaison_arriere").setValue(false);
        dr.child("Commandes").child("Pince").child("inclinaison_avant").setValue(false);
        dr.child("Commandes").child("Pince").child("ouvre").setValue(false);
        dr.child("Commandes").child("Pince").child("rotation_droite").setValue(false);
        dr.child("Commandes").child("Pince").child("rotation_gauche").setValue(false);
        dr.child("Commandes").child("reinitialiser").setValue(false);
        dr.child("Commandes").child("servomoteur").setValue(false);


        Button ButtonConnexion = findViewById(R.id.start);   //Appel du "button1"
        Button ButtonQuitter = findViewById(R.id.end);
        ButtonConnexion.setOnClickListener(new View.OnClickListener()      //Creation du listener sur ce bouton
        {
            public void onClick(View actuelView)    //au clic sur le bouton
            {
                dr.child("Application").child("connection").setValue(true);
                Intent myIntent = new Intent(HomeActivity.this, InteractionActivity.class);
                startActivity(myIntent);    //Afficher la vue
            }
        });

        ButtonQuitter.setOnClickListener(new View.OnClickListener()      //Creation du listener sur ce bouton
        {
            public void onClick(View actuelView)    //au clic sur le bouton
            {
                finish();
            }
        });

         dr.addValueEventListener(new ValueEventListener() {

                    @SuppressLint("SetTextI18n")
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                        boolean esp32 = (boolean) (dataSnapshot.child("ESP32").child("WiFi")).getValue();
                        if(esp32) dr.child("ESP32").child("WiFi").setValue(false);

                            }
                        }, 20000);

                    }
                    @Override
                    public void onCancelled(DatabaseError databaseError) {

                    }
                });




    }

    public void change(View v) {
        Switch switch1 = (Switch) findViewById(R.id.theme);

        if (AppCompatDelegate.getDefaultNightMode() == AppCompatDelegate.MODE_NIGHT_YES) {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
        } else {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
        }
        recreate();
    }


}