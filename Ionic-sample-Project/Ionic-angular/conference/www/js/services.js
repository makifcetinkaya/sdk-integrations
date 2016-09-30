angular.module('starter.services', ['ngResource'])

.service('ogury', function () {

        return {
            adToServe: function () {
                var ad = {
                    onAdEvent: function (event) {
                        console.log('onAdEvent called here');
                        if (event == 'AdFound') {
                            console.log('AD FOUND');
                            // If you want to do specific stuff when an ad is about to be displayed, even just a log
                        } else if (event == 'AdClosed') {
                            console.log('AD CLOSED');
                            // If you want to do specific stuff when an ad is clicked or dismissed, even just a log
                        }
                        else if (event == 'AdError') {
                            console.log('AD ERROR');
                        }
                        else if (event == 'AdDisplayed') {
                            console.log('AD DISPLAYED');
                        }
                    },
                    onAdNotFound: function (error) {
                        console.log('AD NOT FOUND');
                        // If you want to do specific stuff when no ad to display, even just a log
                    }
                };

                if (typeof CPresage !== "undefined") {
                    CPresage.adToServe(ad.onAdEvent, ad.onAdNotFound);
                }
            }
        };

    })

.factory('Session', function ($resource) {
    return $resource('http://localhost:5000/sessions/:sessionId');
});