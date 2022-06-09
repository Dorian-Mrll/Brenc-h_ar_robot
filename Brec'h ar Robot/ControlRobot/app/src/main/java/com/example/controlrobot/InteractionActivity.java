package com.example.controlrobot;

import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.tabs.TabLayout;

import androidx.viewpager.widget.ViewPager;
import androidx.appcompat.app.AppCompatActivity;

import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

import com.example.controlrobot.ui.main.SectionsPagerAdapter;
import com.example.controlrobot.databinding.FragmentInteractionBinding;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class InteractionActivity extends AppCompatActivity {

    private FragmentInteractionBinding binding;
    private int compteur;
    public FirebaseDatabase database = FirebaseDatabase.getInstance();
    public DatabaseReference dr = database.getReference();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = FragmentInteractionBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        SectionsPagerAdapter sectionsPagerAdapter = new SectionsPagerAdapter(this, getSupportFragmentManager());
        ViewPager viewPager = binding.viewPager;
        viewPager.setAdapter(sectionsPagerAdapter);
        TabLayout tabs = binding.tabs;
        tabs.setupWithViewPager(viewPager);
        FloatingActionButton fab = binding.fab;

        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });


        Button reinitialiser = (Button) findViewById(R.id.btn_reinitialiser);   //Appel du "button1"
        ImageButton quitter = (ImageButton) findViewById(R.id.btn_quitter);   //Appel du "button1"



        reinitialiser.setOnClickListener(new View.OnClickListener()      //Creation du listener sur ce bouton
        {
            public void onClick(View actuelView)    //au clic sur le bouton
            {
                /*dr.child("commandes").removeValue();
                setCompteur(0);
                dr.child("commandes").child(String.valueOf(getCompteur())).setValue("reinitialiser");
                dr.child("compteur").setValue(getCompteur());*/
                dr.child("Commandes").child("reinitialiser").setValue(true);
                dr.child("Commandes").child("reinitialiser").setValue(false);
            }
        });
        quitter.setOnClickListener(new View.OnClickListener()      //Creation du listener sur ce bouton
        {
            public void onClick(View actuelView)    //au clic sur le bouton
            {
                dr.child("Application").child("connection").setValue(false);
                //Intent myIntent = new Intent(InteractionActivity2.this, HomeActivity.class);
                //startActivity(myIntent);    //Afficher la vue
                InteractionActivity.this.finish();
            }
        });
    }

    public int getCompteur(){
        return compteur;
    }

    public void setCompteur(int cpt){
        compteur = cpt;
    }
}