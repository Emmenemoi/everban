<?php

class everban_handler_field_trap_operation extends views_handler_field_numeric {

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

		// trap IP
		if ($this->view->base_table == 'accesslog'){
		
			$ipalias = 'accesslog_hostname';
			$value = $values->{$ipalias} ;
			$action = !$status ? 'trap/ip/' : 'untrap/ip/' ;
			
		// trap UID
		} else {      // base_table == 'users'
		
			$uidalias = 'uid'; 
			$value = $values->{$uidalias};
			$action = !$status ? 'trap/uid/' : 'untrap/uid/' ;
		}

		$out = l( substr($action, 0, 4)=='trap' ? 'TRAP' : 'untrap', 'admin/user/everban/'.$action.$value);
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