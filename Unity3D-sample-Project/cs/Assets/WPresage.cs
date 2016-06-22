using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.Collections.Generic;

/**
 * This version of Presage's Wrapper was tested with 1.8.1 Presage lib
 */
public class WPresage : MonoBehaviour {

	private const string WPRESAGE_ID = "io.presage.Presage";
	private const string WHANDLER_ID = "io.presage.utils.IADHandler";
	private const string WEULA_ID = "io.presage.utils.IEulaHandler";

	// Method used to Initialize Presage SDK
	public static void Initialize() {
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(() =>
       	{
			AndroidJavaClass presageClass = new AndroidJavaClass(WPRESAGE_ID);
			AndroidJavaObject presage = presageClass.CallStatic<AndroidJavaObject> ("getInstance");
			presage.Call("setContext", activity);
			presage.Call("start");
		}));
	}
	
	/**
	 * Method used to Call AdToServ to show interstitial
	 */
	public static void AdToServe(string name, IADHandler handler) {
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(() =>
       	{
			AndroidJavaClass presageClass = new AndroidJavaClass(WPRESAGE_ID);
			AndroidJavaObject presage = presageClass.CallStatic<AndroidJavaObject> ("getInstance");
			IADHandlerProxy proxy = new IADHandlerProxy (handler);
			presage.Call("adToServe", name, proxy);
		}));
	}

	public static void LoadInterstitial(IADHandler handler) {
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(() =>
       	{
			AndroidJavaClass presageClass = new AndroidJavaClass(WPRESAGE_ID);
			AndroidJavaObject presage = presageClass.CallStatic<AndroidJavaObject> ("getInstance");
			IADHandlerProxy proxy = new IADHandlerProxy (handler);
			presage.Call("loadInterstitial", proxy);
		}));
	}

	public static void ShowInterstitial(IADHandler handler) {
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(() =>
       	{
			AndroidJavaClass presageClass = new AndroidJavaClass(WPRESAGE_ID);
			AndroidJavaObject presage = presageClass.CallStatic<AndroidJavaObject> ("getInstance");
			IADHandlerProxy proxy = new IADHandlerProxy (handler);
			presage.Call("showInterstitial", proxy);
		}));
	}
	
	public static void LaunchWithEula(IEulaHandler handler) {
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(() =>
       	{
			AndroidJavaClass presageClass = new AndroidJavaClass(WPRESAGE_ID);
			AndroidJavaObject presage = presageClass.CallStatic<AndroidJavaObject> ("getInstance");
			IEulaHandlerProxy proxy = new IEulaHandlerProxy (handler);
			presage.Call("launchWithEula", proxy);
		}));
	}
	/**
	 * Proxy to interface with the IADHandler of the jar
	 */
	public class IADHandlerProxy : AndroidJavaProxy {
		
		delegate void AdNotFound();
		delegate void AdFound();
		delegate void AdClosed();

		delegate void AdError(int code);
		delegate void AdDisplayed();
		
		AdNotFound adNotFound;
		AdFound adFound;
		AdClosed adClosed;

		AdError adError;
		AdDisplayed adDisplayed;
		
		public IADHandlerProxy(IADHandler handler) : base(WHANDLER_ID) {
			adNotFound = handler.OnAdNotFound;
			adFound = handler.OnAdFound;
			adClosed = handler.OnAdClosed;
			adError = handler.OnAdError;
			adDisplayed = handler.OnAdDisplayed;
		}
		
		void onAdNotFound() {
			// Ad was'nt found
			adNotFound();
		}
		
		void onAdFound() {
			// Ad was found
			adFound();
		}

		void onAdClosed() {
			// Ad was closed
			adClosed();
		}

		void onAdError(int code) {
			// Ad sent an error
			adError(code);
		}

		void onAdDisplayed() {
			// Ad was displayed
			adDisplayed();
		}
	}

	public class IEulaHandlerProxy : AndroidJavaProxy {

		delegate void EulaFound();
    	delegate void EulaNotFound();
    	delegate void EulaClosed();

    	EulaFound eulaFound;
		EulaNotFound eulaNotFound;
		EulaClosed eulaClosed;

    	public IEulaHandlerProxy(IEulaHandler handler) : base(WEULA_ID) {
			eulaFound = handler.OnEulaFound;
			eulaNotFound = handler.OnEulaNotFound;
			eulaClosed = handler.OnEulaClosed;
		}
	}

	/**
	 * Interface to be implemented by the app
	 */
	public interface IADHandler {
		void OnAdNotFound();
		void OnAdFound();
		void OnAdClosed();
		void OnAdError(int code);
		void OnAdDisplayed();
	}

	public interface IEulaHandler {
		void OnEulaFound();
		void OnEulaNotFound();
		void OnEulaClosed();
	}
}
