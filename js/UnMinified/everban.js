/*!
 * EVERBAN MAIN ALGORITHM v5
 
   Need jQuery Update module for Drupal6
   
 */
jQuery(document).ready(function ()
{	
	// DEBUG Global from everban.module
	$.everban.debug = Drupal.settings.everban.js_debug;

	// jQuery API Plugins List
	var plugins = 			// Three first need cookie API. Cf https://github.com/carhartl/jquery-cookie
		[	'cookieStorage',	// Cookie + Storage API. Cf https://github.com/julien-maurel/jQuery-Storage-API
			'localStorage',		// Storage API - html5
			'sessionStorage', 	// Storage API - html5
			'windowStorage',	// window.name Caching (from S.K.)
			'swfStorage',	 	// Local Share Object - Flash storage
			'pngStorage'		// PNG generation with forced cache and html5 canvas pixel reading (from S.K.)
		];

	// LOAD PLUGINS	- ALGORITHM ENCAPSULATED IN CALLBACK FUNCTION
	$.everban.load( plugins, function( value )
	{
		// WAIT LOADING CALLBACK - 'value' is always true
		if( value )
		{
			// CHECK, ELECT AND RESET LOCAL PEPPER
			$.everban.get( Drupal.settings.everban.id, function( value )
			{
				// NO LOCAL PEPPER FOUND
				if( value == undefined || value.length != 32 )
				{
					// SET PEPPER FROM DRUPAL.DB or SERVER RANDOM
					if ( Drupal.settings.everban.pepper )
					{
						$.everban.set( Drupal.settings.everban.id, Drupal.settings.everban.pepper );
					}			
				}
				// LOCAL PEPPER FOUND
				else if ( value.length == 32 )
				{
					// SET PEPPER EVERYWHERE IF LOCALY RECOVERED
					$.everban.set( Drupal.settings.everban.id, value );
				}
			});
		}
	});

		
});
