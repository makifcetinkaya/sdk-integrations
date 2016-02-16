package com.example.myapp;

import android.os.Build;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.Toast;

import io.presage.Presage;

import com.example.myapp.PresageCustomEvent;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;
import com.jirbo.adcolony.AdColony;
import com.jirbo.adcolony.AdColonyBundleBuilder;
import com.vungle.publisher.VunglePub;

public class MainActivity extends AppCompatActivity {

    private InterstitialAd mCustomEventInterstitial;
    // Ad Colony set up
    private static final String ZONE_ID = "your_ad_colony_zone";
    private static final String APP_ID = "your_ad_colony_app_id";

    // Vungle Instance
    final VunglePub vunglePub = VunglePub.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            WebView.setWebContentsDebuggingEnabled(true);
        }

        mCustomEventInterstitial = new InterstitialAd(this);
        mCustomEventInterstitial.setAdUnitId("your_admob_ad_unit");

        // Ad Colony
        AdColonyBundleBuilder.setZoneId(ZONE_ID);

        mCustomEventInterstitial.setAdListener(new AdListener() {
            @Override
            public void onAdFailedToLoad(int errorCode) {
                Toast.makeText(MainActivity.this,
                        "Error loading custom event interstitial, code " + errorCode,
                        Toast.LENGTH_SHORT).show();
            }
            @Override
            public void onAdClosed(){
                requestNewInterstitial();
            }
        });

        // Presage Initialization
        Presage.getInstance().setContext(this.getBaseContext());
        Presage.getInstance().start();

        // Ad Colony configuration
        AdColony.configure(this, "test", APP_ID,ZONE_ID);

        // Vungle configuration and initialization
        final String app_id = "your_vungle_app_id";
        vunglePub.init(this, app_id);

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
                if (mCustomEventInterstitial.isLoaded()) {
                    mCustomEventInterstitial.show();
                }
            }
        });
    }

    private void requestNewInterstitial() {
        AdRequest adRequest = new AdRequest.Builder().build();

        mCustomEventInterstitial.loadAd(adRequest);
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
        AdColony.pause();
        vunglePub.onPause();
    }
    @Override
    public void onResume(){
        super.onResume();
        AdColony.resume(this);
        vunglePub.onResume();
    }
}
