<?php

class everban_handler_field_blacklist_operation extends views_handler_field_numeric {

/*	function init( &$view, &$options )  {
        parent::init($view, $options);
		//dpm($this, $name='this');	
    }*/
/*	function query() {
	}*/
	
	function render( $values ) 
	{
		//dpm($this, $name='this');	dpm($values,$name='values');
		$status = $values->{$this->field_alias}; // = $values->{everban_traps_status}

		// from accesslog
		if ($this->view->base_table == 'accesslog'){
		
			$ipalias = 'accesslog_hostname';
			$value = $values->{$ipalias} ;
			
		// trap UID
		} else {      // base_table == 'users'
		
			$ipalias = 'ip'; 
			$value = long2ip($values->{$ipalias});
		}
		
		$action = $status == null ? 'blacklist/ip/' : 'unblacklist/ip/' ;

		$out = l( substr($action, 0, 9)=='blacklist' ? 'BLACKLIST' : 'free', 'admin/user/everban/'.$action.$value);
		return ($out);
	}
}
?>

<?php
/* PHP CODE to put in PHP CUSTOM FIELD in EVERBAN VIEW

	// LINK : https://192.168.2.1/drupal6/admin/build/views/edit/user_ips#views-tab-attachment_1
	//print_r ($data);
	$viewName = 'user_ips';
	$display_id = 'attachment_1';
	$myArg = $data->uid;
	print_r ( views_embed_view($viewName, $display_id, $myArg) );
*/
?>