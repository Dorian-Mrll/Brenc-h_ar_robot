package com.example.controlrobot.ui.main;

import android.content.Context;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import com.example.controlrobot.Frag1_Command;
import com.example.controlrobot.Frag2_Camera;
import com.example.controlrobot.Frag3_Stats;
import com.example.controlrobot.Frag4_About;
import com.example.controlrobot.R;

/**
 * A [FragmentPagerAdapter] that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
public class SectionsPagerAdapter extends FragmentPagerAdapter {

    @StringRes
    private static final int[] TAB_TITLES = new int[]{R.string.onglet1, R.string.onglet2, R.string.onglet3, R.string.onglet4};
    private final Context mContext;

    public SectionsPagerAdapter(Context context, FragmentManager fm) {
        super(fm);
        mContext = context;
    }

    @Override
    public Fragment getItem(int position) {
        // getItem is called to instantiate the fragment for the given page.
        // Return a PlaceholderFragment (defined as a static inner class below).
        //return PlaceholderFragment.newInstance(position + 1);
        Fragment fragment = null;
        switch(position){
            case 0:
                fragment = new Frag1_Command();
                break;
            case 1:
                fragment = new Frag2_Camera();
                break;
            case 2:
                fragment = new Frag3_Stats();
                break;
            case 3:
                fragment = new Frag4_About();
                break;
        }
        return fragment;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        return mContext.getResources().getString(TAB_TITLES[position]);
    }

    @Override
    public int getCount() {
        // Show 2 total pages.
        return 4;
    }
}