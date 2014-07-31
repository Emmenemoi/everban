<?php

class views_join_everban_ip extends views_join {
	function join($table, &$query) {
		//dpm($query);
		$accesslog = $query->table_queue['accesslog']['alias'];
		//$output = str_replace( "$table[alias].$this->field", "INET_NTOA($table[alias].$this->field)" ,parent::join($table, $query) );
		$output = parent::join($table, $query);
		$output = str_replace( "$table[alias].$this->field", "(-1 << 32 - class) & $table[alias].$this->field" , $output );
		$output = str_replace( "$accesslog.hostname", "(-1 << 32 - class) & INET_ATON($accesslog.hostname)" , $output );
		
		return $output;
	}
}