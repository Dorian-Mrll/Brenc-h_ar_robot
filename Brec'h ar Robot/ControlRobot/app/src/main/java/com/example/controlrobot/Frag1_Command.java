package com.example.controlrobot;

import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link Frag1_Command#newInstance} factory method to
 * create an instance of this fragment.
 */
public class Frag1_Command extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";
    private final int MAX = 25;


    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;
    int child = 0;

    public Frag1_Command() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment Frag1_Command.
     */
    // TODO: Rename and change types and number of parameters
    public static Frag1_Command newInstance(String param1, String param2) {
        Frag1_Command fragment = new Frag1_Command();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }


    /*public void compteur(InteractionActivity2 activity, DatabaseReference drx){

        //activity.setCompteur(listener_compteur);
    }*/


    public void up_down(InteractionActivity activity, DatabaseReference drx, String command, int up_or_down){
        if (activity.getCompteur() < MAX) {
            //compteur(activity, drx);
            if(up_or_down == 0){
                drx.child("commandes").child(String.valueOf(activity.getCompteur())).setValue(command);
                activity.setCompteur(activity.getCompteur()+1);
                drx.child("compteur").setValue(activity.getCompteur());
            }else{
                drx.child("commandes").child(String.valueOf(activity.getCompteur())).setValue("stop_" + command);
                activity.setCompteur(activity.getCompteur()+1);
                drx.child("compteur").setValue(activity.getCompteur());
            }

        }
    }

    @SuppressLint("ClickableViewAccessibility")
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        InteractionActivity activity = (InteractionActivity) getActivity();
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        DatabaseReference drx = database.getReference();
        DatabaseReference drx2 = database.getReference("Commandes");
        // Inflate the layout for this fragment
        View view =  inflater.inflate(R.layout.frag1, container, false);

        ImageButton PinceOpen = view.findViewById(R.id.pince_open);
        ImageButton PinceClose = view.findViewById(R.id.pince_close);
        ImageButton PinceInclinBas = view.findViewById(R.id.pince_IB);
        ImageButton PinceInclinHaut = view.findViewById(R.id.pince_IH);
        ImageButton PinceRotationDroite = view.findViewById(R.id.pince_RD);
        ImageButton PinceRotationGauche = view.findViewById(R.id.pince_RG);

        ImageButton TourneGauche = view.findViewById(R.id.bras_TG);
        ImageButton TourneDroite = view.findViewById(R.id.bras_TD);
        ImageButton LeverAvantBras = view.findViewById(R.id.bras_LAb);
        ImageButton DescendreAvantBras = view.findViewById(R.id.bras_DAb);
        ImageButton RotationGauche = view.findViewById(R.id.bras_RG);
        ImageButton RotationDroite = view.findViewById(R.id.bras_RD);
        ImageButton LeverBras = view.findViewById(R.id.bras_LB);
        ImageButton DescendreBras = view.findViewById(R.id.bras_DB);


        drx.child("commandes").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                child = (int) dataSnapshot.getChildrenCount();
                Log.e("TAG", String.valueOf(child));
                activity.setCompteur(child);

            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });


        PinceOpen.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "open", 0);
                    drx2.child("Pince").child("ouvre").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "pince", 1);
                    drx2.child("Pince").child("ouvre").setValue(false);
                }
                return true;
            }
        });


        PinceClose.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "close", 0);
                    drx2.child("Pince").child("ferme").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "pince", 1);
                    drx2.child("Pince").child("ferme").setValue(false);
                }
                return true;
            }
        });


        PinceInclinBas.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "inclinaisonPinceArriere", 0);
                    drx2.child("Pince").child("inclinaison_arriere").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "inclinaisonPince", 1);
                    drx2.child("Pince").child("inclinaison_arriere").setValue(false);
                }
                return true;
            }
        });


        PinceInclinHaut.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "inclinaisonPinceAvant", 0);
                    drx2.child("Pince").child("inclinaison_avant").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "inclinaisonPince", 1);
                    drx2.child("Pince").child("inclinaison_avant").setValue(false);
                }
                return true;
            }
        });


        PinceRotationDroite.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "rotationPinceDroite", 0);
                    drx2.child("Pince").child("rotation_droite").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "rotationPince", 1);
                    drx2.child("Pince").child("rotation_droite").setValue(false);
                }
                return true;
            }
        });


        PinceRotationGauche.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "rotationPinceGauche", 0);
                    drx2.child("Pince").child("rotation_gauche").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "rotationPince", 1);
                    drx2.child("Pince").child("rotation_gauche").setValue(false);
                }
                return true;
            }
        });


        TourneGauche.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "tourneBrasGauche", 0);
                    drx2.child("Bras").child("tourne_gauche").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "tourneBras", 1);
                    drx2.child("Bras").child("tourne_gauche").setValue(false);
                }
                return true;
            }
        });


        TourneDroite.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "tourneBrasDroite", 0);
                    drx2.child("Bras").child("tourne_droite").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "tourneBras", 1);
                    drx2.child("Bras").child("tourne_droite").setValue(false);
                }
                return true;
            }
        });


        LeverAvantBras.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "leverAvantBras", 0);
                    drx2.child("Bras").child("lever_avant-bras").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "avantBras", 1);
                    drx2.child("Bras").child("lever_avant-bras").setValue(false);
                }
                return true;
            }
        });


        DescendreAvantBras.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "descendreAvantBras", 0);
                    drx2.child("Bras").child("baisser_avant-bras").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "avantBras", 1);
                    drx2.child("Bras").child("baisser_avant-bras").setValue(false);
                }
                return true;
            }
        });


        RotationGauche.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "rotationBrasGauche", 0);
                    drx2.child("Bras").child("rotation_gauche").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "rotationBras", 1);
                    drx2.child("Bras").child("rotation_gauche").setValue(false);
                }
                return true;
            }
        });


        RotationDroite.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "rotationBrasDroite", 0);
                    drx2.child("Bras").child("rotation_droite").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "rotationBras", 1);
                    drx2.child("Bras").child("rotation_droite").setValue(false);
                }
                return true;
            }
        });


        LeverBras.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "leverBras", 0);
                    drx2.child("Bras").child("lever_bras").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "bras", 1);
                    drx2.child("Bras").child("lever_bras").setValue(false);
                }
                return true;
            }
        });


        DescendreBras.setOnTouchListener(new View.OnTouchListener()      //Creation du listener sur ce bouton
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    //up_down(activity, drx, "descendreBras", 0);
                    drx2.child("Bras").child("baisser_bras").setValue(true);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    //up_down(activity, drx, "bras", 1);
                    drx2.child("Bras").child("baisser_bras").setValue(false);
                }
                return true;
            }
        });

        return view;
    }
}