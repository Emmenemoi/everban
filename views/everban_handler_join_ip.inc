<?php

class views_join_everban_ip extends views_join {
	function join($table, &$query) {
		$output = str_replace( "$table[alias].$this->field", "INET_NTOA($table[alias].$this->field)" ,parent::join($table, $query) );
		return $output;
	}
}