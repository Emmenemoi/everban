/*!
 * jQuery swfStorage interface object
 */
(function (factory) {
	if (typeof define === 'function' && define.amd) {
		// AMD. Register as anonymous module.
		define(['jquery'], factory);
	} else {
		// Browser globals.
		factory(jQuery);
	}
}(function ($) {

	// GLOBAL // ATTENTION URL CONFIG
	var mySwfStore,
		debug = false;
		
	// PLUGIN : INIT, GET, SET, REMOVE
	$.swfStorage =
	{
		// INITIALISATION WITH CALLBACK FOR WAITING SWF LOADING
		init : function( callback )
		{
			// URL CONFIG (!!!)
			var swf_url= Drupal.settings.everban.base_url + 'storage.swf';
			// CREATION OBJET FLASH
			mySwfStore = new SwfStore(
			{
				swf_url: swf_url,
				namespace: 'EVB',
				debug: debug,
				timeout: 1, // number of seconds to wait before concluding there was an error
				onready: function(){ 
					callback(true); },
				onerror: function(){
					if(debug) alert('Swf ERROR Loading\nCheck URL options in jquery.swfstore.js !?\nurl = '+ swf_url );
					callback(false);}
			});
		},
		
		get : function( key )
		{
			try {
				return mySwfStore.get( key );
			}catch(e){throw e;}
		},
		
		set : function( key, value )
		{
			try{
				mySwfStore.set( key, value );
			}catch(e){throw e;}
		},
		
		remove : function( key )
		{
			try{
				mySwfStore.clear( key );
			}catch(e){throw e;}			
		}

		
	};

}));
