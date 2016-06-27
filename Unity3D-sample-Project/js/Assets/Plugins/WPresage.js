/**
 * This version of Presage's Wrapper was tested with 1.8.1 Presage lib
 */
public class WPresage
{
	private static final var WPRESAGE_ID = "io.presage.Presage";
	private static final var WHANDLER_ID = "io.presage.utils.IADHandler";
	private static final var WEULA_ID = "io.presage.utils.IEulaHandler";

	// Method used to Initialize Presage SDK
	static function Initialize() {
		var unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		var activity = unityPlayer.GetStatic.<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(function()
       	{
			var presageClass = new AndroidJavaClass(WPRESAGE_ID);
			var presage = presageClass.CallStatic.<AndroidJavaObject> ("getInstance");
			presage.Call("setContext", activity);
			presage.Call("start");
		}));
	}

	/**
	 * Method used to Call AdToServ to show interstitial
	*/
	static function AdToServe(name, handler) {
		var unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		var activity = unityPlayer.GetStatic.<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(function()
       	{
			var presageClass = new AndroidJavaClass(WPRESAGE_ID);
			var presage = presageClass.CallStatic.<AndroidJavaObject> ("getInstance");
			var proxy = new WHandlerProxy (handler);
			presage.Call("adToServe", name, proxy);
		}));
	}

	static function LoadInterstitial(handler) {
		var unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		var activity = unityPlayer.GetStatic.<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(function()
       	{
			var presageClass = new AndroidJavaClass(WPRESAGE_ID);
			var presage = presageClass.CallStatic.<AndroidJavaObject> ("getInstance");
			var proxy = new WHandlerProxy (handler);
			presage.Call("loadInterstitial", proxy);
		}));
	}

	static function ShowInterstitial(handler) {
		var unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		var activity = unityPlayer.GetStatic.<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(function()
       	{
			var presageClass = new AndroidJavaClass(WPRESAGE_ID);
			var presage = presageClass.CallStatic.<AndroidJavaObject> ("getInstance");
			var proxy = new WHandlerProxy (handler);
			presage.Call("showInterstitial", proxy);
		}));
	}

	static function LaunchWithEula(handler) {
		var unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		var activity = unityPlayer.GetStatic.<AndroidJavaObject>("currentActivity");
		
		activity.Call("runOnUiThread", new AndroidJavaRunnable(function()
       	{
			var presageClass = new AndroidJavaClass(WPRESAGE_ID);
			var presage = presageClass.CallStatic.<AndroidJavaObject> ("getInstance");
			var proxy = new WEulaProxy (handler);
			presage.Call("launchWithEula", proxy);
		}));
	}

	/**
	 * Proxy to interface with the WHandler of the jar
	*/
	public class WHandlerProxy extends AndroidJavaProxy {

		var myHandler: IADHandler;

		function WHandlerProxy(handler) {
			super(WHANDLER_ID);
			myHandler = handler;
		}

		function onAdNotFound() {
			// Ad was'nt found
			myHandler.OnAdNotFound();
		}

		function onAdFound() {
			// Ad was found
			myHandler.OnAdFound();
		}

		function onAdClosed() {
			// Ad was closed
			myHandler.OnAdClosed();
		}

		function onAdError(code) {
			// Ad sent an error
			myHandler.OnAdError(code);
		}

		function onAdDisplayed() {
			// Ad was displayed
			myHandler.OnAdDisplayed();
		}
	}

	public class WEulaProxy extends AndroidJavaProxy {

		var myHandler: IEulaHandler;

		function WEulaProxy(handler) {
			super(WEULA_ID);
			myHandler = handler;
		}

		function onEulaFound() {
			// Ad was'nt found
			myHandler.OnEulaFound();
		}

		function onEulaNotFound() {
			// Ad was found
			myHandler.OnEulaNotFound();
		}

		function onEulaClosed() {
			// Ad was closed
			myHandler.OnEulaClosed();
		}
	}

	/**
	 * Interface to be implemented by the app
	 */
	public interface IADHandler {
		function OnAdNotFound();
		function OnAdFound();
		function OnAdClosed();
		function OnAdError(code);
		function OnAdDisplayed();
	}

	public interface IEulaHandler {
		function OnEulaFound();
		function OnEulaNotFound();
		function OnEulaClosed();
	}
}