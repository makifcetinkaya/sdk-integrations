package com.example.myapp;

/**
 * Created by Loic on 01/02/16.
 */
    import io.presage.Presage;
    import io.presage.utils.IADHandler;

    import java.util.Map;

    import android.content.Context;

    import com.mopub.mobileads.CustomEventInterstitial;
    import com.mopub.mobileads.MoPubErrorCode;

    /**
     * PresageCustomEvent is a CustomEventInterstitial for Google Admob Mediation for Presage
     */
    public class PresageCustomEventMopub extends CustomEventInterstitial {

        private CustomEventInterstitialListener mListener;

        public PresageCustomEventMopub() {
            super();
        }

        @Override
        protected void loadInterstitial(Context context,
                                        CustomEventInterstitialListener listener, Map<String, Object> arg2,
                                        Map<String, String> arg3) {

            mListener = listener;

            Presage.getInstance().adToServe("interstitial", new IADHandler() {

                @Override
                public void onAdNotFound() {
                    mListener.onInterstitialFailed(MoPubErrorCode.NETWORK_NO_FILL);
                }

                @Override
                public void onAdFound() {
                    mListener.onInterstitialLoaded();
                }

                @Override
                public void onAdClosed() {
                    mListener.onInterstitialDismissed();
                }
                @Override
                public void onAdError(int code) {
                    mListener.onInterstitialFailed(MoPubErrorCode.NETWORK_NO_FILL);
                }

                @Override
                public void onAdDisplayed() {
                    mListener.onInterstitialShown();
                }
            });
        }

        @Override
        protected void showInterstitial() {
            mListener.onInterstitialShown();
        }

        @Override
        protected void onInvalidate() {
            mListener = null;
        }

    }

