<?php

class everban_handler_field_ban_operation extends views_handler_field_numeric {

    function init( &$view, $options )  {
        parent::init($view, $options);
        $this->additional_fields['pepper'] = 'pepper';
        $this->additional_fields['status'] = 'status';
        //$this->additional_fields['status'] = 'status';
    }

/*
	function query() {		
		//OFF a cause du faux champs 'ban' qui n'en est pas un
	}
*/
	  function render( $values ) 
	  {
        //dpm($this);

		$status = $values->{$this->aliases['status']};
        $pepper = $values->{$this->aliases['pepper']};

		$action = !$status ? 'ban/' : 'unban/' ;
		$out = l( substr($action, 0, 3)=='ban' ? 'BAN' : 'unban', 'admin/user/everban/'.$action.$pepper );
		
		return ($out); // check_plain(...)
	  }
}
/*	// CUSTOMFIELD: PHP CODE

  if (!$data->everban_status) {
   echo "<a href='/drupal6/admin/user/everban/".$data->everban_pepper."'".">/!\\ BAN /!\\</a>";
}else{
   echo "<a href='/drupal6/admin/user/everban/unban/".$data->everban_pepper."'".">~ Unban ~</a>";
}
*/

/*		// TESTS

		if(DEBUG) dpm($values, $name = '$values in handler');
		$status = $this->definition['status_field'];
		$values->{$this->field_alias};
		$value = $values->{$this->field_alias};
		$status = $data->everban_status;
*/

?>
