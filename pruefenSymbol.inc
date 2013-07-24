<?php
/***
 * Standardverhalten abpruefen + gegebenenfalls ausfuehren:
 ***/
if( isset($_REQUEST["update_x"]) or isset($_REQUEST["delete_x"]) )
  return; //Standardverhalten
if( !isset($_E['wZu']) )
include("forkZu.inc");
?>
