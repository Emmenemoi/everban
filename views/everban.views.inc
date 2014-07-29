<?php

module_load_include('inc', 'everban', 'views/everban_handler_join_ip');

/**
 * This file is used to tell the views module about the everban table.
 *
 
  EVERBAN DATABASE // from everban.install
  ----------------------------------------
  $schema['everban'] = array(
    'fields' => array(
		  'pepper' => array('type' => 'varchar', 'length' => '32', 'not null' => TRUE, 'default' => '', 'description' => 'An Peper id of strong cookie'),
		  'uid' => array('type' => 'int', 'unsigned' => TRUE, 'not null' => TRUE, 'description' => 'Identifier for a ban'),
		  'status' => array('type' => 'int', 'size'=>'tiny', 'unsigned' => TRUE, 'not null' => TRUE, 'description' => 'Ban status'),
    ),
    'primary key' => array('uid', 'pepper'),
    'indexes' => ...
    )
  );

  $schema['everban_traps'] = array(
	'fields' => array(
		  'trap' => array('type' => 'varchar', 'length' => '32', 'not null' => TRUE, 'default' => '', 'description' => 'Trap setup to auto add all peppers'),
		  'type' => array('type' => 'int', 'size'=>'tiny', 'unsigned' => TRUE, 'not null' => TRUE, 'description' => 'Trap type'),
		  'status' => array('type' => 'int', 'size'=>'tiny', 'unsigned' => TRUE, 'not null' => TRUE, 'description' => 'Ban status'),
	),
	'primary key' => array('trap', 'type'),
	'indexes' => ...
	)
  );
 
 */
////////////////////////////////////////////////////////////
//////////////////////// TABLE INFO ////////////////////////
////////////////////////////////////////////////////////////

function everban_views_data()  {
  // Basic table information.
  // ----------------------------------------------------------------
  // everban table
  //  New group within Views called 'Everban', will appear in the UI in the dropdown
  //  that allows you to narrow down which fields and filters are available.

  
	///////////////////////////
	////// BAN DATA   /////////
	///////////////////////////
  
  $data = array();
  $data['everban']['table']['group']  = t('Everban');

  // Advertise this table as a possible base table
  $data['everban']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Ban pepper list'),
    'help' => t('Stores users peppers.'),
    'weight' => 10,
  );
  // Advertise everban table joins the 'users' base table. 
  // Will be available when listing users and automatically make its fields appear.
  // We also show up for node (??) revisions.
 $data['everban']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  //// STATUS ///////////////////////////////////
  $data['everban']['status'] = array(
    'title' => t('Status'),
    'help' => t('Status of associated pepper'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //// PEPPER ////////////////////////////////////
  $data['everban']['pepper'] = array(
    'title' => t('Pepper'),
    'help' => t('Pepper'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
     'sort' => array(
      'handler' => 'views_handler_sort',
     ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
    


	///////////////////////////
	////// TRAP DATA  /////////
	///////////////////////////
	
  $data['everban_traps']['table']['group']  = t('Everban Trap');
  
  // Advertise everban_traps table joins the 'users' base table, nodes and accesslog
  $data['everban_traps']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'trap',
      'extra' => array( array( 'field'=>'type', 'value'=>EVB_TRAP_TYPE_UID , 'type'=>'numeric'))
    ),
    'node' => array(
      'left_field' => 'uid',
      'field' => 'trap',
      'extra' => array( array( 'field'=>'type', 'value'=>EVB_TRAP_TYPE_UID , 'type'=>'numeric'))
    ),
    'accesslog' => array(
      'left_field' => 'hostname',
      'field' => 'trap',
      'extra' => array( array( 'field'=>'type', 'value'=>EVB_TRAP_TYPE_IP , 'type'=>'numeric'))
    ),
  );  
  // STATUS OF TRAP
  $data['everban_traps']['status'] = array(
    'title' => t('Status of Trap'),
    'help' => t('Status of Trap'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
     ),
     'sort' => array(
      'handler' => 'views_handler_sort',
     ),
  );
  // NBLOG : aditional field showing IP AGREGATION COUNT
  $data['everban_traps']['nblog'] = array(
    'title' => t('Number of logs'),
    'help' => t('Number of logs'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
     'sort' => array(
      'handler' => 'views_handler_sort',
     ),
  );
  

    ///////////////////////////
  ////// NETS DATA  /////////
  ///////////////////////////
  $data['everban_net_bans']['table']['group']  = t('Everban net bans');
  
    // Advertise this table as a possible base table
  $data['everban_net_bans']['table']['base'] = array(
    'field' => 'ip',
    'title' => t('Everban network black/white lists'),
    'weight' => 10,
  );

  // Advertise everban_traps table joins the 'users' base table, nodes and accesslog
  $data['everban_net_bans']['table']['join'] = array(
    'accesslog' => array(
      'left_field' => 'hostname',
      'field' => 'ip',
      'handler' => 'views_join_everban_ip',
    ),
  );  
  // STATUS OF TRAP
  $data['everban_net_bans']['status'] = array(
    'title' => t('Status of ban'),
    'help' => t('Status of ban'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
     'sort' => array(
      'handler' => 'views_handler_sort',
     ),
  );
  // NBLOG : aditional field showing IP AGREGATION COUNT
  $data['everban_net_bans']['ip'] = array(
    'title' => t('IP'),
    'help' => t('IP of network'),
    'field' => array(
      'handler' => 'everban_handler_field_ip',
      'click sortable' => TRUE,
     ),
     'sort' => array(
      'handler' => 'views_handler_sort',
     ),
  );
    // NBLOG : aditional field showing IP AGREGATION COUNT
  $data['everban_net_bans']['class'] = array(
    'title' => t('Class'),
    'help' => t('Class of network'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
  );

  return $data;
}

////////////////////////////////////////////////////////////
//////////////////////// OPERATIONS ////////////////////////
////////////////////////////////////////////////////////////

function everban_views_data_alter(&$data) {

  ////////////// BAN OPERATION HANDLER //////////////////
  $data['everban']['ban'] = array(
    'real field' => 'status',
    'title' => t('Pepper Action'),
    'help' => t('Provide Pepper Ban/Unban Action Links'),
    'field' => array( //'label'...
      'handler' => 'everban_handler_field_ban_operation',     
	  'click sortable' => FALSE,
      //'status_field' => 'status',
    ),
  );
  ///////////// TRAP OPERATION HANDLER //////////////////
  $data['everban_traps']['TRAPING'] = array(
    'real field' => 'status',
    'title' => t('Trap Action'),
    'help' => t('Provide Trap/Untrap Action Links'),
    'field' => array( //'label'...
      'handler' => 'everban_handler_field_trap_operation',     
	  'click sortable' => FALSE,
    ),
  );

  ////////////// BLACKLIST OPERATION HANDLER //////////////////
  $data['everban_net_bans']['action'] = array(
    'real field' => 'status',
    'title' => t('Net Action'),
    'help' => t('Provide net blacklist action Links'),
    'field' => array( //'label'...
      'handler' => 'everban_handler_field_blacklist_operation',     
    'click sortable' => FALSE,
      //'status_field' => 'status',
    ),
  );

}

//////////////////    INCLUDES PATHS  ////////////////////////

function everban_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module','everban') . '/views',
    ),
    'handlers' => array(
      'everban_handler_field_ban_operation' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'everban_handler_field_trap_operation' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'everban_handler_field_blacklist_operation' => array(
        'parent' => 'views_handler_field',
      ),
      'everban_handler_field_ip' => array(
        'parent' => 'views_handler_field',
      ),
    )
  );
}



////////////////////////////////////////////////////////////
///////////////// USER_IPS QUERY : GROUP BY IP /////////////
////////////////////////////////////////////////////////////

// INITIAL QUERY TO ALTER (example with UID=1):
/*
 SELECT 
   accesslog.aid AS aid,
   accesslog.hostname AS accesslog_hostname,
   everban_traps.status AS everban_traps_status
 FROM accesslog accesslog 
 INNER JOIN users users_accesslog ON accesslog.uid = users_accesslog.uid
 LEFT JOIN everban_traps everban_traps ON accesslog.hostname = everban_traps.trap AND everban_traps.type = '1'
 WHERE users_accesslog.uid = 1 
*/
// RESULTING QUERY "GROUP BY IP" AND COUNT) :
/*
SELECT 
   accesslog.aid AS aid,
   COUNT(accesslog.hostname) AS everban_traps_nblog,
   accesslog.hostname AS accesslog_hostname,
   everban_traps.status AS everban_traps_status
 FROM accesslog accesslog 
 INNER JOIN users users_accesslog ON accesslog.uid = users_accesslog.uid
 LEFT JOIN everban_traps everban_traps ON accesslog.hostname = everban_traps.trap AND everban_traps.type = '1'
 WHERE users_accesslog.uid = 1 
 GROUP BY accesslog.hostname
*/

/* http://drupal.stackexchange.com/questions/12359/add-a-group-by-in-views

 See the resulting query in the preview when editing the view and make sure it is correct. 
 Field aliases in the code refer to "SELECT table.field1 as fieldalias1 ...", 
 it's easy to get them just by checking the query shown in the preview.
*/
function everban_views_query_alter(&$view, &$query) 
{
  if ($view->name == 'user_ips') { 						
    if ($view->current_display == 'attachment_1') { 	//dpm($query);

      // Tell the query constructor these fields must be used with the GROUP BY clause
      // $query->add_groupby('field1');
      $query->add_groupby('accesslog.hostname');


      // hack to make the query constructor just ignore these fields (not adding them to the GROUP BY clause. It's needed to let it continue without problems
      // $query->fields['fieldalias3']['aggregate'] = TRUE;
      $query->fields['aid']['aggregate'] = TRUE;
      $query->fields['everban_traps_status']['aggregate'] = TRUE;
      $query->fields['accesslog_hostname']['aggregate'] = TRUE;
      $query->fields['everban_traps_nblog']['aggregate'] = TRUE;
	  // ... all but the grouped and aggregated fieldaliases must have this.
	
      // Configure the fields that perform the aggregation (SUM, AVG, etc)
      // $query->fields['aggregatedfieldaliasA']['table'] = '';
      $query->fields['everban_traps_nblog']['table'] = '';
      // $query->fields['aggregatedfieldaliasA']['field'] = "SUM(fieldA)";
      $query->fields['everban_traps_nblog']['field'] = "COUNT(accesslog.hostname)";
    }
  }
}


?>
