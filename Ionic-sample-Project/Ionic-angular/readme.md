# Ionic Angular

This project has been developed with an AngularJS approach.
The important code for the integration is only in the conference folder.

- Conference
	- www
		- index.html where all the JS has been added (CPresage.js and the content of the js folder)
		- js 
			- app.js with all the routes
			- controller.js is the app controller, ogury.adToServe() has been added to call ads when the login is submitted or the login page is closed
			- services.js with the service Ogury where ads behaviour are handled

### How to use it
	- Clone the project
	- Go on the AndroidManifest.xml and replace the "ADD_API_KEY_HERE" by your own presage api_key
	- ionic build android
	- ionic run android
	- Don't forget to request an impression adding your device here : http://admin.ogury.co/integration_test/devices
	- When the app is running on your device, tap on the icon menu > Login. You will have the first ad call, the second ad call is when you click on the close button on the top right corner of the login page.
	- Enjoy :)