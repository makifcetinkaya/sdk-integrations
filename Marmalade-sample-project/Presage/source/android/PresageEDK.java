/*
java implementation of the PresageEDK extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import io.presage.Presage;
import io.presage.utils.IADHandler;
import io.presage.utils.IEulaHandler;

import com.ideaworks3d.marmalade.LoaderActivity;
import com.ideaworks3d.marmalade.LoaderAPI;

import android.util.Log;
// Comment in the following line if you want to use ResourceUtility
// import com.ideaworks3d.marmalade.ResourceUtility;

class PresageEDK
{

	public static native void onAdNotFoundNative();  
	public static native void onAdFoundNative();  
	public static native void onAdClosedNative(); 
	public static native void onAdErrorNative(); 
	public static native void onAdDisplayedNative(); 

	public static native void onEulaFoundNative();
	public static native void onEulaNotFoundNative();
	public static native void onEulaClosedNative();

	private static final String PRESAGE_LOG_TAG = "Presage";

    public void PresageStart()
    {
		Log.v(PRESAGE_LOG_TAG, "Initialising Presage");

	        	Presage.getInstance().setContext(LoaderAPI.getActivity().getBaseContext());
				Presage.getInstance().start();
    }
    public void PresageAdToServe()
    {
    	Log.v(PRESAGE_LOG_TAG, "Showing an Ad");

		Presage.getInstance().adToServe("interstitial", new IADHandler() {
			@Override
			public void onAdNotFound() {
				onAdNotFoundNative();
				Log.v(PRESAGE_LOG_TAG, "Ad not found");
			}

			@Override
			public void onAdFound() {
				onAdFoundNative();
				Log.v(PRESAGE_LOG_TAG, "Ad found");
			}
	
			@Override
			public void onAdClosed() {
				onAdClosedNative();
				Log.v(PRESAGE_LOG_TAG, "Ad closed");
			}

			@Override
			public void onAdError(int code) {
				onAdErrorNative();
				Log.v(PRESAGE_LOG_TAG, "Ad error : " + code);
			}

			@Override
			public void onAdDisplayed() {
				onAdDisplayedNative();
				Log.v(PRESAGE_LOG_TAG, "Ad displayed");
			}
		  });
    }
    public void PresageLoadAd() {
    	Log.v(PRESAGE_LOG_TAG, "Loading an Ad");

		Presage.getInstance().loadInterstitial(new IADHandler() {
			@Override
			public void onAdNotFound() {
				onAdNotFoundNative();
				Log.v(PRESAGE_LOG_TAG, "Ad not found");
			}

			@Override
			public void onAdFound() {
				onAdFoundNative();
				Log.v(PRESAGE_LOG_TAG, "Ad found");
			}
	
			@Override
			public void onAdClosed() {
				onAdClosedNative();
				Log.v(PRESAGE_LOG_TAG, "Ad closed");
			}

			@Override
			public void onAdError(int code) {
				onAdErrorNative();
				Log.v(PRESAGE_LOG_TAG, "Ad error : " + code);
			}

			@Override
			public void onAdDisplayed() {
				onAdDisplayedNative();
				Log.v(PRESAGE_LOG_TAG, "Ad displayed");
			}
		  });
    }
    public void PresageShowAd() {
    	Log.v(PRESAGE_LOG_TAG, "Showing a previously loaded Ad");

		Presage.getInstance().showInterstitial(new IADHandler() {
			@Override
			public void onAdNotFound() {
				onAdNotFoundNative();
				Log.v(PRESAGE_LOG_TAG, "Ad not found");
			}

			@Override
			public void onAdFound() {
				onAdFoundNative();
				Log.v(PRESAGE_LOG_TAG, "Ad found");
			}
	
			@Override
			public void onAdClosed() {
				onAdClosedNative();
				Log.v(PRESAGE_LOG_TAG, "Ad closed");
			}

			@Override
			public void onAdError(int code) {
				onAdErrorNative();
				Log.v(PRESAGE_LOG_TAG, "Ad error : " + code);
			}

			@Override
			public void onAdDisplayed() {
				onAdDisplayedNative();
				Log.v(PRESAGE_LOG_TAG, "Ad displayed");
			}
		  });
    }
    public void PresageLaunchEula() 
    {
    	Log.v(PRESAGE_LOG_TAG, "Showing an Eula");
    	Presage.getInstance().launchWithEula(new IEulaHandler() {
    		@Override
            public void onEulaFound() {
            	onEulaFoundNative();
            	Log.v(PRESAGE_LOG_TAG, "Eula found");
            }

            @Override
            public void onEulaNotFound() {
            	onEulaNotFoundNative();
            	Log.v(PRESAGE_LOG_TAG, "Eula not found");
            }

            @Override
            public void onEulaClosed() {
            	onEulaClosedNative();
            	Log.v(PRESAGE_LOG_TAG, "Eula closed");
            }
    	});
    }
}
