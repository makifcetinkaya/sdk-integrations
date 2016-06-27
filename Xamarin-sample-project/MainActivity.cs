using System;

using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using IO.Presage.Utils;
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
			EulaHandlerEvents events = new EulaHandlerEvents(Presage.Instance);

			events.EulaFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("EulaFound");
			};

			events.EulaNotFound += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("EulaNotFound");
			};

			events.EulaClosed += (s, e) =>
			{
				System.Diagnostics.Debug.WriteLine("EulaClosed");
			};
			Presage.Instance.LaunchWithEULA(events);

		}

		void ShowInterstitialClick(object sender, EventArgs ea)
		{
			ADHandlerEvents loadEvents = new ADHandlerEvents(Presage.Instance);

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
			Presage.Instance.LoadInterstitial(loadEvents);

		}

		void ShowInterstitial() 
		{
			ADHandlerEvents showEvents = new ADHandlerEvents(Presage.Instance);
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

			Presage.Instance.ShowInterstitial(showEvents);

		}



		void OnAdToServeButtonClick(object sender, EventArgs ea)
		{
			ADHandlerEvents interstitialEvents = new ADHandlerEvents(Presage.Instance);
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
			Presage.Instance.AdToServe("interstitial", interstitialEvents);
		}


		protected override void OnResume()
		{
			base.OnResume();
		}
	}
}


