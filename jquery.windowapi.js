/*!
 * jQuery window.name Plugin v0 - inspired from S.a.m.y.K
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


	$.windowStorage = 
	{
		get : function( key )
		{
			try {
				return getFromStr( key, window.name );
			}catch(e){throw e;}
		},
		
		set : function( key, value )
		{
			try{
				window.name = param_replace( window.name, key, value );
			}catch(e){throw e;}
		},
		
		remove : function( key )
		{
			try{
				window.name = param_replace( window.name, key, "" );
			}catch(e){throw e;}			
		}
	};

	
	///////////////////////////// UTILITIES /////////////////////////////////
	
   // SET PARAM-LIKE STRING VALUE (eg, "x=y&key=VALUE") [from S.K.]
 	var param_replace = function (str, key, value) {
	  if (str.indexOf("&" + key + "=") > -1 || str.indexOf(key + "=") === 0) {
		// find start
		var idx = str.indexOf("&" + key + "="),
		  end, newstr;
		if (idx === -1) {
		  idx = str.indexOf(key + "=");
		}
		// find end
		end = str.indexOf("&", idx + 1);
		if (end !== -1) {
		  newstr = str.substr(0, idx) + str.substr(end + (idx ? 0 : 1)) + "&" + key + "=" + value;
		} else {
		  newstr = str.substr(0, idx) + "&" + key + "=" + value;
		}
		return newstr;
	  } else {
		return str + "&" + key + "=" + value;
	  }
	};

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