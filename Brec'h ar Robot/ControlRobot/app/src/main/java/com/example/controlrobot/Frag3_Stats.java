package com.example.controlrobot;

import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link Frag3_Stats#newInstance} factory method to
 * create an instance of this fragment.
 */
public class Frag3_Stats extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    public final String INCLINAISON = "Inclinaison";
    public final String PINCE = "Pince";
    public final String ROTATION = "Rotation";
    public final String BRAS = "Bras";
    public final String AVANTBRAS = "AvantBras";
    public final String TOURNE = "Tourne";


    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    public Frag3_Stats() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment Frag.
     */
    // TODO: Rename and change types and number of parameters
    public static Frag3_Stats newInstance(String param1, String param2) {
        Frag3_Stats fragment = new Frag3_Stats();
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

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        InteractionActivity activity = (InteractionActivity) getActivity();
        //FirebaseDatabase database = FirebaseDatabase.getInstance();
        //DatabaseReference drx = database.getReference();

        // Inflate the layout for this fragment
        View view =  inflater.inflate(R.layout.frag3, container, false);

        Button servomoteur = (Button)view.findViewById(R.id.btn_servomoteur);

        servomoteur.setOnClickListener(new View.OnClickListener()      //Creation du listener sur ce bouton
        {
            public void onClick(View actuelView)    //au clic sur le bouton
            {
                /*drx.child("commandes").child(String.valueOf(activity.getCompteur())).setValue("servomoteur");
                activity.setCompteur(activity.getCompteur()+1);
                drx.child("compteur").setValue(activity.getCompteur());*/
                activity.dr.child("Commandes").child("servomoteur").setValue(true);
                activity.dr.child("Commandes").child("servomoteur").setValue(false);
            }
        });

        // Inflate the layout for this fragment
        return view;
    }

    @Override
    public void onResume() {
        Log.e("DEBUG", "onResume of LoginFragment");
        super.onResume();

        InteractionActivity activity = (InteractionActivity) getActivity();
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        DatabaseReference drs = database.getReference("Servomoteurs");

        TextView textViewInclinaisonPince = (TextView) getView().findViewById(R.id.angle1);
        TextView textViewPince = (TextView) getView().findViewById(R.id.angle2);
        TextView textViewRotationPince = (TextView) getView().findViewById(R.id.angle3);
        TextView textViewAvantBras = (TextView) getView().findViewById(R.id.angle4);
        TextView textViewBras = (TextView) getView().findViewById(R.id.angle5);
        TextView textViewRotationBras = (TextView) getView().findViewById(R.id.angle6);
        TextView textViewTourneBras = (TextView) getView().findViewById(R.id.angle7);


        drs.addValueEventListener(new ValueEventListener() {

            @SuppressLint("SetTextI18n")
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {

                textViewInclinaisonPince.setText((dataSnapshot.child(PINCE).child(INCLINAISON)).getValue().toString() + "°");
                textViewPince.setText((dataSnapshot.child(PINCE).child(PINCE)).getValue().toString() + "°");
                textViewRotationPince.setText((dataSnapshot.child(PINCE).child(ROTATION)).getValue().toString() + "°");
                textViewAvantBras.setText((dataSnapshot.child(BRAS).child(AVANTBRAS)).getValue().toString() + "°");
                textViewBras.setText((dataSnapshot.child(BRAS).child(BRAS)).getValue().toString() + "°");
                textViewRotationBras.setText((dataSnapshot.child(BRAS).child(ROTATION)).getValue().toString() + "°");
                textViewTourneBras.setText((dataSnapshot.child(BRAS).child(TOURNE)).getValue().toString() + "°");

            }
            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }
}