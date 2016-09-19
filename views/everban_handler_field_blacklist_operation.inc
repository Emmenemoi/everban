<?php

class everban_handler_field_blacklist_operation extends views_handler_field {

/*	function init( &$view, &$options )  {
        parent::init($view, $options);
		//dpm($this, $name='this');	
    }*/
/*	function query() {
	}*/
	

	function init( &$view, &$options )  {
        parent::init($view, $options);

	    if ( $options['action_type'] != 'view') {
	    	//dpm($this);
	      	$this->additional_fields[] = array('table' => $this->table, 'field' => 'class') ;
	      	$this->additional_fields[] = array('table' => $this->table, 'field' => 'ip') ;
	    }
	}

	function option_definition() {
		$options = parent::option_definition();

		$options['action_type'] = array('default' => 'simple');
		return $options;
	}

	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);

		$form['action_type'] = array(
		  '#type' => 'select',
		  '#title' => t('Action type'),
		  '#default_value' => $this->options['action_type'],
		  '#options' => array(
		    'simple' => t('Simple blacklist'),
		    'complete' => t('All possible choices'),
		    'range' => t('Display range'),
		    'view' => t('View whois')
		  ),
		);

	}

	function render( $values ) 
	{
		//dpm($this->query, $name='this');	dpm($values,$name='values');	dpm($this,$name='values');
		$status = $values->{$this->field_alias}; // = $values->{everban_traps_status}

		$netipalias = isset($this->query->fields[$this->table.'_ip']) ? $this->table.'_ip' : 'ip'; 
		// from accesslog
		if ($this->view->base_table == 'accesslog'){
		
			$ipalias = 'accesslog_hostname';
			$value = $values->{$ipalias} ;
			
		// trap UID
		} else {      // base_table == 'users'
			$value = long2ip($values->{$netipalias});
		}
		//dpm($ipalias);
		switch($this->options['action_type']) {
			case 'view': $out = l('whois', "https://www.ultratools.com/tools/ipWhoisLookupResult?ipAddress=$value", array('attributes'=>array('target'=>'_blank'))); break;
			case 'range': 
				$ip_count = 1 << (32 - $values->everban_net_bans_class) ;
				if ($ip_count==1) {
					$out = "$value"; 
				} else {
					$start = -1 << (32 - $values->everban_net_bans_class) & ip2long($value);
					$start_value = long2ip($start);
					$end = ($start + $ip_count - 1);
					$end_value= long2ip($end);
					$out = "{$start_value} - {$end_value}"; 
				}
				break;
			default:
				$action = $status == null ? 'blacklist/ip/' : 'unblacklist/ip/' ;
				$value = $status == null ? $value : long2ip($values->{$netipalias});
				$out = l( substr($action, 0, 9)=='blacklist' ? 'BLACKLIST' : 'free', 'admin/user/everban/'.$action.$value);
		}

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