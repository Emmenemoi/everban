/*!
 * jQuery pngStorage API
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

	// GLOBAL
	var document = window.document, Image = window.Image,
		canvas, img, ctx, origvalue, pngData, imgURL,
		init=true;
		debug=false;

	// PLUGIN : INIT, GET, SET, REMOVE
	$.pngStorage =
	{
		// INITIALISATION WITH CALLBACK FOR WAITING PNG LOADING
		init : function( callback )
		{
			imgURL = Drupal.settings.everban.base_path+'everpng.php?name=';
		 try{
			canvas = document.createElement("canvas")
			canvas.style.visibility = "hidden";
			canvas.style.position = "absolute";
			canvas.width = 11;
			canvas.height = 1;

		  if (canvas && canvas.getContext) 
		  {
			// everpng.php handles the hard part of generating the image
			// based off of the http cookie and returning it cached
			img = new Image();
			img.style.visibility = "hidden";
			img.style.position = "absolute";
			
			  pngData = undefined;
			  ctx = canvas.getContext("2d");

			  // erase EVP http cookie so the php will force a cached response
			  origvalue = getFromStr("EVP", document.cookie);
			  document.cookie = "EVP=; expires=Mon, 20 Sep 2010 00:00:00 UTC; path=/";

			  // onload event function
			  img.onload = function () 
			  {
				// put our cookie back
				if(init) document.cookie = "EVP=" + origvalue + "; expires=Tue, 31 Dec 2030 00:00:00 UTC; path=/";
				pngData = "";
				ctx.drawImage(img, 0, 0);

				// get CanvasPixelArray from  given coordinates and dimensions
				var imgd = ctx.getImageData(0, 0, 11, 1),
				  pix = imgd.data, i, n;

				// loop over each pixel to get the "RGB" values (ignore alpha)
				for( i=0, n=pix.length ; i < n ; i+=4 ) 
				{
				  if( pix[i] === 0 )   { break; }
				  pngData += String.fromCharCode( pix[i] );

				  if( pix[i+1] === 0 ) { break; }
				  pngData += String.fromCharCode( pix[i+1] );

				  if( pix[i+2] === 0 ) { break; }
				  pngData += String.fromCharCode( pix[i+2] );
				}			

				if(init) callback(true); // Say to main algo that initialisation is done
			  };
			  
			  // Errors handling
			  img.onerror = function(){
				if(debug) alert('--- img error ---');
				if(init) callback(false);
			  };
			  img.onabort = function(){
				if(debug) alert('--- img abort ---');
				if(init) callback(false);
			  };
			  
			// Load image
			img.src = imgURL + Drupal.settings.everban.id ;
		  }
		 }catch(e){ 
			if(debug) alert('-- Error PNG INIT --\n' + e ); 
			if(init) callback(false);
		 }
		},
		
		////////////////////// GET /////////////////////////////
		get : function( key )
		{
			try {
				return pngData ;
			}catch(e){throw e;}
		},

		////////////////////// SET /////////////////////////////		
		set : function( key, value )
		{
			try{
			  // Deactivate all callback methods for init
			  init=false;
			  // Make sure we have EVP session defined first
			  document.cookie = "EVP=" + value + "; path=/";
			  // Load image
			  img.src = imgURL + key ;
			}catch(e){throw e;}
		},

		////////////////////// REM /////////////////////////////		
		remove : function( key )
		{
			try{
				document.cookie = "EVP=; expires=Mon, 20 Sep 2010 00:00:00 UTC; path=/";
			}catch(e){throw e;}			
		}
		
	};
	

	///////////////////////////// UTILITIES /////////////////////////////////

    // GET VALUE FROM PARAM-LIKE STRING (eg, "x=y&name=VALUE") [from S.K.]
    var getFromStr = function (name, text) {
      if (typeof text !== "string") {
        return;
      }
      var nameEQ = name + "=",
        ca = text.split(/[;&]/),
        i, c;
      for (i = 0; i < ca.length; i++) {
        c = ca[i];
        while (c.charAt(0) === " ") {
          c = c.substring(1, c.length);
        }
        if (c.indexOf(nameEQ) === 0) {
          return c.substring(nameEQ.length, c.length);
        }
      }
    };


}));
