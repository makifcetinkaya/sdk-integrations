package com.example.myapp;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.Toast;

import com.mopub.mobileads.MoPubInterstitial;
import com.mopub.mobileads.DefaultInterstitialAdListener;

import io.presage.Presage;
import java.util.Date;

public class MainActivity extends AppCompatActivity  {

    private MoPubInterstitial mCustomEventInterstitial;
    public static Context contextOfApplication;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        contextOfApplication = getApplicationContext();

        SharedPreferences pref = contextOfApplication.getSharedPreferences("lastAd", 0); // 0 - for private mode
        final long AdDisplayed= pref.getLong("lastAd", 0L);
        Date today = new Date();
        final long AdToDisplay = today.getTime();

        Log.i("PresageCount", "The count is " + (AdToDisplay - AdDisplayed));

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            WebView.setWebContentsDebuggingEnabled(true);
        }

        mCustomEventInterstitial = new MoPubInterstitial(this, "Your Mopub Key");

        mCustomEventInterstitial.setInterstitialAdListener(new DefaultInterstitialAdListener());

        // Presage Initialization
        Presage.getInstance().setContext(this.getBaseContext());
        Presage.getInstance().start();

        setContentView(R.layout.activity_main);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Contact techsupport@ogury.co if you have any questions :)", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        Button ad = (Button) findViewById(R.id.ad);
        ad.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                requestNewInterstitial();
                if (mCustomEventInterstitial.isReady()) {
                    mCustomEventInterstitial.show();
                }
            }
        });
    }

    private void requestNewInterstitial() {
        mCustomEventInterstitial.load();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;

        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onPause(){
        super.onPause();
    }
    @Override
    public void onResume(){
        super.onResume();
    }
    public static Context getContextOfApplication(){
        return contextOfApplication;
    }
    public static void resetAdTime(){
        Context applicationContext = MainActivity.getContextOfApplication();
        SharedPreferences pref = applicationContext.getSharedPreferences("lastAd", 0);
        SharedPreferences.Editor editor = pref.edit();
        Date currentDate=new Date();
        editor.putLong("lastAd", currentDate.getTime());
        editor.commit();
    }
}
