/*!
 * jQuery EVERBAN Plugin v5
   
   Document is ready
   
 */
(function (factory) {
	if (typeof define === 'function' && define.amd) {
		// AMD. Register as anonymous module.
		define(['jquery'], factory);
	} else {
		// Browser globals.
		factory(jQuery);
	}
}(function ($)
{
	// GLOBAL
	var plugins=[];
		//debug = false;

	// PLUGIN : REGISTER, GET, SET, REMOVE
	$.everban =
	{
		// LOAD PLUGINS WITH CALLBACK SIGNAL FOR CRITICAL TIMING APPS
		load : function( pluginList, callback )
		{
			plugins = pluginList;

			// SYNCHRONIZED CALLBACK FOR RESUMING EVERBAN MAIN ALGORITHM
			var counter=0, callbacks=2;
			var done = function(){
				if( ++counter == callbacks ) { callback(true); }
			};
			
			// SWF INITIALISATION
			if ( $.inArray('swfStorage',plugins) != -1 ) // Use of JQuery for IE
			{
				if( $.swfStorage ){ 
					$.swfStorage.init( function( value )
					{
						if( !value ){ // REMOVE FROM PLUGINS IF ERROR
							plugins.splice( $.inArray('swfStorage',plugins), 1 );
						}
						done(); // DONE SIGNAL
					});
				}
			}
			
			// PNG INITIALISATION
			if ( $.inArray('pngStorage',plugins) != -1 ) // Use of JQuery for IE
			{
				if( $.pngStorage ){ 
					$.pngStorage.init( function( value )
					{
						done(); // DONE SIGNAL
					});
				}
			}			
			
			// COOKIE CONFIGURATION
			if( $.inArray('cookieStorage',plugins) != -1 )
			{
				if($.cookieStorage)	$.cookieStorage.setExpires(3650); // valid for 10*365 days
				if($.cookie) 		$.cookie.defaults = { path: '/' }; // available across entire domain
			}
			
		},

		// RETURN ELECTED PEPPER IF FOUND, ELSE NULL ( USING CALLBACK )
		get : function( key, callback )
		{
			var plugin, pepper, peppers=[];
	
			// GET VALUES - dynamic function call
			for( var i in plugins )
			{
				plugin = plugins[i];
				
				try{
					// Call plugins get() function
					pepper = String( $[plugin].get(key) );
					// Check for pepper consistancy : 32 alphanumeric characters
					if( pepper.length!=32 || /\W/.test(pepper) ) { pepper = undefined; }
					// Put in pepper list
					peppers.push( pepper );
					
				}catch(e){ if(this.debug) alert( 'GET problem with plugin : ' + plugin + '\n' + e ); }
			}
			if(this.debug) alert(	"EVERBAN JAVASCRIPT - DATA READING" + "\n\n" +
									"Plugins : " + JSON.stringify(plugins,"","") + "\n\n" +
									"Peppers found : \n" + JSON.stringify(peppers,""," "));

			// SEND ELECTED PEPPER THROUGH CALLBACK
			callback( election( peppers ) );
			
		},

		// SET PEPPER 'EVERYWHERE'
		set : function( key, pepper )
		{
			var plugin ;
			
			// SET VALUES  -  will overwrite
			for( var i in plugins )
			{
				plugin = plugins[i];
				try{
					$[plugin].set( key, pepper ); // !! assume all plugins have method set() !!
					
				}catch(e){ if(this.debug) alert( 'SET problem using plugin : ' + plugin + '\n' + e ); }
			}
		},

		// REMOVE ALL - !!!!!!!!!! TODO TOCHECK
		remove : function( key )
		{
			var plugin ;
			
			for( var i in plugins )
			{
				plugin = plugins[i];
				try{
					$[plugin].remove( key ); // !! assume all plugins have method remove() !!
					
				}catch(e){ if(this.debug) alert( 'REMOVE problem using plugin : ' + plugin + '\n' + e ); }
			}
		}
		
	};
	
	
	/////////////////////// PRIVATE UTILITIES /////////////////////////////
	
	// FIGURE OUT WHICH PEPPER IS THE BEST CANDIDATE - inspired from S.K.
	var election = function( peppers )
	{
		var pepper, candidates=[], candidate=null, bestnum=0;

		// Count occurence of different peppers
		for( var i in peppers ){
			pepper = peppers[i];
			if ( pepper && pepper!=="null" && pepper!=="undefined" && pepper.length==32) {
				candidates[pepper] =
					candidates[pepper] === undefined ? 1 : candidates[pepper] + 1;
			}
		}
		// Select most present pepper
		for ( pepper in candidates ){
			if ( candidates[pepper] > bestnum) {
				bestnum = candidates[pepper];
				candidate = pepper;
			}
		}
		return candidate;		
	};

	
	///////////// JQUERY PATCHES for unavailable functions ///////////////
	
	if( !$.isArray ) // Ok with jQuery Update module from v1.2.4 to v1.3.2
	{	
		$.isArray = function( x ){
			return ( x instanceof Array );
		};
	}
	
	if( !$.isPlainObject ) // Only from jQuery 1.4 // Needed for jquery.storageapi.js
	{
	// Real Code there : http://james.padolsey.com/jquery/#v=1.4.1&fn=jQuery.isPlainObject
	// Here done ugly, but necessary for IE8 compatibility.

		$.isPlainObject = function (obj)
		{
			return false;
		};
	}
	
}));