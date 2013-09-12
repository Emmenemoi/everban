
/*!
 * jQuery EVERBAN Module history

 Placing and retrieve 'armored_192_168_2_1' cookies
 Length : 32. ex : '12345678901234567890123456789012'


 */
 


v1 : coming out

v2 : thinking	
		setting a callback value for general 'get' method
		reflexion on dynamic function naming - cf jquery.everban.2.js l.36

v3 : debuging

		GENERAL FEELING : 
		problems to come because of jQuery 'obsolete' version in Drupal6
		
		HELP
		How to manage variables / this.xxx ... ex : 'i' etc ...	

		everban.module
		change paths : drupal_add_js(...)
		
		jquery.everban.3.js & everban.3.js
		adapt 'for(x in y)' iterations

		jquery.storageapi.3.js l.341 & 344
		change for having 'get'/'set' methods
		set:function(n,v){ // // MODIF : setItem
		get:function(n){ // MODIF : getItem
		change many other calls

		jquery.storageapi.3.js l.225 etc ...
		TypeError: $.isArray is not a function
		if(!$.isArray(a0)){
		-> PB : jQuery 1.2.6 in Drupal ; v1.3 needed.
		write javascript function patch using (x instanceof Array) in jquery.everban.3.js

		jquery.storageapi.3.js l.44
		TypeError: s.get is not a function
		return s.get(a1);
		
		jquery.storageapi.3.js l.43
		Caught exception e :
		SyntaxError: JSON.parse: unexpected character
		return JSON.parse(s.get(a1));
		!! seems OK
		
		jquery.storageapi.3.js l.43
		Caught exception e : ...
		SyntaxError: JSON.parse: unexpected character (?)
		return JSON.parse(s.get(a1)); (?)
		TypeError: s.get is not a function
		return s.get(a1);
		!! 2nd iteration : for 'localStorage' function 'get' unknown ....

		jquery.everban.3.js
		insert try/catch in general 'get' method to prevent crash
		
		jquery.everban.3.js
		plugin's 'get' methods do not always return a string !!!
		cast : String(X) ( exists also X + "" and X.toString() )		
	
XX : reverse ( and forward )

		everban.module
		keep & call original plugins : jquery.cookie.js & jquery.storageapi.js

		jquery.everban.3.js
		function election
		rewrite due to table access ( for ( var i in peppers ) {...} )
		
		jquery.everban.3.js / everban.3.js
		callback problem : function never called

		everban.3.js
		rewrite function set for dynamic function naming
	
		??? why isn't there any 'this' in my code ??? ;-)
		
		Added jQuery Update module
		https://drupal.org/project/jquery_update
		"Upgrades the version of jQuery in Drupal core to a newer version of jQuery"
		
		everban.3.js
		Added patch for function $.isPlainObject - not in jQuery 1.3
		https://github.com/bestiejs/lodash/blob/v1.3.1/dist/lodash.js#L1833
		Needed for SET methods in jquery.storageapi
		
		jquery.cookie.js ~~> jquery.cookie.path.js
		Cookie path forced to '/' : change on l.56
		-> make cookie available across the entire domain
		CHANGE : back to original jquery.cookie.js
		
		|_> jquery.everban.3.js
		put an option in REGISTER CONFIGURATION
		l.28 : $.cookie.defaults = { path: '/' };
		
		Change cookie ID 'armored_192_168_2_1' to 'EVB'

		OoOoOK ! 
		
		Caution : lots of debug stuff in everban.module
		!! Like $[cookie] set to ''
		
		Try/catch ?? How deep needed ? Tests with windowStorage
		Plugins will throw exception to jquery.everban.js
		
		Add swfstore.js and storage.swf. 
		From https://github.com/nfriedly/Javascript-Flash-Cookies
		Debug = True
		URL for storage.swf should be changed :
		https://www.bureau.emmene-moi.fr/drupal6/sites/all/modules/everban/storage.swf'
		https://192.168.2.1/drupal6/sites/all/modules/everban/storage.swf'
		PB callback and time for charging object
		Exception message :
		"SwfStore is not yet finished initializing. Pass a config.onready callback 
		"or wait until this.ready is true before trying to use a SwfStore instance.
		!! Modif swfstore.js !! l.270 & 288 to have this.log activated 
		-> reset again to comment : generate bug : event onready never fired !

		
v4		Between everban.4.js and jquery.everban.4.js : function register
		Create callback to let plugins have time loading or being disabled if failure.
		Encapsulate the get/set methods in that callback
		
		!! Change everban.module for calling v4 files
		
		BUG IE 8 : function indexOf unknown in jquery.everban.4.js
		Try to add a prototype fix : declare new function when unknown,
		but adds an object in our 'plugins' array (that function) : bring bug when reading array.
		Resolved by replacing '.indexOf()' by 'jQuery.inArray()'
		
		BUG IE8 : patch written for '$.isPlainObject()' is not working.
		Resolved ugly but functional : 'return false' ... always.
				
		BUG : everban algorithm stays in a loop if SWF error loading.
		OK : was because of wrong use of false url adress and was looping on.

		
v5		Add PNG caching : 'pngStorage'
		Adapt S.A.M.I.R.K code to our appli, png width is 11 (33 RGB bytes) and not 200 anymore
		
		jquery.everban.5.js - line 84
		Add regex test and check that peppers are length 32 and alphanumeric.
		
		jquery.everban.5.js - line 29
		Add 'done' function, counting callbacks from 'png' and 'swf' initialisations.
		Those can be time greedy operations, so we wait peacefully.
		When both of them initialisated succesfully or not, another callback is sent to main algo.


Module -> backup as OLD/everban.1.module
		
		What is global $cookie_domain ?
		Note that our cookie is now named 'EVB'.
		Making cookie : 'armored'.$cookie_domain still on !? ( function _everban_id() - line 630 )
		Modified.

		Add regex test for local found cookie : is alphanumeric.
		
		--Tests--
		
		Remark : Delete users don't delete in BD everban ...
		
		Link 'ban' is not working : no effect on status in DB
		Tried and many warnings :
		•	warning: array_fill(): Number of elements must be positive in /Volumes/SharedData/www/drupal6/includes/database.inc on line 253.
		•	warning: implode(): Invalid arguments passed in /Volumes/SharedData/www/drupal6/includes/database.inc on line 253.
		•	warning: array_keys() expects parameter 1 to be array, null given in /Volumes/SharedData/www/drupal6/modules/user/user.module on line 528.
		•	user warning: You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ')' at line 1 query: SELECT p.perm FROM role r INNER JOIN permission p ON p.rid = r.rid WHERE r.rid IN () in /Volumes/SharedData/www/drupal6/modules/user/user.module on line 528.
		
		PB considering unique pepper vs group peppers.
		Query PB line 215 ... ? 'uid_count>1'
		If pepper is unique for a user then it's not taken into account.
		
		-> Changed and back-up before Seb's changes in OLD/everban.2.module
		
DEV STATE SUMMARY
		
		From everban.5.js :
		
		var plugins = 			// Three first need cookie API. Cf https://github.com/carhartl/jquery-cookie
		[	'cookieStorage',	// Cookie + Storage API. Cf https://github.com/julien-maurel/jQuery-Storage-API
			'localStorage',		// Storage API - html5
			'sessionStorage', 	// Storage API - html5
			'windowStorage',	// window.name Caching (from S.K.)
			'swfStorage',	 	// Local Share Object - Flash storage
			'pngStorage'		// PNG generation with forced cache and html5 canvas pixel reading (from S.K.)
		];
		
		jquery.everban.5.js
		TODO : 'remove' function not really implemented
		

-------------------------------------------------

VIEWS INTEGRATION

		everban.module archived in OLD/everban.5.module
		
		hook_menu to write actions ?!
		
		