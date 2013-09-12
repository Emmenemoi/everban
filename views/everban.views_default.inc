<?php

/**
* Implements hook_views_default_views().
*/
function everban_views_default_views() {

	 static $views;
	 if (isset($views)) { return $views; }
	 
	 // SEARCH FOR "*.EXPORT.INC" FILES
	 $files = file_scan_directory( drupal_get_path('module', 'everban') . '/views', '^.*\.export\.inc$' );
	 //dpm($files, $name='files.inc found : ');

	 // INCLUDE THEM HERE
	 foreach ($files as $filepath => $file) 
	 {
	   include $filepath;

	   if (isset($view)) 
	   { 
			$views[$view->name] = $view;
	   }
	 }
	 return $views;
}

?>
