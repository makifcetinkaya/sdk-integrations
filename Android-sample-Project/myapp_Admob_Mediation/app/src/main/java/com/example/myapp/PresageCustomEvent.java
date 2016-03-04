package com.example.myapp;

/**
 * Created by Loic on 01/02/16.
 */
    import android.content.Context;
    import android.content.SharedPreferences;
    import android.os.Bundle;
    import android.os.Handler;
    import android.os.Message;
    import android.util.Log;

    import com.google.android.gms.ads.AdRequest;
    import com.google.android.gms.ads.mediation.customevent.CustomEventInterstitial;
    import com.google.android.gms.ads.mediation.customevent.CustomEventInterstitialListener;

    import java.util.Date;

    import io.presage.Presage;
    import io.presage.utils.IADHandler;

    /**
     * PresageCustomEvent is a CustomEventInterstitial for Google Admob Mediation for Presage
     */
    public class PresageCustomEvent implements CustomEventInterstitial {

        private static final String PRESAGE_INTERSTITIAL = "interstitial";

        private CustomEventInterstitialListener mCustomlistener;
        private Handler handler = new Handler(new Handler.Callback() {
            @Override
            public boolean handleMessage(Message msg) {
                mCustomlistener.onAdClosed();
                return true;
            }
        });

        // Callback of our Presage Interstitial as explained in the documentation
        private IADHandler mPresageHandler = new IADHandler() {
            @Override
            public void onAdFound() {
                mCustomlistener.onAdLoaded();
                mCustomlistener.onAdOpened();
                MainActivity.resetAdTime();
            }

            @Override
            public void onAdNotFound() {
                mCustomlistener.onAdFailedToLoad(AdRequest.ERROR_CODE_NO_FILL);
            }

            @Override
            public void onAdClosed() {
                // Necessary to do this way to avoid errors because not on the UIThread
                handler.sendEmptyMessage(0);
            }
        };

        @Override
        public void requestInterstitialAd(Context context, CustomEventInterstitialListener customEventInterstitialListener, String s, com.google.android.gms.ads.mediation.MediationAdRequest mediationAdRequest, Bundle bundle) {
            mCustomlistener = customEventInterstitialListener;
            SharedPreferences pref = context.getSharedPreferences("lastAd", 0);
            final long AdDisplayed= pref.getLong("lastAd", 0L);
            Date today = new Date();
            final long AdToDisplay = today.getTime();
            Log.i("PresageCount", "The count is " + (AdToDisplay - AdDisplayed));
            if (AdToDisplay - AdDisplayed > 6000) {
                Presage.getInstance().adToServe(PRESAGE_INTERSTITIAL, mPresageHandler);
            }
        }

        @Override
        public void showInterstitial() {
        }

        @Override
        public void onDestroy() {

        }

        @Override
        public void onPause() {

        }

        @Override
        public void onResume() {

        }
    }

