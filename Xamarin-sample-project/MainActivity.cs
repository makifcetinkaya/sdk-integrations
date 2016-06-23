using System;

using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;

using IO.Presage;

namespace example
{
	[Activity(Label = "example", MainLauncher = true, Icon = "@drawable/icon")]
	public class MainActivity : Activity
	{
		protected override void OnCreate(Bundle bundle)
		{
			base.OnCreate(bundle);

			Presage.Instance.Context = this.BaseContext;
			Presage.Instance.Start();

			// Set our view from the "main" layout resource
			SetContentView(Resource.Layout.Main);

			// Get our button from the layout resource,
			// and attach an event to it
			Button adToServeButton = FindViewById<Button>(Resource.Id.adToServe);
			adToServeButton.Click += OnAdToServeButtonClick;

			Button showInterstitialButton = FindViewById<Button>(Resource.Id.showInterstitial);
			showInterstitialButton.Click += ShowInterstitialClick;

			Button launchWithEULAButton = FindViewById<Button>(Resource.Id.launchWithEULA);
			launchWithEULAButton.Click += LaunchWithEULAButtonClick;

		}



		void LaunchWithEULAButtonClick(object sender, EventArgs ea)
		{
			var eulaEvents = Presage.Instance.LaunchWithEULA();

			eulaEvents.EulaFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("EulaFound");
			};

			eulaEvents.EulaNotFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("EulaNotFound");
			};

			eulaEvents.EulaClosed += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("EulaClosed");
			};
		}

		void ShowInterstitialClick(object sender, EventArgs ea)
		{

			var loadEvents = Presage.Instance.LoadInterstitial();

			loadEvents.AdClosed += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad closed");
			};


			loadEvents.AdNotFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad not found");
			};

			loadEvents.AdError += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad error - code: " + e.Code);
			};

			loadEvents.AdDisplayed += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad displayed");
			};

			loadEvents.AdFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad found");
				ShowInterstitial();
			};


		}

		void ShowInterstitial()
		{
			var showEvents = Presage.Instance.ShowInterstitial();

			showEvents.AdClosed += (st, et) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad closed");
			};

			showEvents.AdFound += (st, et) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad found");
			};

			showEvents.AdNotFound += (st, et) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad not found");
			};

			showEvents.AdError += (st, et) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad error - code: " + et.Code);
			};

			showEvents.AdDisplayed += (st, et) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad displayed");
			};
		}



		void OnAdToServeButtonClick(object sender, EventArgs ea)
		{
			var interstitialEvents = Presage.Instance.AdToServe("interstitial");

			interstitialEvents.AdClosed += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad closed");
			};

			interstitialEvents.AdFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad found");
			};

			interstitialEvents.AdNotFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad not found");
			};

			interstitialEvents.AdError += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad error - code: " + e.Code);
			};

			interstitialEvents.AdDisplayed += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("Ad displayed");
			};
		}


		protected override void OnResume()
		{
			base.OnResume();
		}
	}
}


