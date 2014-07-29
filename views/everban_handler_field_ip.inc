<?php

class everban_handler_field_ip extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    return long2ip($value);
  }
}
